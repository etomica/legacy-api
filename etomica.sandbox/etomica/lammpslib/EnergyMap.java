package etomica.lammpslib;

import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtom;
import etomica.api.IAtomType;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IVectorMutable;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.Configuration;
import etomica.config.ConfigurationFile;
import etomica.config.ConfigurationLattice;
import etomica.dimer.EnergyMap;
import etomica.dimer.IntegratorEnergyMap;
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
import etomica.space.BoundaryRectangularSlit;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;

/**
 * Simulation class using IntegratorEnergyMap.  Rasterizes a surface with an atom
 * to achieve values of its energy.
 * 
 * @author msellers
 *
 */

public class EnergyMap extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "MEAM Md3D";
    public final PotentialMaster potentialMaster;
    public IntegratorEnergyMap integratorMAP;
    public IBox box;
    public SpeciesSpheresMono sn, snAdatom;
    public PotentialMEAM potential;
    public ActivityIntegrate activityIntegrateMAP;
    public long lammps;
    

    
    public EnergyMap(double height, String fileTail) {
    	super(Space3D.getInstance());
    	
    	potentialMaster = new PotentialMaster();
        lammps = LammpsInterface.makeLammpsSim("/home/msellers/simulation/lammps-couple/in.sn");
        
        
        box = new Box(new BoundaryRectangularSlit(0, 5, space), space);
        addBox(box);
        
        
    	// Sn
<<<<<<< EnergyMap.java
        sn = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        snAdatom = new SpeciesSpheresMono(this, space, Tin.INSTANCE);
        
        getSpeciesManager().addSpecies(sn);
        getSpeciesManager().addSpecies(snAdatom);
=======
        Tin tinFixed = new Tin("SnFix", Double.POSITIVE_INFINITY);
        
        snFix = new SpeciesSpheresMono(space, tinFixed);
        snFix.setIsDynamic(true);
        sn = new SpeciesSpheresMono(space, Tin.INSTANCE);
        sn.setIsDynamic(true);
        snAdatom = new SpeciesSpheresMono(space, Tin.INSTANCE);
        snAdatom.setIsDynamic(true);
        movable = new SpeciesSpheresMono(space, Tin.INSTANCE);
        movable.setIsDynamic(true);
        
        addSpecies(snFix);
        addSpecies(sn);
        addSpecies(snAdatom);
        addSpecies(movable);
>>>>>>> 1.9
        
        ((IAtomTypeSphere)sn.getLeafType()).setDiameter(3.022); 
        ((IAtomTypeSphere)snAdatom.getLeafType()).setDiameter(3.022);
        
        /**
        // Cu
        Copper copperFixed = new Copper("CuFix", Double.POSITIVE_INFINITY);
        
        cuFix = new SpeciesSpheresMono(this, copperFixed);
        cu = new SpeciesSpheresMono(this, Copper.INSTANCE);
        cuAdatom = new SpeciesSpheresMono(this, Copper.INSTANCE);
        movable = new SpeciesSpheresMono(this, Copper.INSTANCE);
        
        getSpeciesManager().addSpecies(cuFix);
        getSpeciesManager().addSpecies(cu);
        getSpeciesManager().addSpecies(cuAdatom);
        getSpeciesManager().addSpecies(movable);
        
        ((AtomTypeSphere)cuFix.getMoleculeType()).setDiameter(2.5561); 
        ((AtomTypeSphere)cu.getMoleculeType()).setDiameter(2.5561); 
        ((AtomTypeSphere)cuAdatom.getMoleculeType()).setDiameter(2.5561);
        ((AtomTypeSphere)movable.getMoleculeType()).setDiameter(2.5561);
         */
            	
		// Sn
        box.setNMolecules(sn, 216);
        
        potential = new PotentialMEAM(space);
        
        potential.setParameters(sn.getLeafType(), ParameterSetMEAM.Sn);
        potential.setParameters(snAdatom.getLeafType(), ParameterSetMEAM.Sn);
        
        this.potentialMaster.addPotential(potential, new IAtomType[]{sn.getLeafType(), snAdatom.getLeafType()});
		
        /**
        // Cu
        box.setNMolecules(cuFix, 64);
        box.setNMolecules(cu, 128);
        box.setNMolecules(cuAdatom, 0);
        
        potential = new PotentialMEAM(space);
        
        potential.setParameters(cuFix, ParameterSetMEAM.Cu);
        potential.setParameters(cu, ParameterSetMEAM.Cu);
        potential.setParameters(cuAdatom, ParameterSetMEAM.Cu);
        potential.setParameters(movable, ParameterSetMEAM.Cu);
        
        this.potentialMaster.addPotential(potential, new Species[]{cu, cuFix, cuAdatom, movable});
        */
    	
        // Sn box
<<<<<<< EnergyMap.java
        //cmin = 0.8
        //rcut = 3.5
        // a=5.797  a/c=0.5459
        
        double a = 5.9245;
        double c = a*0.54599;
        box.getBoundary().setDimensions(new Vector3D(a*3, a*3, c*6));
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, a, c);
=======
     
        box.getBoundary().setBoxSize(new Vector3D(5.8314*3, 5.8314*3, 3.1815*6));
        PrimitiveTetragonal primitive = new PrimitiveTetragonal(space, 5.8318, 3.1819);
