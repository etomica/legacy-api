package etomica.lammpslib;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import etomica.action.WriteConfiguration;
import etomica.action.activity.ActivityIntegrate;
<<<<<<< IntegratorDimerRT.java
import etomica.api.IAtom;
import etomica.api.IAtomPositioned;
=======
import etomica.api.IAtom;
>>>>>>> 1.76
import etomica.api.IBox;
<<<<<<< IntegratorDimerRT.java
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
=======
import etomica.api.IMoleculeList;
>>>>>>> 1.76
import etomica.api.IPotentialMaster;
import etomica.api.IRandom;
import etomica.api.ISimulation;
import etomica.api.ISpecies;
import etomica.api.IVectorMutable;
import etomica.atom.AtomArrayList;
import etomica.atom.AtomLeafAgentManager;
import etomica.atom.MoleculeArrayList;
import etomica.atom.AtomLeafAgentManager.AgentSource;
import etomica.atom.iterator.IteratorDirective;
import etomica.box.Box;
import etomica.data.meter.MeterPotentialEnergy;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerRT;
import etomica.dimer.LammpsInterface;
import etomica.dimer.PotentialMasterListDimer;
import etomica.integrator.IntegratorBox;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.nbr.list.PotentialMasterList;
import etomica.potential.PotentialCalculationForceSum;
import etomica.space.ISpace;
import etomica.space.IVectorRandom;


/**
 * 	Henkelman's Dimer Method (Rotation and Translation).
 * 
 * 	 | Finding saddle points on high dimensional surfaces.
 * 	 |    J. Chem. Phys., Vol. 111, No. 15, 15 October 1999.
 * 
 * 	@author msellers
 */

public class IntegratorDimerRT extends IntegratorBox implements AgentSource {

	public IBox box1, box2;
	public ISimulation sim;
	public double deltaR;
	public double dTheta, deltaXl, dXl;
	public double deltaTheta;
	public double curvature;
	public double deltaXmax;
	public double Frot, Frot2, Fprimerot, dFrot;
	public double saddleT;
	public double dFsq;
	public double gammai;
	public double saddleEnergy;
	public int rotNum;
	public int counter, rotCounter;
	public int movableAtoms;
	public boolean rotate, ortho, ortho2, startOrtho, saddleFound;
	public double energyBox1, energyBox2, energyBox0;
	public IVectorMutable [] THETA, THETAstar, THETAstarstar;
	public IVectorMutable [] F, F1, F2;
	public IVectorMutable [] Fperp, F1perp, F2perp;
	public IVectorMutable [] Gperp, Gperplast, Fperplast;
	public IVectorMutable [] Fstar, F1star, F2star, Fstarperp;
	public IVectorMutable [] Feff, Feffstar, Fr, Fpara;
	public IVectorMutable [] deltaV, V;
	public IVectorMutable [] newPosition;
	public IVectorMutable [] workVector3;
	public IVectorRandom [] N, Nstar, Neff, N1;
	public IVectorMutable NDelta, NstarDelta;
	public IVectorMutable workVector1;
	public IVectorMutable workVector2;
	public IRandom random1;
	public ISpecies [] movableSpecies;
	public PotentialCalculationForceSum force0, force1, force2;
	public AtomArrayList list, list1, list2;
	public AtomLeafAgentManager atomAgent0, atomAgent1, atomAgent2;
	public IteratorDirective allatoms;
	public String file;
	public ActivityIntegrate activityIntegrate;
	public CalcVibrationalModes vib;
	public long lammps;
	private final ISpace space;
	public FileWriter pos;

	
	
	public IntegratorDimerRT(ISimulation sim, long library, IPotentialMaster potentialMaster,
			                 ISpecies[] species, ISpace _space) {
		this(sim, library, potentialMaster, sim.getRandom(), 1.0, species, _space);
	}
	
	public IntegratorDimerRT(ISimulation aSim, long aLibrary, IPotentialMaster potentialMaster,
			                 IRandom random, double temperature,
			                 ISpecies[] aspecies, ISpace _space) {
		super(potentialMaster, temperature);
		//makeLammpsSim("/home/msellers/Java-Workspace/in.sn");
		this.random1 = random;
		this.sim = aSim;
		this.lammps = aLibrary;
		this.force0 = new PotentialCalculationForceSum();
		this.force1 = new PotentialCalculationForceSum();
		this.force2 = new PotentialCalculationForceSum();
		this.allatoms = new IteratorDirective();
		this.movableSpecies = aspecies;
		this.space = _space;
				
		deltaR = 1E-4;
		dXl = 1E-5;
		deltaXl = 0;
		deltaXmax = 0.005;
		
		deltaTheta = 0;
		dTheta = 1E-4;
		
		dFsq = 0.01;
		
		Frot = 1.0;
		dFrot = 0.1;
		counter = 0;

	}
	
	public void setRotNum(int num){
		this.rotNum = num;
	}
	
