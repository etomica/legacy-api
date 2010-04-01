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
	public SpeciesSpheresMono tin, silver, lj;
	public double e0, e1, erej, esys, eps, sigma, eps1, eps0, sigma1, sigma0;
	public int num, step, acc, rej, vac, numSolute;
	public IVectorMutable workVector, lammpsVector, boxVector, vacancyPosition;
	public IAtom atomS;
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
		
		//LENNARD JONES PARTIAL INSERSION POTENTIAL PARAMETERS
		eps = 0.772;
		sigma = 2.532;
		eps0 = 0.772;
		eps1 = 0.0;
		sigma0 = 2.532;
		sigma1 = 0.0;
			
		workVector = space.makeVector();
		lammpsVector = space.makeVector();
		boxVector = space.makeVector();
		vacancyPosition = space.makeVector();

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
		lj = new SpeciesSpheresMono(this, space);
		tin.setIsDynamic(true);
		silver.setIsDynamic(true);
		lj.setIsDynamic(true);
		addSpecies(tin);
		addSpecies(silver);
		addSpecies(lj);
		((IAtomTypeSphere) tin.getLeafType()).setDiameter(3.044);
		((IAtomTypeSphere) silver.getLeafType()).setDiameter(2.8895);
		((IAtomTypeSphere) lj.getLeafType()).setDiameter(2.8895);

		box.setNMolecules(tin, numSpeciesA);
		
		numSolute = numSpeciesB;
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
			
			findVacancy(vacancyPosition);
			
			MCpartialInsersion(eps*0.25, sigma*0.25);
			
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
			//System.out.println("Old box size: "+box.getBoundary().getBoxSize());
			LammpsInterface2.getBox(lammpsSim, boxVector);
			box.getBoundary().setBoxSize(boxVector);
			//System.out.println("New box size: "+boxVector);
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
	
	public void findVacancy(IVectorMutable vacancyLocation){
		//Ensure there are vacant locations
		while(true){
			System.out.println("Searching for vacancy...");
			updateCellVList();
			if(cellVList.size()==0){MDlammps(20);}
			else{break;}
		}		
		Cell cell1;
		Cell cell0;
		int randCell;
		int [] lidx = new int[3];
		double [] size = new double[3];
		IVectorMutable rij = space.makeVector();
		IVectorMutable randv = space.makeVector();
		//Ensure atom is single occupant of cell
		while(true){
			atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
			workVector.E(atomS.getPosition());
			cell0 = neighborCell.getCell(atomS);
			if(cell0.occupants().getAtomCount()<2){break;}
		}
	
		//CHOOSE RANDOM EMPTY CELL
		randCell = random.nextInt(cellVList.size());
		cell1 = cellVList.get(randCell);
		lidx = neighborCell.lattice.latticeIndex(cell1.getLatticeArrayIndex());		
		size = neighborCell.lattice.getCellSize();
		
		//SEARCH FOR POINT WITH 5 OR MORE NEIGHBORS WITHIN 2.8 ANGRSTROMS, 10 Trials in cell
		int trials=0;
		int count1=0;
		IAtom nb;
		IVectorMutable navg = space.makeVector();
		double ncut=2.8;
		double cellspot = 0.0;
		while(true){
			for(int i=0; i<3;i++){
				cellspot = lidx[i]*size[i]-0.5*box.getBoundary().getBoxSize().getX(i);
				cellspot += random.nextDouble()*size[i];
				randv.setX(i,cellspot);
			}
			box.getBoundary().nearestImage(randv);
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
				trials++;
				continue;
			}
			if(trials>10){return;}
		}
		
		//CENTER OF NEIGHBORS
		box.getBoundary().nearestImage(navg);
		rij.Ev1Mv2(randv,navg);
		box.getBoundary().nearestImage(rij);

		//PICK RANDOM POSITION WITHIN 0.15 ANGRSTROMS OF NEIGHBOR CENTER
		IVectorRandom randomvec = (IVectorRandom)space.makeVector();
		randomvec.setRandomInSphere(random);
		randomvec.TE(0.15);
		vacancyLocation.E(navg);
		vacancyLocation.PE(randomvec);
	}
	
	public void MDlammps(int mdsteps){
		e0 = getLammpsEnergy(mdsteps, true, true);
	}
	
	public void MCpartialInsersion(double deltaeps, double deltasigma){
		
		// *** IDENTIFY STATE *** //
		
		// (MEAM-100)-->(LJ-100)
		if(lj.getNumLeafAtoms()==0){
			MCmeam2lj(eps,sigma);
		}
		
		// (MEAM-100)<--(LJ-100)-->(LJ-X)
		else if(eps0/eps==1.0 && lj.getNumLeafAtoms()==1){
			//(LJ-100)-->(MEAM)
			if(random.nextInt(2)==0){MClj2meam(3);}
			//(LJ-100)-->(LJ-X)
			else{
				//Create second LJ Atom
				box.setNMolecules(lj,2);
		        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(vacancyPosition);
				LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single 0.0 0.0 0.0");
				
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma});
			}
		}
		
		// (LJ-Y)<--(LJ-X)-->(LJ-Z)
		else if(lj.getNumLeafAtoms()==2){
			//(LJ-X)-->(LJ-Y)
			if(random.nextInt(2)==0){MClj2lj(new double[]{eps0+deltaeps, eps1-deltaeps},new double[]{sigma0+deltasigma, sigma1-deltasigma});}
			//(LJ-X)-->(LJ-Z)
			else{
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma});
				//If LJ-Z == LJ-100
				if(eps1/eps==1.0){
					//Remove first LJ Atom
					box.setNMolecules(lj,1);
					LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj3");
				}
			}
		}
		
		// (LJ-X)<--(LJ-100)-->(MEAM-100)
		else if(eps1/eps==1.0 && lj.getNumLeafAtoms()==1){
			//(LJ-100)-->(MEAM)
			if(random.nextInt(2)==0){MClj2meam(4);}
			//(LJ-100)-->(LJ-X)
			else{
				//Create second LJ Atom
				box.setNMolecules(lj,2);
		        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(vacancyPosition);
				LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single 0.0 0.0 0.0");
				
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma});
			}
		}
		
		
	}
	
	public void MClj2lj(double[] eps, double[] sigma){
		String paircoeff;
		LammpsInterface2.doCommand(lammpsSim, "pair_style hybrid meam lj/cut 4.2");
		LammpsInterface2.doCommand(lammpsSim, "pair_coeff * * meam library.meam Ag Sn12 Ag3Sn.meam Ag Sn12");
		paircoeff = "pair_coeff 2 3 lj/cut "+eps[0]+" "+sigma[0];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		paircoeff = "pair_coeff 2 4 lj/cut "+eps[1]+" "+sigma[1];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		
		if(checkMove()){
			eps0 = eps[0];
			eps1 = eps[1];
			sigma0 = sigma[0];
			sigma1 = sigma[1];
			System.out.println(step+" A - lj2lj eps0 "+eps0+" eps1 "+eps1+"  "+e1+"   "+bfactor);
		}	
        else{
            System.out.println(step+" R - lj2lj eps0 "+eps0+" eps1 "+eps1+"  "+e0+"   "+e1+"   "+bfactor);
            paircoeff = "pair_coeff 2 3 lj/cut "+eps0+" "+sigma0;
    		LammpsInterface2.doCommand(lammpsSim, paircoeff);
            paircoeff = "pair_coeff 2 4 lj/cut "+eps1+" "+sigma1;
    		LammpsInterface2.doCommand(lammpsSim, paircoeff);
        }	
	}
	
	public void MClj2meam(int ljtype){
		//Creates new Ag atom in place of LJ atom
		box.setNMolecules(silver, numSolute);
		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
		box.setNMolecules(lj,0);
		//Remove atom from LAMMPS, Create new silver
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj"+ljtype);
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single 0.0 0.0 0.0");
		if(checkMove()){
			System.out.println(step+" A - lj2meam "+e1+"   "+bfactor); 
		}	
        else{
            System.out.println(step+" R - lj2meam "+e0+"   "+e1+"   "+bfactor);
            box.setNMolecules(lj,1);
            box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(atomS.getPosition());
            box.removeMolecule(atomS.getParentGroup());
            LammpsInterface2.doCommand(lammpsSim, "create_atoms "+ljtype+" single 0.0 0.0 0.0"); //LJ Type (old position atom)
        }	
	}
	
	public void MCmeam2lj(double eps, double sigma){
		//Creates new LJ atom in place of Ag atom
		box.setNMolecules(lj,1);
        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(atomS.getPosition());
        String region = "region agrmv sphere "+atomS.getPosition().getX(0)+" "+atomS.getPosition().getX(1)+" "+atomS.getPosition().getX(2)+" 0.5 units box";
		box.removeMolecule(atomS.getParentGroup());
		//Remove Silver from LAMMPS, Create new LJ atom
        LammpsInterface2.doCommand(lammpsSim, region);
        LammpsInterface2.doCommand(lammpsSim, "delete_atoms region agrmv");
        //LJ Type 3 (old position atom)
        LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single 0.0 0.0 0.0");
		if(checkMove()){
			System.out.println(step+" A - meam2lj "+e1+"   "+bfactor); 
			return;
		}
        else{
            System.out.println(step+" R - meam2lj "+e0+"   "+e1+"   "+bfactor);
            box.setNMolecules(silver, numSolute);
    		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
    		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
    		box.setNMolecules(lj,0);
    		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ljatoms");
    		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single 0.0 0.0 0.0");
        }	
	}
	
	public void relaxNeighbors(IVectorMutable compressv, IVectorMutable expandv, double xm, double b){
		//CONTRACT AND EXPAND LATTICE AT OLD AND NEW POINTS
		double rmag;
		IAtom neighbor;
		int exp=0;
		int comp=0;
		IVectorMutable rij = space.makeVector();
		
		//Compress atoms near vector compressv
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			rij.Ev1Mv2(neighbor.getPosition(),compressv);
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();	
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				neighbor.getPosition().Ea1Tv1((rmag-b)/(1.0-(b/xm))/rmag, rij);
				neighbor.getPosition().PE(compressv);
				comp++;
			}	
		}
		//Expand atoms near vector expandv
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			rij.Ev1Mv2(neighbor.getPosition(),expandv);
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();
			if(rmag<0.1){continue;} // neighbor and atom at expandv are same
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				neighbor.getPosition().Ea1Tv1(((-b/xm)*rmag+rmag+b)/rmag, rij);
				neighbor.getPosition().PE(expandv);
				exp++;
			}
		}
		//System.out.println("Expanded: "+exp+"   Compressed: "+comp);
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
        //System.out.println("Cells with vacancies: "+vac);
        //System.out.println("Neighbor cell size: "+neighborCell.lattice.getCellSize()[0]);
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
        sim.getLammpsEnergy(3000, false, true);
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
