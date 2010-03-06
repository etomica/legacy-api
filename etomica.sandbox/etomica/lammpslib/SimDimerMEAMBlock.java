package etomica.lammpslib;

import etomica.action.WriteConfiguration;
import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
import etomica.api.IPotentialMaster;
import etomica.api.ISpecies;
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.Configuration;
import etomica.config.ConfigurationFile;
import etomica.config.ConfigurationLattice;
import etomica.graphics.ColorSchemeByType;
import etomica.graphics.DisplayBox;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.lattice.BravaisLatticeCrystal;
import etomica.lattice.crystal.PrimitiveMonoclinic;
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
    public BravaisLatticeCrystal crystalCu, crystalSn;
    public long lammpsSim;
    //public Boolean saddleFine, calcModes, minSearch, normalDir;
    
    public SimDimerMEAMBlock() {
        super(Space3D.getInstance());    	
        potentialMaster = new PotentialMasterList(this, space);
        potentialMasterD = new PotentialMaster();
        
        //lammpsSim = LammpsInterface.makeLammpsSim("/home/msellers/simulation/lammps-couple/in.block-3072");
        
      //SIMULATION BOX
        box = new Box(new BoundaryRectangularPeriodic(space), space);
        addBox(box);
     
      //SPECIES
        
        //Sn==
       
        fixed = new SpeciesSpheresMono(space, Tin.INSTANCE);
        movable = new SpeciesSpheresMono(space, Tin.INSTANCE);

        fixed.setIsDynamic(true);
        movable.setIsDynamic(true);
        addSpecies(fixed);
        addSpecies(movable);
        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(3.044); 
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(3.044);
        
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Sn);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Sn);

        box.setNMolecules(movable,200);
        
        //Sn
        //beta-Sn box
        
        //The dimensions of the simulation box must be proportional to those of
        //the unit cell to prevent distortion of the lattice.  The values for the 
        //lattice parameters for tin's beta box (a = 5.8314 angstroms, c = 3.1815 
        //angstroms) are taken from the ASM Handbook. 
        /*     
        double a = 5.921; 
        double c = 0.546*a;
        box.getBoundary().setBoxSize(new Vector3D(a*6, a*6, c*10));
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
        crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());
		*/
        
        double a = 11.022;
        double b = 7.282;
        double c = 9.827;
        double beta = 98.84*Math.PI/180.0;
        
        box.getBoundary().setBoxSize(new Vector3D(a*4, b*4, c*4));
        
        PrimitiveMonoclinic primitive = new PrimitiveMonoclinic(space, a, b, c, beta);
        crystalCu = new BravaisLatticeCrystal(primitive, new BasisCu6IMC());
        crystalSn = new BravaisLatticeCrystal(primitive, new BasisSn5IMC());
        
        Configuration configCu = new ConfigurationLattice(crystalCu, space);
        configCu.initializeCoordinates(box);
        Configuration configSn = new ConfigurationLattice(crystalSn, space);
        configSn.initializeCoordinates(box);
        
        /*
        this.potentialMaster.addPotential(potential, new IAtomTypeLeaf[]{movable.getLeafType(), potentialSpecies.getLeafType()});
        potentialMaster.setRange(potential.getRange()*1.1);
        CriterionSimple criteria = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        potentialMaster.setCriterion(potential, new CriterionTypesCombination(criteria, new IAtomTypeLeaf[] {movable.getLeafType(), potentialSpecies.getLeafType()}));
        */
    }
    public void setMovableAtomsSphere(double distance, IVectorMutable center){
        distance = distance*distance;
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
        	rij.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            rij.Ev1Mv2(center, rij);
            box.getBoundary().nearestImage(rij);
            if(rij.squared()<distance){//Math.abs(rij.x(0)) < 0.5 && Math.abs(rij.x(1)) < distance && Math.abs(rij.x(2)) < distance){
               movableList.add(loopSet.getMolecule(i));
            } 
        }
        for (int i=0; i<movableList.getMoleculeCount(); i++){
            IMolecule newMolecule = movable.makeMolecule();
            box.addMolecule(newMolecule);
           newMolecule.getChildList().getAtom(0).getPosition().E(movableList.getMolecule(i).getChildList().getAtom(0).getPosition());
           box.removeMolecule((IMolecule)movableList.getMolecule(i));
        }
        movableSet = box.getMoleculeList(movable);
    }
    
    public void refreshSpecies(){
        IMoleculeList loopSet = box.getMoleculeList(movable);
        MoleculeArrayList movableList = new MoleculeArrayList();
        for (int i=0; i<movableList.getMoleculeCount(); i++){
	        IMolecule newMolecule = fixed.makeMolecule();
	        box.addMolecule(newMolecule);
           newMolecule.getChildList().getAtom(0).getPosition().E(movableList.getMolecule(i).getChildList().getAtom(0).getPosition());
           box.removeMolecule(movableList.getMolecule(i));

        }
        box.setNMolecules(movable, 0);
    }
    public void setMovableAtomsCube(IVectorMutable dimensions, IVectorMutable center){
        IVectorMutable cube = dimensions;
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
        	//if(loopSet.getMolecule(i).getType()==fixed){continue;}
            rij.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            rij.Ev1Mv2(center, rij);
            box.getBoundary().nearestImage(rij);
            if(Math.abs(rij.getX(0)) < cube.getX(0) && Math.abs(rij.getX(1)) < cube.getX(1) && Math.abs(rij.getX(2)) < cube.getX(2)){
               movableList.add(loopSet.getMolecule(i));
            } 
        }
        for (int i=0; i<movableList.getMoleculeCount(); i++){
            IMolecule newMolecule = movable.makeMolecule();
            box.addMolecule(newMolecule);
           newMolecule.getChildList().getAtom(0).getPosition().E(movableList.getMolecule(i).getChildList().getAtom(0).getPosition());
           box.removeMolecule(movableList.getMolecule(i));
        }
        movableSet = box.getMoleculeList(movable);
    }
        
    //Must be run after setMovableAtoms
    public void removeAtoms(double distance, IVectorMutable center){
        distance = distance*distance;
        int rmvCount = 0;
        IVectorMutable rij = space.makeVector();
        //movable species

        IMoleculeList loopSet = box.getMoleculeList(movable);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            rij.Ev1Mv2(center,loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            box.getBoundary().nearestImage(rij);
            if(rij.squared() < distance){
               box.removeMolecule(loopSet.getMolecule(i));
               rmvCount++;
            } 
        }
        System.out.println(rmvCount+" atoms removed!");
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
            currentPos[i] = loopSet3.getMolecule(i).getChildList().getAtom(0).getPosition();
            for(int j=0; j<3; j++){
                offset = random.nextGaussian()/50.0;
                //System.out.println(offset);
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
            currentPos[i].E(movableSet.getMolecule(i).getChildList().getAtom(0).getPosition());
        }
        //Create multiple configurations
        for(int m=0; m<50; m++){
            WriteConfiguration genConfig = new WriteConfiguration(space);
            genConfig.setBox(box);
            genConfig.setConfName(fileName+"_config_"+m);
            //Displaces atom's by at most +/-0.03 in each coordinate
            for(int i=0; i<movableSet.getMoleculeCount(); i++){
                IVectorMutable atomPosition = movableSet.getMolecule(i).getChildList().getAtom(0).getPosition();
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
        //System.out.println(sim.box.getBoundary().getBoxSize());
        
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 0.0);
        vect.setX(1, 0.0);
        vect.setX(2, 0.0);
        
        //Set Box Size  
        //  			500K 59.869602,  59.869602, 39.226563
        //				600K 59.970394,  59.970394, 39.292602
        //				700K 60.10302,  60.10302,  39.379499
        //				800K 60.227779, 60.227779, 39.461241
        //				900K 60.364577, 60.364577, 39.550871
        //				1000K 60.500753, 60.500753, 39.640093
        //				1100K 60.633579, 60.633579, 39.727121
        //				1200K 60.80549, 60.80549, 39.839757
        //				1300K 60.908788, 60.908788,  39.907438
        //				1400K 61.111875 , 61.111875,  40.04050
        //              1600K 61.405116, 61.405116,  40.232632
        //				1700K 61.55784,   61.55784,  40.332697
        //  
        //
        //				1500K Cu 54161.895  37.835366944
        //				1600K Cu 55001.395  38.029846127
        //				large    439598.03  76.035880449
        //				1700K Cu 55852.468  38.22499666
        //				1800K Cu 56906.577  38.463974171
        //				1900K Cu 57705.255  38.643084817
  
        
        //Vector3D move2 = new Vector3D(61.55784, 61.55784, 40.332697);
        //sim.box.getBoundary().setBoxSize(move2);
        
        
        //LXYZ2PropertyReader xyz2prop = new LXYZ2PropertyReader("/home/msellers/simulation/block/Sn/1700-1.xyz","blank",10,sim.box,sim,sim.space);
	    //xyz2prop.actionPerformed();
	    
	    //System.exit(1);
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
        
        sim.enableMolecularDynamics(1000);
        //sim.enableDimerSearch("snblock2", 4000, false, false);             
        //sim.enableMinimumSearch("snblock2", false);
        
	    //move2.setX(1,75.0);
	    
        
	    /**
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
	        	rij1.E(boxList.getMolecule(i).getChildList().getAtom(0).getPosition());
		        	if(Math.abs(rij1.getX(1)-zvec)<=(5.921/4.0)){//Math.abs(rij.x(0)) < 0.5 && Math.abs(rij.x(1)) < distance && Math.abs(rij.x(2)) < distance){
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
	    **/
	    
        SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, 1, sim.space, sim.getController());
        simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));        
        sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
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
