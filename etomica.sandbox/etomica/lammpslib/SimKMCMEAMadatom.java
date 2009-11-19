package etomica.lammpslib;

import etomica.action.activity.ActivityIntegrate;
<<<<<<< SimKMCMEAMadatom.java
import etomica.api.IAtomPositioned;
import etomica.api.IAtomType;
=======
import etomica.api.IAtomType;
>>>>>>> 1.16
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
import etomica.api.ISpecies;
<<<<<<< SimKMCMEAMadatom.java
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
=======
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
>>>>>>> 1.16
import etomica.chem.elements.Tin;
import etomica.config.Configuration;
import etomica.config.ConfigurationFile;
import etomica.config.ConfigurationLattice;
import etomica.dimer.CalcGradientDifferentiable;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.dimer.IntegratorDimerRT;
import etomica.dimer.LammpsInterface;
import etomica.graphics.ColorSchemeByType;
import etomica.graphics.DisplayBox;
import etomica.graphics.SimulationGraphic;
import etomica.lattice.BravaisLatticeCrystal;
import etomica.lattice.crystal.BasisBetaSnA5;
import etomica.lattice.crystal.PrimitiveTetragonal;
import etomica.listener.IntegratorListenerAction;
import etomica.potential.PotentialMaster;
import etomica.simulation.Simulation;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimKMCMEAMadatom extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "DimerMEAMadatomSn";
    public final PotentialMaster potentialMasterD;
    public IBox box;
    public SpeciesSpheresMono fixed,movable;
    public PotentialMEAM potential;
    public ActivityIntegrate activityIntegrateKMC, activityIntegrateDimer, activityIntegrateDimerMin, activityIntegrateKMCCluster;
    public IntegratorKMC integratorKMC;
    public IntegratorKMCCluster integratorKMCCluster;
    public IntegratorDimerRT integratorDimer;
    public IntegratorDimerMin integratorDimerMin;
    public CalcGradientDifferentiable calcGradientDifferentiable;
    public CalcVibrationalModes calcVibrationalModes;
    public double [][] dForces;
    public int [] d, modeSigns;
    public double [] positions;
    public double [] lambdas, frequencies;
<<<<<<< SimKMCMEAMadatom.java
    public IVectorMutable adAtomPos;
    public IMoleculeList movableSet;
    public long lammpsSim;
=======
    public IVectorMutable adAtomPos;
    public IMoleculeList movableSet;
>>>>>>> 1.16
    //public Boolean saddleFine, calcModes, minSearch, normalDir;
    
    public SimKMCMEAMadatom() {
        super(Space3D.getInstance());    	

<<<<<<< SimKMCMEAMadatom.java
        potentialMasterD = new PotentialMaster();
        lammpsSim = LammpsInterface.makeLammpsSim("/usr/users/msellers/simulation/lammps-couple/in.snblock");
        //lammpsSim = LammpsInterface.makeLammpsSim("/home/msellers/Lammps-Workspace/in.sn");
        //SIMULATION BOX
        //box = new Box(new BoundaryRectangularSlit(0, 5, space), space);
=======
        potentialMasterD = new PotentialMasterListDimer(this, space);
        
      //SIMULATION BOX
        box = new Box(new BoundaryRectangularSlit(0, 5, space), space);
>>>>>>> 1.16
        addBox(box);
     
      //SPECIES
        
<<<<<<< SimKMCMEAMadatom.java
        //Sn  
        fixed = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
=======
        //Sn
        Tin tinFixed = new Tin("SnFix", Double.POSITIVE_INFINITY);  
        fixed = new SpeciesSpheresMono(space, tinFixed);
        movable = new SpeciesSpheresMono(space, Tin.INSTANCE);
        potentialSpecies = new SpeciesSpheresMono(space, tinFixed);
        addSpecies(fixed);
        addSpecies(movable);
        addSpecies(potentialSpecies);
>>>>>>> 1.16
        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(3.022); 
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(3.022);
        box.setNMolecules(fixed, 216);
        
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Sn);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Sn);
        
        //Sn
        //beta-Sn box
        
        //The dimensions of the simulation box must be proportional to those of
        //the unit cell to prevent distortion of the lattice.  The values for the 
        //lattice parameters for tin's beta box (a = 5.8314 angstroms, c = 3.1815 
        //angstroms) are taken from the ASM Handbook. 
              
        double a = 5.92; 
        double c = 3.23;
