package etomica.lammpslib;

import etomica.action.BoxImposePbc;
import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtomType;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.ISpecies;
import etomica.api.IVectorMutable;
import etomica.box.Box;
import etomica.chem.elements.Tin;
import etomica.config.GrainBoundaryTiltConfiguration;
import etomica.data.AccumulatorAverageCollapsing;
import etomica.data.AccumulatorHistory;
import etomica.data.DataPump;
import etomica.data.AccumulatorAverage.StatType;
import etomica.data.meter.MeterPotentialEnergy;
import etomica.dimer.IntegratorDimerRT;
import etomica.dimer.SimDimerLJgb;
import etomica.graphics.ColorSchemeByType;
import etomica.graphics.DisplayBox;
import etomica.graphics.DisplayPlot;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.lattice.BravaisLatticeCrystal;
import etomica.lattice.crystal.BasisCubicFcc;
import etomica.lattice.crystal.PrimitiveCubic;
import etomica.listener.IntegratorListenerAction;
import etomica.potential.P2LennardJones;
import etomica.potential.PotentialMaster;
import etomica.potential.PotentialMasterMonatomic;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularSlit;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;
import etomica.util.HistoryCollapsingAverage;

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimDimerLJgb extends Simulation{

    private static final long serialVersionUID = 1L;
    private static final String APP_NAME = "DimerLJgb";
    public final PotentialMaster potentialMaster;
    public IntegratorVelocityVerlet integratorMD;
    public IntegratorDimerRT integratorDimer;
    public IBox box;
    public IVectorMutable [] saddle;
    public SpeciesSpheresMono fixed, movable;
    public P2LennardJones potential;

    public ActivityIntegrate activityIntegrateMD, activityIntegrateDimer;
    
    
    
    public SimDimerLJgb() {
<<<<<<< SimDimerLJgb.java
    	super(Space3D.getInstance(), true);
    	potentialMaster = new PotentialMasterMonatomic(this);
=======
    	super(Space3D.getInstance());
    	potentialMaster = new PotentialMasterMonatomic(this);
>>>>>>> 1.21
    	
    //SIMULATION BOX
        box = new Box(new BoundaryRectangularSlit(2, 5, space), space);
        addBox(box);
        
        BoxImposePbc imposePbc = new BoxImposePbc(box, space);
        
    // INTEGRATOR - MD
    	integratorMD = new IntegratorVelocityVerlet(this, potentialMaster, space);
    	integratorMD.setTimeStep(0.01);
    	integratorMD.setTemperature(0.1);
    	integratorMD.setThermostatInterval(100);
    	integratorMD.setIsothermal(true);
    	integratorMD.setBox(box);
    	activityIntegrateMD = new ActivityIntegrate(integratorMD);
    	integratorMD.getEventManager().addListener(new IntegratorListenerAction(imposePbc));
    	
    //SPECIES
    	double sigma = 1.0;
    	Tin tinFixed = new Tin("SnFixed", Double.POSITIVE_INFINITY);
    	fixed = new SpeciesSpheresMono(space, tinFixed);
    	fixed.setIsDynamic(true);
        movable = new SpeciesSpheresMono(this, space);
        movable.setIsDynamic(true);
        addSpecies(fixed);
        addSpecies(movable);
        ((IAtomTypeSphere)fixed.getLeafType()).setDiameter(sigma);
        ((IAtomTypeSphere)movable.getLeafType()).setDiameter(sigma);
    	
        // Must be in same order as the respective species is added to SpeciesManager
        //box.setNMolecules(fixed, 256);    	
    	
    	
    	
    	potential = new P2LennardJones(space, sigma, 1.0);
		potentialMaster.addPotential(potential, new IAtomType[]{fixed.getLeafType(), fixed.getLeafType()});
		potentialMaster.addPotential(potential, new IAtomType[]{movable.getLeafType(), fixed.getLeafType()});
		potentialMaster.addPotential(potential, new IAtomType[]{movable.getLeafType(), movable.getLeafType()});
        
    	
	 //CRYSTAL
    	box.getBoundary().setBoxSize(new Vector3D(Math.sqrt(5)*4,Math.pow(4, 1.0/3.0)*4,Math.pow(4, 1.0/3.0)*8));
        BravaisLatticeCrystal crystal = new BravaisLatticeCrystal(new PrimitiveCubic(space, Math.pow(4, 1.0/3.0)),new BasisCubicFcc());
        GrainBoundaryTiltConfiguration gbtilt = new GrainBoundaryTiltConfiguration(crystal, crystal, new ISpecies[] {fixed, movable}, 2.5, space);
        //gbtilt.setRotation(2, 45*Math.PI/180);
        gbtilt.setRotationTOP(1, 63.434948829*Math.PI/180);
        gbtilt.setRotationBOTTOM(1, 63.434948829*Math.PI/180);
        
        gbtilt.setMobileSpecies(movable);
        gbtilt.setFixedSpecies(fixed);
        gbtilt.initializeCoordinates(box);

      //INTEGRATOR - Dimer
        integratorDimer = new IntegratorDimerRT(this, 0, potentialMaster, new ISpecies[]{movable}, space);
        integratorDimer.setBox(box);
        integratorDimer.setOrtho(false, false);
        integratorDimer.setFileName("lj");
        activityIntegrateDimer = new ActivityIntegrate(integratorDimer);
        integratorDimer.setActivityIntegrate(activityIntegrateDimer);

    //ADD CONTROLLER ACTIONS
    	getController().addAction(activityIntegrateMD);
    	getController().addAction(activityIntegrateDimer);
    	
        //Set movable atoms
        /** 
        IVector rij = space.makeVector();
        AtomArrayList movableList = new AtomArrayList();
        AtomSet loopSet = box.getMoleculeList(cu);
        
        for (int i=0; i<loopSet.getAtomCount(); i++){
            rij.Ev1Mv2(((IAtomPositioned)iAtom).getPosition(),((IAtomPositioned)loopSet.getAtom(i)).getPosition());  
            if(rij.squared()<21.0){
               movableList.add(loopSet.getAtom(i));
            } 
        }
       for (int i=0; i<movableList.getAtomCount(); i++){
           ((IAtomPositioned)box.addNewMolecule(movable)).getPosition().E(((IAtomPositioned)movableList.getAtom(i)).getPosition());
           box.removeMolecule(movableList.getAtom(i));
       }
       */
    }

    public static void main(String[] args){
    	final SimDimerLJgb sim = new SimDimerLJgb();

    	sim.activityIntegrateMD.setMaxSteps(1000);
    	sim.activityIntegrateDimer.setMaxSteps(0);
    	    	
        MeterPotentialEnergy energyMeter = new MeterPotentialEnergy(sim.potentialMaster);
        energyMeter.setBox(sim.box);
        
        AccumulatorHistory energyAccumulator = new AccumulatorHistory(new HistoryCollapsingAverage());
        AccumulatorAverageCollapsing accumulatorAveragePE = new AccumulatorAverageCollapsing();
        
        DataPump energyPump = new DataPump(energyMeter,accumulatorAveragePE);       
        accumulatorAveragePE.addDataSink(energyAccumulator, new StatType[]{StatType.MOST_RECENT});
        
        DisplayPlot plotPE = new DisplayPlot();
        plotPE.setLabel("PE Plot");
        
        energyAccumulator.setDataSink(plotPE.getDataSet().makeDataSink());
        accumulatorAveragePE.setPushInterval(1);      
    	
    	SimulationGraphic simGraphic = new SimulationGraphic(sim, SimulationGraphic.TABBED_PANE, APP_NAME, sim.space, sim.getController());
    	simGraphic.getController().getReinitButton().setPostAction(simGraphic.getPaintAction(sim.box));

        simGraphic.add(plotPE);
<<<<<<< SimDimerLJgb.java
    	 sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(energyPump));
        sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
        sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(energyPump));
    	sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
=======
    	
        sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(energyPump));
        sim.integratorMD.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
        
        sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(energyPump));
    	sim.integratorDimer.getEventManager().addListener(new IntegratorListenerAction(simGraphic.getPaintAction(sim.box)));
>>>>>>> 1.21
    	//sim.integratorDimerMin.addIntervalAction(simGraphic.getPaintAction(sim.box));
    	
    	ColorSchemeByType colorScheme = ((ColorSchemeByType)((DisplayBox)simGraphic.displayList().getFirst()).getColorScheme());

    	colorScheme.setColor(sim.fixed.getLeafType(),java.awt.Color.blue);
        colorScheme.setColor(sim.movable.getLeafType(),java.awt.Color.PINK);
    	
        simGraphic.makeAndDisplayFrame(APP_NAME);
    }

}
