package etomica.lammpslib;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import etomica.action.WriteConfiguration;
import etomica.action.XYZWriter;
<<<<<<< IntegratorKMCCluster.java
import etomica.api.IAtomPositioned;
import etomica.api.IAtomType;
import etomica.api.IBox;
=======
import etomica.api.IMoleculeList;
>>>>>>> 1.17
import etomica.api.IPotentialMaster;
import etomica.api.IRandom;
import etomica.api.ISimulation;
import etomica.api.ISpecies;
<<<<<<< IntegratorKMCCluster.java
import etomica.api.IVectorMutable;
import etomica.atom.iterator.AtomIterator;
=======
import etomica.api.IVector;
import etomica.api.IVectorMutable;
import etomica.atom.iterator.AtomIterator;
>>>>>>> 1.17
import etomica.atom.iterator.AtomIteratorBoxDependent;
import etomica.atom.iterator.AtomIteratorLeafFilteredType;
import etomica.config.ConfigurationFile;
import etomica.data.meter.MeterMeanSquareDisplacement;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.exception.ConfigurationOverlapException;
import etomica.integrator.IntegratorBox;
<<<<<<< IntegratorKMCCluster.java
import etomica.listener.IntegratorListenerAction;
=======
import etomica.listener.IntegratorListenerAction;
import etomica.nbr.list.PotentialMasterList;
>>>>>>> 1.17
import etomica.space.ISpace;

public class IntegratorKMCCluster extends IntegratorBox{

    private static final long serialVersionUID = 1L;
    IntegratorDimerMin integratorMin;
    IPotentialMaster potentialMaster;
    double temperature;
    private final ISpace space;
    IRandom random;
    ISimulation sim;
    ISpecies [] species;
    IVectorMutable [] minPosition, currentSaddle, previousSaddle;
    double[] saddleVib;
    double[] saddleEnergies;
    double[] rates;
<<<<<<< IntegratorKMCCluster.java
    double tau, tauTemp;
    IVectorMutable msdVect, msdTemp;
=======
    double tau;
    IVectorMutable msd;
>>>>>>> 1.17
    double beta;
    double massSec;
    double minEnergy;
    double freqProd;
    double saddleEnergy;
    int negMode;
    double minVib;
    boolean search, diffMin1, diffMin2;
    int searchNum;
    int kmcStep;
    int rateNum;
    int totalSearches;
    long lammps;
    XYZWriter xyzMin;
    MeterMeanSquareDisplacement msd1;
    FileReader fileReader, writeTau;
    BufferedReader buffReader;
    FileWriter writer;
    CalcVibrationalModes vib;
    
    public IntegratorKMCCluster(ISimulation _sim, long library, IPotentialMaster _potentialMaster, double _temperature, int _totalSearches, IRandom _random, ISpecies [] _species, ISpace _space){
        super(_potentialMaster, _temperature);
        
        this.potentialMaster = _potentialMaster;
        this.temperature = _temperature;
        this.space = _space;
        this.random = _random;
        this.sim = _sim;
        this.lammps = library;
        this.species = _species;
        this.totalSearches = _totalSearches;
        kmcStep = 1;
  
        // TODO Auto-generated constructor stub
    }