<<<<<<< SimKMCMEAMadatom.java
        box.getBoundary().setDimensions(new Vector3D(a*3, a*3, c*6));
=======
        box.getBoundary().setBoxSize(new Vector3D(a*3, a*3, c*5));
>>>>>>> 1.16
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());
        
                
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
        
        */
    
        
        //Cu
        /*
        //Copper copperFixed = new Copper("CuFix", Double.POSITIVE_INFINITY);
        fixed = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        movable = new SpeciesSpheresMono(this, space, Copper.INSTANCE);
        getSpeciesManager().addSpecies(fixed);
        getSpeciesManager().addSpecies(movable);
        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(2.5561); 
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(2.5561);
        potential = new PotentialMEAM(space);
        potential.setParameters(fixed.getLeafType(), ParameterSetMEAM.Cu);
        potential.setParameters(movable.getLeafType(), ParameterSetMEAM.Cu);
        box.setNMolecules(fixed, 256);
        
        double a = 3.535;
        box.getBoundary().setDimensions(new Vector3D(a*4, a*4, a*4));
        PrimitiveCubic primitive = new PrimitiveCubic(space, a);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        */
        
        Configuration config = new ConfigurationLattice(crystal, space);
        config.initializeCoordinates(box);

<<<<<<< SimKMCMEAMadatom.java
        this.potentialMasterD.addPotential(potential, new IAtomType[]{movable.getLeafType(), fixed.getLeafType()});
       
=======
        this.potentialMasterD.addPotential(potential, new IAtomType[]{movable.getLeafType(), potentialSpecies.getLeafType()});
        potentialMasterD.setSpecies(new ISpecies []{potentialSpecies, movable});
        potentialMasterD.setRange(potential.getRange()*1.1);
        CriterionSimple criteria2 = new CriterionSimple(this, space, potential.getRange(), potential.getRange()*1.1);
        potentialMasterD.setCriterion(potential, new CriterionTypesCombination(criteria2, new IAtomType[] {movable.getLeafType(), potentialSpecies.getLeafType()}));
        
>>>>>>> 1.16
    //ADATOM CREATION AND PLACEMENT
        // Sn, Ag, or Cu
        /*
        IMolecule iMolecule = movable.makeMolecule();
        box.addMolecule(iMolecule);
        adAtomPos = iMolecule.getChildList().getAtom(0).getPosition();
        //adAtomPos = getSpace().makeVector();
        adAtomPos.setX(0, 8.0);
        adAtomPos.setX(1, -1.0);
        adAtomPos.setX(2, -1.0);
<<<<<<< SimKMCMEAMadatom.java
        IVectorMutable newBoxLength = space.makeVector();
        newBoxLength.E(box.getBoundary().getDimensions());
        newBoxLength.setX(0, 2.0*adAtomPos.x(0)+6.0);
        box.getBoundary().setDimensions(newBoxLength);
=======
        IVectorMutable newBoxLength = space.makeVector();
        newBoxLength.E(box.getBoundary().getBoxSize());
        newBoxLength.setX(0, 2.0*adAtomPos.getX(0)+2.0);
        box.getBoundary().setBoxSize(newBoxLength);
        
        /**
        //Ag
        IAtom iAtom = agAdatom.getMoleculeFactory().makeAtom();
        box.getAgent(agAdatom).addChildAtom(iAtom);
        iAtom).getPosition().setX(0, 7.5);
        iAtom).getPosition().setX(1, 0.9477016722828758);
        iAtom).getPosition().setX(2, 1.0709520701043456);
        */
        /**
        //Cu
        IAtom iAtom = cuAdatom.getMoleculeFactory().makeAtom();
        box.getAgent(cuAdatom).addChildAtom(iAtom);
        iAtom).getPosition().setX(0, 6.0);
        iAtom).getPosition().setX(1, 0.9477016722828758);
        iAtom).getPosition().setX(2, 1.0709520701043456);
>>>>>>> 1.16
        */
    }
    
    public void setMovableAtoms(double distance, IVectorMutable center){
        //distance = distance*distance;
<<<<<<< SimKMCMEAMadatom.java
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            if(loopSet.getMolecule(i).getType()==movable){
                continue;
            }
            
            rij.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(rij.x(0) > 0.8){
                rij.ME(center);
                box.getBoundary().nearestImage(rij);
                if(rij.squared() < distance){   
                    movableList.add(loopSet.getMolecule(i));
                }
            }
=======
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            rij.Ev1Mv2(center,loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            if(rij.getX(0) > (box.getBoundary().getBoxSize().getX(0) - 3.0)){continue;}
            //box.getBoundary().nearestImage(rij);
            if(rij.squared() < distance){
               movableList.add(loopSet.getMolecule(i));
            } 
>>>>>>> 1.16
        }
        for (int i=0; i<movableList.getMoleculeCount(); i++){
            IMolecule newMolecule = movable.makeMolecule();
            box.addMolecule(newMolecule);
<<<<<<< SimKMCMEAMadatom.java
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)movableList.getMolecule(i).getChildList().getAtom(0)).getPosition());
            box.removeMolecule(movableList.getMolecule(i));
