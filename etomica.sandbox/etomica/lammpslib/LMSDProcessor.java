package etomica.lammpslib;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import etomica.api.IVectorMutable;
import etomica.space.ISpace;
import etomica.util.DoubleRange;
import etomica.util.HistogramNotSoSimple;
import etomica.util.HistogramSimple;

public class LMSDProcessor {

    public LMSDProcessor(ISpace space, String inputFile, String outputFile){
        msdOutput = outputFile;
        msdInput = inputFile;
        try {
            fileReader = new FileReader(inputFile);
            System.out.println("Successivly opened inputFile");
        }
        catch(IOException e) {
            throw new RuntimeException("Cannot open "+inputFile+", caught IOException: " + e.getMessage());
        }
		
        try {
            buffReader = new BufferedReader(fileReader);
            numAtoms = Integer.parseInt(buffReader.readLine());
        } catch(IOException e) {
            throw new RuntimeException("Problem reading "+inputFile+", caught IOException: " + e.getMessage());
        }
        
        try {
        	buffReader.readLine();
        	int numLines=2;
        	
        	for(int i=0; i<numAtoms; i++){
	        	//count species
	        	positionLine = buffReader.readLine();
	        	coordString = positionLine.split(" ");
	        	species = Integer.parseInt(coordString[0]);
	        	if(species>numSpecies){
	        		numSpecies=species;
	        	}
	        	numLines++;
        	}
            while (buffReader.readLine()!=null){
            	numLines++;
            }
            //Sanity check! numAtoms should be a multiple of numLines.            
            if (numLines%(numAtoms+2)!=0){
                throw new RuntimeException("Read "+numLines+" line(s) and there are "+numAtoms+" atom(s) in the simulation.");
            }
            
            numBlocks = numLines/(numAtoms+2);
            deltaTmax = numBlocks/3;
        } catch(IOException e) {
            throw new RuntimeException("Problem reading "+inputFile+", caught IOException: " + e.getMessage());
        }
        try {
            buffReader.close();
            fileReader.close();
        } catch(IOException e){
            throw new RuntimeException("Couldn't shut down readers, caught IOException: " +e.getMessage());
        }
        
        coordBlock1 = new IVectorMutable[numAtoms];
        coordVector2 = space.makeVector();
        coordVectorAtom = space.makeVector();
        for (int j=0; j<numAtoms; j++){
            coordBlock1[j] = space.makeVector();
        }
       
	}
    
    /**
     * Allows for a new value of deltaTmax.  This variable defaults to 1/3 of numBlocks.
     * deltaTmax is the largest difference in block number for which the Mean Squared
     *   Displacement will be calculated.
     * @param newDeltaTmax - The new value of deltaTmax.
     */
    
    public void setDeltaTmax(int newDeltaTmax){
        deltaTmax = newDeltaTmax;
    }

