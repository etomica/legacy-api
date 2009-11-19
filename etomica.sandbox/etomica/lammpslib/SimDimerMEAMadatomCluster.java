package etomica.lammpslib;

<<<<<<< SimDimerMEAMadatomCluster.java
import etomica.api.IAtomPositioned;
import etomica.api.IAtomType;
import etomica.api.IVectorMutable;
import etomica.atom.iterator.AtomIterator;
import etomica.atom.iterator.AtomIteratorBoxDependent;
import etomica.atom.iterator.AtomIteratorLeafFilteredType;
import etomica.data.meter.MeterMeanSquareDisplacement;
import etomica.dimer.SimDimerMEAMadatom;
import etomica.dimer.SimDimerMEAMadatomCluster;
=======
import etomica.action.WriteConfiguration;
import etomica.action.XYZWriter;
import etomica.api.IVectorMutable;
>>>>>>> 1.21
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

public class SimDimerMEAMadatomCluster extends Simulation{

	public SimDimerMEAMadatomCluster(Space space) {
		super(space);
	}

	public static void main(String[] args){
	        
        String fileName = args[0];
        double displacement = Double.parseDouble(args[1]);
        //boolean ortho = Boolean.parseBoolean(args[1]);
<<<<<<< SimDimerMEAMadatomCluster.java
		
		final SimDimerMEAMadatom sim = new SimDimerMEAMadatom();
		
        //System.out.println("Box vector: "+sim.box.getBoundary().getDimensions());
        //System.out.println("Number of Atoms: "+sim.box.getMoleculeList().getMoleculeCount());
        
		sim.refreshSpecies();

        IVectorMutable[] adatomList = new IVectorMutable[sim.box.getMoleculeList().getMoleculeCount()];
        IVectorMutable vect = sim.getSpace().makeVector();
        
        sim.setMovableAtoms(40.0, new Vector3D(13.5, -3.17, 3.75));
        sim.removeAtoms(2.0, new Vector3D(10.5, -3.17, 3.75));
        sim.randomizePositions(displacement);
        sim.setMovableAtoms(150.0, new Vector3D(13.5, -3.17, 3.75));
                
        sim.enableDimerSearch(fileName, 5000, false, false);
        //sim.enableMinimumSearch("110", true);
=======
        
    	final String APP_NAME = "SimDimerMEAMadatomCluster";

    	final SimDimerMEAMadatom sim = new SimDimerMEAMadatom();
        IVectorMutable vect = sim.getSpace().makeVector();
        vect.setX(0, 9.8);
        vect.setX(1, -0.2);
        vect.setX(2, -0.2);
        
        sim.setMovableAtoms(100.0, vect);
        
        sim.setPotentialListAtoms();
        
        //sim.removeAtoms(2.9, vect);
        
        //sim.initializeConfiguration("sns101-initial3");
        
        /*
        sim.initializeConfiguration(fileName+"_saddle");
        sim.calculateVibrationalModes(fileName+"_saddle");
        
        sim.initializeConfiguration(fileName+"_A_minimum");
        sim.calculateVibrationalModes(fileName+"_A_minimum");
        
        sim.initializeConfiguration(fileName+"_B_minimum");
        sim.calculateVibrationalModes(fileName+"_B_minimum");
        */
        
        
        //sim.initializeConfiguration(fileName+"_saddle");
        
        //sim.enableMolecularDynamics(5000);
        
        sim.enableDimerSearch(fileName, 2000, false, false);
        sim.integratorDimer.setRotNum(0);
        
        //sim.enableMinimumSearch(fileName, true);
>>>>>>> 1.21
        
        /*
        //Limit MSD calculation to a specific species
        AtomIterator aif = new AtomIteratorLeafFilteredType(sim.box, (IAtomType)sim.movable.getAtomType(0));
        MeterMeanSquareDisplacement msd1 = new MeterMeanSquareDisplacement(sim.getSpace(), sim.integratorDimerMin);
        msd1.setIterator((AtomIteratorBoxDependent)aif);
  		*/
        
    	sim.getController().actionPerformed();
    	
    	/*
		double sum = 0;
	    IVectorMutable msd = sim.getSpace().makeVector();
	    IVectorMutable [] msdVect = (IVectorMutable[]) msd1.getDataAsArray();
	     
	    for(int i=0; i<msdVect.length; i++){
	    	System.out.println(msdVect[i]);
	        sum = msd.x(0);
	        sum += msdVect[i].x(0)*msdVect[i].x(0);
	        msd.setX(0, sum);
	         
	        sum = msd.x(1);
	        sum += msdVect[i].x(1)*msdVect[i].x(1);
	        msd.setX(1, sum);
	         
	        sum = msd.x(2);
	        sum += msdVect[i].x(2)*msdVect[i].x(2);
	        msd.setX(2, sum);
	    }
	    System.out.println("MSD_____");
	    System.out.println(msd1.getDataAsScalar());
	    System.out.println(msd);
	    System.out.println(msd1.getDataAsArray()[msd1.getDataAsArray().length-1]+"     "+msd1.getDataAsArray()[msd1.getDataAsArray().length-1].squared());
		*/
    }

}
