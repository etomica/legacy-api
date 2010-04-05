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
	public int num, step, acc, vac, numSolute, ljstages;
	public IVectorMutable workVector, lammpsVector, boxVector, vacancyPosition, interstitialPosition;
	public IAtom atomS;
	public long lammpsSim;
	public RandomNumberGenerator random;
	double bfactor, beta;
	public IMoleculeList moleculeList;
	public XYZWriter writer;
	public HistogramSimple histz1, histz2;
	public ArrayList<Cell> cellVList;
	public IVectorMutable[] neighborPositions;
	public double[] stateBias;
	private BoxImposePbc pbc;
	public boolean comments, rejf, rejb, rej;
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
		vac = 0;
		comments=false;	
			
		workVector = space.makeVector();
		lammpsVector = space.makeVector();
		boxVector = space.makeVector();
		vacancyPosition = space.makeVector();
		interstitialPosition = space.makeVector();

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
		box.setNMolecules(lj,0);
		
		box.getBoundary().setBoxSize(boxSize);
		
		System.out.println("Number of Tin atoms: "+ box.getMoleculeList(tin).getMoleculeCount());
		System.out.println("Number of Silver atoms: "+ box.getMoleculeList(silver).getMoleculeCount());
		System.out.println("Box Size: " + box.getBoundary().getBoxSize());
	
		
		moleculeList = box.getMoleculeList();
		
		neighborCell = new NeighborCellManager(this, box, 5.5, space);
		cellVList = new ArrayList<Cell>();
		
		//Get Lammps Energy
		e0 = getLammpsEnergy(0,false,true);

		neighborCell.assignCellAll();
		System.out.println("Neighbor Cell size is "+neighborCell.lattice.getCellSize()[0]+" "+neighborCell.lattice.getCellSize()[1]+"  "+neighborCell.lattice.getCellSize()[2]);
		
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
		
		while (true) {
			
			if(step>maxsteps && lj.getNumLeafAtoms()==0){System.out.println("> Simulation finished.");break;}		
			
			
			//Insertion via LJ growth - parameters are deltas
			PartialInsersion(eps/(stateBias.length-2), 0.0, false, 0.05);			

			if(bfactor>0.5){
				System.out.println(e0+" "+e1+" "+eps1+" "+sigma1+" "+bfactor);
			}
			else{System.out.println(e0+" "+e1+" "+eps1+" "+sigma1+" "+bfactor+" -----!!----");}
			
			//Relax system with MD
			MDlammps(5);
			
			step++;
		}
		
	}
	
	public void setParameters(double ljeps, double ljsigma, double[] energyBias){
		
		//LENNARD JONES PARTIAL INSERSION POTENTIAL PARAMETERS
		eps = ljeps;
		sigma = ljsigma;
		
		eps0 = eps;
		eps1 = 0.0;
		
		sigma0 = sigma;
		sigma1 = sigma;
		
		stateBias = new double[7];
		stateBias = energyBias;
		
		ljstages = stateBias.length-1;
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
			LammpsInterface2.getBox(lammpsSim, boxVector);
			box.getBoundary().setBoxSize(boxVector);
			pbc.actionPerformed();
			updateCellVList();
		}
		return LammpsInterface2.getEnergy(lammpsSim);	
	}

	public void calcAverages() {
		// XYZ Writer
		writer.actionPerformed();
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
	
	public void findVacancyRandom(IVectorMutable vacancyLocation){
		vacancyLocation.setX(0,0.5*box.getBoundary().getBoxSize().getX(0)*(2.0*random.nextDouble()-1));
		vacancyLocation.setX(1,0.5*box.getBoundary().getBoxSize().getX(1)*(2.0*random.nextDouble()-1));
		vacancyLocation.setX(2,0.5*box.getBoundary().getBoxSize().getX(2)*(2.0*random.nextDouble()-1));		
	}
	
	public void findSoluteRandom(){
		atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
		interstitialPosition.E(atomS.getPosition());
	}
	
	public void findVacancyCell(IVectorMutable vacancyLocation){
		Cell cell1;
		Cell cell0;
		int randCell;
		int [] lidx = new int[3];
		double [] size = new double[3];
		IVectorMutable rij = space.makeVector();
		IVectorMutable randv = space.makeVector();
		int trials=0;
		int count1=0;
		IAtom nb;
		IVectorMutable navg = space.makeVector();
		double ncut=2.8;
		double cellspot = 0.0;
		
		while(true){
			if(comments){System.out.println("\n> Looking for random interstitial/vacancy pair...");}
			//Ensure there are vacant locations and interstitial is single occupant of cell
			trials=0;
			while(true){
				if(comments && trials==0){System.out.print("  >> Searching for vacant cell and single interstitial...");}
				updateCellVList();
				atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
				interstitialPosition.E(atomS.getPosition());
				cell0 = neighborCell.getCell(atomS);
				if(cellVList.size()==0 || trials>box.getNMolecules(silver)){MDlammps(5);}
				if(cell0.occupants().getAtomCount()<2){if(comments){System.out.print("found.\n");}break;}
				trials++;
			}
			
			//CHOOSE RANDOM EMPTY CELL
			randCell = random.nextInt(cellVList.size());
			cell1 = cellVList.get(randCell);
			lidx = neighborCell.lattice.latticeIndex(cell1.getLatticeArrayIndex());		
			size = neighborCell.lattice.getCellSize();
			
			//SEARCH FOR POINT WITH 5 OR MORE NEIGHBORS WITHIN 2.8 ANGRSTROMS, 10 Trials in cell
			trials=0;
			while(true){
				if(comments && trials==0){System.out.print("  >> Searching for 5 or more neighbors of vacant cell...");};
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
					if(comments){System.out.print("found.\n");}
					break;
				}
				if(trials>9){break;}
				trials++;
			}
			if(count1>4 && trials<11){break;}
			trials=0;
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
		if(comments){System.out.println("  >> Insertion location set.");};
	}
	
	public void MDlammps(int mdsteps){
		e0 = getLammpsEnergy(mdsteps, true, true);
	}
	
	public void PartialInsersion(double deltaeps, double deltasigma, boolean relax, double relaxB){		
		
		// *** IDENTIFY STATE *** //
		// [0]=100-MEAM, [1]=100-LJ, [2]=XLJ, ....
		int biasRow = (int) (ljstages - (eps0/deltaeps));
		
		// ************************ 
		//   (MEAM-100)-->(LJ-100)
		//
		// ************************
		if(box.getNMolecules(lj)==0){
			//find random silver atom
			findSoluteRandom();
			if(comments){System.out.println("> Found random silver atom "+atomS.getLeafIndex()+".");}
			if(comments){System.out.println("\n> Begin partial insertion of atom...");}
			if(comments){System.out.println("  >> Bias is "+stateBias[0]+" for current state, and "+stateBias[1]+" for attempted state.");}
			MCmeam2lj(eps,sigma,stateBias[1]-stateBias[0]);
		}
		
		// ************************ 
		// (MEAM-100)<--(LJ-100)-->(LJ-X)
		//
		// ************************
		else if(eps0/eps==1.0 && sigma0/sigma==1.0 && box.getNMolecules(lj)==1){
			if(comments){System.out.println("\n> Continue insertion or return to MEAM...");}
			
			//(LJ-100)-->(MEAM-100)
			if(random.nextInt(2)==0){if(comments){
				System.out.println("  >> Returning to MEAM potential.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[0]+" for attempted state.");}
				MClj2meam(3,stateBias[0]-stateBias[1]);
				if(rej==false){calcAverages();}
			}
			//(LJ-100)-->(LJ-X)
			else{
				//find new vacancy location
				findVacancyRandom(vacancyPosition);
				
				if(comments){System.out.println("  >> Randomly finding a vacancy location.");}
				
				if(comments){System.out.println("  >> Continuing insertion by creating second LJ atom at vacancy.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[2]+" for attempted state.");}
				if(relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma},4,stateBias[2]-stateBias[1]);
				if(rej && relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
			}
		}
		
		// ************************
		// (LJ-Y)<--(LJ-X)-->(LJ-Z)
		//
		// ************************
		else if(box.getNMolecules(lj)==2){
			if(comments){System.out.println("\n> Grow or shrink inserted atom...");}
			
			//(LJ-X)-->(LJ-Y)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Shrinking inserted atom.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[biasRow]+" for current state, and "+stateBias[biasRow-1]+" for attempted state.");}
				if(relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0+deltaeps, eps1-deltaeps},new double[]{sigma0+deltasigma, sigma1-deltasigma},0,stateBias[biasRow-1]-stateBias[biasRow]);
				if(rej && relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
				
				//If LJ-Y == LJ-100 (move accepted)
				if(eps0/eps==1.0 && sigma0/sigma==1.0){
					if(comments){System.out.println("  >> Initial atom is mature.  Removing inserted atom.");}
					//Remove first LJ Atom
					box.removeMolecule(box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getParentGroup());
					LammpsInterface2.doCommand(lammpsSim, "group lj4 type 4");
					LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj4");
				}
			}
			//(LJ-X)-->(LJ-Z)
			else{
				if(comments){System.out.println("  >> Growing inserted atom.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[biasRow]+" for current state, and "+stateBias[biasRow+1]+" for attempted state.");}
				if(relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma},0,stateBias[biasRow+1]-stateBias[biasRow]);
				if(rej && relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
				//If LJ-Z == LJ-100
				if(eps1/eps==1.0 && sigma1/sigma==1.0){
					if(comments){System.out.println("  >> Inserted atom is mature.  Removing first interstitial.");}
					//Remove first LJ Atom
					box.removeMolecule(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getParentGroup());
					LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
					LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj3");
				}
			}
		}
		
		// ************************
		// (LJ-X)<--(LJ-100)-->(MEAM-100)
		//
		// ************************
		else if(eps1/eps==1.0 && sigma1/sigma==1.0 && box.getNMolecules(lj)==1){
			if(comments){System.out.println("> Shrink insertion or return to MEAM...");}
			
			//(LJ-100)-->(LJ-X)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Shrinking insertion by creating LJ atom at first interstitial.");}			
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[stateBias.length-2]+" for attempted state.");}
				if(relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0+deltaeps, eps1-deltaeps},new double[]{sigma0+deltasigma, sigma1-deltasigma},3,stateBias[stateBias.length-2]-stateBias[1]);
				if(rej && relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
			}
			//(LJ-100)-->(MEAM)
			else{
				if(comments){System.out.println("  >> Returning to MEAM potential.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[0]+" for attempted state.");}
				MClj2meam(4,stateBias[0]-stateBias[1]);
				if(rej==false){calcAverages();}
			}
		}	
	}
	
	public void MClj2lj(double[] eps, double[] sigma, int newatom, double ebias){
		if(newatom==4){
			if(comments){System.out.println("  >> Creating new atom LJ"+newatom+".");}
			//Create second LJ Atom
			box.setNMolecules(lj,2);
	        box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition().E(vacancyPosition);
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single 0.0 0.0 0.0");
		}
		if(newatom==3){
			if(comments){System.out.println("  >> Creating new atom LJ"+newatom+".");}
			//Create interstitial and vacancy LJ Atom
			box.setNMolecules(lj,2);
	        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(interstitialPosition);
	        box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition().E(vacancyPosition);
	        LammpsInterface2.doCommand(lammpsSim, "group lj4 type 4");
	        LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj4");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single 0.0 0.0 0.0");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single 0.0 0.0 0.0");
		}
		
		if(comments){System.out.print("  >> MC - LJ("+eps[0]+","+sigma[0]+") to LJ("+eps[1]+","+sigma[1]+") move...");};
				
		String paircoeff;
		paircoeff = "pair_coeff 2 3 lj/cut "+eps[0]+" "+sigma[0];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		paircoeff = "pair_coeff 2 4 lj/cut "+eps[1]+" "+sigma[1];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		
		if(checkMove(ebias)){
			rej=false;
			if(comments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");}
			eps0 = eps[0];
			eps1 = eps[1];
			sigma0 = sigma[0];
			sigma1 = sigma[1];
		}	
        else{
        	rej=true;
        	if(comments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");} 
            paircoeff = "pair_coeff 2 3 lj/cut "+eps0+" "+sigma0;
    		LammpsInterface2.doCommand(lammpsSim, paircoeff);
            paircoeff = "pair_coeff 2 4 lj/cut "+eps1+" "+sigma1;
    		LammpsInterface2.doCommand(lammpsSim, paircoeff);
    		
    		if(newatom==4){
    			if(comments){System.out.println("  >> Deleting new atom LJ"+newatom+".");}
    			//Delete vacancy LJ Atom
    			box.setNMolecules(lj,1);
    	        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(interstitialPosition);
    	        LammpsInterface2.doCommand(lammpsSim, "group lj4 type 4");
    	        LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj4");
    		}
    		if(newatom==3){
    			if(comments){System.out.println("  >> Deleting new atom LJ"+newatom+".");}
    			//Delete interstitial LJ Atom
    			box.setNMolecules(lj,1);
    	        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(vacancyPosition);
    	        LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
    	        LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj3");
    		}
        }	
	}
	
	public void MClj2meam(int ljtype, double ebias){
		if(comments){System.out.print("  >> MC - LJ to MEAM move...");};
		
		//Creates new Ag atom in place of LJ atom
		box.setNMolecules(silver, numSolute);
		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
		box.setNMolecules(lj,0);
		//Remove atom from LAMMPS, Create new silver
		LammpsInterface2.doCommand(lammpsSim, "group lj"+ljtype+" type "+ljtype);
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj"+ljtype);
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single 0.0 0.0 0.0");
		if(checkMove(ebias)){
			if(comments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}	
        else{
        	rej=true;
        	if(comments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");} 
            box.setNMolecules(lj,1);
            box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(atomS.getPosition());    		
    		//Remove Silver from LAMMPS, Create new LJ atom
    		LammpsInterface2.doCommand(lammpsSim, "create_atoms "+ljtype+" single "+atomS.getPosition().getX(0)+" "+atomS.getPosition().getX(1)+" "+atomS.getPosition().getX(2)+" units box"); //LJ Type (old position atom)
    		box.removeMolecule(atomS.getParentGroup());
    		LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
    		LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
            LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver lj"+ljtype);
            
        }	
	}
	
	public void MCmeam2lj(double eps, double sigma, double ebias){
		if(comments){System.out.print("  >> MC - MEAM to LJ move...");};
		//Creates new LJ atom in place of Ag atom
		box.setNMolecules(lj,1);
        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(atomS.getPosition());
        //Remove Silver from LAMMPS, Create new LJ atom
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+atomS.getPosition().getX(0)+" "+atomS.getPosition().getX(1)+" "+atomS.getPosition().getX(2)+" units box"); //LJ Type (old position atom)
		box.removeMolecule(atomS.getParentGroup());
		LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
		LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
        LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver lj3");
        //Set default potential parameters for LJ
        String paircoeff = "pair_coeff 2 3 lj/cut "+eps+" "+sigma;
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		if(checkMove(ebias)){
			if(comments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
        else{
        	rej=true;
        	if(comments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");} 
            box.setNMolecules(silver, numSolute);
    		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
    		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
    		box.setNMolecules(lj,0);
    		LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
    		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj3");
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
		if(comments){System.out.print("  >> Compressing neighbors...");};
		//Compress atoms near vector compressv
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			neighbor = box.getMoleculeList().getMolecule(i).getChildList().getAtom(0);
			rij.Ev1Mv2(neighbor.getPosition(),compressv);
			box.getBoundary().nearestImage(rij);
			rmag = rij.squared();
			if(rmag<0.1){continue;} 
			if(rmag<(xm*xm)){
				rmag = Math.sqrt(rmag);
				neighbor.getPosition().Ea1Tv1((rmag-b)/(1.0-(b/xm))/rmag, rij);
				neighbor.getPosition().PE(compressv);
				comp++;
			}	
		}
		if(comments){System.out.print(comp+"compressed.\n");};
		if(comments){System.out.print("  >> Expanding neighbors...");};
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
		if(comments){System.out.print(exp+"expanded.\n");};
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
        //if(comments){System.out.println("Cells with vacancies: "+vac);}
        //System.out.println("Neighbor cell size: "+neighborCell.lattice.getCellSize()[0]);
	}
	
	public boolean checkMove(double ebias){
		// Check acceptance criteria
		e1 = getLammpsEnergy(0, true, false);
		bfactor = Math.exp(-beta * (e1 - e0 + ebias));
		if (bfactor > 1.0 || random.nextDouble() < bfactor) {// Accepted
			e0 = e1;
			acc++;
			return true;
		} else {// Rejected
			esys +=e0;
			erej +=e1;
			return false;
		}
	}
		
	public void reset() {
		step = 0;
		histz1.reset();
		histz2.reset();
		
		eps0 = eps;
		eps1 = 0.0;
		
		sigma0 = sigma;
		sigma1 = sigma;
	}
	
	public void doLJgetParams(){
		double[] meamModes = new double[3];
		double[] tempModes = new double[3];
	    CalcVibrationalModes vib = new CalcVibrationalModes(lammpsSim);
        vib.setup(box, box.getMoleculeList(silver), space);
        vib.actionPerformed();
        for(int i=0; i<meamModes.length;i++){
        	meamModes[i] = vib.modes[i];
        }

        LammpsInterface2.doCommand(lammpsSim, "pair_style hybrid meam lj/cut 4.2");
		LammpsInterface2.doCommand(lammpsSim, "pair_coeff * * meam library.meam Ag Sn12 Ag3Sn.meam Ag Sn12 Ag Ag");
		//LammpsInterface2.doCommand(sim.lammpsSim, "pair_coeff 1 2 lj/cut 0.70984 2.637");
		
		WriteConfiguration writer = new WriteConfiguration(getSpace());
	    writer.setBox(box);
	    writer.setConfName("temp");
	    writer.actionPerformed();
	    
	    ConfigurationFile config = new ConfigurationFile("temp");
	    config.initializeCoordinates(box);
	    
		double eps=0.41;
		double modeSave=500000;
		double modeSum=0;
		String temp12;
		for(int i=0; i<100; i++){
			double sigma=2.62;
			for(int j=0; j<100; j++){
				temp12 = "pair_coeff 1 2 lj/cut "+eps;
				temp12 = temp12+" "+sigma;
				//System.out.println(temp12);
				LammpsInterface2.doCommand(lammpsSim, temp12);
				
				config.initializeCoordinates(box);
				vib.actionPerformed();
				
				modeSum=0;
		        for(int k=0; k<meamModes.length;k++){
		        	tempModes[k] = meamModes[k] - vib.modes[k];
		        	modeSum+=Math.abs(tempModes[k]);
		        }
			    
		        if(modeSum<modeSave){
			    	System.out.println(eps+"   "+sigma+"   "+LammpsInterface2.getEnergy(lammpsSim)+"    "+modeSum);
			    	modeSave=modeSum;
			    }
				sigma+=0.001;
			}
			System.out.println(eps);
			eps+=0.001;
		} 
	}
		
	public void setComments(boolean commentOn){
		comments = commentOn;
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
        
        // Params for Silver and 5 Stage LJ Energy Bias (100-75-50-25-0);
        sim.setParameters(0.442,2.664,new double[]{3.06,3.23,1.23,1.0,1.23,3.23});
        
        sim.setComments(true);
        sim.getLammpsEnergy(2000,false,true);
        sim.doMC(50);
     
        
        
        
        
        // Disperse Solute
        //sim.randomizeSolute();
        // Equilibrate
        //sim.getLammpsEnergy(600, false, true);
       //sim.setComments(false);
        //sim.doMC(50);
        //sim.getLammpsEnergy(20000);
        
        /**
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
