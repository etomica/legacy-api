package etomica.lammpslib;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import etomica.api.IBox;
import etomica.api.ISimulation;
import etomica.data.meter.MeterRDF;
import etomica.space.ISpace;

public class LXYZ2PropertyReader {
		private FileReader fileReader;
		private String inputFile, outputFile;
		private BufferedReader buffReader;
		private int numAtoms, numLines, step;
		private MeterRDF meterRDF;
		private IBox box;

		public LXYZ2PropertyReader(String xyzfile, String outputfile, int step, IBox box, ISimulation sim, ISpace space){
			this.inputFile = xyzfile;
			this.outputFile = outputfile;
			this.step = step;
			this.box = box;
			meterRDF = new MeterRDF(space);
			meterRDF.setBox(box);
			meterRDF.getXDataSource().setXMax(15.0);
			meterRDF.getXDataSource().setXMin(0.0);
			meterRDF.getXDataSource().setNValues(1000);
			
			//Open file
			try {
	            fileReader = new FileReader(inputFile);
	            System.out.println("Successivly opened "+inputFile);
	        }
	        catch(IOException e) {
	            throw new RuntimeException("Cannot open "+inputFile+", caught IOException: " + e.getMessage());
	        }
			
	        //Read in number of atoms
	        try {
	            buffReader = new BufferedReader(fileReader);
	            numAtoms = Integer.parseInt(buffReader.readLine());
	        } catch(IOException e) {
	            throw new RuntimeException("Problem reading "+inputFile+", caught IOException: " + e.getMessage());
	        }
	        box.setNMolecules(sim.getSpecies(0), numAtoms);
			
	        //Read in number of lines
	        try {
	        	numLines=1;
	            while (buffReader.readLine()!=null){
	              numLines++;
	            }
	            buffReader.close();
		        fileReader.close();
	        } catch(IOException e) {
	            throw new RuntimeException("Problem reading "+inputFile+", caught IOException: " + e.getMessage());
	        }
	        System.out.println("Atoms: "+numAtoms);
	        System.out.println("Lines: "+numLines);
	        try {
	            fileReader = new FileReader(inputFile);
	            buffReader = new BufferedReader(fileReader);
	            System.out.println("Successivly opened inputFile");

	        }
	        catch(IOException e) {
	            throw new RuntimeException("Cannot open "+inputFile+", caught IOException: " + e.getMessage());
	        }
	        
	  			
		}
		
		public void actionPerformed(){
			//Main step loop
	        int counter=0;
	        for(int i=0; i<numLines/(numAtoms+2); i++){
	        	
	        	//Sampled block and data collection
	        	if(counter%step==0){
	        		try {
	    	            buffReader.readLine();
	    	            buffReader.readLine();
						for(int a=0; a<numAtoms; a++){
							String positionLine = buffReader.readLine();
	                        String [] coordString = positionLine.split(" ");
	                        //Set atom position
	                        if(coordString.length!=4){throw new RuntimeException();}
	                        for (int icoord=1; icoord<4; icoord++) {
	                            double coord = Double.valueOf(coordString[icoord]).doubleValue();
	                            box.getLeafList().getAtom(a).getPosition().setX(icoord-1,coord);
	                        }
						}
					} catch (IOException e) {e.printStackTrace();
					}
					
					//ComputeRDF
					meterRDF.actionPerformed();
					
				}else{
					//Reads through one block
		        	try {
						for(int r=0; r<numAtoms+2; r++){
							buffReader.readLine();
						}
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				//Block done, increment counter.
	        	//System.out.println("Block "+counter+" of "+numLines/(numAtoms+2)+"");
				counter++;
	        }
			
	        //Output RDF
			for(int k=0; k<meterRDF.getData().getLength(); k++){
				System.out.println(meterRDF.getXDataSource().getData().getValue(k)+"   "+meterRDF.getData().getValue(k));
			}
			
			try {
				buffReader.close();
				fileReader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
}
