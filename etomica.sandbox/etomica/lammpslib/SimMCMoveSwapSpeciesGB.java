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
import etomica.config.ConfigurationFile;
import etomica.nbr.cell.Cell;
import etomica.nbr.cell.NeighborCellManager;
import etomica.simulation.Simulation;
import etomica.space.BoundaryRectangularPeriodic;
import etomica.space.IVectorRandom;
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
	public double e0, e1, erej, esys;
	public int num, step, acc, rej, vac;
	public IVectorMutable workVector, lammpsVector, boxVector;
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
		erej = 0;
		esys = 0;
		num = 0;
		step = 0;
		acc = 0;
		rej = 0;
		vac = 0;
		workVector = space.makeVector();
		lammpsVector = space.makeVector();
		boxVector = space.makeVector();

		random = new RandomNumberGenerator();

		beta = 1.0/(temp * (8.61734315E-5)); // in 1/(eV/K)

		//INITIALIZE LAMMPS
		lammpsSim = LammpsInterface2.makeLammpsSim(infile);

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
		
		neighborCell = new NeighborCellManager(this, box, 6.0, space);
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
			
			//MCsoluteRelaxCell();
			MDlammps(10);
			MCswapPotential2LJ();
			
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
			LammpsInterface2.getBox(lammpsSim, boxVector);
			box.getBoundary().setBoxSize(boxVector);
			System.out.println("New box size: "+boxVector);
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
			for(int j=0; j<3;j++){
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
	
	public void MCswapPotential2LJ(){
				
		LammpsInterface2.doCommand(lammpsSim, "pair_style hybrid meam lj/cut 4.2");
		LammpsInterface2.doCommand(lammpsSim, "pair_coeff * * meam library.meam Ag Sn12 Ag3Sn.meam Ag Sn12");
		LammpsInterface2.doCommand(lammpsSim, "pair_coeff 1 2 lj/cut 0.772 2.532");
		
		if(checkMove()){
			LammpsInterface2.doCommand(lammpsSim, "pair_style meam");
    		LammpsInterface2.doCommand(lammpsSim, "pair_coeff * * library.meam Ag Sn12 Ag3Sn.meam Ag Sn12");
			System.out.println(step+" A - SwapNeighbors   "+e0+"   "+e1+"   "+bfactor); 
			return;
		}
		
        else{
            System.out.println(step+" R - SwapNeighbors   "+e0+"   "+e1+"   "+bfactor);
            LammpsInterface2.doCommand(lammpsSim, "pair_style meam");
    		LammpsInterface2.doCommand(lammpsSim, "pair_coeff * * library.meam Ag Sn12 Ag3Sn.meam Ag Sn12");
        }		
		
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

	public void MCsoluteRelaxCell(){
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
		
		//SEARCH FOR POINT WITH 5 OR MORE NEIGHBORS WITHIN 2.8 ANGRSTROMS
		int trials=0;
		int count1=0;
		IAtom nb;
		IVectorMutable navg = space.makeVector();
		double ncut=2.8;
		double cellspot = 0.0;
		while(true){
			
			for(int i=0; i<3;i++){
				//Choose cell corner
				cellspot = lidx[i]*size[i]-0.5*box.getBoundary().getBoxSize().getX(i);
				//Choose random point in cell
				cellspot += random.nextDouble()*size[i];
				randv.setX(i,cellspot);
			}
			box.getBoundary().nearestImage(randv);
			//Find nearest neighbors
			count1=0;
			
			double avx=0;
			double avy=0;
			double avz=0;
			
			for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
				nb = box.getMoleculeList().getMolecule(j).getChildList().getAtom(0);
				if(nb==atomS){continue;}
				rij.Ev1Mv2(randv,nb.getPosition());
				box.getBoundary().nearestImage(rij);
				if(rij.squared()<(ncut*ncut)){
					avx += nb.getPosition().getX(0);
					avy += nb.getPosition().getX(1);
					avz += nb.getPosition().getX(2);
					count1++;
					//System.out.println("Found neighbor: "+count1);
				}
			}
			//Catch 2
			if(count1>4){
				navg.setX(0,avx/count1);
				navg.setX(1,avy/count1);
				navg.setX(2,avz/count1);
				break;
			}
			if(count1<5 && trials<11){
				//System.out.println("Not enough neighbors. Trial  "+trials);
				trials++;
				continue;
			}
			if(trials>10){return;}
		}
		
		//CENTER OF NEIGHBORS
		box.getBoundary().nearestImage(navg);
		//System.out.println("Count is: "+count1);
		//System.out.println("Neighbor Number: "+count1);
		//System.out.println("RandomVec: "+randv);
		//System.out.println("Neighbor Center: "+navg);
		rij.Ev1Mv2(randv,navg);
		box.getBoundary().nearestImage(rij);
		//System.out.println("Distance between Rand and Neigh: "+Math.sqrt(rij.squared()));
		//System.out.println("Neighbor Center: "+navg);

		//PICK RANDOM POSITION WITHIN 0.15 ANGRSTROMS OF NEIGHBOR CENTER
		
		//MOVE ATOM S
		atomS.getPosition().E(navg);
		//System.out.println("System Energy (N-avg): "+getLammpsEnergy(0,true,false));
		IVectorRandom randomvec = (IVectorRandom)space.makeVector();
		randomvec.setRandomInSphere(random);
		randomvec.TE(0.15);
		//System.out.println("Random Vector Length: "+Math.sqrt(randomvec.squared()));
		navg.PE(randomvec);
		//System.out.println("Random Center: "+navg);
		
		//MOVE ATOM S
		//atomS.getPosition().E(navg);
		//System.out.println("System Energy (N-avg+R: "+getLammpsEnergy(0,true,false));

		//CONTRACT AND EXPAND LATTICE AT OLD AND NEW POINTS
		double xm=2.85;
		double b=1.66;
		double rmag;
		IAtom neighbor;
		int exp=0;
		int comp=0;
		//System.out.println("Interstitial Move Energy: "+getLammpsEnergy(0,true,false));
		
		//Compress atoms near old interstitial
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			rij.Ev1Mv2(neighbor.getPosition(),workVector);
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();	
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				//compression of site
				neighbor.getPosition().Ea1Tv1((rmag-b)/(1.0-(b/xm))/rmag, rij);
				neighbor.getPosition().PE(workVector);
				//System.out.println("Compress "+rmag+" --> "+((rmag-b)/(1.0-(b/xm)))+" E: "+getLammpsEnergy(0,true,false));
				comp++;
			}	
		}
		//System.out.println("----------------------");
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
				//System.out.println("Expand "+rmag+" --> "+((-b/xm)*rmag+rmag+b)+" E: "+getLammpsEnergy(0,true,false));
				exp++;
			}
		}
		//System.out.println("Expanded: "+exp+"   Compressed: "+comp);
		
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
					//System.out.println(rmag+" --> "+((rmag-b)/(1.0-(b/xm)))+"   deltaE: "+getLammpsEnergy(0,true,false));
					comp++;
				}
			}
			//System.out.println("-----------------------------");
			
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
					//System.out.println(rmag+" --> "+((-b/xm)*rmag+rmag+b)+"   E: "+getLammpsEnergy(0,true,false));
					exp++;
				}
			}
		}

		//System.out.println("Energy (should match E0): "+getLammpsEnergy(0,true,false));			
		return;		
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
			esys +=e0;
			erej +=e1;
			rej++;
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
    	int tin = 1152;
    	int silver = 1;
    	
    	// Box
    	Vector3D boxVector = new Vector3D(2.0*17.76305,2.0*17.550016608,2.0*54.62403960); 
    	// Temperature
    	double temp1 = 300;
    	// Lammps infile
    	String infile = "/usr/users/msellers/simulation/meam/Cu-Sn/in.aglj";
        final String APP_NAME = "SimMCMoveSwapSpeciesGB";
        final SimMCMoveSwapSpeciesGB sim = new SimMCMoveSwapSpeciesGB(tin,silver,temp1,boxVector,infile);        
        
        // Disperse Solute
        //sim.randomizeSolute();
        // Equilibrate
        sim.getLammpsEnergy(2000, false, true);
        sim.doMC(1000);
        //sim.getLammpsEnergy(20000);
        
        /**
	    CalcVibrationalModes vib = new CalcVibrationalModes(sim.lammpsSim);
        vib.setup(sim.box, sim.box.getMoleculeList(sim.silver), sim.space);
                
        LammpsInterface2.doCommand(sim.lammpsSim, "pair_style hybrid meam lj/cut 4.2");
		LammpsInterface2.doCommand(sim.lammpsSim, "pair_coeff * * meam library.meam Ag Sn12 Ag3Sn.meam Ag Sn12");
		//LammpsInterface2.doCommand(sim.lammpsSim, "pair_coeff 1 2 lj/cut 0.70984 2.637");
		
		WriteConfiguration writer = new WriteConfiguration(sim.getSpace());
	    writer.setBox(sim.box);
	    writer.setConfName("temp");
	    writer.actionPerformed();
	    
	    ConfigurationFile config = new ConfigurationFile("temp");
		double epsSave=10;
		double sigmaSave=10;
		double energySave=10;
		double vibSave=10;
		double eps=0.5;
		String temp12;
		for(int i=0; i<1000; i++){
			double sigma=2.45;
			for(int j=0; j<100; j++){
				temp12 = "pair_coeff 1 2 lj/cut "+eps;
				temp12 = temp12+" "+sigma; 
				//System.out.println(temp12);
				LammpsInterface2.doCommand(sim.lammpsSim, temp12);
		        vib.actionPerformed();
		        config.initializeCoordinates(sim.box);
			    if(Math.abs(vib.getProductOfFrequencies()-5.15779156428)<vibSave && Math.abs(sim.getLammpsEnergy(0, true, false)+3555.5705)<energySave){
			    	vibSave = Math.abs(vib.getProductOfFrequencies()-5.15779156428);
			    	energySave = Math.abs(LammpsInterface2.getEnergy(sim.lammpsSim)+3555.5705);
			    	System.out.println(eps+"   "+sigma+"   "+LammpsInterface2.getEnergy(sim.lammpsSim)+"    "+vib.getProductOfFrequencies());
			    }
				sigma+=0.001;
			}
			System.out.println(eps);
			eps+=0.001;
		}
        **/    
       
        /**     
        // Run Simulation
        //sim.doMCSwap(steps);
        System.out.println("Average System Energy: "+(sim.esys/(double)sim.rej));
        System.out.println("Average Relaxed Energy: "+(sim.erej/(double)sim.rej));
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
	  **/
    }

	static {
		System.loadLibrary("LAMMPS");
		// System.loadLibrary("lmp_thomas");
	}
}
