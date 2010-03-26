package etomica.lammpslib;

import java.util.ArrayList;

import etomica.action.BoxImposePbc;
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
import etomica.nbr.cell.Cell;
import etomica.nbr.cell.NeighborCellManager;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularPeriodic;
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
	public int num, step, acc, vac;
	public IVectorMutable workVector, lammpsVector;
	public IAtom atomT, atomS;
	public long lammpsSim;
	public RandomNumberGenerator random;
	double bfactor, beta;
	public IMoleculeList moleculeList;
	public XYZWriter writer;
	public HistogramSimple histz1, histz2;
	public ArrayList<Cell> cellVList;
	public IVectorMutable[] neighborPositions;
	private BoxImposePbc pbc;
	public NeighborCellManager neighborCell;

	public SimMCMoveSwapSpeciesGB(int numSpeciesA, int numSpeciesB,
			double temp, IVector boxSize, String infile) {
		super(Space3D.getInstance());

		e1 = 0;
		e0 = 0;
		num = 0;
		step = 0;
		acc = 0;
		vac = 0;
		workVector = space.makeVector();
		lammpsVector = space.makeVector();

		random = new RandomNumberGenerator();

		beta = 1.0/(temp * (8.61734315E-5)); // in 1/(eV/K)

		//INITIALIZE LAMMPS
		lammpsSim = LammpsInterface2.makeLammpsSim("/usr/users/msellers/workspace/sandbox/in.gbmc");

		// SIMULATION BOX
		box = new Box(new BoundaryRectangularPeriodic(space), space);
		addBox(box);
		pbc = new BoxImposePbc(box,space);
		
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

		System.out.println("Number of Tin atoms: "+ box.getMoleculeList(tin).getMoleculeCount());
		System.out.println("Number of Silver atoms: "+ box.getMoleculeList(silver).getMoleculeCount());
		System.out.println("Box Size: " + box.getBoundary().getBoxSize());

		moleculeList = box.getMoleculeList();
		
		neighborCell = new NeighborCellManager(this, box, 7.75, space);
		cellVList = new ArrayList<Cell>();
		
		//Get Lammps Energy
		e0 = getLammpsEnergy(0,false,true);

		neighborCell.assignCellAll();
		
		// XYZ File Output
		writer = new XYZWriter(box);
		writer.setFileName("mcrun-md4.xyz");
		writer.setIsAppend(true);
		writer.actionPerformed();

		// Histograms
		double zextreme = box.getBoundary().getBoxSize().getX(2);
		histz1 = new HistogramSimple(200, new DoubleRange(zextreme, -zextreme));
		histz2 = new HistogramSimple(200, new DoubleRange(zextreme, -zextreme));

		System.out.println(e0);
	}

	public void doMC(int maxsteps) {
		e0 = getLammpsEnergy(0, true, false);
		
		while (step < maxsteps) {

			if(step % 500==0 || vac==0) {				
				MDlammps(20);
				step++;
				continue;
			}
			
			MCsoluteCell();
			
			//MCswapNeighbors();
			
			step++;
		}
		
	}

	public double getLammpsEnergy(int run, boolean setcoords, boolean getcoords) {// in eV
		pbc.actionPerformed();		
		if(setcoords){
			for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
				lammpsVector.E(moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition());
				LammpsInterface2.setAtomPosition(lammpsSim, i,lammpsVector.getX(0), lammpsVector.getX(1), lammpsVector.getX(2));
			}
		}
		
		LammpsInterface2.doLammpsStep(lammpsSim, run);
		
		if(getcoords){
			for (int i = 0; i < moleculeList.getMoleculeCount(); i++) {
				LammpsInterface2.getAtomPosition(lammpsSim, i, lammpsVector);
				moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition().E(lammpsVector);
			}
			// Set new box size
			System.out.println("Old box size: "+box.getBoundary().getBoxSize());
			LammpsInterface2.getBox(lammpsSim, workVector);
			box.getBoundary().setBoxSize(workVector);
			System.out.println("New box size: "+workVector);
			pbc.actionPerformed();
			updateCellVList();
		}
		return LammpsInterface2.getEnergy(lammpsSim);
	}

	public void calcAverages() {
		// XYZ Writer
		if (step % 100 == 0) {
			writer.actionPerformed();
		}

		// Z density of Solute
		for (int i = 0; i < box.getMoleculeList(silver).getMoleculeCount(); i++) {
			histz2.addValue(moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition().getX(2));
		}
		// Z density of Solvent
		for (int i = 0; i < box.getMoleculeList(tin).getMoleculeCount(); i++) {
			histz1.addValue(moleculeList.getMolecule(i).getChildList().getAtom(0).getPosition().getX(2));
		}
	}
	
	public void randomizeSolute(){
		Cell cell1;
		int randCell = 0;
		int [] lidx = new int[3];
		double [] randv = new double[3];
		double [] size = new double[3];
				
		for(int i=0; i<box.getMoleculeList(silver).getMoleculeCount(); i++){
			atomS = box.getMoleculeList(silver).getMolecule(i).getChildList().getAtom(0);
			//Choose random empty cell 
			randCell = random.nextInt(cellVList.size());
			cell1 = cellVList.get(randCell);
			lidx = neighborCell.lattice.latticeIndex(cell1.getLatticeArrayIndex());		
			size = neighborCell.lattice.getCellSize();
			for(int j=0; j<space.D();j++){
				randv[j] = lidx[j]*size[j] - box.getBoundary().getBoxSize().getX(j)/2.0;
				randv[j] = randv[j] + random.nextDouble()*size[j];
				atomS.getPosition().setX(j,randv[j]);
			}
			cellVList.remove(randCell);
		}
	}
	
	public void MDlammps(int mdsteps){
		e0 = getLammpsEnergy(mdsteps, true, true);
	}
	
	public void MCswapNeighbors(){
        double mindist=16;
        atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
        for(int i=0; i<box.getMoleculeList().getMoleculeCount();i++){
                if(atomS.getType()==box.getMoleculeList().getMolecule(i).getChildList().getAtom(0).getType()){continue;}
                if(atomS==box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)){continue;}
                workVector.Ev1Mv2(atomS.getPosition(),box.getMoleculeList().getMolecule(i).getChildList().getAtom(0).getPosition());
                box.getBoundary().nearestImage(workVector);
                if(workVector.squared()<mindist){
                        atomT = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
                        mindist = workVector.squared();
                }
        }
        workVector.E(atomS.getPosition());
        atomS.getPosition().E(atomT.getPosition());
        atomT.getPosition().E(workVector);

        // "Slide" Atoms
        //workVector.Ev1Mv2(atom[0].getPosition(), atom[1].getPosition());
        //workVector.normalize();
       // workVector.Ea1Tv1(0.9, workVector);
        //atom[0].getPosition().PE(workVector);
        //atom[1].getPosition().PE(workVector);

        if(checkMove()){System.out.println(step+" A - SwapNeighbors   "+e0+"   "+e1+"   "+bfactor); return;}
                else{
                    System.out.println(step+" R - SwapNeighbors   "+e0+"   "+e1+"   "+bfactor);
                        // Swap atoms back
                    	//atom[0].getPosition().ME(workVector);
                        //atom[1].getPosition().ME(workVector);
                        
                        workVector.E(atomS.getPosition());
                        atomS.getPosition().E(atomT.getPosition());
                        atomT.getPosition().E(workVector);
        }
    }
		
	public void MCsoluteCell(){
		Cell cell1;
		Cell cell0;
		int randCell;
		int [] lidx = new int[3];
		double [] size = new double[3];
		IVectorMutable rij = space.makeVector();
		IVectorMutable randv = space.makeVector();
		
		//Choose random atom
		atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
		workVector.E(atomS.getPosition());
		cell0 = neighborCell.getCell(atomS);
				
		//Catch 1
		if(cell0.occupants().getAtomCount()>1){return;}
		
		//CHOOSE RANDOM EMPTY CELL
		randCell = random.nextInt(cellVList.size());
		cell1 = cellVList.get(randCell);
		lidx = neighborCell.lattice.latticeIndex(cell1.getLatticeArrayIndex());		
		size = neighborCell.lattice.getCellSize();
		
		//System.out.println("Cell #: "+cell1.getLatticeArrayIndex());
		//System.out.println("Cell size: "+size[0]+"   "+size[1]+"   "+size[2]);
		//System.out.println("Cell lattice index: "+lidx[0]+"   "+lidx[1]+"   "+lidx[2]);
		
		//SEARCH FOR POINT WITH 5 OR MORE NEIGHBORS WITHIN 2.6 ANGRSTROMS
		int trials=0;
		int count1=0;
		IAtom nb;
		IVectorMutable navg = space.makeVector();
		double ncut=2.6;
		while(true){
			//Choose random point in cell
			for(int i=0; i<space.D();i++){
				randv.setX(i,lidx[i]*size[i]-0.5*(box.getBoundary().getBoxSize().getX(i)-size[i]));		
				randv.setX(i,randv.getX(i)+0.5*(2.0*random.nextDouble()-1.0)*size[i]);
			}
			//Find nearest neighbors
			navg.TE(0.0);
			for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
				nb = box.getMoleculeList().getMolecule(j).getChildList().getAtom(0);
				if(nb==atomS){continue;}
				rij.Ev1Mv2(randv,nb.getPosition());
				if(rij.squared()<ncut*ncut){
					navg.PE(nb.getPosition());
					count1++;
					System.out.println("Found neighbor: "+count1);
					if(count1>4){break;}
				}
			}
			//Catch 2
			if(count1>4){break;}
			if(count1<5){System.out.println("Not enough neighbors. Trial  "+trials);trials++;continue;}
			if(trials>10){return;}
		}
		//CENTER OF NEIGHBORS
		navg.TE(1.0/count1);

		//PICK RANDOM POSITION WITHIN 0.08 ANGRSTROMS
		for(int i=0; i<space.D();i++){
			navg.setX(i,navg.getX(i)*(1.0+(0.08*random.nextDouble())));
		}
		//MOVE ATOM S
		atomS.getPosition().E(navg);
		
		//CONTRACT AND EXPAND LATTICE AT OLD AND NEW POINTS
		double b=1.8;
		double xm=3.0;				
		double rmag;
		IAtom neighbor;
		int exp=0;
		int comp=0;
		
		//Compress atoms near old interstitial
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			if(atomS==neighbor){continue;}
			rij.Ev1Mv2(neighbor.getPosition(),workVector);
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();	
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				//compression of site
				neighbor.getPosition().Ea1Tv1((rmag-b)/(1.0-(b/xm))/rmag, rij);
				neighbor.getPosition().PE(workVector);
				System.out.println(rmag+" --> "+((rmag-b)/(1.0-(b/xm)))+"   deltaE: "+getLammpsEnergy(0,true,false));
				comp++;
			}	
		}
		//Expand atoms near new interstitial
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			if(atomS==neighbor){continue;}
			rij.Ev1Mv2(neighbor.getPosition(),atomS.getPosition());
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();	
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				//expansion of site
				neighbor.getPosition().Ea1Tv1(((-b/xm)*rmag+rmag+b)/rmag, rij);
				neighbor.getPosition().PE(atomS.getPosition());
				System.out.println(rmag+" --> "+((-b/xm)*rmag+rmag+b)+"   E: "+getLammpsEnergy(0,true,false));
				exp++;
			}
		}
		System.out.println("Expanded: "+exp+"   Compressed: "+comp);
		
		//CHECK ACCEPTANCE
		if(checkMove()){
			cellVList.remove(randCell);
			cellVList.add(cell0);
			System.out.println(step+" A "+e0+"   "+bfactor);
			return;
		}
		else{
			System.out.println(step+" R "+e0+"   "+e1+"   "+bfactor);
			//Compress atoms near new interstitial
			for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
				neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
				if(atomS==neighbor){continue;}
				rij.Ev1Mv2(neighbor.getPosition(),atomS.getPosition());
				box.getBoundary().nearestImage(rij);
				rmag = rij.squared();	
				if(rmag<(xm*xm)){
					rmag = Math.sqrt(rmag);
					//compression of old site
					neighbor.getPosition().Ea1Tv1((rmag-b)/(1.0-(b/xm))/rmag, rij);
					neighbor.getPosition().PE(atomS.getPosition());
					System.out.println(rmag+" --> "+((rmag-b)/(1.0-(b/xm)))+"   deltaE: "+getLammpsEnergy(0,true,false));
					comp++;
				}
			}
			//Move atom back
			atomS.getPosition().E(workVector);
			//Expand atoms near old interstitial
			for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
				neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
				if(atomS==neighbor){continue;}
				rij.Ev1Mv2(neighbor.getPosition(),atomS.getPosition());
				box.getBoundary().nearestImage(rij);
				rmag = rij.squared();	
				if(rmag<(xm*xm)){
					rmag = Math.sqrt(rmag);
					//expansion of new site
					neighbor.getPosition().Ea1Tv1(((-b/xm)*rmag+rmag+b)/rmag, rij);
					neighbor.getPosition().PE(atomS.getPosition());
					System.out.println(rmag+" --> "+((-b/xm)*rmag+rmag+b)+"   E: "+getLammpsEnergy(0,true,false));
					exp++;
				}
			}

			System.out.println("Energy (should match E0): "+getLammpsEnergy(0,true,false));			
			return;
		}
		
	}
	
	public void updateCellVList(){
		cellVList.clear();
		neighborCell.assignCellAll();
		Object[] allCells = neighborCell.lattice.sites();
        for (int i=0; i<allCells.length; i++) {
            if(((Cell)allCells[i]).occupants().getAtomCount()==0){
            	cellVList.add((Cell)allCells[i]);
            	//System.out.println("Vacant cell "+i);
            }
        }
        vac = cellVList.size();
        System.out.println("Cells with vacancies: "+vac);
        System.out.println("Neighbor cell size: "+neighborCell.lattice.getCellSize()[0]);
	}
	
	public boolean checkMove(){
		// Check acceptance criteria
		e1 = getLammpsEnergy(0, true, false);
		bfactor = Math.exp(-beta * (e1 - e0));
		if (bfactor > 1.0 || random.nextDouble() < bfactor) {// Accepted
			e0 = e1;
			acc++;
			return true;
		} else {// Rejected
			return false;
		}
	}
	
	public void reset() {
		step = 0;
		histz1.reset();
		histz2.reset();
	}

	public static void main(String[] args){
    	// Simulation Steps
    	int steps = 10000;
    	// Atoms Numbers
    	int tin = 4788;
    	int silver = 100;
    	// Box
    	Vector3D boxVector = new Vector3D(2.0*17.76305,2.0*17.550016608,2.0*54.62403960); 
    	// Temperature
    	double temp1 = 300;
    	// Lammps infile
    	String infile = "/home/msellers/workspace/sandbox/in.gbmc";
        final String APP_NAME = "SimMCMoveSwapSpeciesGB";
        final SimMCMoveSwapSpeciesGB sim = new SimMCMoveSwapSpeciesGB(tin,silver,temp1,boxVector,infile);        
        
        // Disperse Solute
        //sim.randomizeSolute();
        // Equilibrate
        sim.getLammpsEnergy(100, true, true);
        sim.doMC(1000000);
        //sim.getLammpsEnergy(20000);
             
        // Run Simulation
        //sim.doMCSwap(steps);
        
        WriteConfiguration writer = new WriteConfiguration(sim.getSpace());
	    writer.setBox(sim.box);
	    writer.setConfName("201ag-"+steps);
	    //writer.actionPerformed();
	    
	    //Output Averages
	    System.out.println("******************** MC Stats ***********************\n");
	    System.out.println("Number of accepted moves: "+sim.acc);
	    System.out.println("Number of steps: "+sim.step);
	    System.out.println("Acceptance percentage: "+(double)sim.acc/sim.step);
	    
	    System.out.println("************** Solute Z Histogram Data **************\n");
	    System.out.println(sim.histz2.getXRange());
	    for(int i=0; i<sim.histz2.getNBins(); i++){
	    //	System.out.println(sim.histz2.getHistogram()[i]);
	    }
	    System.out.println();
	    System.out.println("************** Solvent Z Histogram Data **************\n");
	    System.out.println(sim.histz1.getXRange());
	    for(int i=0; i<sim.histz1.getNBins(); i++){
	    //	System.out.println(sim.histz1.getHistogram()[i]);
	    }
	  
    }

	static {
		System.loadLibrary("LAMMPS");
		// System.loadLibrary("lmp_thomas");
	}
}
