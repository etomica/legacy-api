package etomica.lammpslib;

import etomica.api.IVector;

public class LammpsInterface {

    public final static native long makeLammpsSim(String arg1);
    public final static native void setAtomPosition(long lammpsSim, int idx, double x, double y, double z);
    public final static native void getForce(long lammpsSim, int idx, IVector force);
    public final static native double getEnergy(long lammpsSim);
    public final static native void doLammpsStep(long lammpsSim, int num);

}
