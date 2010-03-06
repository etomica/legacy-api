package etomica.lammpslib;

import etomica.lattice.crystal.Basis;
import etomica.space3d.Vector3D;

public class BasisCu6IMC extends Basis{

	public BasisCu6IMC() {
		super(unscaledCoordinates);
		// TODO Auto-generated constructor stub
	}
	
	private static final Vector3D[] unscaledCoordinates = new Vector3D[] {
	    	//Cu1
	    	new Vector3D(0.10109, 0.47571, 02.0264),
			//Cu2
	    	new Vector3D(0.30531, 0.50560, 0.60856),
			//Cu3
	    	new Vector3D(0.0, 0.0, 0.0),
			//Cu4
	    	new Vector3D(0.0, 0.16058, 0.25)
    };

    private static final long serialVersionUID = 1L;
    
}
