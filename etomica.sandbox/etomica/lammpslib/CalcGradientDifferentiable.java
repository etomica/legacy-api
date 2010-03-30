package etomica.lammpslib;

import etomica.api.IAtom;
import etomica.api.IAtomType;
import etomica.api.IBox;
import etomica.api.IMoleculeList;
import etomica.api.IPotentialMaster;
import etomica.api.IVectorMutable;
import etomica.atom.AtomLeafAgentManager;
import etomica.atom.AtomLeafAgentManager.AgentSource;
import etomica.atom.iterator.IteratorDirective;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.nbr.list.PotentialMasterList;
import etomica.potential.PotentialCalculationForceSum;
import etomica.space.ISpace;
import etomica.units.ElectronVolt;
import etomica.util.FunctionMultiDimensionalDifferentiable;
import etomica.util.numerical.FiniteDifferenceDerivative;


/**
 * Uses finite difference methods to determine the second order differential of the potential (i.e. dF/dx).
 * Part of a larger scheme, a user may employ this to fill a two-dimensional array of changes in molecule 
 * A's Force with respect to the movement of other molecules.
 * 
 * @author msellers and ajschultz
 *
 */


public class CalcGradientDifferentiable implements FunctionMultiDimensionalDifferentiable, AgentSource {

    public IBox box;
    public IPotentialMaster potentialMaster;
    public double forceConstant;
    int  derivativeOrder;
    FiniteDifferenceDerivative finiteDifferenceDerivative;
    public IteratorDirective allAtoms;
    PotentialCalculationForceSum force;
    AtomLeafAgentManager atomAgent;
    int gradDcomponent, startAtom, stopAtom;
    IMoleculeList movableSet;
    private final ISpace space;
    long lammps;
    
    
    public CalcGradientDifferentiable(IBox aBox, long library, IMoleculeList ms, ISpace _space){
        this.box = aBox;
        this.movableSet = ms;
        this.space = _space;
        this.lammps = library;
        
        if(potentialMaster instanceof PotentialMasterList){
            ((PotentialMasterList)potentialMaster).getNeighborManager(box).reset();
         }
        
        force = new PotentialCalculationForceSum();
        allAtoms = new IteratorDirective();
        atomAgent = new AtomLeafAgentManager(this, box);
        force.setAgentManager(atomAgent);
        
        finiteDifferenceDerivative = new FiniteDifferenceDerivative(this);
        finiteDifferenceDerivative.setH(0.00001);
        finiteDifferenceDerivative.setHOptimizer(true);
        finiteDifferenceDerivative.setNtab(10);
    }
    

    public void setComponent(int aGradDcomponent){
        this.gradDcomponent = aGradDcomponent;
    }
    
    
    public double f(double [] position){
        
        for(int i=0; i<position.length/3; i++){
           for(int j=0; j<3; j++){
        	  movableSet.getMolecule(i).getChildList().getAtom(0).getPosition().setX(j, position[(3*i)+j]);
           }
        }
        
        //force.reset();
        //potentialMaster.calculate(box, allAtoms, force);
        
        IMoleculeList loopSet = box.getMoleculeList();
        IVectorMutable workVector = space.makeVector();
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
            workVector.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            LammpsInterface2.setAtomPosition(lammps, i, workVector.getX(0), workVector.getX(1), workVector.getX(2));
        }
        LammpsInterface2.doLammpsStep(lammps, 1);
        
        //not used
        //return ((IntegratorVelocityVerlet.MyAgent)atomAgent.getAgent((IAtomLeaf)movableSet.getMolecule(gradDcomponent/3).getChildList().getAtom(0))).force().x(gradDcomponent%3);
        return 0.0;
    }
    
    public double df(int [] d, double [] position){
        return finiteDifferenceDerivative.df(d, position);
    }
    
    /**
     * Uses the potential's force calculation at different displacements of a molecule in X, Y and Z
     * to determine the second derivative of the potential.  Here, H (our displacement distance) is
     * equal to 0.0001.
     * 
     * @param d A one-dimensional array describing what column of our larger, global dF/dx array we are working with.
     * @param position A one dimensional array of doubles describing the molecules positions.
     * @return
     */
    public double[] df2(int [] d, double [] position){
        double newH = 0.0001;
        double[] forceRow = new double[d.length];
        int elem = 0;
        
        for(int i=0; i<d.length; i++){
            if(d[i]==1){
                elem = i;
                break;                
            }
        }
        
        position[elem]+=newH;
        f(position);
        
        /*
        for(int j=0; j<forceRow.length; j++){
            forceRow[j] = -((IntegratorVelocityVerlet.MyAgent)atomAgent.getAgent((IAtomLeaf)((IMolecule)movableSet.getAtom(j/3)).getChildList().getAtom(0))).force.x(j%3);
        }
        */
        
        IMoleculeList loopSet = box.getMoleculeList();
        IVectorMutable workvector = space.makeVector();
        int rowCount = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(loopSet.getMolecule(i).getType()==movableSet.getMolecule(0).getType()){
        		workvector.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
            	LammpsInterface2.getForce(lammps, i, workvector);
	        	for(int l=0; l<3; l++){
	                forceRow[rowCount] = -ElectronVolt.UNIT.toSim(workvector.getX(l));
	                rowCount++;
	            }
        	}
        }
                
        position[elem]-=2*newH;
        f(position);
        
        /*
        for(int j=0; j<forceRow.length; j++){
            forceRow[j] -= -((IntegratorVelocityVerlet.MyAgent)atomAgent.getAgent((IAtomLeaf)((IMolecule)movableSet.getAtom(j/3)).getChildList().getAtom(0))).force().x(j%3);
            forceRow[j] /= (2.0*newH);
        }
        */
        
        rowCount = 0;
        for(int i=0; i<loopSet.getMoleculeCount(); i++){
        	if(loopSet.getMolecule(i).getType()==movableSet.getMolecule(0).getType()){
	        	workvector.E(loopSet.getMolecule(i).getChildList().getAtom(0).getPosition());
	        	LammpsInterface2.getForce(lammps, i, workvector);
	            for(int l=0; l<3; l++){
	                forceRow[rowCount]-= -ElectronVolt.UNIT.toSim(workvector.getX(l));
	                forceRow[rowCount]/= (2.0*newH);
	                rowCount++;
	            }
        	}
        }
        
        return forceRow;
    }
    
    public int getDimension(){
        return space.D();
    }

    public Class getAgentClass() {
        return IntegratorVelocityVerlet.MyAgent.class;
    }


    public void releaseAgent(Object agent, IAtomType atom) {
        // do nothing  
    }


	public Object makeAgent(IAtom a) {
		// TODO Auto-generated method stub
		return null;
	}


	
	public void releaseAgent(Object agent, IAtom atom) {
		// TODO Auto-generated method stub
		
	}
    
}
