package etomica.lammpslib;

import etomica.api.IVectorMutable;
import etomica.simulation.Simulation;
import etomica.space.ISpace;

public class SimKMCmaster extends Simulation{

    /**
     * 
     */
    private static final long serialVersionUID = 1L;

    public SimKMCmaster(ISpace space) {
        super(space);
    }

    public static void main(String[] args){
        double temp = Double.parseDouble(args[0]);
        int steps = Integer.parseInt(args[1]);
        int totalSearch = Integer.parseInt(args[2]);
        int kmcStep = Integer.parseInt(args[3]);
        final String APP_NAME = "SimKMCmaster";

<<<<<<< SimKMCmaster.java
        final SimKMCMEAMGB sim = new SimKMCMEAMGB(new int[] {1,0,1}, new int[] {3,3,8});
=======
        final SimKMCMEAMadatom sim = new SimKMCMEAMadatom();
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 9.8);
        vect.setX(1, -0.2);
        vect.setX(2, -0.2);
               
        sim.setMovableAtoms(100.0, vect);
>>>>>>> 1.6
        
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
        sim.initializeConfiguration("initialStart");
        sim.integratorKMCCluster(temp, steps, totalSearch);
        sim.integratorKMCCluster.setKMCStep(kmcStep);

        sim.getController().actionPerformed();
    }
}
