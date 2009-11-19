package etomica.lammpslib;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import etomica.action.BoxImposePbc;
import etomica.action.WriteConfiguration;
import etomica.action.XYZWriter;
<<<<<<< IntegratorKMC.java
import etomica.api.IAtomPositioned;
import etomica.api.IBox;
import etomica.api.IMolecule;
import etomica.api.IMoleculeList;
=======
import etomica.api.IMoleculeList;
>>>>>>> 1.15
import etomica.api.IPotentialMaster;
import etomica.api.IRandom;
import etomica.api.ISimulation;
import etomica.api.ISpecies;
<<<<<<< IntegratorKMC.java
import etomica.api.IVectorMutable;
import etomica.atom.MoleculeArrayList;
import etomica.box.Box;
=======
import etomica.api.IVectorMutable;
>>>>>>> 1.15
import etomica.config.ConfigurationFile;
import etomica.dimer.CalcVibrationalModes;
import etomica.dimer.IntegratorDimerMin;
import etomica.dimer.IntegratorDimerRT;
import etomica.exception.ConfigurationOverlapException;
import etomica.graphics.SimulationGraphic;
import etomica.integrator.IntegratorBox;
import etomica.space.ISpace;

public class IntegratorKMC extends IntegratorBox{

    private static final long serialVersionUID = 1L;
    IntegratorDimerRT integratorDimer;
    IntegratorDimerMin integratorMin;
    IPotentialMaster potentialMaster;
    double temperature;
    private final ISpace space;
    IRandom random;
    ISimulation sim;
    ISpecies [] species;
    IVectorMutable [] minPosition, currentSaddle, previousSaddle;
    double[] saddleVib;
    double massSec;
    double[] saddleEnergies;
    double[] rates;
    double tau;
    double msd;
    double beta;
    double minEnergy;
    double minVib;
    boolean search;
    int goodSearch;
    boolean diffMin1, diffMin2;
    int stepCounter;
    int searchlimit;
    long lammps;
    SimulationGraphic graphic;
    XYZWriter xyzfile;
    BoxImposePbc imposePbc;
    CalcVibrationalModes vib;
    IBox boxVib;
    
    public IntegratorKMC(ISimulation _sim, long library, IPotentialMaster _potentialMaster, double _temperature, IRandom _random, ISpecies [] _species, ISpace _space){
        super(_potentialMaster, _temperature);
        this.potentialMaster = _potentialMaster;
        this.temperature = _temperature;
        this.space = _space;
        this.random = _random;
        this.sim = _sim;
        this.lammps = library;
        this.species = _species;
        
        searchlimit = 5;
        tau = 0;
        
                
        // TODO Auto-generated constructor stub
    }
 
