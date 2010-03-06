package etomica.lammpslib;

import etomica.action.WriteConfiguration;
import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtom;
import etomica.api.IAtomType;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
import etomica.api.ISpecies;
import etomica.api.IVector;
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.ConfigurationFile;
import etomica.config.GrainBoundaryTiltConfiguration;
import etomica.graphics.ColorSchemeByType;
import etomica.graphics.DisplayBox;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.lattice.BravaisLatticeCrystal;
import etomica.lattice.crystal.BasisBetaSnA5;
import etomica.lattice.crystal.PrimitiveTetragonal;
import etomica.listener.IntegratorListenerAction;
import etomica.potential.PotentialMaster;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularPeriodic;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;
import etomica.util.RandomNumberGenerator;
import etomica.util.numerical.CalcGradientDifferentiable;

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimDimerMEAMGB extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "DimerMEAMadatomSn";
    public final PotentialMaster potentialMaster;
    public final PotentialMaster potentialMasterD;
    public IntegratorVelocityVerlet integratorMD;
    public IntegratorDimerRT integratorDimer;
    public IntegratorDimerMin integratorDimerMin;
    public IBox box;
    public double clusterRadius;
    public IVectorMutable [] saddle;
    public SpeciesSpheresMono fixed, movable;
    public PotentialMEAM potential;
    public PotentialCalculationForcePressureSumGB pcGB;
    public ActivityIntegrate activityIntegrateMD, activityIntegrateDimer, activityIntegrateMin;
    public CalcGradientDifferentiable calcGradientDifferentiable;
    public CalcVibrationalModes calcVibrationalModes;
    public double [][] dForces;
    public int [] d, modeSigns;
    public double [] positions;
    public double [] lambdas, frequencies;
    public IVectorMutable adAtomPos;
    public IMoleculeList movableSet;
    public int [] millerPlane;
    public long lammpsSim;
    private BravaisLatticeCrystal crystal;
    public  GrainBoundaryTiltConfiguration gbtilt;
    

    
    public SimDimerMEAMGB(int[] amillerPlane, int[] boxSize) {
    	super(Space3D.getInstance());
    	
    	this.millerPlane = amillerPlane;
    	potentialMaster = new PotentialMaster();
    	potentialMasterD = new PotentialMaster();
    	//lammpsSim = LammpsInterface.makeLammpsSim("/home/msellers/simulation/lammps-couple/in.sngb210");
    	//SIMULATION BOX
        box = new Box(new BoundaryRectangularPeriodic(space), space);
    	//box = new Box(new BoundaryRectangularSlit(2, 5, space), space);
        addBox(box);
        //SPECIES
        
        //Sn
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

        //Sn
        //beta-Sn box
        
        //The dimensions of the simulation box must be proportional to those of
        //the unit cell to prevent distortion of the lattice.  The values for the 
        //lattice parameters for tin's beta box (a = 5.8314 angstroms, c = 3.1815 
        //angstroms) are taken from the ASM Handbook. 
              
        double a = 5.921;
        //double a = 5.9305;
        //double c = 3.24;
        double c = a*0.54689;
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
        crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());

        gbtilt = new GrainBoundaryTiltConfiguration(crystal, crystal, new ISpecies[] {fixed, movable}, potential.getRange(), space);
            
        
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
        potential.setParameters(movable, ParameterSetMEAM.Ag);
        
        double a = 4.0863;
        PrimitiveCubic primitive = new PrimitiveCubic(space, a);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        GrainBoundaryTiltConfiguration gbtilt = new GrainBoundaryTiltConfiguration(crystal, crystal, new ISpecies[] {fixed, movable}, 4.56, space);

        */
    
        
        //Cu
       /**
        //Copper copperFixed = new Copper("CuFix", Double.POSITIVE_INFINITY);
        fixed = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        dimer = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        getSpeciesManager().addSpecies(dimer);
        ((AtomTypeSphere)fixed.getLeafType()).setDiameter(2.5561); 
        ((AtomTypeSphere)dimer.getLeafType()).setDiameter(2.5561); 
        ((AtomTypeSphere)movable.getLeafType()).setDiameter(2.5561);
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Cu);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Cu);
        potential.setParameters(dimer.getLeafType(), ParameterSetMEAM.Cu);
        
        double a = 3.6148;
        PrimitiveCubic primitive = new PrimitiveCubic(space, a);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        GrainBoundaryTiltConfiguration gbtilt = new GrainBoundaryTiltConfiguration(crystal, crystal, new ISpecies[] {fixed, movable}, potential.getRange(), space);
       */
        
        this.potentialMaster.addPotential(potential, new IAtomType[]{fixed.getLeafType(), movable.getLeafType()});
        //potentialMaster.setRange(potential.getRange()*1.1);
        //CriterionSimple criteria = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        //potentialMaster.setCriterion(potential, new CriterionTypesCombination(criteria, new IAtomTypeLeaf[] {fixed.getLeafType(), movable.getLeafType()}));
        
        this.potentialMasterD.addPotential(potential, new IAtomType[]{movable.getLeafType(), fixed.getLeafType()});
        
        gbtilt.setFixedSpecies(fixed);
        gbtilt.setMobileSpecies(movable);

        gbtilt.setGBplane(millerPlane);
        gbtilt.setBoxSize(box, boxSize);
        
        //gbtilt.setRotationBOTTOM(2, Math.PI);
        
        gbtilt.initializeCoordinates(box);        
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
    
    public void witeExcelPlot(){
    	//WRITE EXCEL PLOT  
    	IMoleculeList loopSet = box.getMoleculeList();
    	
    	Vector3D move0 = new Vector3D(3.0,1.205,-2.9);
        Vector3D move1 = new Vector3D(0.0,0.1,0.0);
        Vector3D move2 = new Vector3D(3.0,1.205,-2.9);
        
        IVectorMutable workVector = getSpace().makeVector();
        
        System.out.print(" ");
        for(int x=0; x<150; x++){
        	System.out.print(""+(move0.getX(0)*x)+" ");
        }
        System.out.println();
	    for(int y=0; y<50; y++){  
		   System.out.print(""+(move1.getX(1)*y)+" ");
		   for(int x=0; x<150; x++){
			   for(int i=0; i<loopSet.getMoleculeCount(); i++){
			    	if(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().getX(2)>0.0001){
			    		(loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition().PE(move0);
			    		workVector.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
			    		IVector shift = box.getBoundary().centralImage(workVector);
		                if (!shift.isZero()) {
	                        workVector.PE(shift);
	                        loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().E(workVector);
	                    }
			    	}
			    }
			   for(int i=0; i<loopSet.getMoleculeCount(); i++){
			        workVector.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
			        LammpsInterface2.setAtomPosition(lammpsSim, i, workVector.getX(0), workVector.getX(1), workVector.getX(2));
			    }
			    LammpsInterface2.doLammpsStep(lammpsSim, 1);
			    System.out.print(LammpsInterface2.getEnergy(lammpsSim)+" ");
		   }
		   System.out.println();
		   move0.setX(0, move0.getX(0)*150);
		   for(int i=0; i<loopSet.getMoleculeCount(); i++){
	        	if(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().getX(2)>0.0001){
	        		loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().PE(move1);
	        		loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().ME(move0);
		    	}	   
		   }
		   move0.setX(0,0.1);
	   }	     
	   
    	
    }
        
    public void enableMolecularDynamics(long maxSteps){
        integratorMD = new IntegratorVelocityVerlet(this, potentialMaster, space);
        integratorMD.setTimeStep(0.01);
        integratorMD.setTemperature(0);
        integratorMD.setThermostatInterval(100);
        integratorMD.setIsothermal(true);
        integratorMD.setBox(box);
        //pcGB = new PotentialCalculationForcePressureSumGB(space, box);
        //integratorMD.setForceSum(pcGB);
        //integratorMD.addNonintervalListener(potentialMaster.getNeighborManager(box));
        //integratorMD.addIntervalAction(potentialMaster.getNeighborManager(box));  
        activityIntegrateMD = new ActivityIntegrate(integratorMD);
        getController().addAction(activityIntegrateMD);
        activityIntegrateMD.setMaxSteps(maxSteps);
    }
    
    public void enableDimerSearch(String fileName, long maxSteps, boolean orthoSearch, boolean fine){
        
        integratorDimer = new IntegratorDimerRT(this, lammpsSim, potentialMasterD, new ISpecies[]{movable}, space);
        integratorDimer.setBox(box);
        integratorDimer.setRotNum(1);
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
        //String fileName = "sngb101-test" ;//args[0];
        //int mdSteps = 10;//Integer.parseInt(args[1]);
        /*
        int h = Integer.parseInt(args[1]);
        int k = Integer.parseInt(args[2]);
        int l = Integer.parseInt(args[3]);
        
        int x = Integer.parseInt(args[4]);
        int y = Integer.parseInt(args[5]);
        int z = Integer.parseInt(args[6]);
        */
        final String APP_NAME = "SimDimerMEAMGBCluster";
        
        final SimDimerMEAMGB sim = new SimDimerMEAMGB(new int[] {2,0,1}, new int[] {6,4,50});        
        //sim.refreshSpecies();
           
        Vector3D move0 = new Vector3D(0.0,0.0,0.0);  
        Vector3D move1 = new Vector3D(0.0,0.1,0.0);
        Vector3D move2 = new Vector3D(0.0,1.0,0.0);
               
        //System.out.println(remove);
	    for(int i=0; i<sim.box.getMoleculeList().getMoleculeCount(); i++){
	    	//IAtom atom = sim.box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
	    	//if(atom.getPosition().getX(2)>0.0){atom.getPosition().PE(move2);}
	    }
	    
	    move2.setX(0,0.0);
	    move2.setX(1,0.0);
	    move2.setX(2,1.0);
	    move2.PE(sim.box.getBoundary().getBoxSize());
	    sim.box.getBoundary().setBoxSize(move2);
	    //System.out.println("Interface Area: "+move2.getX(0)*move2.getX(1)+" angstroms");
	    move2.E(sim.box.getBoundary().getBoxSize());
	    move2.TE(0.5);
	    System.out.println("Box Dimensions: "+move2);
	    System.out.println("Number of Atoms: "+sim.box.getMoleculeList().getMoleculeCount());
	    
	    WriteConfiguration writer = new WriteConfiguration(sim.getSpace());
	    writer.setBox(sim.box);
	    writer.setConfName("equil-6450");
	    writer.actionPerformed();
	    
	    
	    /*
	    //STRUCTURE FACTOR CALCULATION
        MeterStructureFactor meterS = new MeterStructureFactor(sim.getSpace(), sim.crystal, sim.box);
	    sim.box.setNMolecules(sim.fixed, 0);
	    sim.box.setNMolecules(sim.movable, 0);
	    sim.box.setNMolecules(sim.movable, 3864);
	    System.out.println(sim.box.getMoleculeList().getMoleculeCount());
	    sim.initializeConfiguration("/home/msellers/simulation/GB/401/450-15");
        IVectorMutable[] waveVec;
        waveVec = sim.getSpace().makeVectorArray(5);
        
        waveVec[0].E(sim.gbtilt.waveVector[0]);
        
        waveVec[1].E(sim.gbtilt.waveVector[1]);
        
        waveVec[2].Ev1Pv2(waveVec[0], waveVec[1]);
        
        waveVec[3].Ea1Tv1(2.0, waveVec[0]);
        waveVec[3].PE(waveVec[1]);
        
        waveVec[4].Ea1Tv1(2.0, waveVec[1]);
        waveVec[4].PE(waveVec[0]);
        
        IMoleculeList boxList = sim.box.getMoleculeList();
        IVectorMutable rij1 = sim.getSpace().makeVector();
        System.out.println(sim.gbtilt.spacing);
        double zvec=26.5;
        for(int z=0; z<45; z++){ 	
        	MoleculeArrayList structArray = new MoleculeArrayList();
	        for (int i=0; i<boxList.getMoleculeCount(); i++){
	        	rij1.E(boxList.getMolecule(i).getChildList().getAtom(0).getPosition());
		        	if(Math.abs(rij1.getX(2)-zvec)<=sim.gbtilt.spacing/8.0){//Math.abs(rij.x(0)) < 0.5 && Math.abs(rij.x(1)) < distance && Math.abs(rij.x(2)) < distance){
			               structArray.add(boxList.getMolecule(i));  
			               //if(zvec>23.0)System.out.println(rij1);
		            }
	        }
	        meterS.reset();
	        meterS.setWaveVec(waveVec);
	        meterS.setAtoms(structArray);
	        meterS.actionPerformed();
	        //System.out.println(meterS.getDataAsArray()[0]);
	        System.out.println(meterS.getDataAsArray()[0]+"    "+meterS.getDataAsArray()[1]);
	        //sim.refreshSpecies();
	        zvec=zvec-sim.gbtilt.spacing;
        }
	    
	    
	    System.exit(1);
	    */
	    
	    //LXYZ2PropertyReader xyz2prop = new LXYZ2PropertyReader("310-300.xyz","blank",1000,sim.box,sim,sim.space);
	    //xyz2prop.actionPerformed();
	    
	    //sim.randomizePositions();
	    //sim.setMovableAtomsSphere(10.0, dimerCenter);
	    //sim.enableDimerSearch("gb2-123", 2000, false, false);
	    //sim.enableMinimumSearch("shortest", true);
	    sim.enableMolecularDynamics(10000);
	    /*
	    XYZWriter xyzwrite = new XYZWriter(sim.box);
	    xyzwrite.setFileName("test.xyz");
	    xyzwrite.setIsAppend(true);
	    xyzwrite.actionPerformed();
	    */
		/*
	    CalcVibrationalModes vib = new CalcVibrationalModes(sim.lammpsSim);
	    vib.setup(sim.box, sim.potentialMaster, sim.box.getMoleculeList(sim.movable), sim.space);
	    vib.actionPerformed();
	    System.out.println(vib.getProductOfFrequencies());
	    */
	    
	    //System.out.println(vib.getProductOfFrequencies());
	    
	    SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, 1, sim.space, sim.getController());
	    simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));        
	    
	    sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
	    
	    ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());
	    colorScheme.setColor(sim.fixed.getLeafType(),java.awt.Color.gray);
	    colorScheme.setColor(sim.movable.getLeafType(),java.awt.Color.white);
	    simGraphic.makeAndDisplayFrame(APP_NAME);
    }

	static {
	//	System.loadLibrary("LAMMPS");
	//  System.loadLibrary("lmp_thomas");
    }
}