=======
            newMolecule.getChildList().getAtom(0).getPosition().E(movableList.getMolecule(i).getChildList().getAtom(0).getPosition());
            box.removeMolecule(movableList.getMolecule(i));
>>>>>>> 1.16
        }
        movableSet = box.getMoleculeList(movable);
    }
    
<<<<<<< SimKMCMEAMadatom.java
    public void refreshSpecies(){
        IMoleculeList loopSet = box.getMoleculeList(movable);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            IMolecule newMolecule = getSpeciesManager().getSpecies(0).makeMolecule();
            box.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
=======
    public void setPotentialListAtoms(){
        MoleculeArrayList neighborList = new MoleculeArrayList();
        MoleculeArrayList fixedList = new MoleculeArrayList();
        IMoleculeList loopSet = box.getMoleculeList();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            if(loopSet.getMolecule(i).getType()==movable){
                continue;
            }
            if(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition().getX(0) < -4.0){continue;}
            boolean fixedFlag = true;
            for(int j=0; j<movableSet.getMoleculeCount(); j++){
                IVectorMutable dist = space.makeVector();
                dist.Ev1Mv2(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition(),movableSet.getMolecule(j).getChildList().getAtom(0).getPosition());
                box.getBoundary().nearestImage(dist);
                if(Math.sqrt(dist.squared())<potentialMasterD.getMaxPotentialRange()+2.0){
                    neighborList.add(loopSet.getMolecule(i));
                    fixedFlag = false;
                    break;
                }               
            
            }
            if(fixedFlag){
                fixedList.add(loopSet.getMolecule(i));
            }
>>>>>>> 1.16
        }
<<<<<<< SimKMCMEAMadatom.java
        box.setNMolecules(movable, 0);
=======
        for (int i=0; i<neighborList.getMoleculeCount(); i++){
            IMolecule newMolecule = potentialSpecies.makeMolecule();
            box.addMolecule(newMolecule);
            newMolecule.getChildList().getAtom(0).getPosition().E(neighborList.getMolecule(i).getChildList().getAtom(0).getPosition());
            box.removeMolecule(neighborList.getMolecule(i));
         }
        for (int i=0; i<fixedList.getMoleculeCount(); i++){
            IMolecule newMolecule = fixed.makeMolecule();
            box.addMolecule(newMolecule);
            newMolecule.getChildList().getAtom(0).getPosition().E(fixedList.getMolecule(i).getChildList().getAtom(0).getPosition());
            box.removeMolecule(fixedList.getMolecule(i));
         }
        
>>>>>>> 1.16
    }
    public void randomizePositions(){
        IVectorMutable workVector = space.makeVector();
        IMoleculeList loopSet3 = box.getMoleculeList(movable);
        IVectorMutable [] currentPos = new IVectorMutable [loopSet3.getMoleculeCount()];
        double offset = 0;
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
<<<<<<< SimKMCMEAMadatom.java
            currentPos[i] = (((IAtomPositioned)loopSet3.getMolecule(i).getChildList().getAtom(0)).getPosition());
=======
            currentPos[i] = (loopSet3.getMolecule(i).getChildList().getAtom(0).getPosition());
>>>>>>> 1.16
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
    
<<<<<<< SimKMCMEAMadatom.java
=======
    //Must be run after setMovableAtoms
    public void removeAtoms(double distance, IVectorMutable center){
        distance = distance*distance;
        IVectorMutable rij = space.makeVector();
        
        IMoleculeList loopSet = box.getMoleculeList(movable);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            rij.Ev1Mv2(center,loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            box.getBoundary().nearestImage(rij);
            if(rij.squared() < distance){
               box.removeMolecule(loopSet.getMolecule(i));
            } 
        }   
    }
>>>>>>> 1.16
    
    public void initializeConfiguration(String fileName){
        ConfigurationFile config = new ConfigurationFile(fileName);
        config.initializeCoordinates(box);
    }
    
    public void integratorKMC(){
        integratorKMC = new IntegratorKMC(this, lammpsSim, potentialMasterD, 273.15, this.getRandom(), new ISpecies[]{movable}, this.getSpace());
        integratorKMC.setBox(box);
        activityIntegrateKMC = new ActivityIntegrate(integratorKMC);
        getController().addAction(activityIntegrateKMC);
    }
    
    public void integratorKMCCluster(double temp, int steps, int totalSearch){
        integratorKMCCluster = new IntegratorKMCCluster(this, lammpsSim, potentialMasterD, temp, totalSearch, this.getRandom(), new ISpecies[]{movable}, this.getSpace());
        integratorKMCCluster.setBox(box);
        activityIntegrateKMCCluster = new ActivityIntegrate(integratorKMCCluster);
        activityIntegrateKMCCluster.setMaxSteps(steps);
        getController().addAction(activityIntegrateKMCCluster);
    }
    
public void enableDimerSearch(String fileName, long maxSteps, boolean ortho){
        
        integratorDimer = new IntegratorDimerRT(this, lammpsSim, potentialMasterD, new ISpecies[]{movable}, space);
        integratorDimer.setBox(box);
        integratorDimer.setRotNum(1);
        integratorDimer.setOrtho(ortho, false);
        integratorDimer.setFileName(fileName);
<<<<<<< SimKMCMEAMadatom.java
        //integratorDimer.addNonintervalListener(potentialMasterD.getNeighborManager(box));
        //integratorDimer.addIntervalAction(potentialMasterD.getNeighborManager(box));  
=======
        integratorDimer.getEventManager().addListener(potentialMasterD.getNeighborManager(box));  
>>>>>>> 1.16
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
    activityIntegrateDimerMin = new ActivityIntegrate(integratorDimerMin);
    integratorDimerMin.setActivityIntegrate(activityIntegrateDimerMin);
    getController().addAction(activityIntegrateDimerMin);
}
    public static void main(String[] args){
       
        final SimKMCMEAMadatom sim = new SimKMCMEAMadatom();
<<<<<<< SimKMCMEAMadatom.java
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 7.6);
        vect.setX(1, -1.0);
        vect.setX(2, -1.0);
 
        sim.setMovableAtoms(200.0, vect);
        System.out.println("Box vector: "+sim.box.getBoundary().getDimensions());
        //sim.initializeConfiguration("test-cu_saddle");
        //sim.integratorKMC();
        //sim.integratorKMC.setup();
        sim.randomizePositions();
        sim.enableDimerSearch("sn-vacancy", 1000, false);
        //sim.enableMinimumSearch("test-cu", true);
=======
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 9.8);
        vect.setX(1, -0.2);
        vect.setX(2, -0.2);
        
        sim.setMovableAtoms(100.0, vect);
        
        sim.setPotentialListAtoms();
        sim.initializeConfiguration("0-MEAM_saddle");
        sim.integratorKMCCluster(400.0, 800, 30);

        //energy: -3331480.584975273    Vib: 9.561284069712113E96
        sim.integratorKMCCluster.setInitialStateConditions(-3331480.584975273, 9.561284069712113E96);
        
>>>>>>> 1.16
        SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME,1, sim.space, sim.getController());
        simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));
        
<<<<<<< SimKMCMEAMadatom.java
        sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
        //sim.integratorKMC.addIntervalAction(simGraphic.getPaintAction(sim.box));
        //sim.integratorKMC.integratorMin.addIntervalAction(simGraphic.getPaintAction(sim.box));
        //sim.integratorKMC.integratorDimer.addIntervalAction(simGraphic.getPaintAction(sim.box));
=======
        //sim.integratorMD.addIntervalAction(simGraphic.getPaintAction(sim.box));
        sim.integratorKMCCluster.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
>>>>>>> 1.16

    	ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());
    	
    	colorScheme.setColor(sim.fixed.getLeafType(),java.awt.Color.gray);
        colorScheme.setColor(sim.movable.getLeafType(),java.awt.Color.red);

    	simGraphic.makeAndDisplayFrame(APP_NAME);
    }
    static {
        System.loadLibrary("LAMMPS");
//        System.loadLibrary("lmp_thomas");
    }

}