    public void fillArrays(){
    	coordString = new String[4];
    	int[] numAtomsS = new int[numSpecies];
        //Total RMS displacement
        double[] totalRsquared = new double[deltaTmax];
        //XYZ Components
        double[][][] RsquaredXYZ = new double[deltaTmax][3][numSpecies];
        //Total RMS displacement
        double[] RsquaredAtom = new double[numAtoms];
        //Current Z direction
        double[] Zlocation = new double[numAtoms];
        //Create histogram instance for Z plane
        HistogramNotSoSimple hist = new HistogramNotSoSimple(30, new DoubleRange(-30,30));
        HistogramNotSoSimple histdelt1 = new HistogramNotSoSimple(30, new DoubleRange(-30,30));
        HistogramNotSoSimple histdelt2 = new HistogramNotSoSimple(30, new DoubleRange(-30,30));
        
        //Fills Block1 and 2, subtracts, and fills totalRsquared.  Repeat.
        for (int i=1; i<numBlocks; i++){
            System.out.println("Solving for iteration "+i);
        	try{
        		fileReader = new FileReader(msdInput);
            	buffReader = new BufferedReader(fileReader);
                //Gets buffReader to start of block 1 in question
                for (int j=0; j<(i-1)*(numAtoms+2)+2; j++){
                    buffReader.readLine();
                }
                
                //Block 1 Loop - Grabs XYZ lines from block 1
                for (int k=0; k<numAtoms; k++){
                    positionLine = buffReader.readLine();
                    coordString = positionLine.split(" ");
                    //get species number
                    species = Integer.parseInt(coordString[0]);
                    //count species
                    numAtomsS[species-1]++;
                    for (int l=1; l<coordString.length; l++) {
                        coord = Double.valueOf(coordString[l]).doubleValue();
                        coordBlock1[k].setX(l-1,coord);
                    }
                }
                
                //Block 2 Loop - Subtracts sucessive blocks from Block 1 (coordBlock1[])
                for (int deltaT=1; deltaT<deltaTmax+1; deltaT++){
                	if (i + deltaT > numBlocks) {
	                     continue;
	                 }
	            	 buffReader.readLine();
	            	 buffReader.readLine();
                	
                	//Block 2 Loop over Atoms - Adds XYZ lines from block 2
                    for (int iatom=0; iatom<numAtoms; iatom++){
                    	/*//Restricts number of block pairs subtracted 
                    	//skip head in deltaT
                    	if(deltaT<(deltaTmax/2)){
                    		buffReader.readLine();
                    		continue;
                    	}*/
                        String positionLine = buffReader.readLine();
                        String [] coordString = positionLine.split(" ");
                        species = Integer.parseInt(coordString[0]);
                   
                        for (int icoord=1; icoord<coordString.length; icoord++) {
                            double coord = Double.valueOf(coordString[icoord]).doubleValue();
                            coordVector2.setX(icoord-1,coord);
                        }
                        //get Z location of atoms
                        if(deltaT==deltaTmax/2.0){
                        	Zlocation[iatom] = coordVector2.getX(2);
                        }
                        //per Z Planar Diffusivity information
                        if(deltaT==(deltaTmax-50)){
                        	coordVectorAtom.Ev1Mv2(coordVector2, coordBlock1[iatom]);
                        	coordVectorAtom.setX(2, 0.0);
                            RsquaredAtom[iatom]=coordVectorAtom.squared();
                        	histdelt1.addValue(Zlocation[iatom], RsquaredAtom[iatom]);
                        }
                        //get per atom displacement in XY
                        if(deltaT==deltaTmax){
                            coordVectorAtom.Ev1Mv2(coordVector2, coordBlock1[iatom]);
                        	coordVectorAtom.setX(2, 0.0);
                            RsquaredAtom[iatom]=coordVectorAtom.squared();
                           	hist.addValue(Zlocation[iatom],RsquaredAtom[iatom]);
                           	histdelt2.addValue(Zlocation[iatom], RsquaredAtom[iatom]);
                        }
                        //record MSD per deltaT
                        coordVector2.ME(coordBlock1[iatom]);
                        totalRsquared[deltaT-1] += coordVector2.squared();
                        //add X Y and Z for a particular deltaT and species
                        for(int j=0;j<3;j++){
                        	RsquaredXYZ[deltaT-1][j][species-1] += Math.pow(coordVector2.getX(j),2.0);
                        }

                    }
                   
                }
                
                fileReader.close();
                buffReader.close();
                
                //break;
            } catch(IOException e) {
                throw new RuntimeException("Problem creating array of positions, caught IOException: " + e.getMessage());
            }
        }
         
        /*
         * Each row of totalRsquared initially contains the summation of all
         * the atoms position differences for a specific deltaT (i.e. row 
         * three is the difference of block1 and block4, plus the difference 
         * of block2 and block5, etc.)
         * 
         * These sums are being divided by the number of atoms, and the respective
         * deltaT
         */
        for (int ideltaT=1; ideltaT<deltaTmax+1; ideltaT++){
            totalRsquared[ideltaT-1] /= (numAtoms*(numBlocks-ideltaT));
            for(int j=0;j<3;j++){
            	for(int k=0; k<numSpecies; k++){
            		RsquaredXYZ[ideltaT-1][j][k] /= (numAtomsS[k]*(numBlocks-ideltaT));
            	}
            }
        }
        
        //Writes totalRsquared to file
        try{
            fileWriter = new FileWriter(msdOutput, false);
            fileWriter.write(numAtoms+"\n");
            fileWriter.write(numBlocks+"\n");
            
            fileWriter.write("__Total Rsquared for All Species________________________________\n");
            for (int irow=0; irow<deltaTmax; irow++){
                fileWriter.write(irow+"\t"+totalRsquared[irow]+"\n");
            }
            
            
            for(int j=0;j<numSpecies;j++){
            	fileWriter.write("___SPECIES "+(j+1)+" Time dependent data for X,Y,Z_______________________\n");
            	for(int i=0;i<deltaTmax;i++){
            		fileWriter.write(RsquaredXYZ[i][0][j]+" "+RsquaredXYZ[i][1][j]+" "+RsquaredXYZ[i][2][j]+"\n");
            	}
            	fileWriter.write("\n");
            }
            
            fileWriter.write("___Per Atom Histogram Displacement Data_______________________\n");
            fileWriter.write("+Range is "+hist.getXRange().minimum()+" to "+hist.getXRange().maximum()+".\n");
            fileWriter.write("+Number of bins is "+hist.getNBins()+".\n");
            for(int i=0;i<hist.getHistogram().length;i++){
            	fileWriter.write(hist.getHistogram()[i]+"\n");	
            }
            
            fileWriter.write("___Per Z-plane Diffusion Data_______________________\n");
            fileWriter.write("+Range is "+hist.getXRange().minimum()+" to "+hist.getXRange().maximum()+".\n");
            fileWriter.write("+Number of bins is "+hist.getNBins()+".\n");
            double D;
            for(int i=0;i<histdelt2.getHistogram().length;i++){
            	D=(histdelt2.getHistogram()[i]-histdelt1.getHistogram()[i])/(4*50);
            	fileWriter.write(D+"\n");
            }
            
            fileWriter.close();
            
            fileReader.close();
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    
	private IVectorMutable [] coordBlock1;
	private IVectorMutable coordVector2, coordVectorAtom;
	private int numAtoms;
    private int numBlocks;
    private int deltaTmax;
	private FileReader fileReader;
    private BufferedReader buffReader;
	private FileWriter fileWriter;
    private String msdOutput;
    private String msdInput;
    private double coord;
    private String positionLine;
    private String[] coordString;
    private int species;
    private int numSpecies;
    

}
