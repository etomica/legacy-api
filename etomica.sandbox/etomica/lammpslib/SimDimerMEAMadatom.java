package etomica.lammpslib;

import etomica.action.WriteConfiguration;
import etomica.action.activity.ActivityIntegrate;
<<<<<<< SimDimerMEAMadatom.java
import etomica.api.IAtomPositioned;
import etomica.api.IAtomType;
=======
import etomica.api.IAtomType;
>>>>>>> 1.67
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
<<<<<<< SimDimerMEAMadatom.java
import etomica.api.IMoleculeList;
import etomica.api.IPotentialMaster;
=======
import etomica.api.IMoleculeList;
>>>>>>> 1.67
import etomica.api.ISpecies;
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.Configuration;
import etomica.config.ConfigurationFile;
import etomica.config.ConfigurationLattice;
<<<<<<< SimDimerMEAMadatom.java
=======
import etomica.data.AccumulatorAverageCollapsing;
import etomica.data.AccumulatorHistory;
import etomica.data.DataPump;
import etomica.data.AccumulatorAverage.StatType;
import etomica.data.meter.MeterPotentialEnergy;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.dimer.IntegratorDimerRT;
import etomica.dimer.SimDimerMEAMadatom;
>>>>>>> 1.67
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
import etomica.space.BoundaryRectangularSlit;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;
import etomica.units.Kelvin;
<<<<<<< SimDimerMEAMadatom.java
import etomica.util.RandomNumberGenerator;
=======
import etomica.util.HistoryCollapsingAverage;
import etomica.util.numerical.CalcGradientDifferentiable;
>>>>>>> 1.67

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimDimerMEAMadatom extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "DimerMEAMadatomSn";
    public final PotentialMasterList potentialMaster;
    public final IPotentialMaster potentialMasterD;
    public IntegratorVelocityVerlet integratorMD;
    public IntegratorDimerRT integratorDimer;
    public IntegratorDimerMin integratorDimerMin;
    public IBox box;
    public IVectorMutable [] saddle, normal;
    public SpeciesSpheresMono fixed, dimer, saddle2, saddle3, saddle4, movable;
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
    public long lammpsSim;
    //public Boolean saddleFine, calcModes, minSearch, normalDir;
    
    public SimDimerMEAMadatom() {  	
    	
        super(Space3D.getInstance(), true);   
        //setRandom(new RandomNumberGenerator(25));
        potentialMaster = new PotentialMasterList(this, space);
        potentialMasterD = new PotentialMaster();
        
        lammpsSim = LammpsInterface.makeLammpsSim("/home/msellers/simulation/lammps-couple/in.sn");
        
      //SIMULATION BOX
        box = new Box(new BoundaryRectangularSlit(0, 5, space), space);
        addBox(box);
     
      //SPECIES
        
        //Sn==
       
        fixed = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        dimer = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle1 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle2 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle3 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //saddle4 = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        //potentialSpecies = new SpeciesSpheresMono(this, space, tinFixed);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        getSpeciesManager().addSpecies(dimer);
        
        //getSpeciesManager().addSpecies(saddle1);
        //getSpeciesManager().addSpecies(saddle2);
        //getSpeciesManager().addSpecies(saddle3);
        //getSpeciesManager().addSpecies(saddle4);

        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(3.022); 
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(3.022);
        ((IAtomTypeSphere)dimer.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle1.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle2.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle3.getLeafType()).setDiameter(3.022);
        //((IAtomTypeSphere)saddle4.getLeafType()).setDiameter(3.022);
        box.setNMolecules(fixed, 512);
        
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Sn);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Sn);
        //potential.setParameters(potentialSpecies.getLeafType(), ParameterSetMEAM.Sn);
        
        //Sn
        //beta-Sn box

        //cmin = 0.8
        //rcut = 3.5
        // a=5.797  a/c=0.5459
        
        double a = 5.9245;
        double c = a*0.54599;
        box.getBoundary().setDimensions(new Vector3D(a*4, a*4, c*8));

        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());
                
        Configuration config = new ConfigurationLattice(crystal, space);
        config.initializeCoordinates(box);

        this.potentialMasterD.addPotential(potential, new IAtomType[]{movable.getLeafType(), fixed.getLeafType()});
        //potentialMasterD.setRange(potential.getRange()*1.1);
        //CriterionSimple criteria2 = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        //potentialMasterD.setCriterion(potential, new CriterionTypesCombination(criteria2, new IAtomTypeLeaf[] {movable.getLeafType()}));
           
        //ADATOM CREATION AND PLACEMENT
        // Sn
        //initializeConfiguration("surf252-min");       
        /**
        IMolecule iMolecule = movable.makeMolecule();
        box.addMolecule(iMolecule);
        adAtomPos = iMolecule.getChildList().getAtom(0).getPosition();
        //adAtomPos = getSpace().makeVector();
        adAtomPos.setX(0, 13.0);
        adAtomPos.setX(1, -3.17228);
        adAtomPos.setX(2, 3.75);
        IVectorMutable newBoxLength = space.makeVector();
        newBoxLength.E(box.getBoundary().getDimensions());
        newBoxLength.setX(0, 35);
        box.getBoundary().setDimensions(newBoxLength);
        */
        //initializeConfiguration("surf-217-min");
        adAtomPos.setX(0, 9.8);
        adAtomPos.setX(1, 0.2);
        adAtomPos.setX(2, -1.0);
        IVectorMutable newBoxLength = space.makeVector();
        newBoxLength.E(box.getBoundary().getBoxSize());
        newBoxLength.setX(0, 2.0*adAtomPos.getX(0)+2.0);
        box.getBoundary().setBoxSize(newBoxLength);

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
            
            if(rij.x(0) > -4.0){
                rij.ME(center);
                box.getBoundary().nearestImage(rij);
                
                if(rij.squared() < distance){   
                    movableList.add(loopSet.getMolecule(i));
                }
            }
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
               box.removeMolecule(loopSet.getMolecule(i));
            } 
        }   
    }
    public void initializeConfiguration(String fileName){
        ConfigurationFile config = new ConfigurationFile(fileName);
        config.initializeCoordinates(box);
    }
    public void randomizePositions(double percentScale){
    	IVectorMutable workVector = space.makeVector();
        IMoleculeList loopSet3 = box.getMoleculeList(movable);
        IVectorMutable [] currentPos = new IVectorMutable [loopSet3.getMoleculeCount()];
        double offset = 0;
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
            currentPos[i] = (((IAtomPositioned)loopSet3.getMolecule(i).getChildList().getAtom(0)).getPosition());
            for(int j=0; j<3; j++){
                offset = random.nextGaussian()/percentScale;
                if(Math.abs(offset)>0.4){
                    if(offset<0.0){
                        offset = -0.4;
                        workVector.setX(j,offset);
                        continue;
                    }
                    offset=0.4;
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
        integratorDimer.setRotNum(3);
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
        
        final SimDimerMEAMadatom sim = new SimDimerMEAMadatom();
        /*
        IMoleculeList loopSet = sim.box.getMoleculeList();
        IVectorMutable workVector = sim.getSpace().makeVector();
        workVector.setX(0,1.1);
        workVector.setX(1,1.1);
        workVector.setX(2,1.1);
        ((IAtomPositioned)loopSet.getMolecule(1).getChildList().getAtom(0)).getPosition().E(workVector);
        for(int j=0; j<500;j++){
	        	workVector.E(((IAtomPositioned)loopSet.getMolecule(1).getChildList().getAtom(0)).getPosition());
		        LammpsInterface.setAtomPosition(sim.lammpsSim,1, workVector.x(0), workVector.x(1), workVector.x(2));
		        LammpsInterface.doLammpsStep(sim.lammpsSim, 1);
		        System.out.println(Math.sqrt(workVector.squared())+"    "+LammpsInterface.getEnergy(sim.lammpsSim));
		        ((IAtomPositioned)loopSet.getMolecule(1).getChildList().getAtom(0)).getPosition().PE(0.01);
		    
        }
        */
        
        /*
        //saddle 110
        IMolecule iMolecule1 = sim.saddle1.makeMolecule();
        sim.box.addMolecule(iMolecule1);
        ((IAtomPositioned)iMolecule1.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.115612850674847, -0.004029456051517499, 1.57211668896446}));
       
        IMolecule iMolecule2 = sim.saddle1.makeMolecule();
        sim.box.addMolecule(iMolecule2);
        ((IAtomPositioned)iMolecule2.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.035811110102202, -0.04542244764527403, 3.140011238403323}));
        
        
        //saddle117
        IMolecule iMolecule7 = sim.saddle2.makeMolecule();
        sim.box.addMolecule(iMolecule7);
        ((IAtomPositioned)iMolecule7.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.021509225254873, -2.9922254459497086, -0.023322311991961442}));
       
        IMolecule iMolecule8 = sim.saddle2.makeMolecule();
        sim.box.addMolecule(iMolecule8);
        ((IAtomPositioned)iMolecule8.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.130870978666138, -1.5069422372830061, -0.44635318821938696}));
        
        //saddle127 - minimum
        IMolecule iMolecule10 = sim.saddle3.makeMolecule();
        sim.box.addMolecule(iMolecule10);
        ((IAtomPositioned)iMolecule10.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.131045997368222, 1.4994154464322627, 0.3765192352776605}));
       
        IMolecule iMolecule12 = sim.saddle3.makeMolecule();
        sim.box.addMolecule(iMolecule12);
        ((IAtomPositioned)iMolecule12.getChildList().getAtom(0)).getPosition().E(sim.space.makeVector(new double[] {10.018087586000238, 2.9847989858898423, -0.02001194806451778}));
        */
        //String fileName = "test2";
        //sim.initializeConfiguration("searchStart");
        sim.refreshSpecies();

        IVectorMutable[] adatomList = new IVectorMutable[sim.box.getMoleculeList().getMoleculeCount()];
        IVectorMutable vect = sim.getSpace().makeVector();
        
        sim.setMovableAtoms(40.0, new Vector3D(13.5, -3.17, 3.75));
        //sim.removeAtoms(2.0, new Vector3D(10.5, -3.17, 3.75));
        sim.randomizePositions(1.0);
        sim.setMovableAtoms(150.0, new Vector3D(13.5, -3.17, 3.75));
        
        for(int i=0; i<sim.box.getMoleculeList().getMoleculeCount(); i++){
            adatomList[i] = sim.getSpace().makeVector();
            vect.E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(vect.x(0)>7.6){
                adatomList[i].E(vect);
                //sim.setMovableAtoms(400.0, vect);
            }
        }

        //sim.randomizePositions();
        /*
        IMoleculeList loopSet = sim.box.getMoleculeList();
	    IVectorMutable workVector = sim.getSpace().makeVector();
	    for(int i=0; i<loopSet.getMoleculeCount(); i++){
	        workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
	        LammpsInterface.setAtomPosition(sim.lammpsSim, i, workVector.x(0), workVector.x(1), workVector.x(2));
	    }
	    LammpsInterface.doLammpsStep(sim.lammpsSim, 1);
	    double e0 = LammpsInterface.getEnergy(sim.lammpsSim);
	    System.out.println(e0);
	    IVectorMutable vect = sim.getSpace().makeVector();
        MoleculeArrayList vibList = new MoleculeArrayList();
    	for(int i=0; i<sim.box.getMoleculeList().getMoleculeCount(); i++){
            vect.E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(vect.x(0)>3.0){
                vibList.add(sim.box.getMoleculeList().getMolecule(i));
            }
        }
    	*/
  
	    //CalcVibrationalModes vib = new CalcVibrationalModes(sim.lammpsSim);
        //vib.setup(sim.box, sim.potentialMaster, sim.box.getMoleculeList(sim.movable), sim.space);
       // vib.actionPerformed();
	   // System.out.println(vib.getProductOfFrequencies());
	    
	    /*
	    double rate = Math.exp(747.7741-vib.getProductOfFrequencies())/((Math.sqrt(118)*0.000000000001));
	    System.out.println(rate);
	    double beta = 1.0/300*1.3806503E-023;
	    System.out.println(beta);
	    double D = Math.exp(-0.11386*beta)*3E-10*3E-10 / 4.0;
	    System.out.println(D);
	    D = D * rate;
	    System.out.println(D);
	    */
	    //sim.initializeConfiguration("/home/msellers/simulation/surface/513-disp1/s_01_saddle");
	    //sim.randomizePositions();
	    //sim.enableMolecularDynamics(1000);
        //sim.enableDimerSearch("/home/msellers/simulation/surface/513-disp50/s_51_A_minimum_A_minimum", 8000, false, false);             
        //sim.enableMinimumSearch("/home/msellers/simulation/surface/513-disp1/s_01", true);

        SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, 1, sim.space, sim.getController());
        simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));        

        //sim.integratorMD.addIntervalAction(simGraphic.getPaintAction(sim.box));
        sim.integratorDimerMin.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));

    	ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());
    	colorScheme.setColor(sim.fixed.getLeafType(),java.awt.Color.gray);
        colorScheme.setColor(sim.movable.getLeafType(),java.awt.Color.red);
        
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
