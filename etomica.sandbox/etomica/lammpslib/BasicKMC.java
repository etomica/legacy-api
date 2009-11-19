package etomica.lammpslib;

import etomica.api.IVectorMutable;
import etomica.simulation.Simulation;
import etomica.space3d.Space3D;

public class BasicKMC extends Simulation{
	
	double[] kmcData;
	double sumrates;
	int steps;
	double tau;
	IVectorMutable msd;
	int print;
	double rand;
	double[][] msdA = new double[300][4];
	int cmech, amech;
	
	public BasicKMC(double temp, double[] _kmcData, int _steps, int _print) {
		super(Space3D.getInstance());
		this.kmcData = _kmcData;
		this.sumrates = kmcData[0] + kmcData[0]+ kmcData[2] + kmcData[2];
		this.steps = _steps;
		this.print = _print;
		msd = space.makeVector();
		tau = 0;
		double interval = 0.0000005;
		double holder;
		amech=0;
		cmech=0;
		
		int count = 0;
		//System.out.println("RATE   "+"MSD   "+"TAU   ");
		for(int i=0; i<steps; i++){
			rand = random.nextDouble()*sumrates;
			tau = tau + (-Math.log(random.nextDouble())/sumrates);
			
			if(tau> interval){
				msdA[count][0] = interval;
				msdA[count][1] = msd.x(1)*msd.x(1);
				msdA[count][2] = msd.x(2)*msd.x(2);
				msdA[count][3] = msd.squared();
				interval += 0.0000005;
				count++;
			}
			
			if(rand <= kmcData[0]){
				holder = msd.x(1);
				holder += kmcData[1];
				msd.setX(1, holder);
				amech++;
			}
			//else{
			else if (rand <= (kmcData[0]+kmcData[0]) ){
				holder = msd.x(1);
				holder -= kmcData[1];
				msd.setX(1, holder);
				amech++;
			}
			
			else if (rand <= (kmcData[0]+kmcData[0]+kmcData[2]) ){
			//else{
				holder = msd.x(2);
				holder += kmcData[3];
				msd.setX(2, holder);
				cmech++;
			}
			
			else{
				holder = msd.x(2);
				holder -= kmcData[3];
				msd.setX(2, holder);
				cmech++;
			}
			
			//if(i>1000000){
			 // System.out.println(tau+"    "+msd.x(1)*msd.x(1)*1E-16/(2.0*tau)+"    "+msd.x(2)*msd.x(2)*1E-16/(2.0*tau)+"    "+(msd.squared()*1E-16)/(2.0*tau));
			//}
		}
		//System.out.println(tau+" seconds simulated.");
		
		//System.out.println("Dy("+temp+")= "+(msd.x(1)*1E-16)/(2.0*tau));
		//System.out.println("Dz("+temp+")= "+(msd.x(2)*1E-16)/(2.0*tau));
		//System.out.println(tau+"    "+msd.x(1)*msd.x(1)*1E-16/(2.0*tau)+"    "+msd.x(2)*msd.x(2)*1E-16/(2.0*tau)+"    "+(msd.squared()*1E-16)/(2.0*tau));
	}

	public static void main(String[] args){
		double temp = 300;
		int steps = 500000;
		int cee, ayy;
		double[][] msdArray = new double[300][4];
		double[] data = new double[4];
				cee=0;
				ayy=0;
				System.out.println(temp);
				for(int i=0; i<2000; i++){			
					double beta = 1.0/(temp*1.3806503E-023);
					
					//a-dir
					//rate
					data[0] = 647172559952.167 * Math.exp(-0.11386*(1.60217646E-19)*beta);
					//msd/jump
					data[1] = 2.96;
					
					//c-dir
					data[2] = 1.717E12 * Math.exp(-0.1493*(1.60217646E-19)*beta);
					data[3] = 3.23;
					

					final BasicKMC basicKMC = new BasicKMC(temp, data, steps,100000);
					cee += basicKMC.cmech;
					ayy += basicKMC.amech;
					for(int k=0; k<msdArray.length; k++){
						msdArray[k][0] = basicKMC.msdA[k][0];
						for(int m=1; m<4; m++){
							msdArray[k][m] += basicKMC.msdA[k][m];
						}
					}

				}
				for(int k=0; k<msdArray.length; k++){
					for(int m=1; m<4; m++){	
						msdArray[k][m] /= 2000;
					}
					System.out.println(msdArray[k][0]+"    "+msdArray[k][1]+"    "+msdArray[k][2]+"    "+msdArray[k][3]);
				}
				System.out.println(ayy/2000+"    "+cee/2000+"    ");

	}
}
