package etomica.lammpslib;

import etomica.lattice.crystal.Basis;
import etomica.space3d.Vector3D;

public class BasisSn5IMC extends Basis{

	public BasisSn5IMC() {
		super(unscaledCoordinates);
		// TODO Auto-generated constructor stub
	}
	
	private static final Vector3D[] unscaledCoordinates = new Vector3D[] {
	    	//Sn1
	    	new Vector3D(0.39197, 0.16378, 0.52920),
			//Sn2
	    	new Vector3D(0.28720, 0.65607, 0.35605),
			//Sn3
	    	new Vector3D(0.0, 0.80035, 0.25)
    };

    private static final long serialVersionUID = 1L;
    
}
