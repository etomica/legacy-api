package etomica.lammpslib;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import etomica.action.activity.ActivityIntegrate;
import etomica.api.IAtomType;
import etomica.api.IVector;
import etomica.atom.AtomTypeSphere;
import etomica.box.Box;
import etomica.config.ConfigurationFile;
import etomica.dimer.CoordinationViewerSim;
import etomica.graphics.ColorScheme;
import etomica.graphics.ColorSchemeCoordination;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorMC;
import etomica.nbr.list.PotentialMasterList;
import etomica.potential.P2HardSphere;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularSlit;
import etomica.space.ISpace;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.Species;
import etomica.species.SpeciesSpheresMono;

public class CoordinationViewerSim extends Simulation{

		public CoordinationViewerSim(ISpace space, String posFile, IVector boxVector) {
		super(space);
		
		int numAtoms=0;
		
		Box box = new Box(new BoundaryRectangularSlit(2, 5, space), space);
		box.getBoundary().setDimensions(boxVector);
		
		addBox(box);
		
		Species species = new SpeciesSpheresMono(this, space);
		((AtomTypeSphere)species.getAtomType(0)).setDiameter(3.022);
		getSpeciesManager().addSpecies(species);
		
		try{
			FileReader fileReader = new FileReader(posFile+".pos");
			BufferedReader buffReader = new BufferedReader(fileReader);
			while(buffReader.readLine()!=null){
				numAtoms++;
			}
			buffReader.close();
			
		}catch(IOException e){throw new RuntimeException(e);}
			
		box.setNMolecules(species, numAtoms);
		
		IntegratorMC integrator = new IntegratorMC(this, null);
		integrator.setBox(box);
		ActivityIntegrate activityIntegrator = new ActivityIntegrate(integrator);
		getController().addAction(activityIntegrator);
		
		ConfigurationFile config = new ConfigurationFile(posFile);
		config.initializeCoordinates(box);
	}

	public static void main(String[] args){
		double x = Double.parseDouble(args[1]);
		double y = Double.parseDouble(args[2]);
		double z = Double.parseDouble(args[3]);
		IVector boxVector = new Vector3D(x,y,z);
		
		CoordinationViewerSim sim = new CoordinationViewerSim(Space3D.getInstance(), args[0], boxVector);
		SimulationGraphic simGraphic = new SimulationGraphic(sim, sim.getSpace(), sim.getController());
		PotentialMasterList potentialMaster = new PotentialMasterList(sim, 3.2, sim.getSpace());
		P2HardSphere potential = new P2HardSphere(sim.getSpace());
		potentialMaster.addPotential(potential, new IAtomType[] {sim.getSpeciesManager().getSpecies(0).getAtomType(0),sim.getSpeciesManager().getSpecies(0).getAtomType(0)});
		
		potentialMaster.getNeighborManager(sim.getBox(0)).reset();
		
		
		ColorScheme colorScheme = new ColorSchemeCoordination(sim, potentialMaster, sim.getBox(0));
		simGraphic.getDisplayBox(sim.getBox(0)).setColorScheme(colorScheme);
		simGraphic.makeAndDisplayFrame();
		
	}
}
