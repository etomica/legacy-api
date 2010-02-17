package etomica.lammpslib;

import etomica.space3d.Space3D;

public class LXYZ2MSDOrderN {
	
	
	
	public static void main(String[] args){
		
		String inputFile = args[0];
		String outputFile = inputFile+".msd";
		int dtmax = Integer.parseInt(args[1]);
		
		LMSDProcessorOrderN msdproc =  new LMSDProcessorOrderN(Space3D.getInstance(), inputFile, outputFile);
		msdproc.setDeltaTmax(dtmax);
		msdproc.fillArrays();
			
		}
}
