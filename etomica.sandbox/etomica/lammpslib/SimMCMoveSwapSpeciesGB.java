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
import etomica.atom.MoleculeArrayList;
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
	public double e0, e1, e1avg, e0avg, eps, sigma, eps1, eps0, sigma1, sigma0;
	public int num, step, acc, vac, numSolute, ljstages, average,state;
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
	public boolean comments, mccomments, rej;
	public NeighborCellManager neighborCell;

	public SimMCMoveSwapSpeciesGB(int numSpeciesA, int numSpeciesB,
			double temp, IVector boxSize, String infile) {
		super(Space3D.getInstance());

		e1 = 0;
		e0 = 0;
		e1avg = 0;
		e0avg= 10;
		num = 0;
		step = 1;
		acc = 0;
		vac = 0;
		state=0;
		average=0;
		comments=false;	
		mccomments=false;
			
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
		writer.setFileName("ag7525.xyz");
		writer.setIsAppend(true);

		// Histograms
		double zextreme = box.getBoundary().getBoxSize().getX(2);
		histz1 = new HistogramSimple(200, new DoubleRange(zextreme, -zextreme));
		histz2 = new HistogramSimple(200, new DoubleRange(zextreme, -zextreme));

		System.out.println(e0);
	}

	public void doMC(int maxsteps) {
		
		while (step<maxsteps) {
						
			//Insertion via LJ growth - parameters are deltas
			//PartialInsersionLJ(eps/(stateBias.length-3), 0.0, false, 0.05);			
			
			//Insertion via MEAM growth
			PartialInsersionMEAM(stateBias);		
			
			//Relax system with MD
			if(state>0){MDlammps(10);}
			
			step++;
			
		}
		
	}
	
	public void setParameters(double ljeps, double ljsigma, double[] energyBias){
		
		//LENNARD JONES (MEAM) PARTIAL INSERSION POTENTIAL PARAMETERS
		eps = ljeps;
		sigma = ljsigma;
		
		eps0 = eps;
		eps1 = 0.0;
		
		sigma0 = sigma;
		sigma1 = sigma;
		
		stateBias = new double[energyBias.length];
		stateBias = energyBias;
		
		ljstages = stateBias.length-2;
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
	
	public void findSoluteRandom(IVectorMutable pos){
		atomS = box.getMoleculeList(silver).getMolecule(random.nextInt(box.getMoleculeList(silver).getMoleculeCount())).getChildList().getAtom(0);
		pos.E(atomS.getPosition());
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
	
	/************************************
	 * MEAM Partial Insertion Section
	 * 
	 */
	
	public void PartialInsersionMEAM(double [] stateBias){
		// SPECIES LIST: 1-Ag 2-Sn 3-Ag75 4-Ag50 5-Ag25 6-Ag0
		

		// ************************ 
		//   (MEAM-100)-->(MEAM-75)
		//
		// ************************
		if(state==0){
			if(comments){System.out.println("*** State "+state+". ***");}
			//find random silver atom
			findSoluteRandom(interstitialPosition);
			if(comments){System.out.println("> Found random silver atom "+atomS.getLeafIndex()+".");}
			
			if(comments){System.out.println("  >> Randomly finding a vacancy location.");}
			findVacancyRandom(vacancyPosition);
			
			
			if(comments){System.out.println("\n> Begin partial insertion of atom...");}
			if(comments){System.out.println("  >> Bias is "+stateBias[0]+".");}
			MCmeam2s75(stateBias[0]);
			if(rej==false){state=1;}
		}
		
		// ************************ 
		// (MEAM-100)<--(MEAM-75)-->(MEAM-50)
		//
		// ************************
		else if(state==1){
			if(comments){System.out.println("*** State "+state+". ***");}
			//Update vectors
			interstitialPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			vacancyPosition.E(box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition());
			
			if(comments){System.out.println("\n> Continue insertion or return to MEAM...");}
			
			//(MEAM-75)-->(MEAM-100)
//			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Returning to MEAM-100 potential.");}
				if(comments){System.out.println("  >> Bias is "+(-stateBias[0])+".");}
				MCs752meam(-stateBias[0]);
				if(rej==false){state=0;}
/**			}
			//(LMEAM-75)-->(MEAM-50)
			else{
								
				if(comments){System.out.println("  >> Continuing insertion by growing second MEAM atom at vacancy.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+".");}
				MCs752s50(stateBias[1]);
				//Extra relaxation
				if(rej==false){MDlammps(20);state=2;}
			}
**/		}
		
		// ************************
		// (MEAM-75)<--(MEAM-50)-->(MEAM-25)
		//
		// ************************
		else if(state==2){
			if(comments){System.out.println("*** State "+state+". ***");}

			//Update vectors
			interstitialPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			vacancyPosition.E(box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition());
			
			if(comments){System.out.println("\n> Grow or shrink inserted atom...");}
			
			//(MEAM-50)-->(MEAM-75)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Shrinking inserted atom.");}
				if(comments){System.out.println("  >> Bias is "+(-stateBias[1])+".");}
				MCs502s75(-stateBias[1]);
				if(rej==false){state=1;}
				
			}
			//(MEAM-50)-->(MEAM-25)
			else{
				if(comments){System.out.println("  >> Growing inserted atom.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[2]+".");}
				MCs502s25(stateBias[2]);
				if(rej==false){state=3;}
			}
		}
		
		// ************************
		// (MEAM-50)<--(MEAM-25)-->(MEAM-100)
		//
		// ************************
		else if(state==3){
			if(comments){System.out.println("*** State "+state+". ***");}
			//Update vectors
			interstitialPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			vacancyPosition.E(box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition());
			
			if(comments){System.out.println("> Shrink insertion or return to MEAM...");}
			
			//(MEAM-25)-->(MEAM-50)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Shrinking insertion.");}			
				if(comments){System.out.println("  >> Bias is "+(-stateBias[2])+".");}
				MCs252s50(-stateBias[2]);
				if(rej==false){state=2;}
			}
			//(MEAM-25)-->(MEAM-100)
			else{
				if(comments){System.out.println("  >> Returning to MEAM potential.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[3]+".");}
				MCs252meam(stateBias[3]);
				if(rej==false){state=0;}
			}
		}	
		
	}
	
	public void MCmeam2s75(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-100 to MEAM-75 move...");};
		
		//ETOMICA - Creates new LJ atom in place of Ag atom
		box.setNMolecules(lj,2);
        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(interstitialPosition);
        box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition().E(vacancyPosition);
        box.removeMolecule(atomS.getParentGroup());
        
        //LAMMPS - Create new MEAM Atoms
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-75
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-25		
		LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
		LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver ag75");
		

		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			//Delete new atoms
			box.setNMolecules(lj,0);
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
			//Create new MEAM Silver
			box.setNMolecules(silver, numSolute);
			atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
			atomS.getPosition().E(interstitialPosition);
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-100
			LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
		}
	}
	
	public void MCs752meam(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-75 to MEAM-100 move...");};
		//ETOMICA - Delete new atoms
		box.setNMolecules(lj,0);
		box.setNMolecules(silver, numSolute);
		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
		atomS.getPosition().E(interstitialPosition);
		
		//LAMMPS
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-100
		LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			box.setNMolecules(lj,2);
	        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(interstitialPosition);
	        box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition().E(vacancyPosition);
	        box.removeMolecule(atomS.getParentGroup());
	        //Create new MEAM Atoms
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-75
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-25
			LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
			LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
			LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver ag75");
			
			writer.actionPerformed();
		}
	}
	
	public void MCs752s50(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-75 to MEAM-50 move...");};
		//LAMMPS - Create new atoms
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-50
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-50
		LammpsInterface2.doCommand(lammpsSim, "group ag50 type 3");
		//Remove atoms
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag50");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-75
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-25
			LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
			LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
		}
	}
	
	public void MCs502s75(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-50 to MEAM-75 move...");};
		//LAMMPS - Create new atoms
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-75
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-25
		LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
		LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
		//Remove atoms
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag50");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			//Delete new atoms
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-50
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-50
			LammpsInterface2.doCommand(lammpsSim, "group ag50 type 3");
		}
	}
	
	public void MCs502s25(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-50 to MEAM-25 move...");};
		//LAMMPS - Create new atoms
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-75
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-25
		LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
		LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
		//Remove atoms
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag50");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			//Delete new atoms
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-50
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-50
			LammpsInterface2.doCommand(lammpsSim, "group ag50 type 3");
		}
	}
	
	public void MCs252s50(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-25 to MEAM-50 move...");};
		//LAMMPS - Create new atoms
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-50
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 3 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-50
		LammpsInterface2.doCommand(lammpsSim, "group ag50 type 3");
		//Remove atoms
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			//Delete new atoms
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag50");
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-25
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-75
			LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
			LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
		}
	}
	
	public void MCs252meam(double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM-25 to MEAM-100 move...");};
		
		//ETOMICA - Delete new atoms
		box.setNMolecules(lj,0);
		box.setNMolecules(silver, numSolute);
		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
		atomS.getPosition().E(interstitialPosition);
		
		//LAMMPS
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag75");
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group ag25");	
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-100
		LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
		
		if(checkMove(ebias)){//Accepted
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{//Rejected, cleanup.
			rej=true;
			if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");}
			box.setNMolecules(lj,2);
	        box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(interstitialPosition);
	        box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition().E(vacancyPosition);
	        box.removeMolecule(atomS.getParentGroup());
	        //Create new MEAM Atoms
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 4 single "+interstitialPosition.getX(0)+" "+interstitialPosition.getX(1)+" "+interstitialPosition.getX(2)+" units box"); //MEAM-25
			LammpsInterface2.doCommand(lammpsSim, "create_atoms 2 single "+vacancyPosition.getX(0)+" "+vacancyPosition.getX(1)+" "+vacancyPosition.getX(2)+" units box"); //MEAM-75
			LammpsInterface2.doCommand(lammpsSim, "group ag75 type 2");
			LammpsInterface2.doCommand(lammpsSim, "group ag25 type 4");
			//Remove Silver from LAMMPS
			LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
			LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver ag75");
		}
	}
	
	/*****************************************
	 * Lennard Jones Partial Insertion Section
	 * @param deltaeps
	 * @param deltasigma
	 * @param relax
	 * @param relaxB
	 */
	
	public void PartialInsersionLJ(double deltaeps, double deltasigma, boolean relax, double relaxB){		
		
		// *** IDENTIFY STATE *** //
		// [0]=100-MEAM, [1]=100-LJ, [2]=XLJ, ....
		int biasRow = (int) (ljstages - (eps0/deltaeps));
		
		// ************************ 
		//   (MEAM-100)-->(LJ-100)
		//
		// ************************
		if(box.getNMolecules(lj)==0){
			//find random silver atom
			findSoluteRandom(interstitialPosition);
			
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
			
			//Update vectors
			interstitialPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			
			if(comments){System.out.println("\n> Continue insertion or return to MEAM...");}
			
			//(LJ-100)-->(MEAM-100)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Returning to MEAM potential.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[0]+" for attempted state.");}
				MClj2meam(3,stateBias[0]-stateBias[1]);
				if(rej==false){calcAverages();}
			}
			//(LJ-100)-->(LJ-X)
/**			else{
				//find new vacancy location
				findVacancyRandom(vacancyPosition);
				
				if(comments){System.out.println("  >> Randomly finding a vacancy location.");}
				
				if(comments){System.out.println("  >> Continuing insertion by creating second LJ atom at vacancy.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[1]+" for current state, and "+stateBias[2]+" for attempted state.");}
				if(relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0-deltaeps, eps1+deltaeps},new double[]{sigma0-deltasigma, sigma1+deltasigma},4,stateBias[2]-stateBias[1]);
				if(rej && relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
				//Extra relaxation
				if(rej==false){MDlammps(10);}
**/ //		}
		}
		
		// ************************
		// (LJ-Y)<--(LJ-X)-->(LJ-Z)
		//
		// ************************
		else if(box.getNMolecules(lj)==2){
			//Update vectors
			interstitialPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			vacancyPosition.E(box.getMoleculeList(lj).getMolecule(1).getChildList().getAtom(0).getPosition());
			
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
			
			//Update vectors
			vacancyPosition.E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
			
			if(comments){System.out.println("> Shrink insertion or return to MEAM...");}
			
			//(LJ-100)-->(LJ-X)
			if(random.nextInt(2)==0){
				if(comments){System.out.println("  >> Shrinking insertion by creating LJ atom at first interstitial.");}			
				if(comments){System.out.println("  >> Bias is "+stateBias[stateBias.length-3]+" for current state, and "+stateBias[stateBias.length-2]+" for attempted state.");}
				if(relax){relaxNeighbors(vacancyPosition,interstitialPosition,2.8,relaxB);}
				MClj2lj(new double[]{eps0+deltaeps, eps1-deltaeps},new double[]{sigma0+deltasigma, sigma1-deltasigma},3,stateBias[stateBias.length-2]-stateBias[stateBias.length-3]);
				if(rej && relax){relaxNeighbors(interstitialPosition,vacancyPosition,2.8,relaxB);}
			}
			//(LJ-100)-->(MEAM)
			else{
				if(comments){System.out.println("  >> Returning to MEAM potential.");}
				if(comments){System.out.println("  >> Bias is "+stateBias[stateBias.length-2]+" for current state, and "+stateBias[stateBias.length-1]+" for attempted state.");}
				MClj2meam(4,stateBias[stateBias.length-1]-stateBias[stateBias.length-2]);
				if(rej==false){
					//Reset epsilons
					eps0 = eps;
					eps1 = 0.0;
					MDlammps(1000);
					calcAverages();
				}
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
		
		if(mccomments){System.out.print("  >> MC - LJ("+eps[0]+","+sigma[0]+")--LJ("+eps[1]+","+sigma[1]+") move...");};
				
		String paircoeff;
		paircoeff = "pair_coeff 2 3 lj/cut "+eps[0]+" "+sigma[0];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);
		paircoeff = "pair_coeff 2 4 lj/cut "+eps[1]+" "+sigma[1];
		LammpsInterface2.doCommand(lammpsSim, paircoeff);	
		if(checkMove(ebias)){
			rej=false;
			if(mccomments){System.out.print("accepted. "+step+" "+(e1-e0)+" "+e0+" "+e1+" "+bfactor+"\n");}
			eps0 = eps[0];
			eps1 = eps[1];
			sigma0 = sigma[0];
			sigma1 = sigma[1];
		}	
        else{
        	rej=true;
        	if(mccomments){System.out.print("rejected. "+step+" "+(e1-e0)+" "+e0+" "+e1+" "+bfactor+"\n");} 
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
		if(mccomments){System.out.print("  >> MC - LJ to MEAM move...");};
		
		//Creates new Ag atom in place of LJ atom
		box.setNMolecules(silver, numSolute);
		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
		box.setNMolecules(lj,0);
		//Remove atom from LAMMPS, Create new silver
		LammpsInterface2.doCommand(lammpsSim, "group lj"+ljtype+" type "+ljtype);
		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj"+ljtype);
		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single "+atomS.getPosition().getX(0)+" "+atomS.getPosition().getX(1)+" "+atomS.getPosition().getX(2)+" units box");
		//Change integrator to NPT
		LammpsInterface2.doCommand(lammpsSim, "unfix int2"); 
		LammpsInterface2.doCommand(lammpsSim, "fix int1 all npt 300.0 300.0 0.1 xyz 0.0 0.0 0.1 drag 1.0");
		checkMove(0);
/**		if(checkMove(ebias)){
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}	
		else{
**/        	rej=true;
        	if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");} 
            box.setNMolecules(lj,1);
            box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition().E(atomS.getPosition());    		
    		//Remove Silver from LAMMPS, Create new LJ atom
    		LammpsInterface2.doCommand(lammpsSim, "create_atoms "+ljtype+" single "+atomS.getPosition().getX(0)+" "+atomS.getPosition().getX(1)+" "+atomS.getPosition().getX(2)+" units box"); //LJ Type (old position atom)
    		box.removeMolecule(atomS.getParentGroup());
    		LammpsInterface2.doCommand(lammpsSim, "group lj"+ljtype+" type "+ljtype);
    		LammpsInterface2.doCommand(lammpsSim, "group silver type 1");
            LammpsInterface2.doCommand(lammpsSim, "delete_atoms overlap 0.1 silver lj"+ljtype);       
            //Change integrator to NVT
    		LammpsInterface2.doCommand(lammpsSim, "unfix int1"); 
    		LammpsInterface2.doCommand(lammpsSim, "fix int2 all nvt 300.0 300.0 0.1 drag 1.0");
 //      }	

	}
	
	public void MCmeam2lj(double eps, double sigma, double ebias){
		if(mccomments){System.out.print("  >> MC - MEAM to LJ move...");};
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
		//Change integrator to NVT
		LammpsInterface2.doCommand(lammpsSim, "unfix int1"); 
		LammpsInterface2.doCommand(lammpsSim, "fix int2 all nvt 300.0 300.0 0.1 drag 1.0");
		
/**		if(checkMove(ebias)){
			if(mccomments){System.out.print("accepted. "+step+" "+e1+" "+bfactor+"\n");} 
			rej=false;
		}
		else{ 
        	rej=true;
        	if(mccomments){System.out.print("rejected. "+step+" "+e0+" "+e1+" "+bfactor+"\n");} 
            box.setNMolecules(silver, numSolute);
    		atomS = box.getMoleculeList(silver).getMolecule(numSolute-1).getChildList().getAtom(0);
    		atomS.getPosition().E(box.getMoleculeList(lj).getMolecule(0).getChildList().getAtom(0).getPosition());
    		box.setNMolecules(lj,0);
    		LammpsInterface2.doCommand(lammpsSim, "group lj3 type 3");
    		LammpsInterface2.doCommand(lammpsSim, "delete_atoms group lj3");
    		LammpsInterface2.doCommand(lammpsSim, "create_atoms 1 single 0.0 0.0 0.0");
    		//Change integrator to NPT
			LammpsInterface2.doCommand(lammpsSim, "unfix int2"); 
			LammpsInterface2.doCommand(lammpsSim, "fix int1 all npt 300.0 300.0 0.1  xyz 0.0 0.0 0.1 drag 1.0");
		}	
**/	}
	
	public void doLJgetParams(){
		MoleculeArrayList marray = new MoleculeArrayList();
		IAtom atom1;
		atom1 = box.getMoleculeList(silver).getMolecule(0).getChildList().getAtom(0);
		marray.add(atom1.getParentGroup());
		IVectorMutable rij = space.makeVector();
		for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
			rij.Ev1Mv2(atom1.getPosition(),box.getMoleculeList().getMolecule(i).getChildList().getAtom(0).getPosition());
			if(rij.squared()<20){
				marray.add(box.getMoleculeList().getMolecule(i));
			}
		}
		
		WriteConfiguration writer = new WriteConfiguration(getSpace());
	    writer.setBox(box);
	    writer.setConfName("temp");
	    writer.actionPerformed();
	    
	    double[][] meamModes = new double[marray.getMoleculeCount()][3];
		double[][] tempModes = new double[marray.getMoleculeCount()][3];
	    
	    CalcVibrationalModes vib = new CalcVibrationalModes(lammpsSim);
        vib.setup(box, marray, space);
        vib.actionPerformed();
        for(int i=0; i<meamModes.length;i++){
        	for(int j=0; j<meamModes[0].length;j++){
        		meamModes[i][j] = vib.dForces[i][j];
        	}
        	System.out.println(meamModes[i][0]+" "+meamModes[i][1]+" "+meamModes[i][2]);
        }
	    
	    ConfigurationFile config = new ConfigurationFile("temp");
	    config.initializeCoordinates(box);
	    
		double eps=0.2;
		double modeSave=900000;
		double modeSum=0;
		double eee;
		String temp12;
		for(int i=0; i<100; i++){
			double sigma=1.80;
			for(int j=0; j<100; j++){
				temp12 = "pair_coeff 1 2 lj/cut "+eps+" "+sigma+"";
				// System.out.println(temp12);
				LammpsInterface2.doCommand(lammpsSim, temp12);
				
				// System.out.println(box.getMoleculeList(silver).getMolecule(0).getChildList().getAtom(0).getPosition());
				vib.actionPerformed();
				
				modeSum=0;
				
		        for(int k=0; k<meamModes.length;k++){
		        	for(int l=0; l<meamModes[0].length;l++){
			        	tempModes[k][l] = meamModes[k][l]  - vib.dForces[k][l];
			        	modeSum+=Math.abs(tempModes[k][l]);
		        	}
		        }
		        
		        //Reset Coordinates
		        config.initializeCoordinates(box);
		        eee = getLammpsEnergy(0,true,false);
		        
		        //System.out.println(eps+"   "+sigma+"   "+LammpsInterface2.getEnergy(lammpsSim)+"    "+modeSum);
		        if(modeSum<modeSave){
			    	System.out.println("***** "+eps+"   "+sigma+"   "+eee+"    "+modeSum+" *****");
			    	for(int k=0; k<meamModes.length;k++){
			    		//System.out.println(vib.dForces[k][0]+" "+vib.dForces[k][1]+" "+vib.dForces[k][2]);
			        	//System.out.println("> "+tempModes[k][0]+" "+tempModes[k][1]+" "+tempModes[k][2]);
			    	}
			    	modeSave=modeSum;
			    }
				sigma+=0.01;
			}
			modeSave=200;
			System.out.println(eps);
			eps+=0.01;
		} 
	}
	
	public void relaxNeighbors(IVectorMutable compressv, IVectorMutable expandv, double xm, double b){
		// CONTRACT AND EXPAND LATTICE AT OLD AND NEW POINTS
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
		
		if((e1-e0)<e0avg){
		e0avg =(e1-e0);
		average++;
		}
		
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
		
		eps0 = eps;
		eps1 = 0.0;
		
		sigma0 = sigma;
		sigma1 = sigma;
	}
		
	public void setComments(boolean commentOn, boolean mccommentOn){
		comments = commentOn;
		mccomments = mccommentOn;
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
    	String infile = "in.agmeam";
        final String APP_NAME = "SimMCMoveSwapSpeciesGB";
        final SimMCMoveSwapSpeciesGB sim = new SimMCMoveSwapSpeciesGB(tin,silver,temp1,boxVector,infile);
        
        sim.e0 = sim.getLammpsEnergy(2500,false,true);
                
        
        /** // LENNARD JONES INSERTION
        sim.doLJgetParams();
        //Params for Silver and 5 Stage LJ Energy Bias (MEAM-LJ100-LJ75-LJ50-LJ25-LJ0-LJ100-MEAM);
        sim.setParameters(0.10,2.62,new double[]{0.0,0.0,2.4,0.0,2.4,2.0,0.0});
        **/
        
        // MEAM INSERSION - State 1 (100<->75/25, 75/25<->50/50, 50/50<->25/75, 25/75<->100)
        sim.setParameters(0.0,0.0,new double[]{-0.25,0.0,0.0,-0.25});
        
        sim.setComments(true,true);
        sim.doMC(2500);
        
        System.out.println(sim.e0avg);
        
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