    protected void doStepInternal(){
        
        //Set minimum config
        loadConfiguration((kmcStep-1)+"", box);
                        
        setInitialStateConditions();
        
        //msd1.reset();
        
        launchSearches();
        
        loadSaddles();
        
        calcRates();
        
        //update TAU
        calcTau();
        tau += tauTemp;
        
        rateNum = chooseRate();
        System.out.println("Rate "+rateNum+" is chosen.");
        System.out.println("Step "+(kmcStep-1)+": tau is "+tau);
<<<<<<< IntegratorKMCCluster.java
=======
                
        //Minimum Search with random transition
        integratorMin1.setFileName("s_"+rateNum);
        try {
            integratorMin1.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        xyzMin1.setFileName((kmcStep-1)+"_s-A.xyz");
        writeConfiguration((kmcStep-1)+"_s");      
>>>>>>> 1.17
        
        loadConfiguration("s_"+rateNum+"_saddle",box);
        writeConfiguration((kmcStep-1)+"_s");
        
        getMinimumData2(rateNum);
        
        
        /**
        while(true){
            rateNum = chooseRate();
            if(rateNum==99999){
                break;
            }
<<<<<<< IntegratorKMCCluster.java
            
            System.out.println("Rate "+rateNum+" is chosen.");
            System.out.println("Step "+(kmcStep-1)+": tau is "+tau);
            
            //FIRST MINIMUM SEARCH
            findMinima(rateNum, true, "A");
            //compute msd
            msdTemp.E(msdCalc());
            diffMin1 = checkMin();
            //first search returned new minimum.
            if(diffMin1==true){
                getMinimumData();
            }

            //SECOND MINIMUM SEARCH
            String xyzNombre;
            if(diffMin1==true){
                xyzNombre = "B";
                findMinima(rateNum, false, xyzNombre);
            }
            else{
                xyzNombre = "A-fwd";
                findMinima(rateNum, false, xyzNombre); 
=======
        }
        msdCalc(msd1);
        if(checkMin()){
            minEnergy = integratorMin1.e0;
            minVib = integratorMin1.vib.getProductOfFrequencies();
            writeConfiguration(kmcStep+"");
            writeConfiguration("searchStart");
            setInitialStateConditions(minEnergy, minVib);
            System.out.println("Good minimum found. Computing MSD for other direction...");
            integratorMin2.setFileName("s_"+rateNum);
            try {
                integratorMin2.reset();
            } catch (ConfigurationOverlapException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
>>>>>>> 1.17
            }
            msdTemp.PE(msdCalc());
            diffMin2 = checkMin();
            
            // good - first search returned original minimum, second was new.
            if(diffMin1==false && diffMin2==true){
                System.out.println("Good minima.");
                getMinimumData();
                break;
            }
<<<<<<< IntegratorKMCCluster.java
            //good - first search returned new, second was original.
            if(diffMin1==true && diffMin2==false){
                System.out.println("Good minima.");
                break;
=======
            msdCalc(msd2);
        }else{
            integratorMin2.setFileName("s_"+rateNum);
            //rename minimum 1 search XYZ file
            try {
                integratorMin2.reset();
            } catch (ConfigurationOverlapException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
>>>>>>> 1.17
            }
            
            //malo - both minimum are new or same minimum, choose another saddle.
            System.out.println("Bad mechanism #"+rateNum+".  Choosing another...");
            rates[rateNum] = 0.0;
            //remove xyz files from minimum search.
            new File((kmcStep-1)+"_s-A.xyz").delete();
            new File((kmcStep-1)+"_s-"+xyzNombre+".xyz").delete();
        }
        
        
        //All rates are zero, recompute saddles.
        if(rateNum==99999){
            tau -= tauTemp;
            return;
        }
        **/
        
        //Update MSD
        //msdVect.PE(msdTemp);
        
        //Write out positions for new dimer search
        loadConfiguration(kmcStep+"", box);
        writeConfiguration("searchStart");
        
        try {
            writer = new FileWriter("tau-msd.dat", true);
            writer.write("-step "+kmcStep+"\n"+"tau: "+tau+"\n"+"msd: "+msdVect+"\n");
            writer.close();
            
            FileWriter writer2 = new FileWriter(kmcStep+"_ev");
            writer2.write(minEnergy+"\n"+minVib);
            writer2.close();
            
            FileWriter writer3 = new FileWriter((kmcStep-1)+"_s_ev");
            writer3.write(saddleEnergies[rateNum]+"\n"+saddleVib[rateNum]);
            writer3.close();
            
        }catch(IOException e) {
            
        }
        
        for(int i=0; i<totalSearches; i++){
            new File("s_"+i+"_min_ev").delete();            
        }
        clearRatesandEnergies();
        kmcStep++;
    }
    
    public void setup(){
        search = true;
        saddleVib = new double[totalSearches];
        saddleEnergies = new double[totalSearches];
<<<<<<< IntegratorKMCCluster.java
        massSec = Math.sqrt(species[0].getAtomType(0).getMass()) * 0.000000000001;
        msdVect = space.makeVector();
        msdTemp = space.makeVector();
=======
        massSec = Math.sqrt(species[0].getAtomType(0).getMass()) * 0.000000000001;
        msd = space.makeVector();
>>>>>>> 1.17
        tau = 0;
        tauTemp = 0;

        searchNum = 0;
        rates = new double[totalSearches];
        beta = 1.0/(temperature*1.3806503E-023);
<<<<<<< IntegratorKMCCluster.java
        currentSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        previousSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        minPosition = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
=======
        currentSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        previousSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
>>>>>>> 1.17
        for(int i=0; i<currentSaddle.length; i++){
            minPosition[i] = space.makeVector();
            currentSaddle[i] = space.makeVector();
            previousSaddle[i] = space.makeVector();
        }
        
        //createIntegrators();
        
        vib = new CalcVibrationalModes(lammps);
        vib.setup(box, potentialMaster, box.getMoleculeList(species[0]), space);
        
    }
    
    public void setInitialStateConditions(){
    	try {
            FileReader fileReaderInit = new FileReader((kmcStep-1)+"_ev");
            BufferedReader buffReaderInit = new BufferedReader(fileReaderInit);
            minEnergy = Double.parseDouble(buffReaderInit.readLine());
            minVib = Double.parseDouble(buffReaderInit.readLine());
        }
        catch(IOException e) {}

    	
        for(int i=0; i<minPosition.length; i++){
            minPosition[i].E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
        }  
    }
    
    public void setKMCStep(int step){
    	kmcStep = step;
    }
        
    public void launchSearches(){
    	
        for(int i=0; i<totalSearches; i++){
        	new File(i+".done").delete();
        	
        }
    	   	
        for(int i=0; i<totalSearches; i++){
            try {
                FileWriter goWriter = new FileWriter(i+".go");
                goWriter.close();
            } catch (IOException e1) {        }
        }
        
        new File("workers.stop").delete();
        
        while(true){
            int success = 0;
            for(int i=0; i<totalSearches; i++){
                if(new File(i+".done").exists()){
                    success++;
                }  
            }
            if(success>10){
                break;
            }
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e){        }
        }
    
        try {
            FileWriter goWriter2 = new FileWriter("workers.stop");
            goWriter2.close();
        } catch (IOException e1) {        }
        
        
<<<<<<< IntegratorKMCCluster.java
        for(int i=0; i<totalSearches; i++){
            try {
                FileWriter quitWriter = new FileWriter("s_"+i+".stop");
                quitWriter.close();
            } catch (IOException e1) {        }
            
            new File(i+".go").delete();
            
=======
        IMoleculeList loopSet2 = box.getMoleculeList();
        minPosition = new IVectorMutable[loopSet2.getMoleculeCount()];
        for(int i=0; i<minPosition.length; i++){
            minPosition[i] = space.makeVector();
>>>>>>> 1.17
        }
        
<<<<<<< IntegratorKMCCluster.java
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e){        }
        
=======
        for(int i=0; i<loopSet2.getMoleculeCount(); i++){
            minPosition[i].E(loopSet2.getMolecule(i).getChildList().getAtom(0).getPosition());
        }  
>>>>>>> 1.17
    }
    
<<<<<<< IntegratorKMCCluster.java
    public void loadSaddles(){
        searchNum = 0;
        for(int i=0; i<saddleEnergies.length; i++){
        	if(new File(i+".done").exists()){
	            loadConfiguration("s_"+i+"_saddle",box);
	            try {
	                fileReader = new FileReader("s_"+i+"_s_ev");
	                buffReader = new BufferedReader(fileReader);
	                saddleEnergy = Double.parseDouble(buffReader.readLine());
	                freqProd = Double.parseDouble(buffReader.readLine());
	                negMode = Integer.parseInt(buffReader.readLine());
	            }
	            catch(IOException e) {}
	
	            if(checkUniqueSaddle() && negMode==1){
	                System.out.println("Good search "+i+", adding saddle data.");
	                saddleEnergies[i] = saddleEnergy;
	                saddleVib[i] = freqProd;
	            }
        	}
            searchNum++;
=======
    public void randomizePositions(){
        IVectorMutable workVector = space.makeVector();
        IMoleculeList loopSet3 = box.getMoleculeList(species[0]);
        IVectorMutable [] currentPos = new IVectorMutable [loopSet3.getMoleculeCount()];
        double offset = 0;
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
            currentPos[i] = (loopSet3.getMolecule(i).getChildList().getAtom(0).getPosition());
            for(int j=0; j<3; j++){
                offset = random.nextGaussian()/10.0;
                if(Math.abs(offset)>0.1){offset=0.1;}
                workVector.setX(j,offset);
            }
            currentPos[i].PE(workVector);
>>>>>>> 1.17
        }
    }
    
    public void calcRates(){
        //convert energies to Joules and use hTST
        double rateSum = 0;
        minEnergy = minEnergy*1.60217646E-19;
        for(int i=0; i<rates.length; i++){
            if(saddleEnergies[i]==0){continue;}
            saddleEnergies[i] = saddleEnergies[i]*1.60217646E-19;
            rates[i] = ( Math.exp(minVib - saddleVib[i]) / massSec ) * Math.exp( -(saddleEnergies[i] - minEnergy)*beta );
            rateSum += rates[i];
        }

    }
    
    public void calcTau(){
        double rateSum = 0;
        for(int i=0; i<rates.length; i++){
            rateSum += rates[i];
        }
        tauTemp = -Math.log(random.nextDouble())/rateSum;
    }
    public void findMinima(int mechanism, boolean dir, String xyzName){
        integratorMin.setFileName("s_"+mechanism);
        integratorMin.setDirection(dir);
        try {
            integratorMin.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        xyzMin.setFileName((kmcStep-1)+"_s-"+xyzName+".xyz");
        writeConfiguration((kmcStep-1)+"_s");      
        msd1.reset();
        for(int j=0;j<2000;j++){
            integratorMin.doStep();
            if(integratorMin.minFound){
                break;
            }
        }
    }
    
    public void getMinimumData(){
        integratorMin.quitSearch();
        minEnergy = integratorMin.e0;
        calcVibrationalModes();
        minVib = vib.getProductOfFrequencies();
        writeConfiguration(kmcStep+"");
        System.out.println("Good minimum found.");
    }
    
    public void getMinimumData2(int rate){
    	String dir = null;
        try {
            fileReader = new FileReader("s_"+rate+"_min_ev");
            buffReader = new BufferedReader(fileReader);
            minEnergy = Double.parseDouble(buffReader.readLine());
            dir = buffReader.readLine();
        }
        catch(IOException e) {}
        loadConfiguration("s_"+rate+"_"+dir+"_minimum",box);
        calcVibrationalModes();
        minVib = vib.getProductOfFrequencies();
        writeConfiguration(kmcStep+"");
        System.out.println("Good minimum found.");
        if(dir=="A"){
        	new File("s_"+rate+"_A_minimum.xyz").renameTo(new File((kmcStep-1)+"_s.xyz"));
        	new File("s_"+rate+"_B_minimum.xyz").renameTo(new File((kmcStep-1)+".xyz"));
        }
        else{
        	new File("s_"+rate+"_B_minimum.xyz").renameTo(new File((kmcStep-1)+"_s.xyz"));
        	new File("s_"+rate+"_A_minimum.xyz").renameTo(new File((kmcStep-1)+".xyz"));
        }
    }
    
    public IVectorMutable msdCalc(){
        double sum = 0;
        IVectorMutable msd = space.makeVector();
        IVectorMutable [] msdVect = (IVectorMutable[]) msd1.getDataAsArray();
        
        for(int i=0; i<msdVect.length; i++){
            sum = msd.getX(0);
            sum += msdVect[i].getX(0)*msdVect[i].getX(0);
            msd.setX(0, sum);
            
            sum = msd.getX(1);
            sum += msdVect[i].getX(1)*msdVect[i].getX(1);
            msd.setX(1, sum);
            
            sum = msd.getX(2);
            sum += msdVect[i].getX(2)*msdVect[i].getX(2);
            msd.setX(2, sum);
        }
        return msd;
    }
    
    public void clearRatesandEnergies(){
    	new File("log.lammps").delete();
        for(int i=0; i<rates.length; i++){
            rates[i] = 0.0;
            saddleEnergies[i] = 0.0;
            saddleVib[i] = 0.0;
        }
    }

    public int chooseRate(){
        int rt = 0;
        double sum = 0;
        double rand = random.nextDouble();
        for(int q=0; q<rates.length; q++){
            sum += rates[q];
        }
        if(sum==0){
            return 99999;
        }
        double sumgrt = 0;
        for(int i=0; i<rates.length; i++){
            sumgrt += rates[i];
            if(rand*sum<=sumgrt){
                rt = i;
                System.out.println("-----Choosing a rate-----");
                for(int l=0; l<rates.length; l++){
                    if(rates[i]==0){continue;}
                    System.out.println("Rate "+l+": "+rates[l]);
                }
                System.out.println("Sum:    "+sum);
                System.out.println("-------------------------");
                System.out.println(rand*sum+" <= "+sumgrt);
                break;
            }
        }
        return rt;
    }
    
<<<<<<< IntegratorKMCCluster.java
    private boolean checkUniqueSaddle(){ 
        double positionDiff = 0;
        /*
        //check against minimum (surface)
        for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
            currentSaddle[j].E(((IAtomPositioned)box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
            currentSaddle[j].ME(minPosition[j]);
            box.getBoundary().nearestImage(currentSaddle[j]);
            positionDiff += currentSaddle[j].squared();
        }
        if(positionDiff < 0.2){
            System.out.println("Position difference from minimum: "+positionDiff);
            System.out.println("Too similar to minimum.");
            return false;
        }
        System.out.println("Position difference from minimum: "+positionDiff);
        
        */
        //check against other saddles
        for(int p=0; p<box.getMoleculeList().getMoleculeCount(); p++){
            currentSaddle[p].E(((IAtomPositioned)box.getMoleculeList().getMolecule(p).getChildList().getAtom(0)).getPosition());
=======
    private boolean checkUniqueSaddle(){    
        for(int p=0; p<box.getMoleculeList().getMoleculeCount(); p++){
            currentSaddle[p].E(box.getMoleculeList().getMolecule(p).getChildList().getAtom(0).getPosition());
>>>>>>> 1.17
        }
        for(int i=0; i<searchNum; i++){
<<<<<<< IntegratorKMCCluster.java
        	if(new File("s_"+i+"_min_ev").exists()){
	            positionDiff = 0;
	            loadConfiguration("s_"+i+"_saddle",box);
	            for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
	                previousSaddle[j].E(((IAtomPositioned)box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
	                previousSaddle[j].ME(currentSaddle[j]);
	                box.getBoundary().nearestImage(previousSaddle[j]);
	                positionDiff += previousSaddle[j].squared();
	            }
	            if(positionDiff < 0.2){
	                System.out.println("Duplicate saddle found. Position difference: "+positionDiff);
	                return false;
	            }
        	}
=======
            double positionDiff = 0;
            loadConfiguration("s_"+i+"_saddle");
            for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
                previousSaddle[j].E(box.getMoleculeList().getMolecule(j).getChildList().getAtom(0).getPosition());
                previousSaddle[j].ME(currentSaddle[j]);
                positionDiff += previousSaddle[j].squared();
            }
            if(positionDiff < 0.5){
                System.out.println("Duplicate saddle found.");
                return false;
            }
>>>>>>> 1.17
        }
        System.out.println("Unique saddle found.  Position difference: "+positionDiff);
        return true;  
    }
    
    public boolean checkMin(){
        IVectorMutable workVector = space.makeVector();
        double positionDiff=0;
<<<<<<< IntegratorKMCCluster.java
        for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            workVector.ME(minPosition[i]);
            box.getBoundary().nearestImage(workVector);
=======
        for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
            workVector.Ev1Mv2(minPosition[i],box.getMoleculeList().getMolecule(i).getChildList().getAtom(0).getPosition());
>>>>>>> 1.17
            positionDiff += workVector.squared();
        }
        System.out.println("mincheck pos diff:"+positionDiff);
        if(positionDiff > 0.5){return true;}
        return false;
    }
    
    public void calcVibrationalModes(){
        vib.actionPerformed();
    }
    
    public void writeConfiguration(String file){
        WriteConfiguration writer = new WriteConfiguration(space);
        writer.setBox(box);
        writer.setConfName(file);
        writer.actionPerformed();
    }
    
    public void loadConfiguration(String file, IBox boxA){
        ConfigurationFile config = new ConfigurationFile(file);
        config.initializeCoordinates(boxA); 
    }
    
    public void createIntegrators(){
        integratorMin = new IntegratorDimerMin(sim, lammps, potentialMaster, species, space);
        
        integratorMin.setBox(box);
        xyzMin = new XYZWriter(box);
        xyzMin.setIsAppend(true);
        IntegratorListenerAction xyzMinListener = new IntegratorListenerAction(xyzMin);
        xyzMinListener.setInterval(5);               
        
        
<<<<<<< IntegratorKMCCluster.java
        integratorMin.getEventManager().addListener(xyzMinListener);
=======
        if(potentialMaster instanceof PotentialMasterListDimer){
            integratorMin2.getEventManager().addListener(((PotentialMasterList)potentialMaster).getNeighborManager(box)); 
        }
                
        xyzMin1 = new XYZWriter(box);
        xyzMin2 = new XYZWriter(box);
        xyzMin1.setIsAppend(true);
        xyzMin2.setIsAppend(true);
        
        IntegratorListenerAction xyzMin1Listener = new IntegratorListenerAction(xyzMin1);
        xyzMin1Listener.setInterval(5);
        IntegratorListenerAction xyzMin2Listener = new IntegratorListenerAction(xyzMin2);
        xyzMin2Listener.setInterval(5);
        integratorMin1.getEventManager().addListener(xyzMin1Listener);
        integratorMin2.getEventManager().addListener(xyzMin2Listener);
        IntegratorListenerAction imposePbc1Listener = new IntegratorListenerAction(imposePbc);
        imposePbc1Listener.setInterval(1);
        IntegratorListenerAction imposePbc2Listener = new IntegratorListenerAction(imposePbc);
        imposePbc2Listener.setInterval(1);
        integratorMin1.getEventManager().addListener(imposePbc1Listener);
        integratorMin2.getEventManager().addListener(imposePbc2Listener);
>>>>>>> 1.17
        
        //Limit MSD calculation to a specific species
<<<<<<< IntegratorKMCCluster.java
        AtomIterator aif = new AtomIteratorLeafFilteredType(box, (IAtomType)species[0].getAtomType(0));
        msd1 = new MeterMeanSquareDisplacement(space, integratorMin);
=======
        AtomIterator aif = new AtomIteratorLeafFilteredType(box, species[0].getAtomType(0));
        msd1 = new MeterMeanSquareDisplacement(space, integratorMin1);
        msd2 = new MeterMeanSquareDisplacement(space, integratorMin2);
>>>>>>> 1.17
        msd1.setIterator((AtomIteratorBoxDependent)aif);
    }

    
}
