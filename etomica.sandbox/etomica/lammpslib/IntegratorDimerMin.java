package etomica.lammpslib;

import java.io.FileWriter;

import etomica.action.WriteConfiguration;
import etomica.action.XYZWriter;
import etomica.action.activity.ActivityIntegrate;
<<<<<<< IntegratorDimerMin.java
import etomica.api.IAtom;
import etomica.api.IAtomPositioned;
=======
import etomica.api.IAtom;
>>>>>>> 1.51
import etomica.api.IBox;
<<<<<<< IntegratorDimerMin.java
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
=======
import etomica.api.IMoleculeList;
>>>>>>> 1.51
import etomica.api.IPotentialMaster;
import etomica.api.ISimulation;
import etomica.api.ISpecies;
import etomica.api.IVectorMutable;
import etomica.atom.AtomArrayList;
import etomica.atom.AtomLeafAgentManager;
import etomica.atom.AtomLeafAgentManager.AgentSource;
import etomica.atom.iterator.IteratorDirective;
import etomica.box.Box;
import etomica.config.ConfigurationFile;
<<<<<<< IntegratorDimerMin.java
=======
import etomica.data.meter.MeterPotentialEnergy;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.dimer.LammpsInterface;
>>>>>>> 1.51
import etomica.integrator.IntegratorBox;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.nbr.list.PotentialMasterList;
import etomica.potential.PotentialCalculationForceSum;
import etomica.space.ISpace;


/**
 * 	Henkelman's Dimer Method (Minimum Energy Path).
 * 
 * 	 | Finding saddle points on high dimensional surfaces.
 * 	 |    J. Chem. Phys., Vol. 111, No. 15, 15 October 1999.
 * 
 * 	@author msellers
 */

public class IntegratorDimerMin extends IntegratorBox implements AgentSource {

	public ISimulation sim;
	public IBox boxMin;
	public AtomLeafAgentManager atomAgent0, atomAgentMin;
	public PotentialCalculationForceSum force0, forceMin;
	public IteratorDirective allatoms;
	public FileWriter fileWriter;
	public ActivityIntegrate activityIntegrate;
	public XYZWriter xyzwrite;
	public FileWriter fwrite;
	public IVectorRandom [] N, Nstar;
	public IVectorMutable NDelta, NstarDelta;
	public IVectorMutable workVector1;
	public IVectorMutable workVector2;
	public IVectorMutable [] saddle;
	public IVectorMutable [] F0, Fmin, Fmin2;
	public IVectorMutable [] THETA, THETAstar;
	public IVectorMutable [] Fperp, Fminperp, Fmin2perp;
	public IVectorMutable [] Fstar, Fminstar, Fmin2star, Fstarperp;
	public IVectorMutable [] Fpara;
	public ISpecies [] movableSpecies;
	public AtomArrayList list, listMin;
	public int movableAtoms;
	public double deltaR;
	public double deltaTheta;
	public double stepLength;
	public double dTheta;
	public double Frot, dFrot;
	public double Fprimerot;
	public double sinDtheta, cosDtheta;
	public double eMin, e0;
	public int rotCounter, counter;
	public boolean rotate, minFound;
	boolean normalD;
	public String file;
	public WriteConfiguration writer;
	private final ISpace space;
	public CalcVibrationalModes vib;
	public long lammps;
	double e0prev1, e0prev2;
	
	public IntegratorDimerMin(ISimulation sim,  long library, IPotentialMaster potentialMaster,
			                  ISpecies[] species, ISpace _space) {
		this(sim, library, potentialMaster, sim.getRandom(), 1.0, species,  _space);
	}
	
	public IntegratorDimerMin(ISimulation aSim, long aLibrary, IPotentialMaster potentialMaster,
			                  IRandom arandom, double temperature,
			                  ISpecies[] aspecies, ISpace _space) {
		super(potentialMaster, temperature);
		this.sim = aSim;
	    this.lammps = aLibrary;
		this.force0 = new PotentialCalculationForceSum();
		this.forceMin = new PotentialCalculationForceSum();
		this.allatoms = new IteratorDirective();
		this.movableSpecies = aspecies;
		this.space = _space;
		
		stepLength = 0.005;
		deltaR = 1E-4;
		dTheta = 1E-15;
		dFrot = 0.005;
		rotCounter = 0;
		counter = 0;
		Frot = 1;
		rotate = true;
		minFound = false;
		e0 = 0;
		eMin = 0;
	}
	
