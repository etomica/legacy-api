package etomica.lammpslib;

import etomica.action.WriteConfiguration;
import etomica.action.XYZWriter;
import etomica.api.IAtom;
import etomica.api.IAtomTypeSphere;
import etomica.api.IBox;
import etomica.api.IMoleculeList;
import etomica.api.IVector;
import etomica.api.IVectorMutable;
import etomica.box.Box;
import etomica.chem.elements.Silver;
import etomica.chem.elements.Tin;
import etomica.config.ConfigurationFile;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularSlit;
import etomica.space3d.Space3D;
import etomica.space3d.Vector3D;
import etomica.species.SpeciesSpheresMono;
import etomica.util.DoubleRange;
import etomica.util.HistogramSimple;
import etomica.util.RandomNumberGenerator;

/**
 * 
 * @author msellers
 * 
 */

public class SimMCMoveSwapSpeciesGB extends Simulation {

	private static final long serialVersionUID = 1L;
	private static final String APP_NAME = "MCMoveSwapSpeciesGB";
	public IBox box;
	public SpeciesSpheresMono tin, silver;
	public double e0, e1;
	public int num, step, maxsteps;
	public IVectorMutable workVector, lammpsVector;
	public IAtom atomT, atomS;
	public long lammpsSim;
	public RandomNumberGenerator random;
	double bfactor, beta;
	public IMoleculeList moleculeList;
	public XYZWriter writer;
	public HistogramSimple histz;

	public SimMCMoveSwapSpeciesGB(int steps, int numSpeciesA, int numSpeciesB,
			double temp, IVector boxSize, String infile) {
		super(Space3D.getInstance());

		e1 = 0;
		e0 = 0;
		num = 0;
		step = 0;
		maxsteps = steps;
		workVector = space.makeVector();
		lammpsVector = space.makeVector();

		random = new RandomNumberGenerator();

		beta = temp * (8.61734315E-5); // in eV/K

		// Initialize Lammps Simulation
		lammpsSim = LammpsInterface2
				.makeLammpsSim("/home/msellers/workspace/sandbox/in.gbmc");

		// SIMULATION BOX
		box = new Box(new BoundaryRectangularSlit(2, 5, space), space);
		addBox(box);

		// SPECIES
		tin = new SpeciesSpheresMono(space, Tin.INSTANCE);
		silver = new SpeciesSpheresMono(space, Silver.INSTANCE);
		tin.setIsDynamic(true);
		silver.setIsDynamic(true);
		addSpecies(tin);
		addSpecies(silver);
		((IAtomTypeSphere) tin.getLeafType()).setDiameter(3.044);
		((IAtomTypeSphere) silver.getLeafType()).setDiameter(2.8895);

		box.setNMolecules(tin, numSpeciesA);
		box.setNMolecules(silver, numSpeciesB);

		box.getBoundary().setBoxSize(boxSize);

		System.out.println("Number of Tin atoms: "
				+ box.getMoleculeList(tin).getMoleculeCount());
		System.out.println("Number of Silver atoms: "
				+ box.getMoleculeList(silver).getMoleculeCount());
		System.out.println("Box Size: " + box.getBoundary().getBoxSize());

		// ConfigurationFile config = new ConfigurationFile("equil");
		// config.initializeCoordinates(box);

		moleculeList = box.getMoleculeList();

		// Get Lammps Coordinates
		for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
			LammpsInterface2.getAtomPosition(lammpsSim, i, lammpsVector);
			moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition()
					.E(lammpsVector);
		}

		// XYZ File Output
		writer = new XYZWriter(box);
		writer.setFileName("mcrun-md.xyz");
		writer.setIsAppend(true);
		writer.actionPerformed();

		// Histograms
		double zextreme = box.getBoundary().getBoxSize().getX(2);
		histz = new HistogramSimple(100, new DoubleRange(zextreme, -zextreme));

