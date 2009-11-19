package etomica.lammpslib;

import etomica.action.WriteConfiguration;
import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtomPositioned;
import etomica.api.IAtomType;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
import etomica.api.IPotentialMaster;
import etomica.api.ISpecies;
import etomica.api.IVector;
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.Configuration;
import etomica.config.ConfigurationFile;
import etomica.config.ConfigurationLattice;
import etomica.dimer.CalcGradientDifferentiable;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.dimer.IntegratorDimerRT;
import etomica.dimer.MeterStructureFactor;
import etomica.dimer.SimDimerMEAMBlock;
import etomica.graphics.ColorSchemeByType;
import etomica.graphics.DisplayBox;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.lattice.BravaisLatticeCrystal;
import etomica.lattice.crystal.BasisBetaSnA5;
import etomica.lattice.crystal.PrimitiveTetragonal;
import etomica.listener.IntegratorListenerAction;
import etomica.nbr.list.PotentialMasterList;
import etomica.potential.PotentialMaster;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularPeriodic;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;
import etomica.units.Kelvin;
import etomica.util.RandomNumberGenerator;

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimDimerMEAMBlock extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "DimerMEAMadatomSn";
    public final PotentialMasterList potentialMaster;
    public final IPotentialMaster potentialMasterD;
    public IntegratorVelocityVerlet integratorMD;
    public IntegratorDimerRT integratorDimer;
    public IntegratorDimerMin integratorDimerMin;
    public IBox box;
    public IVectorMutable [] saddle, normal;
    public SpeciesSpheresMono fixed, saddle1, saddle2, saddle3, saddle4, movable;
    public PotentialMEAM potential;
    public ActivityIntegrate activityIntegrateMD, activityIntegrateDimer, activityIntegrateMin;
    public CalcGradientDifferentiable calcGradientDifferentiable;
    public CalcVibrationalModes calcVibrationalModes;
    public double [][] dForces;
    public int [] d, modeSigns;
    public double [] positions;
    public double [] lambdas, frequencies;
    public IVectorMutable adAtomPos;
    public IMoleculeList movableSet;
    public BravaisLatticeCrystal crystal;
    public long lammpsSim;
    //public Boolean saddleFine, calcModes, minSearch, normalDir;
    
    public SimDimerMEAMBlock() {
        super(Space3D.getInstance(), true);    	
        potentialMaster = new PotentialMasterList(this, space);
        potentialMasterD = new PotentialMaster();
        
        //lammpsSim = LammpsInterface.makeLammpsSim("/home/msellers/simulation/lammps-couple/in.block-3072");
        
      //SIMULATION BOX
        box = new Box(new BoundaryRectangularPeriodic(space), space);
        addBox(box);
     
      //SPECIES
        
        //Sn==
       
        fixed = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle1 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle2 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle3 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle4 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //potentialSpecies = new SpeciesSpheresMono(this, space, tinFixed);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        //getSpeciesManager().addSpecies(saddle1);
        //getSpeciesManager().addSpecies(saddle2);
        //getSpeciesManager().addSpecies(saddle3);
        //getSpeciesManager().addSpecies(saddle4);
        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(3.022); 
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle1.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle2.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle3.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle4.getLeafType()).setDiameter(3.022);
        box.setNMolecules(fixed, 1440);
        
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Sn);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Sn);
        //potential.setParameters(potentialSpecies.getLeafType(), ParameterSetMEAM.Sn);
        
        
        
        //Sn
        //beta-Sn box
        
        //The dimensions of the simulation box must be proportional to those of
        //the unit cell to prevent distortion of the lattice.  The values for the 
        //lattice parameters for tin's beta box (a = 5.8314 angstroms, c = 3.1815 
        //angstroms) are taken from the ASM Handbook. 
              
        double a = 5.921; 
        double c = 0.546*a;
        box.getBoundary().setDimensions(new Vector3D(a*6, a*6, c*10));
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
        crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());
		
                
        //Ag
        /**
        Silver silverFixed = new Silver("AgFix", Double.POSITIVE_INFINITY);
        fixed = new SpeciesSpheresMono(this, Silver.INSTANCE);
        movable = new SpeciesSpheresMono(this, Silver.INSTANCE);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        ((AtomTypeSphere)fixed.getLeafType()).setDiameter(2.8895); 
        ((AtomTypeSphere)movable.getLeafType()).setDiameter(2.8895);
        potential = new PotentialMEAM(space);
        potential.setParameters(agFix, ParameterSetMEAM.Ag);
        potential.setParameters(ag, ParameterSetMEAM.Ag);
        potential.setParameters(agAdatom, ParameterSetMEAM.Ag);
        potential.setParameters(movable, Paramete712388980384691rSetMEAM.Ag);
        
        double a = 4.0863;
        PrimitiveCubic primitive = new PrimitiveCubic(space, a);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        
        */
    
        
        //Cu
        /**
        //Copper copperFixed = new Copper("CuFix", Double.POSITIVE_INFINITY);
        fixed = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        ((AtomTypeSphere)fixed.getLeafType()).setDiameter(2.5561); 
        ((AtomTypeSphere)movable.getLeafType()).setDiameter(2.5561);
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Cu);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Cu);
        box.setNMolecules(fixed, 256);
        double a = 3.535;//3.6148;
        box.getBoundary().setDimensions(new Vector3D(a*4, a*4, a*4));
        PrimitiveCubic primitive = new PrimitiveCubic(space, a);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        **/
        
        Configuration config = new ConfigurationLattice(crystal, space);
        config.initializeCoordinates(box);
        
        /*
        this.potentialMaster.addPotential(potential, new IAtomTypeLeaf[]{movable.getLeafType(), potentialSpecies.getLeafType()});
        potentialMaster.setRange(potential.getRange()*1.1);
        CriterionSimple criteria = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        potentialMaster.setCriterion(potential, new CriterionTypesCombination(criteria, new IAtomTypeLeaf[] {movable.getLeafType(), potentialSpecies.getLeafType()}));
        */
        
        this.potentialMasterD.addPotential(potential, new IAtomType[]{movable.getLeafType(), fixed.getLeafType()});
        //potentialMasterD.setRange(potential.getRange()*1.1);
        //CriterionSimple criteria2 = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        //potentialMasterD.setCriterion(potential, new CriterionTypesCombination(criteria2, new IAtomTypeLeaf[] {movable.getLeafType()}));
   
        /*712388980384691
        //ADATOM CREATION AND PLACEMENT
        // Sn
        setMovableAtoms(50.0, new Vector3D(9.0,-0.005,8.75));
        IMolecule iMolecule = movable.makeMolecule();
        box.addMolecule(iMolecule);
        adAtomPos = ((IAtomPositioned)iMolecule.getChildList().getAtom(0)).getPosition();
        //adAtomPos = getSpace().makeVector();
        adAtomPos.setX(0,9.0);
        adAtomPos.setX(1, -0.005);
        adAtomPos.setX(2, 8.75);
        */   
       
        /**
        //Ag
        IAtom iAtom = agAdatom.getMoleculeFactory().makeAtom();
        box.getAgent(agAdatom).addChildAtom(iASimulationtom);
        ((IAtomPositioned)iAtom).getPosition().setX(0, 7.5);
        ((IAtomPositioned)iAtom).getPosition().setX(1, 0.9477016722828758);
        ((IAtomPositioned)iAtom).getPosition().setX(2, 1.0709520701043456);
        */
        /**
        //Cu
        IAtom iAtom = cuAdatom.getMoleculeFactory().makeAtom();
        box.getAgent(cuAdatom).addChildAtom(iAtom);
        ((IAtomPositioned)iAtom).getPosition().setX(0, 6.0);
        ((IAtomPositioned)iAtom).getPosition().setX(1, 0.9477016722828758);
        ((IAtomPositioned)iAtom).getPosition().setX(2, 1.0709520701043456);
        */

    }
    
    public void setMovableAtoms(double distance, IVectorMutable center){
        //distance = distance*distance;
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            if(loopSet.getMolecule(i).getType()==movable){
                continue;
            }
            rij.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            rij.ME(center);
            box.getBoundary().nearestImage(rij);
          
            movableList.add(loopSet.getMolecule(i));
            
        }
        for (int i=0; i<movableList.getMoleculeCount(); i++){
            IMolecule newMolecule = movable.makeMolecule();
            box.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)movableList.getMolecule(i).getChildList().getAtom(0)).getPosition());
            box.removeMolecule((IMolecule)movableList.getMolecule(i));
        }
        movableSet = box.getMoleculeList(movable);
    }
    
    public void refreshSpecies(){
        IMoleculeList loopSet = box.getMoleculeList(movable);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            IMolecule newMolecule = getSpeciesManager().getSpecies(0).makeMolecule();
            box.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
        }
        box.setNMolecules(movable, 0);
    }
    
    public void setPotentialListAtoms(){
        MoleculeArrayList neighborList = new MoleculeArrayList();
        MoleculeArrayList fixedList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        IMoleculeList movableSet = box.getMoleculeList(movable);
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            if(loopSet.getMolecule(i).getType()==movable){
                continue;
            }
            if(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition().x(0) < -4.0){continue;}
            boolean fixedFlag = true;
            for(int j=0; j<movableSet.getMoleculeCount(); j++){
                IVectorMutable dist = space.makeVector();
                dist.Ev1Mv2(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition(),((IAtomPositioned)movableSet.getMolecule(j).getChildList().getAtom(0)).getPosition());
                box.getBoundary().nearestImage(dist);
                if(Math.sqrt(dist.squared())<8.0){
                    neighborList.add(loopSet.getMolecule(i));
                    fixedFlag = false;
                    break;
                }               
            
            }
            if(fixedFlag){
                fixedList.add(loopSet.getMolecule(i));
            }
        }
        for (int i=0; i<neighborList.getMoleculeCount(); i++){
            IMolecule newMolecule = movable.makeMolecule();
            box.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)neighborList.getMolecule(i).getChildList().getAtom(0)).getPosition());
            box.removeMolecule(neighborList.getMolecule(i));
         }
        for (int i=0; i<fixedList.getMoleculeCount(); i++){
            IMolecule newMolecule = fixed.makeMolecule();
            box.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)fixedList.getMolecule(i).getChildList().getAtom(0)).getPosition());
            box.removeMolecule(fixedList.getMolecule(i));
         }
        
    }
    
    //Must be run after setMovableAtoms
    public void removeAtoms(double distance, IVectorMutable center){
        distance = distance*distance;
        IVectorMutable rij = space.makeVector();
        
        IMoleculeList loopSet = box.getMoleculeList(movable);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            rij.Ev1Mv2(center,((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            box.getBoundary().nearestImage(rij);
            if(rij.squared() < distance){
               box.removeMolecule((IMolecule)loopSet.getMolecule(i));
               System.out.println("Atom removed.");
            } 
        }   
    }
    
    public void initializeConfiguration(String fileName){
        ConfigurationFile config = new ConfigurationFile(fileName);
        config.initializeCoordinates(box);
    }
    
    public void randomizePositions(){
        IVectorMutable workVector = space.makeVector();
        IMoleculeList loopSet3 = box.getMoleculeList(movable);
        IVectorMutable [] currentPos = new IVectorMutable [loopSet3.getMoleculeCount()];
        double offset = 0;
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
            currentPos[i] = (((IAtomPositioned)loopSet3.getMolecule(i).getChildList().getAtom(0)).getPosition());
            for(int j=0; j<3; j++){
                offset = random.nextGaussian()/10.0;
                if(Math.abs(offset)>0.2){
                    if(offset<0.0){
                        offset = -0.2;
                        workVector.setX(j,offset);
                        continue;
                    }
                    offset=0.2;
                }
                workVector.setX(j,offset);
            }
            currentPos[i].PE(workVector);
        }
    }
    
    public void generateConfigs(String fileName, double percentd){       
        
        RandomNumberGenerator random = new RandomNumberGenerator();
        IVectorMutable workVector = space.makeVector();
        IVectorMutable [] currentPos = new IVectorMutable [movableSet.getMoleculeCount()];
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
            currentPos[i].E(((IAtomPositioned)movableSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
        }
        
        //Create multiple configurations
        for(int m=0; m<50; m++){
            WriteConfiguration genConfig = new WriteConfiguration(space);
            genConfig.setBox(box);
            genConfig.setConfName(fileName+"_config_"+m);
            //Displaces atom's by at most +/-0.03 in each coordinate
            for(int i=0; i<movableSet.getMoleculeCount(); i++){
                IVectorMutable atomPosition = ((IAtomPositioned)movableSet.getMolecule(i).getChildList().getAtom(0)).getPosition();
                for(int j=0; j<3; j++){
                    workVector.setX(j,percentd*random.nextGaussian());
                }
                atomPosition.Ev1Pv2(currentPos[i],workVector);
            }
            genConfig.actionPerformed();            
        }
    }
        
    public void enableMolecularDynamics(long maxSteps){
        integratorMD = new IntegratorVelocityVerlet(this, potentialMasterD, space);
        integratorMD.setTimeStep(0.001);
        integratorMD.setTemperature(Kelvin.UNIT.toSim(100));
        integratorMD.setThermostatInterval(100);
        integratorMD.setIsothermal(true);
        integratorMD.setBox(box);
       // integratorMD.addNonintervalListener(potentialMaster.getNeighborManager(box));
       // integratorMD.addIntervalAction(potentialMaster.getNeighborManager(box));  
        activityIntegrateMD = new ActivityIntegrate(integratorMD);
        getController().addAction(activityIntegrateMD);
        activityIntegrateMD.setMaxSteps(maxSteps);
    }
    
    public void enableDimerSearch(String fileName, long maxSteps, boolean orthoSearch, boolean fine){
        
        integratorDimer = new IntegratorDimerRT(this, lammpsSim, potentialMasterD, new ISpecies[]{movable}, space);
        integratorDimer.setBox(box);
        integratorDimer.setRotNum(5);
        integratorDimer.setOrtho(orthoSearch, false);
        if(fine){
            ConfigurationFile configFile = new ConfigurationFile(fileName+"_saddle");
            configFile.initializeCoordinates(box);
            
            integratorDimer.setFileName(fileName+"_fine");
            integratorDimer.deltaR = 0.0005;
            integratorDimer.dXl = 10E-5;       
            integratorDimer.deltaXmax = 0.005;
            integratorDimer.dFsq = 0.0001*0.0001;
            integratorDimer.dFrot = 0.01;
        }
        integratorDimer.setFileName(fileName); 
        //integratorDimer.addNonintervalListener(potentialMasterD.getNeighborManager(box));
       // integratorDimer.addIntervalAction(potentialMasterD.getNeighborManager(box));  
        activityIntegrateDimer = new ActivityIntegrate(integratorDimer);
        integratorDimer.setActivityIntegrate(activityIntegrateDimer);
        getController().addAction(activityIntegrateDimer);
        activityIntegrateDimer.setMaxSteps(maxSteps);
    }
        
    public void enableMinimumSearch(String fileName, boolean normalDir){
        
        integratorDimerMin = new IntegratorDimerMin(this, lammpsSim, potentialMasterD, new ISpecies[]{movable}, space);
        integratorDimerMin.setBox(box);
        integratorDimerMin.setFileName(fileName);
        integratorDimerMin.setDirection(normalDir);
        //integratorDimerMin.addNonintervalListener(potentialMasterD.getNeighborManager(box));
        //integratorDimerMin.addIntervalAction(potentialMasterD.getNeighborManager(box));  
        activityIntegrateMin = new ActivityIntegrate(integratorDimerMin);
        integratorDimerMin.setActivityIntegrate(activityIntegrateMin);
        getController().addAction(activityIntegrateMin);
    }
    
    public static void main(String[] args){
       
        final SimDimerMEAMBlock sim = new SimDimerMEAMBlock();
               
        //sim.initializeConfiguration("/home/msellers/simulation/lammps-couple/block-3071-min");
        System.out.println(sim.box.getBoundary().getDimensions());
        
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 0.0);
        vect.setX(1, 0.0);
        vect.setX(2, 0.0);
        
        
        //sim.setMovableAtoms(500.0, vect);   
        
        //System.out.println(sim.movableSet.getMoleculeCount());
        
	    IVectorMutable workVector = sim.getSpace().makeVector();
	    //for(int i=0; i<loopSet.getMoleculeCount(); i++){
	   //     workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
	  //      LammpsInterface.setAtomPosition(sim.lammpsSim, i, workVector.x(0), workVector.x(1), workVector.x(2));
	   // }
	   // LammpsInterface.doLammpsStep(sim.lammpsSim, 1);
	   // double e0 = LammpsInterface.getEnergy(sim.lammpsSim);
	  //  System.out.println(e0);

	   // CalcVibrationalModes vib = new CalcVibrationalModes(sim.lammpsSim);
       // vib.setup(sim.box, sim.potentialMaster, sim.box.getMoleculeList(sim.movable), sim.space);
      //  vib.actionPerformed();
      //  System.out.println(vib.getHarmonicEntropy(300.0));
        
        //sim.enableMolecularDynamics(1000);
        sim.enableDimerSearch("snblock2", 4000, false, false);             
        //sim.enableMinimumSearch("snblock2", false);
        Vector3D move2 = new Vector3D(0.0,2.5,1.5);
	    move2.E(sim.box.getBoundary().getDimensions());
	    move2.setX(0,74.0);
	    move2.setX(1,74.0);
	    move2.setX(2,66.0);
	    //move2.setX(1,75.0);
	    sim.box.getBoundary().setDimensions(move2);
        
	    //	STRUCTURE FACTOR CALCULATION
        MeterStructureFactor meterS = new MeterStructureFactor(sim.getSpace(), sim.crystal, sim.box);
	    IMolecule molecule;
	    
	    System.out.println(sim.box.getMoleculeList().getMoleculeCount());
	    sim.refreshSpecies();
	    sim.initializeConfiguration("/home/msellers/simulation/block/block-400-s02");
        IVectorMutable[] waveVec;
        waveVec = sim.getSpace().makeVectorArray(3);
        
        waveVec[0].setX(0,4.0*2.0*Math.PI/5.921);
        waveVec[1].setX(1,4.0*2.0*Math.PI/5.921);
        waveVec[2].setX(2,4.0*2.0*Math.PI/3.23287);
                
        IMoleculeList boxList = sim.box.getMoleculeList();
        IVectorMutable rij1 = sim.getSpace().makeVector();
        double zvec=35.40;
        for(int z=0; z<40.0; z++){ 	
        	MoleculeArrayList structArray = new MoleculeArrayList();
	        for (int i=0; i<boxList.getMoleculeCount(); i++){
	        	rij1.E(((IAtomPositioned)boxList.getMolecule(i).getChildList().getAtom(0)).getPosition());
		        	if(Math.abs(rij1.x(1)-zvec)<=(5.921/4.0)){//Math.abs(rij.x(0)) < 0.5 && Math.abs(rij.x(1)) < distance && Math.abs(rij.x(2)) < distance){
			               structArray.add(boxList.getMolecule(i));  
			               //if(zvec<80.0)     System.out.println(rij1.x(1));
		            }
	        }
	        meterS.reset();
	        meterS.setWaveVec(waveVec);
	        meterS.setAtoms(structArray);
	        meterS.actionPerformed();
	        System.out.println(meterS.getDataAsArray()[0]);
	        //System.out.println(zvec+"   "+meterS.getDataAsArray()[0]);
	        sim.refreshSpecies();
	        zvec=zvec-(5.921/2.0);
        }
	    
	    System.exit(1);
       
        SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, 1, sim.space, sim.getController());
        simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));        
        sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
        //simGraphic.add(plotPE);
    	ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());
    	
    	colorScheme.setColor(sim.fixed.getLeafType(),java.awt.Color.gray);
        colorScheme.setColor(sim.movable.getLeafType(),java.awt.Color.white);
     //   colorScheme.setColor(sim.saddle1.getLeafType(),java.awt.Color.red);
     //   colorScheme.setColor(sim.saddle2.getLeafType(),java.awt.Color.green);
     //   colorScheme.setColor(sim.saddle3.getLeafType(),java.awt.Color.blue);
       // colorScheme.setColor(sim.potentialSpecies.getLeafType(),java.awt.Color.PINK);

    	simGraphic.makeAndDisplayFrame(APP_NAME);
    	
    }
    static {
       System.loadLibrary("LAMMPS");
//        System.loadLibrary("lmp_thomas");
    }
}
