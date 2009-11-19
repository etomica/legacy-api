package etomica.lammpslib;

import java.io.IOException;
import java.util.Formatter;

<<<<<<< IntegratorEnergyMap.java
import etomica.api.IAtom;
import etomica.api.IAtomPositioned;
import etomica.api.IMoleculeList;
=======
import etomica.api.IAtom;
>>>>>>> 1.15
import etomica.api.ISimulation;
import etomica.api.IVectorMutable;
import etomica.atom.AtomLeafAgentManager.AgentSource;
import etomica.data.meter.MeterPotentialEnergy;
import etomica.dimer.IntegratorEnergyMap;
import etomica.dimer.LammpsInterface;
import etomica.integrator.IntegratorBox;
import etomica.integrator.IntegratorVelocityVerlet;
import etomica.potential.PotentialMaster;
import etomica.space.ISpace;

public class IntegratorEnergyMap extends IntegratorBox implements AgentSource{

    IAtom adatom;
    public MeterPotentialEnergy energy;
    String fileTail;
    long lammps;
    private final ISpace space;

<<<<<<< IntegratorEnergyMap.java
    public IntegratorEnergyMap(ISimulation aSim, long _lammps, PotentialMaster potentialMaster,
    		                   IAtomPositioned aAdatom, String aFileTail,
=======
    public IntegratorEnergyMap(ISimulation aSim, PotentialMaster potentialMaster,
    		                   IAtom aAdatom, String aFileTail,
>>>>>>> 1.15
    		                   ISpace _space) {
        super(potentialMaster, 1.0);
        this.fileTail = aFileTail;
        this.adatom = aAdatom;
        this.space = _space;
        this.lammps = _lammps;
    }
    
    public void doStepInternal(){
        try {
           
            Formatter formatter = new Formatter("energy-"+fileTail);
            IVectorMutable pos = adatom.getPosition();
            // Move atom along Y-axis, steps by 0.1
            for(int i=0; i<200; i++){ //292
                
                // Return atom to original Z position
                adatom.getPosition().setX(2, 3.54881);
                
                // Move atom along Z-axis, steps by 0.1
                for(int j=0; j<225; j++){  //213
                    // --PRINT-- 
<<<<<<< IntegratorEnergyMap.java
                	updateLammps();
                    formatter.format("%f %7.2f %7.2f %7.2f \n",new Object[] {LammpsInterface.getEnergy(lammps),pos.x(0), pos.x(1), pos.x(2)});
=======
                    formatter.format("%f %7.2f %7.2f %7.2f \n",new Object[] {energy.getDataAsScalar(),pos.getX(0), pos.getX(1), pos.getX(2)});
>>>>>>> 1.15
                    
                    // Step atom by 0.1 along Z-axis
<<<<<<< IntegratorEnergyMap.java
                    adatom.getPosition().setX(2, adatom.getPosition().x(2) -0.01);
=======
                    adatom.getPosition().setX(2, adatom.getPosition().getX(2) +0.02);
>>>>>>> 1.15
                }
                // Step atom by 0.1 along Y-axis
<<<<<<< IntegratorEnergyMap.java
                adatom.getPosition().setX(1, adatom.getPosition().x(1) + 0.01);
=======
                adatom.getPosition().setX(1, adatom.getPosition().getX(1) + 0.02);
>>>>>>> 1.15
     
            }
            formatter.close();
        }
        catch (IOException e) {
            
        }
    }
<<<<<<< IntegratorEnergyMap.java
       
    protected void setup() {
=======
    
    
    protected void setup() {
>>>>>>> 1.15
        super.setup();
        // Set variables for energy
<<<<<<< IntegratorEnergyMap.java
        energy = new MeterPotentialEnergy(potentialMaster);
        energy.setBox(box);        
=======
        energy = new MeterPotentialEnergy(potentialMaster);
        energy.setBox(box);
        
        
>>>>>>> 1.15
    }

    protected void updateLammps(){
		IVectorMutable workVector = space.makeVector();
		IMoleculeList loopSet = box.getMoleculeList();
		for(int i=0; i<box.getLeafList().getAtomCount(); i++){
		    workVector.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
		    LammpsInterface.setAtomPosition(lammps, i, workVector.x(0), workVector.x(1), workVector.x(2));
		}
		LammpsInterface.doLammpsStep(lammps, 1);
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
    
}
