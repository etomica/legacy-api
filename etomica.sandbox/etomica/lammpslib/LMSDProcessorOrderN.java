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

public class LMSDProcessorOrderN {

    public LMSDProcessorOrderN(ISpace space, String inputFile, String outputFile){
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
        	species = new int[numAtoms];
        	for(int i=0; i<numAtoms; i++){
	        	//count species
	        	positionLine = buffReader.readLine();
	        	coordString = positionLine.split(" ");
	        	species[i] = Integer.parseInt(coordString[0]);
	        	if(species[i]>numSpecies){
	        		numSpecies=species[i];
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
            //Reduces the actual number of blocks to a multiple of 10;
            buffnum = (int)Math.floor(Math.log10(numBlocks));
            
        } catch(IOException e) {
            throw new RuntimeException("Problem reading "+inputFile+", caught IOException: " + e.getMessage());
        }
        try {
            buffReader.close();
            fileReader.close();
        } catch(IOException e){
            throw new RuntimeException("Couldn't shut down readers, caught IOException: " +e.getMessage());
        }
        
        coordVectorAtom = space.makeVector();
        
    	coordBlocks = new IVectorMutable[buffnum][10][numAtoms];
    	for(int b=0; b<buffnum; b++){
        	for(int dt=0; dt<10; dt++){
        		for (int j=0; j<numAtoms; j++){
                    coordBlocks[b][dt][j] = space.makeVector();
                }
        	}
    	}
        
	}
    
    /**
     * Allows for a new value of deltaTmax. deltaTmax is the largest difference in block 
     * number for which the Mean Squared
     *   Displacement will be calculated.
     * @param newDeltaTmax - The new value of deltaTmax.
     */
    
    public void setDeltaTmax(int newDeltaTmax){
        //Reduces the actual number of blocks to a multiple of 10;
        buffnum = (int)Math.floor(Math.log10(newDeltaTmax));
    }

    public void fillArrays(){
    	
    	coordString = new String[4];                
        //XYZ Components
        double[][][][] RsquaredXYZ = new double[numSpecies][buffnum][10][3];
        
        //Total RMS displacement per atom from longest block
        double[] RsquaredAtom = new double[numAtoms];
        
        //Create histogram instance for Z plane
        HistogramSimple histz = new HistogramSimple(30, new DoubleRange(-30,30));
        HistogramNotSoSimple histdelt1 = new HistogramNotSoSimple(30, new DoubleRange(-30,30));
        HistogramNotSoSimple histdelt2 = new HistogramNotSoSimple(30, new DoubleRange(-30,30));
        

    	try{
    		fileReader = new FileReader(msdInput);
        	buffReader = new BufferedReader(fileReader);
        	
        	//LOOP OVER CONFIGURATION BLOCKS
        	for (int i=1; i<numBlocks+1; i++){
                System.out.println("Calculating for configuration block "+i);
                
                //Advance past Atom Number and "Atoms" lines.
                buffReader.readLine();
                buffReader.readLine();
        	
                //READ IN CURRENT COORDINATE BLOCK
                for (int k=0; k<numAtoms; k++){
                	positionLine = buffReader.readLine();
	                coordString = positionLine.split(" ");
	                //get configuration and store in 1deltaT spot
	                for (int l=1; l<coordString.length; l++) {
	                    coord = Double.valueOf(coordString[l]).doubleValue();
	                    coordBlocks[0][0][k].setX(l-1,coord);
	                }
                }
                
                //LOOP OVER BUFFERS - 1deltaT, 10deltaT, 100deltaT....
                int tb = 0;
	            for(int b=0;b<buffnum;b++){
	                //catch for deltaT's larger than current buffReader position
	            	if (b==0) {tb = 1;}
	                else {tb *= 10;}
	            	//set largest deltaT(maxj) in BUFFER
                    int maxj = i/tb;
                    if (maxj*tb != i) break;
                    
            	    if (maxj>10) maxj = 10;               
            		System.out.println(i+"  "+b+" "+tb+" "+maxj);
            	    	//Copy 1detaT into current buffer start
            			for(int a=0; a<numAtoms; a++){
            				coordBlocks[b][0][a].E(coordBlocks[0][0][a]);
            			}
            			
            			//PROCESS DATA FROM BUFFERS FOR: +XYZ MSD, +MSD PerAtom, +Z-profile
            			//loop over deltaT's
            			for(int j=1; j<maxj; j++){
            				
            				//DENSITY PROFILE
	            			if(b==1){
	            				for(int a=0; a<numAtoms; a++){
	            					histz.addValue(coordBlocks[b][0][a].getX(2));
	            				}
	            			}
            				
            				//MAIN MSD CALC
            				for(int a=0; a<numAtoms; a++){
            					//difference of current coordinate block and subsequent block in coordBlock array.
            					RsquaredXYZ[species[a]-1][b][j][0] += Math.pow((coordBlocks[b][j][a].getX(0)-coordBlocks[b][0][a].getX(0)),2); 
            					RsquaredXYZ[species[a]-1][b][j][1] += Math.pow((coordBlocks[b][j][a].getX(1)-coordBlocks[b][0][a].getX(1)),2);  
            					RsquaredXYZ[species[a]-1][b][j][2] += Math.pow((coordBlocks[b][j][a].getX(2)-coordBlocks[b][0][a].getX(2)),2);  
            				}
            				
            				//PER-ATOM DISPLACEMENT IN XY (deltaT=500, must have at least 1000 configurations to use) 
            				if(b==2){
            					if(j==4){
	            					for(int a=0; a<numAtoms; a++){
	            						coordVectorAtom.Ev1Mv2(coordBlocks[b][j][a],coordBlocks[b][0][a]);
	            						//remove Z-component
	            						RsquaredAtom[a] = coordVectorAtom.squared()-Math.pow(coordVectorAtom.getX(2), 2);
	        	                    	histdelt1.addValue(coordBlocks[b][j][a].getX(2), RsquaredAtom[a]);
	            					}
            					}
            					if(j==9){
            						for(int a=0; a<numAtoms; a++){
	            						coordVectorAtom.Ev1Mv2(coordBlocks[b][j][a],coordBlocks[b][0][a]);
	            						//remove Z-component
	            						RsquaredAtom[a] = coordVectorAtom.squared()-Math.pow(coordVectorAtom.getX(2),2);
	        	                    	histdelt2.addValue(coordBlocks[b][j][a].getX(2), RsquaredAtom[a]);
	            					}
            					}	
            				}
            				
            			//end loop over deltaT's (j);
            			}
            		
            			//BOOKKEEPING STEP, FREE UP FIRST ROW
            			//Shift sampled values via pointers.  Memory locations of data are maintained.
                        IVectorMutable[] lastBlock = coordBlocks[b][9];
                    	for(int dt=9; dt>0; dt--){
                    	    coordBlocks[b][dt] = coordBlocks[b][dt-1];
                    	}
                    	coordBlocks[b][0] = lastBlock;
	    	                
	            	//end loop over buffers	
	            	}
	            
	            //end loop over configuration blocks
        		}
        	
	        fileReader.close();
	        buffReader.close();
        } 
        catch(IOException e) {throw new RuntimeException("Problem creating array of positions, caught IOException: " + e.getMessage());}
         
      
        //WE'RE DONE! Normalize Rsquared Array. Length is buffnum*10.
        
        for(int k=0; k<numSpecies; k++){
        	//count species
        	int speciesCount=0;
        	for(int a=0; a<species.length; a++){
        		if(species[a]==(k+1)){speciesCount++;}
        	}
        	int tb=1;
        	int nt=0;
        	for(int b=0; b<buffnum; b++){
        		if(b==0)tb=1;
        		else{tb*=10;};
	        	for (int j=1; j<10; j++){
	        			//finish average, normalize by number of SD sums
	        			nt=speciesCount*((numBlocks/tb)-j);
	        			System.out.println(">>"+nt+" "+(RsquaredXYZ[k][b][j][0]+RsquaredXYZ[k][b][j][1]+RsquaredXYZ[k][b][j][2]));
	            		RsquaredXYZ[k][b][j][0] /= nt;
	            		RsquaredXYZ[k][b][j][1] /= nt;
	            		RsquaredXYZ[k][b][j][2] /= nt;            		
	            		System.out.println("> "+nt+" "+(RsquaredXYZ[k][b][j][0]+RsquaredXYZ[k][b][j][1]+RsquaredXYZ[k][b][j][2]));
	        	}
        	}
    	}
        
        //Writes totalRsquared to file
        try{
            fileWriter = new FileWriter(msdOutput, false);
            fileWriter.write("Atoms: "+numAtoms+"\n");
            fileWriter.write("Blocks: "+numBlocks+"\n");     
            fileWriter.write("DeltaTMax: "+Math.pow(10,buffnum)+"\n");     
            
            for(int k=0;k<numSpecies;k++){
            	fileWriter.write("___SPECIES "+(k+1)+" Time dependent data for X,Y,Z_______________________\n");
            	int bt=0;
            	for(int b=0;b<buffnum;b++){
            		if(b==0){bt=1;}
            		else{bt*=10;};
            		for (int j=1; j<10; j++){
	            		fileWriter.write((bt*j)+" "+RsquaredXYZ[k][b][j][0]+" "+RsquaredXYZ[k][b][j][1]+" "+RsquaredXYZ[k][b][j][2]+" "+(RsquaredXYZ[k][b][j][0]+RsquaredXYZ[k][b][j][1]+RsquaredXYZ[k][b][j][2])+"\n");
            		}
            	}
            	fileWriter.write("\n");
            }
            
            fileWriter.write("___Density Profile_______________________\n");
            fileWriter.write("+Range is "+histz.getXRange().minimum()+" to "+histz.getXRange().maximum()+".\n");
            fileWriter.write("+Number of bins is "+histz.getNBins()+".\n");
            for(int i=0;i<histz.getHistogram().length;i++){
            	fileWriter.write(histz.getHistogram()[i]+"\n");	
            }
            
            fileWriter.write("___Z-plane Diffusion Data_______________________\n");
            fileWriter.write("+Range is "+histdelt2.getXRange().minimum()+" to "+histdelt2.getXRange().maximum()+".\n");
            fileWriter.write("+Number of bins is "+histdelt2.getNBins()+".\n");
            double D;
            for(int i=0;i<histdelt2.getHistogram().length;i++){
            	D=(histdelt2.getHistogram()[i]-histdelt1.getHistogram()[i])/(4*500);
            	fileWriter.write(D+"\n");
            }
            
            fileWriter.close();
        }
        catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    
	private IVectorMutable [][][] coordBlocks;
	private IVectorMutable coordVectorAtom;
	private int numAtoms;
    private int numBlocks;
    private	int buffnum;
	private FileReader fileReader;
    private BufferedReader buffReader;
	private FileWriter fileWriter;
    private String msdOutput;
    private String msdInput;
    private double coord;
    private String positionLine;
    private String[] coordString;
    private int[] species;
    private int numSpecies;
    private int[][] jcount;
    

}