	/**
	 * Set's the filename of the output of this integrator.  "-minimum" is appended
	 * to the string.
	 * 
	 * @param fileName String
	 */
	public void setFileName(String fileName){
	    file = fileName;
	}
	
	public String getFileName(){
	    return file;
	}
	
	public void setDirection(boolean normalDir){
	    normalD = normalDir;
	}

	public void reset() {
        super.reset();
        rotate = true;
        minFound = false;
        counter = 0;
	}
	
	public void doStepInternal(){
	    
		System.out.println((e0-eMin)+"   "+e0+"  "+eMin);
	    
		
		e0prev2 = e0prev1;
		e0prev1 = e0;
		
		walkDimer();
		
		if(counter%10==0){
			xyzwrite.actionPerformed();
			try {
				fwrite.write(""+e0);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
        if(eMin>e0){
            minFound = true;
            System.out.println(e0);
            quitSearch();
            return;
        }
        
		rotateDimerNewton();
	
        if(eMin>e0){
            minFound = true;
            System.out.println(e0);
            quitSearch();
            return;
        }
        
    	System.out.println(e0prev1+"   "+e0);
    	
		if(Math.abs(e0-e0prev1)<1E-9 || Math.abs(e0-e0prev2)<1E-9){
			System.out.println("Successive energies are similar.  Dimer has reached minimum.");
            minFound = true;
            System.out.println(e0);
            quitSearch();
            return;
		}
	
        
		counter++;
	}
	protected void setup() {
		super.setup();     
        movableAtoms = 0;
        for(int i=0; i<movableSpecies.length; i++){
            movableAtoms += box.getMoleculeList(movableSpecies[i]).getMoleculeCount();
        }
        N = new IVectorRandom [movableAtoms];
        F0 = new IVectorMutable [movableAtoms];
        Fmin = new IVectorMutable [movableAtoms];
        Fmin2 = new IVectorMutable [movableAtoms];
        Nstar = new IVectorRandom [movableAtoms];
        THETA = new IVectorMutable [movableAtoms];
        THETAstar = new IVectorMutable [movableAtoms];
        Fperp = new IVectorMutable [movableAtoms];
        Fminperp = new IVectorMutable [movableAtoms];
        Fmin2perp = new IVectorMutable [movableAtoms];
        Fstar = new IVectorMutable [movableAtoms];
        Fminstar = new IVectorMutable [movableAtoms];
        Fmin2star = new IVectorMutable [movableAtoms];
        Fstarperp = new IVectorMutable [movableAtoms];
        Fpara = new IVectorMutable [movableAtoms];
        
        for (int i=0; i<movableAtoms; i++){
            N[i] = space.makeVector();
            Nstar[i] = space.makeVector();
            F0[i] = space.makeVector();
            Fmin[i] = space.makeVector();
            Fmin2[i] = space.makeVector();
            Nstar[i] = space.makeVector();
            NDelta = space.makeVector();
            NstarDelta = space.makeVector();
            THETA[i] = space.makeVector();
            THETAstar[i] = space.makeVector();
            Fperp[i] = space.makeVector();
            Fminperp[i] = space.makeVector();
            Fmin2perp[i] = space.makeVector();
            Fstar[i] = space.makeVector();
            Fminstar[i] = space.makeVector();
            Fmin2star[i] = space.makeVector();
            Fstarperp[i] = space.makeVector();
            Fpara[i] = space.makeVector();
        }  
	        
		boxMin = new Box(box.getBoundary(), space);
        sim.addBox(boxMin);

        if(potentialMaster instanceof PotentialMasterListDimer){
            getEventManager().addListener(((PotentialMasterList)potentialMaster).getNeighborManager(boxMin)); 
         }

        //energyBox0 = new MeterPotentialEnergy(this.potential);
        //energyBoxMin = new MeterPotentialEnergy(this.potential);
         
        //energyBox0.setBox(box);
        //energyBoxMin.setBox(boxMin);
         
		// Offset Rmin (half-dimer end) from initial configuration, along N.		
		atomAgent0 = new AtomLeafAgentManager(this, box);
		atomAgentMin = new AtomLeafAgentManager(this, boxMin);
		
		force0.setAgentManager(atomAgent0);
		forceMin.setAgentManager(atomAgentMin);
		
//		ISpecies [] species = sim.getSpeciesManager().getSpecies();
		
		for(int i=0; i<sim.getSpeciesCount(); i++){
			boxMin.setNMolecules(sim.getSpecies(i),
					box.getNMolecules(sim.getSpecies(i)));
		}
		    	    	
		// Atom list for movable and offset atoms
		list = new AtomArrayList();
        listMin = new AtomArrayList();
		
		for(int i=0; i<movableSpecies.length; i++){
            IMoleculeList molecules = box.getMoleculeList(movableSpecies[i]);
            IMoleculeList molecules1 = boxMin.getMoleculeList(movableSpecies[i]);
            for (int j=0; j<molecules.getMoleculeCount(); j++) {
                list.add(molecules.getMolecule(j).getChildList().getAtom(0));
                listMin.add(molecules1.getMolecule(j).getChildList().getAtom(0));
            }
		}  
		
        ConfigurationFile config = new ConfigurationFile(file+"_saddle");
        config.initializeCoordinates(box);        
        
        //Read in coordinates for boxMin atom locations
        ConfigurationFile configFile = new ConfigurationFile(file+"_A_saddle");
        configFile.initializeCoordinates(boxMin);
        writer = new WriteConfiguration(space);
        writer.setConfName(file+"_A_minimum");
        xyzwrite = new XYZWriter(box);
        xyzwrite.setFileName(file+"_A_minimum.xyz");
        try {
			fwrite = new FileWriter(file+"_A_minimum.path");
		} catch (IOException e) {
			e.printStackTrace();
		}
        
		if(normalD==true){
            // Read in coordinates for opposite boxMin atom locations
            ConfigurationFile configFile1 = new ConfigurationFile(file+"_B_saddle");
            configFile1.initializeCoordinates(boxMin);
            writer.setConfName(file+"_B_minimum");
            xyzwrite.setFileName(file+"_B_minimum.xyz");
            try {
    			fwrite = new FileWriter(file+"_B_minimum.path");
    		} catch (IOException e) {
    			e.printStackTrace();
    		}
        }
        
        dimerNormal();

	}
	
	/**
	 * Rotates the dimer in potential energy hyperspace and aligns it with the surface's lowest 
	 * curvature mode.  Using Newton's finite difference method, the rotational force perpendicular to the dimer's
	 * orientation is minimized.  Minimization criteria is dependent on dFrot and rotCounter.
	 * For minimum energy path tracing, rotCounter criteria is commented out to ensure convergence
	 * to lowest curvature mode before stepping the dimer.
	 */
	public void rotateDimerNewton(){
	    dimerNormal();
	    dimerForces(Fmin, F0, Fmin2);
	    //System.out.println(e0);
	    //System.out.println(eMin);
	    //System.out.println("----------");
	    Frot = 1;
	    rotCounter=0;
		while(true){
		    dimerForcesStar(Fmin, Fmin2, F0);
			// Calculate F|_
			dimerForcePerp(N, Fmin, Fperp);
            // Find THETA and normalize
            double mag = 0;
            for(int i=0; i<Fperp.length; i++){
                mag += Fperp[i].squared();
            }
            mag = 1.0 / Math.sqrt(mag);
            
            for(int i=0; i<THETA.length; i++){
                THETA[i].E(Fperp[i]);
                THETA[i].TE(mag);
            }
            // NEWTON'S LINE MINIMIZATION FOR ROTATIONAL FORCE	
            Frot = 0;
            for(int i=0; i<Fperp.length; i++){
                  Frot += Fperp[i].dot(THETA[i]);
            } 
            // Leave loop if Frot at current location is small
            if(Frot<dFrot){
                //System.out.println("rotations: "+rotCounter);
                break;
            }            
            sinDtheta = Math.sin(dTheta);
            cosDtheta = Math.cos(dTheta);
			// Find Nstar and THETAstar after dTheta rotation
	        IVectorMutable workVectorN1 = space.makeVector();
			for(int i=0; i<N.length; i++){
				workVectorN1.Ea1Tv1(cosDtheta, N[i]);
				workVectorN1.PEa1Tv1(sinDtheta, THETA[i]);
				Nstar[i].E(workVectorN1);
				workVectorN1.Ea1Tv1(-sinDtheta, N[i]);
				workVectorN1.PEa1Tv1(cosDtheta, THETA[i]);
				THETAstar[i].E(workVectorN1);
			}           
            // Use Nstar to offset(rotate) replicas
            IVectorMutable workVector1 = space.makeVector();
            for(int i=0; i<Nstar.length; i++){
                workVector1.E(list.getAtom(i).getPosition());
                workVector1.PEa1Tv1(deltaR, Nstar[i]);
                listMin.getAtom(i).getPosition().E(workVector1);
            }
			// Calculate F*'s
			dimerForcesStar(Fminstar, Fmin2star, F0);
			// Calculate F*|_
			dimerForcePerp(Nstar, Fminstar, Fstarperp);
			// second part of Frot
            for(int i=0; i<Fstarperp.length; i++){
                Frot += Fstarperp[i].dot(THETAstar[i]);
            }
            Frot = Frot/2.0;
			Fprimerot = 0;
			for(int i=0; i<Fstar.length; i++){
				Fprimerot += Fstarperp[i].dot(THETAstar[i]);
			}
			for(int i=0; i<Fstar.length; i++){
				Fprimerot -= Fperp[i].dot(THETA[i]);
			}
			Fprimerot = Fprimerot / dTheta;
			// Find actual rotation angle to minimize energy
			deltaTheta = -0.5 * Math.atan(2.0*Frot/Fprimerot) - dTheta/2.0;
			if(Fprimerot>0){deltaTheta = deltaTheta + Math.PI/2.0;}
			//if(deltaTheta > 0.25){deltaTheta = 0.25;}
			//System.out.println("deltaTheta "+deltaTheta+"     Frot "+Frot+"    Fprimerot "+Fprimerot);
			/*
            // Check deltaTheta vs. dTheta and adjust step size
            if (deltaTheta < 0){
                    dTheta /= 10;
                    System.out.println("dTheta changed to "+dTheta);
                    if (deltaTheta < -dTheta){
                        deltaTheta = -dTheta;
                    }
            }
            */
            double sindeltaTheta = Math.sin(deltaTheta);
            double cosdeltaTheta = Math.cos(deltaTheta); 
            // Find N**
            IVectorMutable workVectorN2 = space.makeVector();
            for(int i=0; i<N.length; i++){               
                workVectorN2.Ea1Tv1(cosdeltaTheta, Nstar[i]);
                workVectorN2.PEa1Tv1(sindeltaTheta, THETAstar[i]);
                N[i].E(workVectorN2);
            }            
            // Use new N to offset(rotate) replica
            IVectorMutable workVector2 = space.makeVector();
            for(int i=0; i<N.length; i++){             
                workVector2.E(list.getAtom(i).getPosition());
                workVector2.PEa1Tv1(deltaR, N[i]);
                ((IAtomPositioned)listMin.getAtom(i)).getPosition().E(workVector2);
            }     			
			rotCounter++;
			if(rotCounter>100){   
			    break;
			}
		}
		//System.out.println(rotCounter);
	}
	
	/**
	 *  Moves the half-dimer stepLength*N towards the energy minimum.
	 */
	public void walkDimer(){
	    
		IVectorMutable workvector;
		workvector = space.makeVector();
		
		for(int i=0; i<N.length; i++){
			workvector.Ea1Tv1(stepLength, N[i]);
			list.getAtom(i).getPosition().PE(workvector);
			listMin.getAtom(i).getPosition().PE(workvector);
		}
		dimerNormal();
	}
	
	/**
	 * Called after criteria is met in the rotateDimer method.  If F0dotN is 
	 * negative, the dimer has reached the minimum in an energy basin.
	 * 
	 */
	public void quitSearch(){
        writer.setBox(box);
        writer.actionPerformed();
        
        try {
			fwrite.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
        
		IMoleculeList loopSet = box.getMoleculeList();
	    IVectorMutable workVector = space.makeVector();
	    for(int i=0; i<loopSet.getMoleculeCount(); i++){
	        workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
	        LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
	    }
	    LammpsInterface.doLammpsStep(lammps, 1);
	    e0 = LammpsInterface.getEnergy(lammps);
	    
        activityIntegrate.setMaxSteps(0);
        
	}
	
	/**
	 * Computes an n-dimensional vector in potential energy hyperspace, pointing 
	 * in the direction of the dimer (intersecting both simulation boxes).
	 * 
	 */
	protected void dimerNormal(){
        double mag=0;
        IVectorMutable workvector;
        workvector = space.makeVector();
        
        // N =  (Rmin - R0) / (deltaR)
        for (int i=0; i<N.length; i++){ 
            workvector.E(listMin.getAtom(i).getPosition());
            workvector.ME(list.getAtom(i).getPosition());
            N[i].E(workvector);
            mag += workvector.squared();
        }
        
        mag = Math.sqrt(mag);
        //System.out.println(mag);
        mag = 1.0/mag;
        for (int i=0; i<N.length; i++){
            N[i].TE(mag);
        }
	}
			
	/**
	 * Resets forces in boxes 0 and min, calls potential.calculate, and copies over
	 * the new forces to local arrays.  Approximates the force in virtual box 2.
	 * 
	 * @param aF1 Array of vectors holding the forces in box min
	 * @param aF Array of vectors holding the forces in box 0
	 * @param aF2 Array of vectors holding the forces in virtual box 2
	 */

	protected void dimerForces(IVectorMutable [] aF1, IVectorMutable [] aF, IVectorMutable [] aF2){
		/*
		force0.reset();
		forceMin.reset();
		
		potentialMaster.calculate(box, allatoms, force0);
		potentialMaster.calculate(boxMin, allatoms, forceMin);
		
		// Copy forces of dimer ends (R1, R2) to local array
		for(int i=0; i<aF1.length; i++){
			
			aF[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgent0.getAgent((IAtom)list.getAtom(i))).force());
			aF1[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgentMin.getAgent((IAtom)listMin.getAtom(i))).force());
			aF2[i].Ea1Tv1(2.0, aF[i]);
			aF2[i].ME(aF1[i]);
			
		}
		*/
		
	    //LAMMPS
	    //box0
		IMoleculeList loopSet = box.getMoleculeList();
	    IVectorMutable workVector = space.makeVector();
	    for(int i=0; i<loopSet.getMoleculeCount(); i++){
	        workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
	        LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
	    }
	    LammpsInterface.doLammpsStep(lammps, 1);
	    int atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(loopSet.getMolecule(i).getType()==movableSpecies[0]){
        	    LammpsInterface.getForce(lammps, i, aF[atom]);
	            aF[atom].setX(0, ElectronVolt.UNIT.toSim(aF[atom].x(0)));
	            aF[atom].setX(1, ElectronVolt.UNIT.toSim(aF[atom].x(1)));
	            aF[atom].setX(2, ElectronVolt.UNIT.toSim(aF[atom].x(2)));
	            //System.out.println(aF[atom]);
	            aF2[atom].Ea1Tv1(2.0, aF[atom]);
	            atom++;
        	}
        }
        e0 = LammpsInterface.getEnergy(lammps);
        
        //box1
        loopSet = boxMin.getMoleculeList();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)((IMolecule)loopSet.getMolecule(i)).getChildList().getAtom(0)).getPosition());
            LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
        }
        LammpsInterface.doLammpsStep(lammps, 1);
        atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
        	    LammpsInterface.getForce(lammps, i, aF1[atom]);
	            aF1[atom].setX(0, ElectronVolt.UNIT.toSim(aF1[atom].x(0)));
	            aF1[atom].setX(1, ElectronVolt.UNIT.toSim(aF1[atom].x(1)));
	            aF1[atom].setX(2, ElectronVolt.UNIT.toSim(aF1[atom].x(2)));
	            aF2[atom].ME(aF1[atom]);
	            atom++;
        	}
        }
        eMin = LammpsInterface.getEnergy(lammps);
        //System.out.println(e0+"     "+eMin);
	}
		
	/**
	 * Used in the middle of the rotateDimer method.  Resets forces in box min only (we are rotating
	 * the dimer around a fixed center).  Calls potential.calculate, and copies over the new forces
	 * to local array.  Approximates the force in virtual box 2.
	 * 
	 * @param aF1star Array of vectors holding the forces in box min
	 * @param aF2star Array of vectors holding the forces in virtual box 2
	 * @param aF Array of vectors holding the forces in box 0
	 */
	protected void dimerForcesStar(IVectorMutable [] aF1star, IVectorMutable [] aF2star, IVectorMutable [] aF){
        /*
		forceMin.reset();
        potential.calculate(boxMin, allatoms, forceMin);
        
     // Copy forces of dimer end and center (R1, R) to local array
        for(int i=0; i<aF1star.length; i++){
            aF1star[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgentMin.getAgent((IAtom)listMin.getAtom(i))).force());
            aF2star[i].Ea1Tv1(2.0, aF[i]);
            aF2star[i].ME(aF1star[i]);
        }
        */

	    //box1
		IMoleculeList loopSet = boxMin.getMoleculeList();
	    IVectorMutable workVector = space.makeVector();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)((IMolecule)loopSet.getMolecule(i)).getChildList().getAtom(0)).getPosition());
            LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
        }
        LammpsInterface.doLammpsStep(lammps, 1);
        int atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
        	    LammpsInterface.getForce(lammps, i, aF1star[atom]);
        	    aF1star[atom].setX(0, ElectronVolt.UNIT.toSim(aF1star[atom].x(0)));
        	    aF1star[atom].setX(1, ElectronVolt.UNIT.toSim(aF1star[atom].x(1)));
        	    aF1star[atom].setX(2, ElectronVolt.UNIT.toSim(aF1star[atom].x(2)));
                aF2star[atom].Ea1Tv1(2.0, aF[atom]);
                aF2star[atom].ME(aF1star[atom]);  
                atom++;
        	}
        }
        eMin = LammpsInterface.getEnergy(lammps);
    }
	
	/**
	 * Finds the component of the dimer's total force that is perpendicular to the normal vector.
	 * 
	 * @param aN Array of vectors that create an n-dimensional vector parallel to the orientation of the dimer.
	 * @param aF1 Array of vectors holding the forces in box min
	 * @param aFperp Array of vectors that create an n-dimensional vector perpendicular to the orientation of the dimer.
	*/
	protected void dimerForcePerp(IVectorRandom [] aN, IVectorMutable [] aF1, IVectorMutable [] aFperp){
		
		double mag1 = 0;
		
		// F|_ = F1 - (F1[dot]N)*N
		for(int i=0; i<aF1.length; i++){
			mag1 += aF1[i].dot(aN[i]);
		}
		for (int i=0; i<aFperp.length; i++){
			aFperp[i].E(aF1[i]);
			aFperp[i].PEa1Tv1(-mag1, aN[i]);	
			aFperp[i].TE(1.0/deltaR);
		}

	}
	
	public void setActivityIntegrate(ActivityIntegrate ai){
		activityIntegrate = ai;
	}
	
	public Class getAgentClass() {
		return IntegratorVelocityVerlet.MyAgent.class;
	}

	public Object makeAgent(IAtom a) {
		return new IntegratorVelocityVerlet.MyAgent(space);
	}

	public void releaseAgent(Object agent, IAtom atom) {
		// TODO Auto-generated method stub	
	}
	
    static {
        System.loadLibrary("LAMMPS");
//        System.loadLibrary("lmp_thomas");
    }
	
}
