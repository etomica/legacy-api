package etomica.lammpslib;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import etomica.action.XYZWriter;
import etomica.api.IAtomPositioned;
import etomica.api.ISpecies;
import etomica.api.IVector;
import etomica.api.IVectorMutable;
import etomica.dimer.IntegratorDimerMin;
import etomica.exception.ConfigurationOverlapException;
import etomica.listener.IntegratorListenerAction;
=======
import etomica.api.IVectorMutable;
import etomica.dimer.SimDimerMEAMadatom;
>>>>>>> 1.4
import etomica.simulation.Simulation;
import etomica.space.ISpace;

public class SimKMCworker extends Simulation{

    /**
     * 
     */
    private static final long serialVersionUID = 1L;

    public SimKMCworker(ISpace space) {
        super(space);
    }
    
    public void findMinima(IntegratorDimerMin integrator, boolean dir, String fileName, XYZWriter xyzMin){
        integrator.setFileName(fileName);
        integrator.setDirection(dir);
        try {
            integrator.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        xyzMin.setFileName(fileName+"_B_minimum.xyz");
        if(dir==false){xyzMin.setFileName(fileName+"_A_minimum.xyz");}  
        
    	if(new File(fileName+".stop").exists()){
    		return;
    	}
        
        //msd1.reset();
        for(int j=0;j<2000;j++){
            integrator.doStep();
            if(integrator.minFound){
            	if(new File(fileName+".stop").exists()){
            		return;
            	}
            	integrator.quitSearch();
                return;
            }
        }
    }
    
    public void getWriteData(IntegratorDimerMin integrator, String fileName, boolean dir){
        try{
            FileWriter fileWriter = new FileWriter(fileName+"_min_ev", false);
            if(dir==false){fileWriter.write(integrator.e0+"\n"+"A");}
            else{fileWriter.write(integrator.e0+"\n"+"B");};
            fileWriter.close();
        }catch(IOException e) {
          
        }
    }
    
    public static void main(String[] args){
        String fileName = args[0];
        boolean ortho = Boolean.getBoolean(args[1]);
        
        final String APP_NAME = "SimKMCworker";        
        final SimKMCMEAMGB sim = new SimKMCMEAMGB(new int[] {1,0,1}, new int[] {3,3,8});
        final SimKMCworker worker = new SimKMCworker(sim.getSpace());
        
        if(new File("workers.stop").exists()){
    		System.exit(1);
        }
        
        new File(fileName+".stop").delete();
        new File(fileName+"_saddle.pos").delete();
        new File(fileName+"_A_saddle.pos").delete();
        new File(fileName+"_B_saddle.pos").delete();
        new File(fileName+"_s_ev").delete();
        new File(fileName+"_min_ev").delete();
        new File(fileName+"_A_minimum.pos").delete();
        new File(fileName+"_B_minimum.pos").delete();
        new File(fileName+"_A_minimum.xyz").delete();
        new File(fileName+"_B_minimum.xyz").delete();
                
        sim.initializeConfiguration("sn101-338");
        sim.refreshSpecies();
                
        IVectorMutable dimerCenter = sim.getSpace().makeVector();
        dimerCenter.setX(0, sim.box.getBoundary().getDimensions().x(0)/2.0);
        dimerCenter.setX(1, 2.0);
        dimerCenter.setX(2, -1.0);
        
        IVectorMutable cubeSize = sim.getSpace().makeVector();
        cubeSize.setX(0, 10.0);
        cubeSize.setX(1, 10.0);
        cubeSize.setX(2, 3.0);
        
        sim.setMovableAtomsCube(cubeSize, dimerCenter);
        sim.removeAtoms(1.0, dimerCenter);
	        
        sim.initializeConfiguration("/usr/users/msellers/KMC/sn-gb-lammps/searchStart");
        
        IVectorMutable [] minPosition = new IVectorMutable[sim.box.getMoleculeList().getMoleculeCount()]; 
        IVectorMutable [] currentSaddle = new IVectorMutable[sim.box.getMoleculeList().getMoleculeCount()];
        for(int i=0; i<minPosition.length; i++){
        	minPosition[i] = sim.getSpace().makeVector();
        	currentSaddle[i] = sim.getSpace().makeVector();
        	minPosition[i].E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
        }
        
        sim.randomizePositions();
        
        sim.enableDimerSearch(fileName, 2000, ortho);
        
        sim.getController().actionPerformed();
        
        double positionDiff = 0;
        //check against minimum
        for(int j=0; j<currentSaddle.length; j++){
            currentSaddle[j].E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
            currentSaddle[j].ME(minPosition[j]);
            sim.box.getBoundary().nearestImage(currentSaddle[j]);
            positionDiff += currentSaddle[j].squared();
        }
        if(positionDiff < 0.02 || positionDiff > 200.0){
            System.out.println("Position difference too small or too large: "+positionDiff);
            new File(fileName+"_saddle.pos").delete();
            new File(fileName+"_A_saddle.pos").delete();
            new File(fileName+"_B_saddle.pos").delete();
            new File(fileName+"_s_ev.pos").delete();
            System.out.println("Exiting...");
            System.exit(1);
            
        }
        
        IntegratorDimerMin integratorMin = new IntegratorDimerMin(sim, sim.lammpsSim, sim.potentialMaster, new ISpecies[]{sim.movable}, sim.getSpace());
        
        integratorMin.setBox(sim.box);
                        
        XYZWriter xyzMin = new XYZWriter(sim.box);
        xyzMin.setIsAppend(true);
        
        xyzMin = new XYZWriter(sim.box);
        xyzMin.setIsAppend(true);
        IntegratorListenerAction xyzMinListener = new IntegratorListenerAction(xyzMin);
        xyzMinListener.setInterval(30);               
        
        
        integratorMin.getEventManager().addListener(xyzMinListener);
        
        //FIRST MINIMUM SEARCH
        boolean diffMinA, diffMinB;
        worker.findMinima(integratorMin, false, fileName, xyzMin);
        //compute msd
        //msdTemp.E(msdCalc());
        
        for(int j=0; j<minPosition.length; j++){
            currentSaddle[j].E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
            currentSaddle[j].ME(minPosition[j]);
            sim.box.getBoundary().nearestImage(currentSaddle[j]);
            positionDiff += currentSaddle[j].squared();
        }
        System.out.println("mincheck1 pos diff:"+positionDiff);
        diffMinA = true;
        if(positionDiff < 0.5){
        	diffMinA = false;
        	System.out.println("Common minimum found in the A direction!");
        }
        
    	if(new File(fileName+".stop").exists()){
    		System.exit(1);
        }
        
        //SECOND MINIMUM SEARCH
       	worker.findMinima(integratorMin, true, fileName, xyzMin);
       	//msdTemp.PE(msdCalc());
        for(int j=0; j<minPosition.length; j++){
            currentSaddle[j].E(((IAtomPositioned)sim.box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
            currentSaddle[j].ME(minPosition[j]);
            sim.box.getBoundary().nearestImage(currentSaddle[j]);
            positionDiff += currentSaddle[j].squared();
        }
        System.out.println("mincheck2 pos diff:"+positionDiff);
        diffMinB = true;
        if(positionDiff < 0.5){
        	diffMinB = false;
        	System.out.println("Common minimum found in the B direction!");
        }
        
    	if(new File(fileName+".stop").exists()){
    		diffMinA=false;
    		diffMinB=false;
        }
        
        // good - first search returned original minimum, second was new.
        if(diffMinA==false && diffMinB==true){
        	worker.getWriteData(integratorMin, fileName, true);
        	
        	if(new File(fileName+".stop").exists()){
        		new File(fileName+"_saddle.pos").delete();
                new File(fileName+"_A_saddle.pos").delete();
                new File(fileName+"_B_saddle.pos").delete();
                new File(fileName+"_s_ev").delete();
                new File(fileName+"_A_minimum.pos").delete();
                new File(fileName+"_B_minimum.pos").delete();
                new File(fileName+"_A_minimum.xyz").delete();
                new File(fileName+"_B_minimum.xyz").delete();
                new File(fileName+"_min_ev").delete();
        	}
        	System.exit(1);
        }
        //good - first search returned new, second was original.
        if(diffMinA==true && diffMinB==false){
        	worker.getWriteData(integratorMin, fileName, false);
        	
        	if(new File(fileName+".stop").exists()){
        		new File(fileName+"_saddle.pos").delete();
                new File(fileName+"_A_saddle.pos").delete();
                new File(fileName+"_B_saddle.pos").delete();
                new File(fileName+"_s_ev").delete();
                new File(fileName+"_A_minimum.pos").delete();
                new File(fileName+"_B_minimum.pos").delete();
                new File(fileName+"_A_minimum.xyz").delete();
                new File(fileName+"_B_minimum.xyz").delete();
                new File(fileName+"_min_ev").delete();
        	}
        	System.exit(1);
        }
        
        System.out.println("No common minimum found.  Restarting search...");
        //bad - no minimum found.
        new File(fileName+"_saddle.pos").delete();
        new File(fileName+"_A_saddle.pos").delete();
        new File(fileName+"_B_saddle.pos").delete();
        new File(fileName+"_s_ev").delete();
        new File(fileName+"_A_minimum.pos").delete();
        new File(fileName+"_B_minimum.pos").delete();
        new File(fileName+"_A_minimum.xyz").delete();
        new File(fileName+"_B_minimum.xyz").delete();
        
    }
}