>>>>>>> 1.9
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisBetaSnA5());
        
        /**
        // Cu box
        box.setDimensions(new Vector3D(3.6148*3, 3.6148*4, 3.6148*4));
        PrimitiveCubic primitive = new PrimitiveCubic(space, 3.6148);
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(primitive, new BasisCubicFcc());
        */
        
        Configuration config = new ConfigurationLattice(crystal, space);
        config.initializeCoordinates(box); 

        //ConfigurationFile config2 = new ConfigurationFile("surf252-min");
        //config2.initializeCoordinates(box);
        // Sn
        IMolecule adMolecule = snAdatom.makeMolecule();
        box.addMolecule(adMolecule);
        IAtom adAtom = adMolecule.getChildList().getAtom(0);

        adAtom.getPosition().setX(0, height);
        adAtom.getPosition().setX(1, -1.17228);
        adAtom.getPosition().setX(2, 2.54881);
        
        IVectorMutable newBoxLength = space.makeVector();
        newBoxLength.E(box.getBoundary().getDimensions());
        newBoxLength.setX(0, 35);
        box.getBoundary().setDimensions(newBoxLength);
          

        
        /**
        // Cu
        IAtom iAtom = cuAdatom.getMoleculeFactory().makeAtom();
        box.getAgent(cuAdatom).addChildAtom(iAtom);
        ((IAtomPositioned)iAtom).getPosition().setX(0, 6.3);
        ((IAtomPositioned)iAtom).getPosition().setX(1, -0.8);
        ((IAtomPositioned)iAtom).getPosition().setX(2, -1.2);
        */
         
         /**      
         IVector rij = space.makeVector();
         AtomArrayList movableList = new AtomArrayList();
         AtomSet loopSet = box.getMoleculeList(sn);     
         for (int i=0; i<loopSet.getAtomCount(); i++){
             rij.Ev1Mv2(((IAtomPositioned)iAtom).getPosition(),((IAtomPositioned)loopSet.getAtom(i)).getPosition());
           
             if(rij.squared()<32.49){
                movableList.add(loopSet.getAtom(i));
             } 
         }
        for (int i=0; i<movableList.getAtomCount(); i++){
            ((IAtomPositioned)box.addNewMolecule(movable)).getPosition().E(((IAtomPositioned)movableList.getAtom(i)).getPosition());
            box.removeMolecule(movableList.getAtom(i));
        }
        */
         
		 integratorMAP = new IntegratorEnergyMap(this, lammps, potentialMaster, adAtom, fileTail, space);
		 integratorMAP.setBox(box);
		 integratorMAP.updateLammps();
		 activityIntegrateMAP = new ActivityIntegrate(integratorMAP);
		
		 getController().addAction(activityIntegrateMAP);
       
    }

    public static void main(String[] args){
        double height1 = 10.1099;
        String fileTail1 = ""+height1;
    	final String APP_NAME = "EnergyMapMEAMadatomSn";
    	final EnergyMap sim = new EnergyMap(height1, fileTail1);
    	
    	sim.activityIntegrateMAP.setMaxSteps(1); 
    	
    	SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, sim.space, sim.getController());
    	simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));

    	sim.integratorMAP.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
    	
    	ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());

    	//Sn
    
    	colorScheme.setColor(sim.sn.getLeafType(),java.awt.Color.gray);
        colorScheme.setColor(sim.snAdatom.getLeafType(),java.awt.Color.red);

    	simGraphic.makeAndDisplayFrame(APP_NAME);
    	
    }
    
	static {
		System.loadLibrary("LAMMPS");
    }

}
