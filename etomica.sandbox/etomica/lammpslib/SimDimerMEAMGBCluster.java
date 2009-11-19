package etomica.lammpslib;

<<<<<<< SimDimerMEAMGBCluster.java
import etomica.api.IAtomList;
import etomica.api.IVectorMutable;
=======
import etomica.api.IVectorMutable;
import etomica.dimer.SimDimerMEAMGB;
import etomica.dimer.SimDimerMEAMGBCluster;
>>>>>>> 1.16
import etomica.simulation.Simulation;
import etomica.space.Space;
import etomica.space3d.Vector3D;

/**
 * Simulation using Henkelman's Dimer method to find a saddle point for
 * an adatom of Sn on a surface, modeled with MEAM.
 * 
 * @author msellers
 *
 */

public class SimDimerMEAMGBCluster extends Simulation{
	

	public SimDimerMEAMGBCluster(Space space) {
		super(space);
	}

	public static void main(String[] args){
			
		 String fileName =	args[0];
		 final String APP_NAME = "SimDimerMEAMGBCluster";
	        
	     final SimDimerMEAMGB sim = new SimDimerMEAMGB(new int[] {1,0,1}, new int[] {3,3,8});
	        
	     
	     sim.initializeConfiguration("sn101-338");
	        
	        
        //System.out.println(sim.box.getBoundary().getDimensions().x(0));
        
        IVectorMutable dimerCenter = sim.getSpace().makeVector();
        dimerCenter.setX(0, sim.box.getBoundary().getDimensions().x(0)/2.0);
        dimerCenter.setX(1, 2.0);
        dimerCenter.setX(2, -1.0);
        
<<<<<<< SimDimerMEAMGBCluster.java
        IVectorMutable cubeSize = sim.getSpace().makeVector();
        cubeSize.setX(0, 10.0);
        cubeSize.setX(1, 10.0);
        cubeSize.setX(2, 3.0);
=======
        sim.initializeConfiguration("sngb101-4412-md");
        
        IVectorMutable dimerCenter = sim.getSpace().makeVector();
        dimerCenter.setX(0, sim.box.getBoundary().getBoxSize().getX(0)/2.0);
        dimerCenter.setX(1, 1.0);
        dimerCenter.setX(2, 0.0);
        IVectorMutable cubeSize = sim.getSpace().makeVector();
        cubeSize.setX(0, 6.0);
        cubeSize.setX(1, 8.0);
        cubeSize.setX(2, 8.0);
>>>>>>> 1.16
        
        if(sim.millerPlane[2] == 0){
<<<<<<< SimDimerMEAMGBCluster.java
            dimerCenter.setX(1, sim.box.getBoundary().getDimensions().x(1)/2.0);
            dimerCenter.setX(0, 4.0);
            dimerCenter.setX(2, -1.0);
=======
            dimerCenter.setX(1, sim.box.getBoundary().getBoxSize().getX(1)/2.0);
            dimerCenter.setX(0, 1.0);
            dimerCenter.setX(2, 0.0);
>>>>>>> 1.16
            cubeSize.setX(0, 6.0);
            cubeSize.setX(1, 8.0);
            cubeSize.setX(2, 8.0);
        }
        
        sim.refreshSpecies();
        //sim.setMovableAtomsSphere(7.0, dimerCenter);
        sim.setMovableAtomsCube(cubeSize, dimerCenter);
        sim.randomizePositions();
        sim.removeAtoms(1.0, dimerCenter);
        
        
        //sim.initializeConfiguration("searchStartGB");
        
        IAtomList list = sim.box.getLeafList();
      
        Vector3D move2 = new Vector3D(0.0,0.0,10.0);
        //sim.initializeConfiguration("0");
        move2.PE(sim.box.getBoundary().getDimensions());
        
        System.out.println("Atoms: "+list.getAtomCount());
        System.out.println("Interface Area: "+move2.x(0)*move2.x(1)+" angstroms");
        System.out.println("Box vector: "+sim.box.getBoundary().getDimensions());
        System.out.println("Number of Atoms: "+sim.box.getMoleculeList().getMoleculeCount());
        
        
        sim.enableDimerSearch(fileName, 2000, false, false);
        //sim.enableMinimumSearch("sngb101-d4", false);
        //sim.enableMinimumSearch(fileName, true);
        
        /*
        //Limit MSD calculation to a specific species
        AtomIteratorFiltered aif = AtomIteratorFiltered.makeIterator(new AtomIteratorLeafAtoms(sim.box), 
        		new AtomFilterTypeInstance(sim.dimer.getChildType(0)));
        MeterMeanSquareDisplacement msd = new MeterMeanSquareDisplacement(sim.getSpace(), sim.integratorDimerMin);
        msd.setIterator((AtomIteratorBoxDependent)aif);
        
        
        
        XYZWriter xyzwriter = new XYZWriter(sim.box);
        xyzwriter.setFileName(fileName+"_B_minimum.xyz");
        xyzwriter.setIsAppend(true);
        sim.integratorDimerMin.addIntervalAction(xyzwriter);
        sim.integratorDimerMin.setActionInterval(xyzwriter, 5);
        */
        
        /*
        WriteConfiguration writer = new WriteConfiguration(sim.getSpace());
        writer.setBox(sim.box);
        writer.setConfName(fileName+"-md");
        sim.integratorMD.addIntervalAction(writer);
        sim.integratorMD.setActionInterval(writer, 10000);
		*/
           
        sim.getController().actionPerformed();
        
        /*
        IVectorMutable [] msdarray = msd.getDataAsArray();
        aif.reset();
        int i=0;
        System.out.println("-----MSD Info-----");
        for(IAtom a=aif.nextAtom(); a!=null; a=aif.nextAtom()){
        	System.out.println(((IAtomLeaf)a).getLeafIndex()+"     "+Math.sqrt(msdarray[i].squared()));
        	i++;
        }
		*/
    }

}
