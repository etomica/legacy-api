package etomica.lammpslib;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Serializable;

import Jama.EigenvalueDecomposition;
import Jama.Matrix;
import etomica.api.IAction;
import etomica.api.IAtomList;
import etomica.api.IAtomPositioned;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
import etomica.api.IPotentialMaster;
import etomica.dimer.CalcGradientDifferentiable;
import etomica.space.ISpace;

/**
 * Calculates the eigenvalues of an NxN matrix.  Assumes these are actually changes in
 * a group of molecules' force with respect to changes in other molecules' positions, and
 * returns eigenvalues.
 * 
 * @author msellers and ajschultz
 *
 */

public class CalcVibrationalModes implements IAction, Serializable {

    /**
     * 
     */
    private static final long serialVersionUID = 1L;
    double [] modes;
    double [] frequencies;
    double [] positions;
    int[] d;
    double [][] dForces;
    double prodFreq;
    int[] modeSigns;
    Matrix fC;
    double mass;
    int writeCount;
    IMoleculeList ms;
    long lammps;
    IBox box;
    EigenvalueDecomposition eigenDecomp;
    CalcGradientDifferentiable cgd;
    
    public CalcVibrationalModes(long library){
        this.lammps = library;
        writeCount = 0;
       
        }

    public void setup(IBox aBox, IPotentialMaster aPotentialMaster, IMoleculeList moleculeList, ISpace _space){
        ms = moleculeList; 
        box = aBox;
        mass = ((IMolecule)ms.getMolecule(0)).getType().getAtomType(0).getMass();
        mass = Math.sqrt(mass);
        cgd = new CalcGradientDifferentiable(aBox, lammps, aPotentialMaster, ms, _space);
        d = new int[ms.getMoleculeCount()*3];
        positions = new double[d.length];
        dForces = new double[positions.length][positions.length];
        modeSigns = new int[3];
        
    }
    
    public void actionPerformed() {
        // setup position array
        for(int i=0; i<ms.getMoleculeCount(); i++){
            for(int j=0; j<3; j++){
                positions[(3*i)+j] = ((IAtomPositioned)ms.getMolecule(i).getChildList().getAtom(0)).getPosition().x(j);
            }
        }
        // fill dForces array
        for(int l=0; l<d.length; l++){
            d[l] = 1;
            System.arraycopy(cgd.df2(d, positions), 0, dForces[l], 0, d.length);
            //System.out.println("  -Calculating force constant row "+l+"...");
            d[l] = 0;
        }
        fC = new Matrix(dForces);
        eigenDecomp = new EigenvalueDecomposition(fC);
        modes = eigenDecomp.getRealEigenvalues();
        for(int i=0; i<modes.length; i++){   
            if(modes[i]>0.0){modeSigns[0]++;}
            else {modeSigns[1]++;}
        }
        modeSigns[2] = modes.length;
        frequencies = new double[modes.length];
        for(int i=0; i<frequencies.length; i++){
            //Negative mode catch
            if(modes[i]<0.0){
                frequencies[i] = 0.0;
                continue;
            }
            frequencies[i] = Math.sqrt(modes[i]) / (2*Math.PI) / mass;
            //System.out.println(frequencies[i]);
        }
        
        prodFreq = 0;      
        for(int i=0; i<frequencies.length; i++){
            if(frequencies[i] == 0.0){
                //System.out.println("ZERO TEST");
                continue;
                
            }
            prodFreq = prodFreq + Math.log(frequencies[i]);
            
            //System.out.println("p  "+prodFreq);
        }
        
        System.out.println("Normal mode vibrational data calculated.");
        //System.out.println(prodFreq);
        
    }
    
    /**
     * Performs an eigenvalue decomposition of the NxN matrix, fC.
     * 
     * @return
     */
    public double[] getLambdas(){
        return modes;
    }
    
    /**
     * Returns a one dimensional array of length 3 with the total number of
     * positive, negative, and imaginary modes.
     * 
     * @return modeSigns one-dimensional array
     */
    public int[] getModeSigns(){
        return modeSigns;
    }
    
    /**
     * Calculates the frequencies (omegas) of wave vectors described by the eigenvalues (lambdas) of
     * our system.
     * 
     * lambda = 4 * pi^2 * omega^2.
     * 
     * @return frequencies one-dimensional array of doubles
     */
    public double[] getFrequencies(){
        // where ;
        modes = getLambdas();
        return frequencies;
    }
    
    public double getProductOfFrequencies(){
        return prodFreq;
    }
    
    public double getHarmonicEntropy(double temp){
    	// h (planck's constant) = 6.626068E-34  m2 kg / s
    	// kb (boltzmann's constant) = 1.3806503E-23  m2 kg / s2 K
    	double hkbt = ((1.3806503E-23)*temp)/(6.626068E-34);
    	double lnQuant=0;
    	
    	for(int i=0; i<frequencies.length; i++){
    		lnQuant += Math.log(hkbt/frequencies[i]);
    	}
    	return (1.3806503E-23)*(lnQuant + frequencies.length);	
    }
    
    public void writeDataToFile(String file){
        FileWriter writer;
        //LAMBDAS
        try { 
            writer = new FileWriter(file);
            writer.write("Output "+writeCount+"--------"+"\n");
            writer.write(modeSigns[0]+" positive modes"+"\n");
            writer.write(modeSigns[1]+" negative modes"+"\n");
            writer.write(modeSigns[2]+" total modes"+"\n");
            writer.write("-modes"+"\n");
            for(int i=0; i<modes.length; i++){
                writer.write(modes[i]+"\n");
            }
            writer.write("-frequencies"+"\n");
            for(int i=0; i<frequencies.length; i++){
                writer.write(frequencies[i]+"\n");
            }
            writer.write("-frequency product"+"\n");
            writer.write(prodFreq+"\n");
            writer.close();
            writeCount++;
        }catch(IOException e) {
            System.err.println("Cannot open file, caught IOException: " + e.getMessage());
            return;
        }
    }

    
}
