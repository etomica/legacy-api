package etomica.lammpslib;

import etomica.space3d.Space3D;
import etomica.zeolite.MSDProcessor;

public class xyz2msd {
	
	
	
	public static void main(String[] args){
		
		String inputFile = args[0];
		String outputFile = inputFile+".msd";
		
		MSDProcessor msdproc =  new MSDProcessor(Space3D.getInstance(), inputFile, outputFile);
		msdproc.setDeltaTmax(800);
		msdproc.fillArrays();
			
		}
}