		e0 = getLammpsEnergy();
		System.out.println(e0);
	}

	public void doMCSwap() {

		while (step < maxsteps) {
			// Pick random silver atom
			num = random
					.nextInt(box.getMoleculeList(silver).getMoleculeCount());
			atomS = box.getMoleculeList(silver).getMolecule(num).getChildList()
					.getAtom(0);
			workVector.E(atomS.getPosition());

			// Pick random tin atom
			num = random.nextInt(box.getMoleculeList(tin).getMoleculeCount());
			atomT = box.getMoleculeList(tin).getMolecule(num).getChildList()
					.getAtom(0);

			// Swap atoms
			// System.out.println(workVector);
			// System.out.println(atomT.getPosition());
			atomS.getPosition().E(atomT.getPosition());
			atomT.getPosition().E(workVector);

			// Calculate system energy and boltzmann factor
			e1 = getLammpsEnergy();
			bfactor = Math.exp(-beta * (e1 - e0));

			// Check acceptance criteria
			if (bfactor > 1.0 || random.nextDouble() < bfactor) {// Accepted
				e0 = e1;
				// System.out.println(step+"  Accepted.   E="+e1+"   BF="+bfactor);
			} else {// Rejected
				// Swap atoms back
				atomT.getPosition().E(atomS.getPosition());
				atomS.getPosition().E(workVector);
				// System.out.println(step+"  Rejected.   E1="+e1+"   BF="+bfactor);
			}
			
			if(step%10==0){System.out.println(step+"    "+e0);}
			
			calcAverages();
			if (step > 2000 && step % 50 == 0) {doLammpsMD(801);}
			step++;
		}
		
		doLammpsMD(100000);
	}

	public double getLammpsEnergy() {// in eV

		for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
			lammpsVector.E(moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition());
			LammpsInterface2.setAtomPosition(lammpsSim, i,lammpsVector.getX(0), lammpsVector.getX(1), lammpsVector.getX(2));
		}

		/*
		 * lammpsVector.E(atomT.getPosition());
		 * LammpsInterface2.setAtomPosition(lammpsSim, atomT.getLeafIndex(),
		 * lammpsVector.getX(0), lammpsVector.getX(1), lammpsVector.getX(2));
		 * 
		 * lammpsVector.E(atomS.getPosition());
		 * LammpsInterface2.setAtomPosition(lammpsSim, atomS.getLeafIndex(),
		 * lammpsVector.getX(0), lammpsVector.getX(1), lammpsVector.getX(2));
		 */
		LammpsInterface2.doLammpsStep(lammpsSim, 0);
		return LammpsInterface2.getEnergy(lammpsSim);

	}

	public void doLammpsMD(int mdsteps) {
		// Put coords
		for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
			lammpsVector.E(moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition());
			LammpsInterface2.setAtomPosition(lammpsSim, i,lammpsVector.getX(0), lammpsVector.getX(1), lammpsVector.getX(2));
		}
		System.out.println("Equilibrating with MD...");
		LammpsInterface2.doLammpsStep(lammpsSim, mdsteps);
		//Grab energy of latest configuration
		e0 = LammpsInterface2.getEnergy(lammpsSim);
		
		// Get coords
		for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
			LammpsInterface2.getAtomPosition(lammpsSim, i, lammpsVector);
			moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition().E(lammpsVector);
		}
	}

	public void calcAverages() {
		// XYZ Writer
		if (step % 50 == 0) {
			writer.actionPerformed();
		}

		// Z density
		for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
			histz.addValue(moleculeList.getMolecule(i).getChildList()
					.getAtom(0).getPosition().getX(2));
		}
	}

	public void reset() {
		step = 0;
		histz.reset();
	}

	public static void main(String[] args){
    	// Simulation Steps
    	int steps = 4000;
    	// Atoms Numbers
    	int tin = 4598;
    	int silver = 190;
    	// Box
    	Vector3D boxVector = new Vector3D(2.5*17.76305,2.5*17.550016608,2.5*54.62403960); 
    	// Temperature
    	double temp1 = 300;
    	// Lammps infile
    	String infile = "/home/msellers/workspace/sandbox/in.gbmc";
        final String APP_NAME = "SimMCMoveSwapSpeciesGB";
        
        final SimMCMoveSwapSpeciesGB sim = new SimMCMoveSwapSpeciesGB(steps,tin,silver,temp1,boxVector,infile);        
        
        // Run Simulation
        sim.doMCSwap();
        
        WriteConfiguration writer = new WriteConfiguration(sim.getSpace());
	    writer.setBox(sim.box);
	    writer.setConfName("201ag-"+steps);
	    writer.actionPerformed();
	    
	    //Output Averages
	    System.out.println("************** Z Histogram Data **************\n");
	    for(int i=0; i<sim.histz.getNBins(); i++){
	    	System.out.println(sim.histz.getHistogram()[i]);
	    }
	  
    }

	static {
		System.loadLibrary("LAMMPS");
		// System.loadLibrary("lmp_thomas");
	}
}