    protected void doStepInternal(){
        //Dimer Searches from minimum
        goodSearch = 0;
        search = true;
        while(search){
            loadConfiguration(stepCounter+"", box);
            randomizePositions();
            try {
                System.out.println("Initializing dimer.");
                integratorDimer.reset();
            } catch (ConfigurationOverlapException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            integratorDimer.setFileName("s_"+goodSearch);
            System.out.println("Searching...");
            for(int j=0;j<1000;j++){
                integratorDimer.doStep();
                if(integratorDimer.saddleFound){
                    if(checkUniqueSaddle()){
                        System.out.println("Good search "+goodSearch+", adding saddle data.");
                        saddleEnergies[goodSearch] = integratorDimer.saddleEnergy;
                        saddleVib[goodSearch] = integratorDimer.vib.getProductOfFrequencies();
                        goodSearch++;
                    } 
                    break;
                }    
            }
            if(goodSearch>searchlimit-1){search = false;}
        }
        
        calcRates();
<<<<<<< IntegratorKMC.java
        int rateNum;
        while(true){
            rateNum = chooseRate();
            if(rateNum==99999){
                break;
            }
            
            System.out.println("Rate "+rateNum+" is chosen.");
            System.out.println("Step "+(stepCounter)+": tau is "+calcTau());
            
            //FIRST MINIMUM SEARCH
            findMinima(rateNum, true, "A");
            diffMin1 = checkMin();
            //first search returned new minimum.
            if(diffMin1==true){
                getMinimumData();
            }
=======
        int rateNum = chooseRate();
        System.out.println("Rate "+rateNum+" is chosen.");
        System.out.println("Tau is "+tau);
        //Minimum Search with random transition
        integratorMin1.setFileName("s_"+rateNum);
        try {
            integratorMin1.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        writeConfiguration(stepCounter+"_saddle");
        xyzfile.actionPerformed();
        
        stepCounter++;
>>>>>>> 1.15

            //SECOND MINIMUM SEARCH
            String xyzNombre;
            if(diffMin1==true){
                xyzNombre = "B";
                findMinima(rateNum, false, xyzNombre);
            }
            else{
                xyzNombre = "A-fwd";
                findMinima(rateNum, false, xyzNombre); 
            }
            diffMin2 = checkMin();
            
            // good - first search returned original minimum, second was new.
            if(diffMin1==false && diffMin2==true){
                System.out.println("Good minima.");
                getMinimumData();
                break;
            }
<<<<<<< IntegratorKMC.java
            //good - first search returned new, second was original.
            if(diffMin1==true && diffMin2==false){
                System.out.println("Good minima.");
                break;
=======
        }
        if(checkMin()){
            minEnergy = integratorMin1.e0;
            minVib = integratorMin1.vib.getProductOfFrequencies();
            writeConfiguration(stepCounter+"");
            setInitialStateConditions(minEnergy, minVib);
            System.out.println("Good minimum found.");
        }else{
            integratorMin2.setFileName("s_"+rateNum);
            try {
                integratorMin2.reset();
            } catch (ConfigurationOverlapException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
>>>>>>> 1.15
            }
            
            //malo - both minimum are new or same minimum, choose another saddle.
            System.out.println("Bad mechanism #"+rateNum+".  Choosing another...");
            rates[rateNum] = 0.0;
        }
        if(rateNum==99999){return;}

        clearRatesandEnergies();
        stepCounter++;
        
    }
    
    public void setup(){
        search = true;
        saddleVib = new double[searchlimit];
        saddleEnergies = new double[searchlimit];
        massSec = Math.sqrt(species[0].getAtomType(0).getMass()) * 0.000000000001;
        rates = new double[searchlimit];
        beta = 1.0/(temperature);
        stepCounter = 0;     
        imposePbc = new BoxImposePbc(box, space);
<<<<<<< IntegratorKMC.java
        minPosition = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        currentSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        previousSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
=======
        currentSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
        previousSaddle = new IVectorMutable[box.getMoleculeList().getMoleculeCount()];
>>>>>>> 1.15
        for(int i=0; i<currentSaddle.length; i++){
            currentSaddle[i] = space.makeVector();
            previousSaddle[i] = space.makeVector();
            minPosition[i] = space.makeVector();
        }
        
        createIntegrators();
        
        try {
            integratorDimer.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        vib = new CalcVibrationalModes(lammps);

        boxVib = new Box(box.getBoundary(), space);
        sim.addBox(boxVib);
        for(int i=0; i<sim.getSpeciesManager().getSpeciesCount(); i++){
            boxVib.setNMolecules(sim.getSpeciesManager().getSpecies(i),box.getNMolecules(sim.getSpeciesManager().getSpecies(i)));
        }
        
        try {
            FileReader fileReaderInit = new FileReader("0_ev");
            BufferedReader buffReaderInit = new BufferedReader(fileReaderInit);
            minEnergy = Double.parseDouble(buffReaderInit.readLine());
            minVib = Double.parseDouble(buffReaderInit.readLine());
        }
        catch(IOException e) {}
        
    }

<<<<<<< IntegratorKMC.java
      
    public void setSearchLimit(int limit){
        searchlimit = limit;
    }
    
    public void setInitialStateConditions(){
=======
    public void setInitialStateConditions(double energy, double vibFreq){
        minEnergy = energy;
        minVib = vibFreq;
        
        IMoleculeList loopSet2 = box.getMoleculeList();
        minPosition = new IVectorMutable[loopSet2.getMoleculeCount()];
>>>>>>> 1.15
        for(int i=0; i<minPosition.length; i++){
            minPosition[i].E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
        }  
    }
    
    public void findMinima(int mechanism, boolean dir, String xyzName){
        integratorMin.setFileName("s_"+mechanism);
        try {
            integratorMin.reset();
        } catch (ConfigurationOverlapException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        writeConfiguration(stepCounter+"_s");      
        integratorMin.setDirection(dir);
        for(int j=0;j<2000;j++){
            integratorMin.doStep();
            if(integratorMin.minFound){
                break;
            }
        }
    }
    
    public void getMinimumData(){
        integratorMin.quitSearch();
        loadConfiguration(integratorMin.writer.getConfName(),boxVib);
        refreshSpecies(boxVib);
        calcVibrationalModes();
        minEnergy = integratorMin.e0;
        minVib = vib.getProductOfFrequencies();
        writeConfiguration((stepCounter+1)+"");
        System.out.println("Good minimum found.");
    }
    
    public void refreshSpecies(IBox boxA){
        IMoleculeList loopSet = boxA.getMoleculeList(species[0]);
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            IMolecule newMolecule = sim.getSpeciesManager().getSpecies(0).makeMolecule();
            boxA.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
        }
        boxA.setNMolecules(species[0], 0);
        
        IVectorMutable vect = space.makeVector();
        for(int i=0; i<boxA.getMoleculeList().getMoleculeCount(); i++){
            vect.E(((IAtomPositioned)boxA.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(vect.x(0)>7.6){
                setMovableAtoms(1.0, vect, boxA);
            }
        }
        
<<<<<<< IntegratorKMC.java
=======
        for(int i=0; i<loopSet2.getMoleculeCount(); i++){
            minPosition[i].E(loopSet2.getMolecule(i).getChildList().getAtom(0).getPosition());
        }  
>>>>>>> 1.15
    }
    
    public void setMovableAtoms(double distance, IVectorMutable center, IBox boxA){
        //distance = distance*distance;
        IVectorMutable rij = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
        IMoleculeList loopSet = boxA.getMoleculeList();
        for (int i=0; i<loopSet.getMoleculeCount(); i++){
            if(loopSet.getMolecule(i).getType()==species[0]){
                continue;
            }
            rij.E(((IAtomPositioned)loopSet.getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(rij.x(0) > 2.0){
                boxA.getBoundary().nearestImage(rij);
                rij.ME(center);
                if(rij.squared() < distance){   
                    movableList.add(loopSet.getMolecule(i));
                }
            }
        }
        for (int i=0; i<movableList.getMoleculeCount(); i++){
            IMolecule newMolecule = species[0].makeMolecule();
            boxA.addMolecule(newMolecule);
            ((IAtomPositioned)newMolecule.getChildList().getAtom(0)).getPosition().E(((IAtomPositioned)movableList.getMolecule(i).getChildList().getAtom(0)).getPosition());
            boxA.removeMolecule(movableList.getMolecule(i));
        }
    }
    
    public void randomizePositions(){
        IVectorMutable workVector = space.makeVector();
        IMoleculeList loopSet3 = box.getMoleculeList(species[0]);
        IVectorMutable [] currentPos = new IVectorMutable [loopSet3.getMoleculeCount()];
        double offset = 0;
        for(int i=0; i<currentPos.length; i++){
            currentPos[i] = space.makeVector();
<<<<<<< IntegratorKMC.java
            currentPos[i] = (((IAtomPositioned)loopSet3.getMolecule(i).getChildList().getAtom(0)).getPosition());
=======
            currentPos[i] = (loopSet3.getMolecule(i).getChildList().getAtom(0).getPosition());
>>>>>>> 1.15
            for(int j=0; j<3; j++){
                offset = random.nextGaussian()/10.0;
                if(Math.abs(offset)>0.1){offset=0.1;}
                workVector.setX(j,offset);
            }
            currentPos[i].PE(workVector);
        }
    }
        
    public void calcRates(){
        double rateSum = 0;
        minEnergy = minEnergy*1.60217646E-19;
        for(int i=0; i<rates.length; i++){
            if(saddleEnergies[i]==0){continue;}
            saddleEnergies[i] = saddleEnergies[i]*1.60217646E-19;
            rates[i] = ( Math.exp(minVib - saddleVib[i]) / massSec) * Math.exp( -(saddleEnergies[i] - minEnergy)*beta);
            rateSum += rates[i];
        }

    }
    
    public double calcTau(){
        double rateSum = 0;
        for(int i=0; i<rates.length; i++){
            rateSum += rates[i];
        }
        return -Math.log(random.nextDouble())/rateSum;
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
                    System.out.println("Rate "+l+": "+rates[l]+", v: "+Math.exp(minVib - saddleVib[l]) / massSec);
                }
                System.out.println("Sum:    "+sum);
                System.out.println("-------------------------");
                System.out.println(rand*sum+" <= "+sumgrt);
                break;
            }
        }
        return rt;
    }
    
    private boolean checkUniqueSaddle(){    
<<<<<<< IntegratorKMC.java
        double positionDiff = 0;
        //check against minimum (surface)
        for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
            currentSaddle[j].E(((IAtomPositioned)box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
            currentSaddle[j].ME(minPosition[j]);
            positionDiff += currentSaddle[j].squared();
        }
        if(positionDiff < 1.0){
            System.out.println("Position difference from minimum: "+positionDiff);
            System.out.println("Too similar to minimum.");
            return false;
        }
        
        System.out.println("Position difference from minimum: "+positionDiff);
            	
    	for(int p=0; p<box.getMoleculeList().getMoleculeCount(); p++){
            currentSaddle[p].E(((IAtomPositioned)box.getMoleculeList().getMolecule(p).getChildList().getAtom(0)).getPosition());
=======
        for(int p=0; p<box.getMoleculeList().getMoleculeCount(); p++){
            currentSaddle[p].E(box.getMoleculeList().getMolecule(p).getChildList().getAtom(0).getPosition());
>>>>>>> 1.15
        }
        for(int i=0; i<goodSearch; i++){
<<<<<<< IntegratorKMC.java
            positionDiff = 0;
            loadConfiguration("s_"+i+"_saddle", box);
            for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
                previousSaddle[j].E(((IAtomPositioned)box.getMoleculeList().getMolecule(j).getChildList().getAtom(0)).getPosition());
=======
            double positionDiff = 0;
            loadConfiguration("s_"+i+"_saddle");
            for(int j=0; j<box.getMoleculeList().getMoleculeCount(); j++){
                previousSaddle[j].E(box.getMoleculeList().getMolecule(j).getChildList().getAtom(0).getPosition());
>>>>>>> 1.15
                previousSaddle[j].ME(currentSaddle[j]);
                positionDiff += previousSaddle[j].squared();
            }
            if(positionDiff < 0.5){
                System.out.println("Duplicate saddle found.");
                return false;
            }
        }
        System.out.println("Unique saddle found.");
        return true;  
    }
    
    private double truncate(double numA, int digits){
        digits = (int)Math.pow(10,digits);
        numA = (long)(digits*numA);
        numA = (double)(numA/digits);
        return numA;
    }
    
    public boolean checkMin(){
        IVectorMutable workVector = space.makeVector();
        double positionDiff=0;
<<<<<<< IntegratorKMC.java
        for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
            workVector.E(((IAtomPositioned)box.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            workVector.ME(minPosition[i]);
=======
        for(int i=0; i<box.getMoleculeList().getMoleculeCount(); i++){
            workVector.Ev1Mv2(minPosition[i],box.getMoleculeList().getMolecule(i).getChildList().getAtom(0).getPosition());
>>>>>>> 1.15
            positionDiff += workVector.squared();
        }
        System.out.println("mincheck pos diff:"+positionDiff);
        if(positionDiff > 0.5){return true;}
        return false;
    }
        
    public void writeConfiguration(String file){
        WriteConfiguration writer = new WriteConfiguration(space);
        writer.setBox(box);
        writer.setConfName(file);
        writer.setDoApplyPBC(false);
        writer.actionPerformed();
    }
    
    public void loadConfiguration(String file, IBox boxA){
        ConfigurationFile config = new ConfigurationFile(file);
        config.initializeCoordinates(boxA); 
    }
    
    public void clearRatesandEnergies(){
    	new File("log.lammps").delete();
        for(int i=0; i<rates.length; i++){
            rates[i] = 0.0;
            saddleEnergies[i] = 0.0;
            saddleVib[i] = 0.0;
        }
    }
    
    public void calcVibrationalModes(){
    	IVectorMutable vect = space.makeVector();
        MoleculeArrayList movableList = new MoleculeArrayList();
    	for(int i=0; i<boxVib.getMoleculeList().getMoleculeCount(); i++){
            vect.E(((IAtomPositioned)boxVib.getMoleculeList().getMolecule(i).getChildList().getAtom(0)).getPosition());
            if(vect.x(0)>3.0){
                movableList.add(boxVib.getMoleculeList().getMolecule(i));
            }
        }
    	
        vib.setup(boxVib, potentialMaster, movableList, space);
        vib.actionPerformed();
    }

    public void createIntegrators(){
        integratorMin = new IntegratorDimerMin(sim, lammps, potentialMaster, species, space);
        integratorDimer = new IntegratorDimerRT(sim, lammps, potentialMaster, species, space);
        
        integratorMin.setBox(box);
        integratorDimer.setBox(box);
        integratorDimer.setRotNum(2);
        integratorDimer.setOrtho(false, false);
                
        xyzfile = new XYZWriter(box);
        xyzfile.setIsAppend(true);
        xyzfile.setFileName("kmc-test.xyz");
    }
    

}