	/**
	 * Set's the Dimer search's orthogonality criteria.
	 * @param orthoON (if true) Once the rotation scheme has converged to a small enough Frot value, the orthogonal search is started.
	 * @param o2 (if true) Launches another orthogonal path search after the primary orthogonal search.
	 * 
	 */
	public void setOrtho(boolean orthoON, boolean o2){
		startOrtho = orthoON;
		ortho2 = o2;
		if(startOrtho==true){
		    rotNum=100;
		}
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
	
	
	public void doStepInternal(){
		
		if(counter==0){System.out.println("Searching...");}
				
		//if(counter%20==0){
		//System.out.println(counter+"  "+energyBox0+"  "+energyBox1);
			//}
		//if(counter<2){rotNum=20;}
		//if(counter>2){rotNum=3;}
		
		rotateDimerNewton();
		
		translateDimerQuickmin();

		counter++;
	}

	protected void printDiagnosticsR(){
		System.out.println("<-----------STEP "+counter+"----------->");
		System.out.println("__________after rotation");
		System.out.println("N[0]      "+N[0]);
		System.out.println("F[0]      "+F[0]);
		System.out.println("F1[0]     "+F1[0]);
		System.out.println("Curvature "+curvature);
	}
	
	protected void printDiagnosticsT(){
		System.out.println("<-----------STEP "+counter+"----------->");
		System.out.println("__________after translation");
		System.out.println("F[0]      "+F[0]);
		System.out.println("F1[0]     "+F1[0]);
		System.out.println("Curvature "+curvature);
		System.out.println("Feff[0]    "+Feff[0]);
		System.out.println("Feffstar[0]"+Feffstar[0]);
		System.out.println("Steplength "+deltaXl);
		System.out.println("N[0]      "+N[0]);
		System.out.println("Neff[0]   "+Neff[0]);
	}
	
	public void reset() {
	    super.reset();
        
		deltaR = 1E-4;
		dXl = 1E-3;
		deltaXl = 0;
		deltaXmax = 0.01;
        
        deltaTheta = 0;
        dTheta = 1E-8;
        
        dFsq = 0.01;
        
        Frot = 1.0;
        dFrot = 0.1;
        
        counter = 0;

	    saddleFound=false;
        counter = 0;
	 // Use random unit array for N, N1 to generate dimer.

        // Normalize N, N1
        double mag = 0;
        double magN1 = 0;
        for (int i=0; i<N.length; i++){ 
            N1[i].setRandomSphere(random1);
            N[i].setRandomSphere(random1);
           // N[0].setX(0,0);
            mag += N[i].squared();
            magN1 += N1[i].squared();
        }
        mag = 1.0 / Math.sqrt(mag);
        magN1 = 1.0 / Math.sqrt(magN1);
        for (int i=0; i<N.length; i++){
            N[i].TE(mag);
            N1[i].TE(magN1);
        }
		
        
        // Set positions of atoms in replicas equal to box
        for(int i=0; i<box.getLeafList().getAtomCount(); i++){
            ((IAtomPositioned)box1.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            ((IAtomPositioned)box2.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
        }
        // Offset replicas
        for(int i=0; i<N.length; i++){
            list1.getAtom(i).getPosition().PEa1Tv1(deltaR, N[i]);
            list2.getAtom(i).getPosition().PEa1Tv1(-deltaR, N[i]);
        }
        
        //dimerForceCenter(F);
        dimerForces(F1, F2, F);
        
        System.out.println("Testing dimer direction...");
        System.out.println(energyBox0+"  "+energyBox1);
        	if(energyBox0>energyBox1){
        		System.out.println("Dimer pointed downhill, swapping ends.");
	            for(int i=0; i<N.length; i++){
	                  ((IAtomPositioned)list1.getAtom(i)).getPosition().PEa1Tv1(-2.0*deltaR, N[i]);
	                  ((IAtomPositioned)list2.getAtom(i)).getPosition().PEa1Tv1(2.0*deltaR, N[i]);
	            }
	            dimerForces(F1, F2, F);
	            System.out.println(energyBox0+"  "+energyBox1);
	            dimerNormal();
        	}

        for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
            if(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition().isNaN()){
                throw new RuntimeException();
            }
        }    
	}
	
	/**
	 * Takes in a current configuration of atoms (Rc) and creates a dimer of their positions (R1 and R2).
	 * (R2)-------[Rc]-------(R1) ===> N
	 */
	protected void setup() {
		super.setup();
			
		movableAtoms = 0;
		for(int i=0; i<movableSpecies.length; i++){
		    movableAtoms += box.getMoleculeList(movableSpecies[i]).getMoleculeCount();
		}
		workVector1 = space.makeVector();
        workVector2 = space.makeVector();
		
        N = new IVectorRandom [movableAtoms];
        Neff = new IVectorRandom [movableAtoms];
        Nstar = new IVectorRandom [movableAtoms];
        N1 = new IVectorRandom [movableAtoms];
        THETA = new IVectorMutable [movableAtoms];
        THETAstar = new IVectorMutable [movableAtoms];
        THETAstarstar = new IVectorMutable [movableAtoms];
        F = new IVectorMutable [movableAtoms];
        F1 = new IVectorMutable [movableAtoms];
        F2 = new IVectorMutable [movableAtoms];
        Fperp = new IVectorMutable [movableAtoms];
        Fperplast = new IVectorMutable [movableAtoms];
        Gperp = new IVectorMutable [movableAtoms];
        Gperplast = new IVectorMutable [movableAtoms];
        F1perp = new IVectorMutable [movableAtoms];
        F2perp = new IVectorMutable [movableAtoms];
        Fstar = new IVectorMutable [movableAtoms];
        F1star = new IVectorMutable [movableAtoms];
        F2star = new IVectorMutable [movableAtoms];
        Fstarperp = new IVectorMutable [movableAtoms];
        Feff = new IVectorMutable [movableAtoms];
        Feffstar = new IVectorMutable [movableAtoms];
        Fr = new IVectorMutable [movableAtoms];
        Fpara = new IVectorMutable [movableAtoms];
        deltaV = new IVectorMutable [movableAtoms];
        V = new IVectorMutable [movableAtoms];
        newPosition = new IVectorMutable [movableAtoms];
        workVector3 = new IVectorMutable [movableAtoms];
        
        for(int i=0; i<movableAtoms; i++){
            N[i] = (IVectorRandom)space.makeVector();
            Neff[i] = (IVectorRandom)space.makeVector();
            Nstar[i] = (IVectorRandom)space.makeVector();
            N1[i] = (IVectorRandom)space.makeVector();
            THETA[i] = space.makeVector();
            THETAstar[i] = space.makeVector();
            THETAstarstar[i] = space.makeVector();
            F[i] = space.makeVector();
            F1[i] = space.makeVector();
            F2[i] = space.makeVector();
            Fperp[i] = space.makeVector();
            Fperplast[i] = space.makeVector();
            Gperp[i] = space.makeVector();
            Gperplast[i] = space.makeVector();
            F1perp[i] = space.makeVector();
            F2perp[i] = space.makeVector();
            Fstar[i] = space.makeVector();
            F1star[i] = space.makeVector();
            F2star[i] = space.makeVector();
            Fstarperp[i] = space.makeVector();
            Feff[i] = space.makeVector();
            Feffstar[i] = space.makeVector();
            Fpara[i] = space.makeVector();
            deltaV[i] = space.makeVector();
            V[i] = space.makeVector();
            newPosition[i] = space.makeVector();
            workVector3[i] = space.makeVector();
        }
				
		box1 = new Box(box.getBoundary(), space);
		box2 = new Box(box.getBoundary(), space);
		
		sim.addBox(box1);
		sim.addBox(box2);
		
		if(potentialMaster instanceof PotentialMasterListDimer){
		   this.getEventManager().addListener(((PotentialMasterList)potentialMaster).getNeighborManager(box1)); 
		}
		atomAgent0 = new AtomLeafAgentManager(this, box);
		atomAgent1 = new AtomLeafAgentManager(this, box1);
		atomAgent2 = new AtomLeafAgentManager(this, box2);

		force0.setAgentManager(atomAgent0);
		force1.setAgentManager(atomAgent1);
		force2.setAgentManager(atomAgent2);
		
		for(int i=0; i<sim.getSpeciesCount(); i++){
			ISpecies species = sim.getSpecies(i);
			box1.setNMolecules(species, box.getNMolecules(species));
			box2.setNMolecules(species, box.getNMolecules(species));
		}
		
		// Atom list for movable and offset atoms
		list = new AtomArrayList();
		list1 = new AtomArrayList();
		list2 = new AtomArrayList();
		
		for(int i=0; i<movableSpecies.length; i++){
            IMoleculeList molecules = box.getMoleculeList(movableSpecies[i]);
            IMoleculeList molecules1 = box1.getMoleculeList(movableSpecies[i]);
            IMoleculeList molecules2 = box2.getMoleculeList(movableSpecies[i]);
            for (int j=0; j<molecules.getMoleculeCount(); j++) {
                list.add(molecules.getMolecule(j).getChildList().getAtom(0));
                list1.add(molecules1.getMolecule(j).getChildList().getAtom(0));
                list2.add(molecules2.getMolecule(j).getChildList().getAtom(0));
            }
		}	
				
	}
		

    /**
     * Rotates the dimer in potential energy hyperspace and aligns it with the surface's lowest 
     * curvature mode.  Using Newton's finite difference method, the rotational force perpendicular to the dimer's
     * orientation is minimized.  Minimization criteria is dependent on dFrot and rotCounter.
     * 
     * 
     */
	public void rotateDimerNewton(){
		rotCounter=0;
		
	    // Calculate new F
        dimerForces(F1, F2, F);
                
        double sinDtheta;
        double cosDtheta;
        IVectorMutable workVectorN1 = space.makeVector();
        IVectorMutable workVector1 = space.makeVector();
        IVectorMutable workVectorN2 = space.makeVector();
        IVectorMutable workVector2 = space.makeVector();
        double sindeltaTheta;
        double cosdeltaTheta;
        
        //if(counter>15){return;}
        
	    while(true){
	    	
	    	double normal=0;
	    	for(int i=0; i<N.length; i++){
	    		normal+=N[i].squared();
	    	}
			if(normal<0.99){
				throw new RuntimeException();
			}
			
	        // Calculate F1
            dimerForcesStar(F1, F2, F);
            
	        
	    	//ORTHOGONAL DIMER SEARCH
	    	if(ortho){
				//Remove N1 component from F's and orthogonal N
	    		// F1-(F1[dot]N1)*N1; F2-(F2[dot]N1)*N1; N-(N[dot]N1)*N1
	    		double magF1 = 0;
	    		double magF2 = 0;
	    		double magN1 = 0;
	    		for(int i=0; i<F1.length; i++){
	    	        magF1 += F1[i].dot(N1[i]);
	    	        magF2 += F2[i].dot(N1[i]);
	    			magN1 += N[i].dot(N1[i]);
	    		}
	    		for (int i=0; i<F1.length; i++){
	    			F1[i].PEa1Tv1(-magF1, N1[i]);	
	    			F2[i].PEa1Tv1(-magF2, N1[i]);
	    			N[i].PEa1Tv1(-magN1,N1[i]);
	    		}
        		System.out.println("ortho N: "+N[0].getX(0)+"    "+N[0].getX(1)+"    "+N[0].getX(2));
        		System.out.println(" lcm N1: "+N1[0].getX(0)+"    "+N1[0].getX(1)+"    "+N1[0].getX(2));
        		
        		//N is now a vector orthogonal to N1, check curvatures along each;
                
                testOrthoCurvature(N1, N);
                
			}
	    	
			// Calculate F|_
			dimerForcePerp(N, F1, F2, Fperp);
			
			/**
			//CONJUGATE GRADIENT SEARCH FOR ROTATIONAL PLANE
			// Find Gperp = Fperp + gammai*|Gperplast|*THETAstarstar
			//gammaI = ( (Fperpi - Fperpi-1)[dot]Fperpi )/(Fperpi[dot]Fperpi)
			double gt = 0.0;
			double gb = 0.0;
			for(int i=0; i<Fperp.length; i++){
				Fperplast[i].TE(-1.0);
				Fperplast[i].PE(Fperp[i]);
				gt += Fperplast[i].dot(Fperp[i]);
			}
			for(int i=0; i<Fperp.length; i++){
				gb += Fperp[i].dot(Fperp[i]);
			}
			gammai = gt/gb;
			double magG=0;
			for(int i=0; i<Gperplast.length; i++){
				magG += Gperplast[i].squared();
			}
			magG = Math.sqrt(magG);
			for(int i=0; i<Gperp.length; i++){
				Gperp[i].E(THETAstarstar[i]);
				Gperp[i].TE(gammai*magG);
				Gperp[i].PE(Fperp[i]);
			}			
			if(rotCounter==0){
				for(int i=0; i<Gperp.length; i++){
					Gperp[i].E(Fperp[i]);
				}
			}
			**/
			// Find THETA and normalize
			double mag = 0;
			for(int i=0; i<Fperp.length; i++){
				//mag += Gperp[i].squared();
				mag += Fperp[i].squared();
			}
			mag = 1.0 / Math.sqrt(mag);		
			for(int i=0; i<THETA.length; i++){
			    //THETA[i].E(Gperp[i]);
			    THETA[i].E(Fperp[i]);
				THETA[i].TE(mag);
			}
			
			/*
			//Copy arrays to remember for next iteration
			for(int i=0; i<Fperplast.length; i++){
				Gperplast[i].E(Gperp[i]);
				Fperplast[i].E(Fperp[i]);
				THETAstarstar[i].E(THETA[i]);
			}
			*/
			
            // NEWTON'S LINE MINIMIZATION FOR ROTATIONAL FORCE	
			Frot = 0;
            for(int i=0; i<Fperp.length; i++){
                  //Frot += Gperp[i].dot(THETA[i]);
                  Frot += Fperp[i].dot(THETA[i]);
            }
            //System.out.println("theta    : "+THETA[0]);
            //System.out.println("Frota    : "+Frot);
            // Leave loop if Frot at current location is small
           
            if(Frot<dFrot){            	
            	//First time after converging to lowest curvature mode, N is copied to N1
            	//Start ortho
            	if(startOrtho){
            		System.out.println("Starting othogonal dimer search.");            		
            		IVectorMutable workVec = space.makeVector();
            		for(int i=0;i<N.length;i++){
            			//swap
            			workVec.E(N1[i]);
            			N1[i].E(N[i]);
            			N[i].E(workVec);
            		}            		
            		//Make N orthogonal to N1:  N - (N[dot]N1)*N1
            		double orthN = 0;
            		for(int i=0; i<N1.length; i++){
            			orthN += N[i].dot(N1[i]);
            		}
            		for (int i=0; i<N1.length; i++){
            			N[i].PEa1Tv1(-orthN,N1[i]);
            		}
            		System.out.println("ortho N: "+N[0].getX(0)+"    "+N[0].getX(1)+"    "+N[0].getX(2));
            		System.out.println(" lcm N1: "+N1[0].getX(0)+"    "+N1[0].getX(1)+"    "+N1[0].getX(2));
            		ortho=true;
            		startOrtho = false;
            		rotNum = 10;
            		//file = file+"_ortho";
            	}
            	dimerSaddleTolerance();
            	// Calculate curvature value
        		dimerCurvature(N, F1, F);
        		
            	//System.out.println(rotCounter+" rotations.");
            	break;
            }
            
            sinDtheta = Math.sin(dTheta);
            cosDtheta = Math.cos(dTheta);
            
			// Find Nstar after dTheta rotation
			for(int i=0; i<N.length; i++){
				workVectorN1.Ea1Tv1(cosDtheta, N[i]);
				workVectorN1.PEa1Tv1(sinDtheta, THETA[i]);
				Nstar[i].E(workVectorN1);
				workVectorN1.Ea1Tv1(-sinDtheta, N[i]);
				workVectorN1.PEa1Tv1(cosDtheta, THETA[i]);
				THETAstar[i].E(workVectorN1);
			}
			// Use N* to offset(rotate) replicas
			for(int i=0; i<Nstar.length; i++){
			    workVector1.E(list.getAtom(i).getPosition());
			    workVector1.PEa1Tv1(deltaR, Nstar[i]);
                list1.getAtom(i).getPosition().E(workVector1);
                
                workVector1.E(list.getAtom(i).getPosition());
                workVector1.PEa1Tv1(-deltaR, Nstar[i]);
                list2.getAtom(i).getPosition().E(workVector1);
            }
			// Calculate F*'s
			dimerForcesStar(F1star, F2star, F);     
			
			// Calculate F*|_
			dimerForcePerp(Nstar, F1star, F2star, Fstarperp);
						
			// second part of Frot
			for(int i=0; i<Fstarperp.length; i++){
				Frot += Fstarperp[i].dot(THETAstar[i]);
			}
			//System.out.println("Frotb    : "+Frot);
			Frot = Frot/2.0;
			//System.out.println("Frotavg  : "+Frot);
			Fprimerot = 0;
			for(int i=0; i<Fstarperp.length; i++){
				Fprimerot += Fstarperp[i].dot(THETAstar[i]);
			}
			for(int i=0; i<Fperp.length; i++){
				//Fprimerot -= Gperp[i].dot(THETA[i]);
			    Fprimerot -= Fperp[i].dot(THETA[i]);
			}
			//System.out.println("Fprimerot  : "+Fprimerot);
			Fprimerot = Fprimerot / dTheta;
			//System.out.println("Fprimerot/dTheta  : "+Fprimerot);
			//System.out.println("thetaStar: "+THETAstar[0]);
			
			// Find actual rotation angle to minimize energy
			deltaTheta = -0.5 * Math.atan(2.0*Frot/Fprimerot) - dTheta/2.0;		
			
			//if(deltaTheta > 0.05){deltaTheta = 0.05;}
			if(Fprimerot>0){deltaTheta = deltaTheta + Math.PI/2.0;}
			
			//System.out.println(".R - DeltaTheta "+deltaTheta+"  Frot "+Frot+"  Fprimerot "+Fprimerot);
            			
			sindeltaTheta = Math.sin(deltaTheta);
            cosdeltaTheta = Math.cos(deltaTheta);
			
            /*
            if(deltaTheta < 0.1){
            	dTheta = dTheta/10.0;
            	System.out.println("R. - Scaling dTheta to "+dTheta);
            }
            */
			
            // Find N**
            mag=0;
            for(int i=0; i<N.length; i++){               
                workVectorN2.Ea1Tv1(cosdeltaTheta, Nstar[i]);
                workVectorN2.PEa1Tv1(sindeltaTheta, THETAstar[i]);
                N[i].E(workVectorN2);
                mag+=N[i].squared();
            }
            // Use new N to offset(rotate) replicas
            mag=1.0/Math.sqrt(mag);
            for(int i=0; i<N.length; i++){
            	N[i].TE(mag);
                workVector2.E(((IAtomPositioned)list.getAtom(i)).getPosition());
                workVector2.PEa1Tv1(deltaR, N[i]);
                list1.getAtom(i).getPosition().E(workVector2);
                
                workVector2.E(list.getAtom(i).getPosition());
                workVector2.PEa1Tv1(-deltaR, N[i]);
                list2.getAtom(i).getPosition().E(workVector2);
            }        
			rotCounter++;
			if(rotCounter>rotNum){
				//System.out.println(".R - "+rotCounter+" rotations.");
				
				// Calculate estimated Curvature
				dimerCurvature(Nstar, F1star, F);
				double c1 = 0;
				for(int i=0; i<Fstarperp.length; i++){
					c1 += Fstarperp[i].squared();
				}
				c1 = 1.0 / Math.sqrt(c1);
				//System.out.println(" curveI "+curvature);
				curvature = curvature - (0.5 * c1 * Math.tan(deltaTheta - 0.5*dTheta));
				//System.out.println(" curveE "+curvature);
				dimerSaddleTolerance();
				break;
			}
		}
	    //System.out.println("rotations:"+rotCounter); 
	}
	
	/**
	 * Moves the dimer along the lowest curvature mode of the energy surface, Quickmin style.
	 * Step length is determined using a line search (Newton) and the step direction is obtained
	 * by a calculation of the effective force on the dimer.
	 *  
	 */
	public void translateDimerQuickmin(){
		//if(counter<15){
	    deltaXl = newtonStep();
		//}
		
	    if(deltaXl==0.0){
	        //System.out.println("Stepping out maximum step length");
	        //System.out.println("Neff "+Neff[0]);
	        dimerUpdatePositions(deltaXmax, Neff);
	        return;
	    }
        if(deltaXl<-dXl){
            System.out.println("DeltaXl is negative and greater than dXl. "+deltaXl);
            deltaXl = 0;
        }
        if(deltaXl<0.0){
        	System.out.println("Step direction is negative.  Reducing dXl.");
            dXl = dXl/10.0;
        }
        if(dXl<1E-15){
           System.out.println("Step size became extremely small.");
            activityIntegrate.setMaxSteps(0);
        }
        // Step dimer
        //System.out.println("Neff "+Neff[0]);
        dimerUpdatePositions(deltaXl, Neff);
              
        // Calculate new Normal
        dimerNormal();    
	}
	
	protected double newtonStep(){
        dimerForceEff(F, Feff, N);
        
        // Calculate Effective force normal
        double mag = 0;
        for(int i=0; i<Feff.length; i++){
            mag += Feff[i].squared();
            Neff[i].E(Feff[i]);
        }
        mag = 1.0/Math.sqrt(mag);
        for (int i=0; i<N.length; i++){
            Neff[i].TE(mag);
        }
        // Calculate magnitude before step
        double Feffmag = 0;
        for(int i=0; i<Feff.length; i++){
            Feffmag += Feff[i].dot(Neff[i]);
        }
        // Line search for new step length, move atoms a test distance
        dimerUpdatePositions(dXl, Neff);
        // Calculate new dimer center force
        dimerForceCenter(F);
        // Calculate Feffstar
        dimerForceEff(F, Feffstar, N);
        // Calculate magnitude after step
        double Feffmag2 = 0;
        for(int i=0; i<Feff.length; i++){
            Feffmag2 += Feffstar[i].dot(Neff[i]);
        }
        // If force increases, go back, return.
        if(Feffmag2>Feffmag){
            return 0.0;
        }
        // Calculate magnitude of step
        Feffmag = 0;
        for(int i=0; i<Feffstar.length; i++){
            workVector3[i].Ev1Pv2(Feffstar[i],Feff[i]);
            Feffmag += workVector3[i].dot(Neff[i]);
        }
        Feffmag = Feffmag/2.0;
        // Calculate new line curvature
        double curvatureLM = 0;
        for(int i=0; i<Feffstar.length; i++){
            workVector3[i].Ev1Mv2(Feffstar[i],Feff[i]);
        }
        for(int i=0; i<Feffstar.length; i++){
            curvatureLM += workVector3[i].dot(Neff[i]);
        }
        curvatureLM = curvatureLM/dXl;
                       
        deltaXl = ((-Feffmag/curvatureLM) - dXl/2.0);
        
        if(deltaXl>deltaXmax || curvature>0.0){
            deltaXl = deltaXmax-(dXl/2.0);
        }
        
	    return deltaXl;
	}
	

	
	/**
	 * Computes curvature value, C, for the energy surface.  Quantifies the difference
	 * in forces at each end of the dimer into a single number.
	 * 
	 */
	protected void dimerCurvature(IVectorMutable [] aN, IVectorMutable [] aF1, IVectorMutable [] aF){
		curvature = 0.0;
			
		// (F - F1)[dot]N / deltaR
		for(int i=0; i<aF1.length; i++){
			workVector1.E(aF[i]);
			workVector1.ME(aF1[i]);
			
			curvature += workVector1.dot(aN[i]);
		}
		
		curvature = curvature / deltaR;
		
		//System.out.println(curvature+" curvature");
	}
	
	/**
	 * Checks the curvature value at dimer orientation along a vector orthogonal to
	 * lowest curvature mode's (lcm) vector with the lcm's unit vector.  When 
	 * the ortho vector returns a curvature less than that of the lcm vector, 
	 * ORTHO is turned off.
	 * 
	 */
	protected void testOrthoCurvature(IVectorRandom [] aN1, IVectorRandom [] aNortho){
		
		//Compute current curvature along orthogonal N
		dimerCurvature(aNortho, F1, F2);
		double orthoCurve = curvature;
		
		dimerCurvature(aN1, F1, F2);
		double n1Curve = curvature;
		
		System.out.println("curvatures: "+n1Curve+" (LCM)    "+orthoCurve+" (ORTHO)");
		
		if(orthoCurve<n1Curve){
			System.out.println("Secondary mode found, stopping ortho search.");
			ortho = false;
			
			// Run another Orthogonal search (N1, N2)
			if(ortho2){
				setOrtho(true, false);
			}
		}

	}
	
	// Compute Normal vector for dimer orientation
	protected void dimerNormal(){
	    double mag=0;
		IVectorMutable workvector;
		workvector = space.makeVector();
		
		// N =  (R1 - R2) / (-2*deltaR)
		for (int i=0; i<N.length; i++){	
			workvector.E(list1.getAtom(i).getPosition());
			workvector.ME(list2.getAtom(i).getPosition());
			N[i].E(workvector);
			mag += workvector.squared();
		}
		mag = 1.0/Math.sqrt(mag);		
		for (int i=0; i<N.length; i++){
		    N[i].TE(mag);
		}
	}
	
	protected void dimerNormalize(){
		double mag=0;
		for (int i=0; i<N.length; i++){	
			mag += N[i].squared();
		}
		mag = 1.0/Math.sqrt(mag);		
		for (int i=0; i<N.length; i++){
		    N[i].TE(mag);
		}
	}
		
	// Reset forces in boxes 1 and 2, call calculate, and copy over new forces
	protected void dimerForces(IVectorMutable [] aF1, IVectorMutable [] aF2, IVectorMutable [] aF){
		/*
	    force1.reset();
		force0.reset();
		
		potentialMaster.calculate(box1, allatoms, force1);
		potentialMaster.calculate(box, allatoms, force0);
		
		// Copy forces of dimer end and center (R1, R) to local array
		for(int i=0; i<aF1.length; i++){
			aF1[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgent1.getAgent(list1.getAtom(i))).force());
			aF[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgent0.getAgent(list.getAtom(i))).force());
			aF2[i].Ea1Tv1(2.0, aF[i]);
			aF2[i].ME(aF1[i]);
			System.out.println("Atom "+i+"   "+aF[i]);	
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
	    energyBox0 = LammpsInterface.getEnergy(lammps);

	    int atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
	            LammpsInterface.getForce(lammps, i, aF[atom]);
	            //aF[atom].setX(0, 0.0);
	            aF[atom].setX(0, ElectronVolt.UNIT.toSim(aF[atom].x(0)));
	            aF[atom].setX(1, ElectronVolt.UNIT.toSim(aF[atom].x(1)));
	            aF[atom].setX(2, ElectronVolt.UNIT.toSim(aF[atom].x(2)));
	            //System.out.println(aF[atom]);
	            aF2[atom].Ea1Tv1(2.0, aF[atom]);
	            //System.out.println("Atom "+i+"   "+aF[atom]);
	            atom++;
	            
        	}
        }
        //box1
        loopSet = box1.getMoleculeList();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
        }
        LammpsInterface.doLammpsStep(lammps, 1);
        energyBox1 = LammpsInterface.getEnergy(lammps);
        atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
	            LammpsInterface.getForce(lammps, i, aF1[atom]);
	            //aF1[atom].setX(0, 0.0);
	            aF1[atom].setX(0, ElectronVolt.UNIT.toSim(aF1[atom].x(0)));
	            aF1[atom].setX(1, ElectronVolt.UNIT.toSim(aF1[atom].x(1)));
	            aF1[atom].setX(2, ElectronVolt.UNIT.toSim(aF1[atom].x(2)));
	            aF2[atom].ME(aF1[atom]);
	            atom++;
        	}
        }
        
		
	}
	
	protected void dimerForcesStar(IVectorMutable [] aF1star, IVectorMutable [] aF2star, IVectorMutable [] aF){
	   /* force1.reset();
	    potential.calculate(box1, allatoms, force1);
	    
	 // Copy forces of dimer end and center (R1, R) to local array
	    for(int i=0; i<aF1star.length; i++){
			aF1star[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgent1.getAgent(list1.getAtom(i))).force());
			aF2star[i].Ea1Tv1(2.0, aF[i]);
			aF2star[i].ME(aF1star[i]);	
		}
		*/
	    
	    //box1
		IMoleculeList loopSet = box1.getMoleculeList();
	    IVectorMutable workVector = space.makeVector();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
        }
        LammpsInterface.doLammpsStep(lammps, 1);
        int atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
        	    LammpsInterface.getForce(lammps, i, aF1star[atom]);
        	    //aF1star[atom].setX(0, 0.0);
        	    aF1star[atom].setX(0, ElectronVolt.UNIT.toSim(aF1star[atom].x(0)));
        	    aF1star[atom].setX(1, ElectronVolt.UNIT.toSim(aF1star[atom].x(1)));
        	    aF1star[atom].setX(2, ElectronVolt.UNIT.toSim(aF1star[atom].x(2)));
                aF2star[atom].Ea1Tv1(2.0, aF[atom]);
                aF2star[atom].ME(aF1star[atom]);  
                atom++;
        	}
        }
	    
	}
	
	protected void dimerForceCenter(IVectorMutable [] aF){
	    /*
	    force0.reset();
	    potentialMaster.calculate(box, allatoms, force0);
	    
	 // Copy forces of dimer end and center (R1, R) to local array
	    for(int i=0; i<aF.length; i++){
	    	aF[i].E(((IntegratorVelocityVerlet.MyAgent)atomAgent0.getAgent((IAtomLeaf)list.getAtom(i))).force());
	    	System.out.println("Atom "+i+"   "+aF[i]);
	    }
		*/
		///*
	    IMoleculeList loopSet = box.getMoleculeList();
	    IVectorMutable workVector = space.makeVector();
	    for(int i=0; i<loopSet.getMoleculeCount(); i++){
	        workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
	        LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
	    }
	    LammpsInterface.doLammpsStep(lammps, 1);
	    int atom = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(((IMolecule)loopSet.getMolecule(i)).getType()==movableSpecies[0]){
	            LammpsInterface.getForce(lammps, i, aF[atom]);
	            //aF[atom].setX(0, 0.0);
	            aF[atom].setX(0, ElectronVolt.UNIT.toSim(aF[atom].x(0)));
	            aF[atom].setX(1, ElectronVolt.UNIT.toSim(aF[atom].x(1)));
	            aF[atom].setX(2, ElectronVolt.UNIT.toSim(aF[atom].x(2)));
	            //System.out.println("Atom "+atom+"   "+aF[atom]);
	            atom++;
        	}
        }
        //*/
	}
		
	// Calculate the force, aF, perpendicular to dimer orientation N.
	protected void dimerForcePerp(IVectorRandom [] aN, IVectorMutable [] aF1, IVectorMutable [] aF2, IVectorMutable [] aFperp){
		
		double mag1 = 0;
		double mag2 = 0;
		
		// F|_ = F1 - (F1[dot]N)*N  - F2  +  (F2[dot]N)*N
		for(int i=0; i<aF1.length; i++){
			mag1 += aF1[i].dot(aN[i]);
			mag2 += aF2[i].dot(aN[i]);
		}
		for (int i=0; i<aFperp.length; i++){
			aFperp[i].E(aF1[i]);
			aFperp[i].PEa1Tv1(-mag1, aN[i]);	
			aFperp[i].ME(aF2[i]);
			aFperp[i].PEa1Tv1(mag2, aN[i]);
			aFperp[i].TE(1.0/deltaR);
		}

	}
		
	// Calculate the effective force on the dimer using curvature and F, N
	protected void dimerForceEff(IVectorMutable [] aF, IVectorMutable [] aFeff, IVectorMutable [] aNeff){
		
	    double mag = 0;
	    double mag2 =0;
	    for(int i=0; i<aF.length; i++){
            mag += aF[i].dot(aNeff[i]);
           // mag2 += aF[i].dot(aF[i]);
        }
	    //System.out.println("actual force "+F[0]);
	   // System.out.println("front force  "+F1[0]);
	   //System.out.println("mag "+mag);
	   // System.out.println("mag2 "+mag*mag/mag2);
	    //System.out.println(mag+" F dot N");
	    //System.out.println("curvature: "+curvature);

	   	//if(curvature<-1000000){
	   	//	curvature+=-2.0*curvature;
	   //		System.out.println("Changed curvature sign to +.");
	   	//}
	   	
	   	// Feff = F - 2(F[dot]N)N
		if(curvature<0.0){
			IVectorMutable workvector = space.makeVector();
			for (int i=0; i<aNeff.length; i++){
			    workvector.Ea1Tv1(2.0*mag, aNeff[i]);
			    aFeff[i].Ev1Mv2(aF[i], workvector);
			}
		}
		
		/*
		else if(mag*mag/mag2 < 1E-4){
			for(int i=0; i<aFeff.length; i++){
				aFeff[i].E(Neff[i]);
			}
		}
		*/
		// Feff = -(F[dot]N)N	
		else{
			for(int i=0; i<aFeff.length; i++){
				
				aFeff[i].Ea1Tv1(-mag, aNeff[i]);
			}
		}
	}
	
	// Update positions according Henkelman 2004
	protected void dimerUpdatePositions(double a1, IVectorMutable [] normal){
		IVectorMutable workvector = space.makeVector();	
		for(int i=0; i<normal.length; i++){
		    workvector.Ea1Tv1(a1, normal[i]);			
    		list.getAtom(i).getPosition().PE(workvector);
    		list1.getAtom(i).getPosition().PE(workvector);
    		list2.getAtom(i).getPosition().PE(workvector);
    	}	

	}
	
	protected void resizeDimer(){
	    dimerNormal();
	    // Set positions of atoms in replicas equal to box
        for(int i=0; i<box.getLeafList().getAtomCount(); i++){
            ((IAtomPositioned)box1.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            ((IAtomPositioned)box2.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());

        }
        // Offset replicas
        for(int i=0; i<N.length; i++){
            list1.getAtom(i).getPosition().PEa1Tv1(deltaR, N[i]);
            list2.getAtom(i).getPosition().PEa1Tv1(-deltaR, N[i]);
        }
	}
	
	// Calculates and checks magnitude of 3N dimensional force vector
	protected void dimerSaddleTolerance(){
		saddleT = 0.0;
		//If every force is less than dF, consider saddle point found.
		for(int i=0; i<F.length; i++){
			saddleT += F[i].squared();
		}
		//System.out.println("saddle: "+saddleT);
		/*	
		if(saddleT<5000000.0){
		    if(energyBox0.getDataAsScalar()>energyBox1.getDataAsScalar()){
		        dXl = 0.0001;
		        deltaXmax = 0.005;
		        if(saddleT<10.5){
    		        //deltaR = 1E-5;
                    //resizeDimer();
    		        dXl = 0.00001;
        		    deltaXmax = 0.01;
        		    dTheta = 0.00001;
        		    dFrot = 0.01;
		        }
		    }
		}
		*/
		if(saddleT<dFsq){
	    	if(new File(file+".stop").exists()){
	    		System.exit(1);
	    	}
			
		    energyBox0 = LammpsInterface.getEnergy(lammps);
			System.out.println("Saddle found.  Calculating normal modes...");
			
			//for surface
			IVectorMutable vect = space.makeVector();
	        MoleculeArrayList vibList = new MoleculeArrayList();
	        /*
	    	for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
	            vect.E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
	            if(vect.x(0)>3.0){
	                vibList.add(box.getMoleculeList().getMolecule(i));
	            }
	        }
	    	*/
			
	    	//for GB
			for (int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
				IMolecule a = box.getMoleculeList().getMolecule(i);
				if(a.getType()==movableSpecies[0]){
					vibList.add(a);
				}
			}
			
		    vib = new CalcVibrationalModes(lammps);
	        vib.setup(box, potentialMaster, vibList, space);
	        vib.actionPerformed();
	        
	        if(vib.getModeSigns()[1]!=1){
	        	return;
	        }
	        
		    saddleFound = true;
		        
		    System.out.println(energyBox0);
		    
	    	if(new File(file+".stop").exists()){
	    		System.exit(1);
	    	}
		    
	        try{
	            FileWriter fileWriter = new FileWriter(file+"_s_ev", false);
	            fileWriter.write(energyBox0+"\n"+vib.getProductOfFrequencies()+"\n"+vib.getModeSigns()[1]);
	            fileWriter.close();
	        }catch(IOException e) {
	          
	        }
	        
	        rotNum=50;
	        System.out.println("Performing final rotation of dimer.");
	        rotateDimerNewton();
	        
			// Write out configurations of 3 boxes
		    WriteConfiguration writer = new WriteConfiguration(space);
		    writer.setConfName(file+"_saddle");
		    writer.setBox(box);
		    writer.actionPerformed();
		    
		    writer.setConfName(file+"_A_saddle");
		    writer.setBox(box1);
		    writer.actionPerformed();
		    
		    writer.setConfName(file+"_B_saddle");
		    writer.setBox(box2);
		    writer.actionPerformed();
		    
		    activityIntegrate.setMaxSteps(0);
		    
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
	
	/*
	public static class PotentialMasterListDimer extends PotentialMasterList{

		public PotentialMasterListDimer(ISimulation sim, ISpace space) {
			super(sim, space);
			
		}
		
		public void setSpecies(ISpecies[] species){
			this.species = species;
		}
		
	   public void calculate(IBox box, IteratorDirective id, PotentialCalculation pc) {
	        if(!enabled) return;
	        IAtom targetAtom = id.getTargetAtom();
	        if (targetAtom != null) {
	        	super.calculate(box, id, pc);
	        	return;
	        }
	        NeighborListManager neighborManager = (NeighborListManager)neighborListAgentManager.getAgent(box);
	        
            if (Debug.ON && id.direction() != IteratorDirective.Direction.UP) {
                throw new IllegalArgumentException("When there is no target, iterator directive must be up");
            }
            // invoke setBox on all potentials
            for (int i=0; i<allPotentials.length; i++) {
                allPotentials[i].setBox(box);
            }

            //no target atoms specified
            //call calculate with each SpeciesAgent
	        for(int j=0; j<species.length; j++){    
            	IAtomSet list = box.getMoleculeList(species[j]);
	            int size = list.getAtomCount();
	            for (int i=0; i<size; i++) {
	                calculate((IMolecule)list.getAtom(i), id, pc, neighborManager);//call calculate with the SpeciesAgent
	            }
	        }
	   }
		
		
		public ISpecies [] species;
	}
	*/
    static {
      // System.loadLibrary("LAMMPS");
//        System.loadLibrary("lmp_thomas");
    }
}