/*
 *  LammpsPotentialMaster.cpp
 *  API Glue
 *
 */

#include "atom.h"
#include "atom_vec.h"
#include "library.h"
#include "force.h"
#include "pair_hybrid.h"
#include "pair_lj_cut.h"

#include "LammpsPair.h"
#include "LammpsPotentialMaster.h"
#include "LammpsSimulation.h"
#include "PotentialGroup.h"
#include "LammpsBondHarmonic.h"
#include "LammpsBondFene.h"
#include "LammpsBondFeneExpand.h"
#include "LammpsBondMorse.h"
#include "LammpsBondClass2.h"
#include "LammpsBondNonlinear.h"
#include "LammpsBondQuartic.h"
#include "LammpsPairLennardJonesCutoffCoulombCutoff.h"
#include "LammpsPairLennardJonesCutoff.h"
#include "LammpsPairLennardJonesExpand.h"
#include "LammpsPairMorse.h"
#include "LammpsPairMeam.h"
#include "LammpsPairTable.h"

namespace lammpswrappers
{

    LammpsPotentialMaster::LammpsPotentialMaster(IAPISimulation *sim) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
    }

    /*
     * addPotential()
     */
    void LammpsPotentialMaster::addPotential(IAPIPotentialAtomic *potential,
                                             IAPIAtomType *at1,
                                             IAPIAtomType *at2) {

        PotentialGroup *pg = new PotentialGroup(2);
        pg->addPotential(potential, at1->getIndex(), at2->getIndex());
        pairPotentialList.push_back(pg);
        mSim->getLammpsSim()->atom->nbondtypes = getBondTypeCount();
        mSim->getLammpsSim()->atom->nbonds = getTotalBondCount();
    }

    /*
     * addPotential()
     */
    void LammpsPotentialMaster::addPotential(IAPIPotential *potential,
                                             IAPISpecies *species) {
//printf(" LammpsPotentialMaster::addPotential() NOT implemented yet.\n"); fflush(stdout);
//check potential group nbody == 1 here.
        bondPotentialList.push_back(potential);
        speciesList.push_back(species);
    }

    /*
     * lammpsSetup()
     */
    void LammpsPotentialMaster::lammpsSetup(IAPIBox *box) {

        char command[512];

        //
        // Bonds
        //

        int bondCount = getTotalBondCount();
        int bondStyleCount = setBondStyle(box);

        int bondCtr = 1;
        int groupCtr = 0;
        char *data_bonds_arg;
        data_bonds_arg = (char *) malloc(bondCount * 21 * sizeof(char));
        strcpy(data_bonds_arg, "");
        for(int i = 0; i < bondPotentialList.size(); i++) {
            IAPISpecies *sp = speciesList.at(i);
            IAPIPotential *pot = bondPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);

                for(int j = 0; j < pg->getPotentialCount(); j++) {
                    groupCtr++;

                    IAPIMoleculeList *moleList = box->getMoleculeList(sp);
                    for(int k = 0; k < moleList->getMoleculeCount(); k++) {
                        IAPIAtomList *childList = moleList->getMolecule(k)->getChildList();
                        for(int m = 0; m < pg->getPairCount(j); m++) {
                            char line[512];
                            sprintf(line,
                                "%d %d %d %d\n",
                                bondCtr,
                                groupCtr,
                                dynamic_cast<IAPIAtom *>(childList->getAtom(pg->getAtomIndex1(j,m)))->getLeafIndex()+1,
                                dynamic_cast<IAPIAtom *>(childList->getAtom(pg->getAtomIndex2(j,m)))->getLeafIndex()+1);
                            strcat(data_bonds_arg, line);
                            bondCtr++;
                        }
                    }

                    IAPIPotential *potential = pg->getPotential(j);
                    if(typeid(*potential) == typeid(LammpsBondHarmonic)   ||
                       typeid(*potential) == typeid(LammpsBondFene)       ||
                       typeid(*potential) == typeid(LammpsBondFeneExpand) ||
                       typeid(*potential) == typeid(LammpsBondMorse)      ||
                       typeid(*potential) == typeid(LammpsBondNonlinear)  ||
                       typeid(*potential) == typeid(LammpsBondClass2)     ||
                       typeid(*potential) == typeid(LammpsBondQuartic)) {
                        LammpsPotential *p = dynamic_cast<LammpsPotential *>(potential);
                        sprintf(command,
                                "bond_coeff %d ",
                                groupCtr);
                        if(bondStyleCount > 1) {
                            strcat(command, p->getBondType());
                            strcat(command, " ");
                        }

                        for(int arg = 0; arg < p->getParameterCount(); arg++) {
                            sprintf(command,
                                    "%s %f",
                                    command,
                                    p->getParameter(arg));
                        }
printf("lammps_command : %s\n", command); fflush(stdout);
                        lammps_command(mSim->getLammpsSim(), command);
                    }
                    else {
                        printf("ERROR : Unknown potential type.\n");
                    }
                }
            }
            else {
                printf("ERROR : Unknown potential.  Expected a PotentialGroup\n"); fflush(stdout);
            }
        }
printf("command : %d  %s\n", bondCount, data_bonds_arg); fflush(stdout);
        mSim->getLammpsSim()->atom->data_bonds(bondCount, data_bonds_arg);
//printf("Back from command\n"); fflush(stdout);

        //
        // Pairs
        //

        int pairStyleCount = setPairStyle(box);
        for(int i = 0; i < pairPotentialList.size(); i++) {
            IAPIPotential *pot = pairPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                for(int j = 0; j < pg->getPotentialCount(); j++) {
                    IAPIPotential *pt = pg->getPotential(j);
                    if(typeid(*pt) == typeid(LammpsPairLennardJonesCutoffCoulombCutoff) ||
                       typeid(*pt) == typeid(LammpsPairLennardJonesCutoff)              ||
                       typeid(*pt) == typeid(LammpsPairLennardJonesExpand)              ||
                       typeid(*pt) == typeid(LammpsPairMorse)) {
                        LammpsPotential *p = dynamic_cast<LammpsPotential *>(pt);
                        sprintf(command,
                                "pair_coeff %d %d ",
                                pg->getAtomIndex1(j, 0),
                                pg->getAtomIndex2(j, 0));

                        if(pairStyleCount > 1) {
                            strcat(command, p->getBondType());
                            strcat(command, " ");
                        }

                        for(int arg = 0; arg < p->getParameterCount(); arg++) {
                            sprintf(command,
                                    "%s %f",
                                    command,
                                    p->getParameter(arg));
                        }
printf("lammps_command : %s\n", command); fflush(stdout);
                        lammps_command(mSim->getLammpsSim(), command);
                    }
                    else if(typeid(*pt) == typeid(LammpsPairMeam)) {
                        LammpsPairMeam *p = dynamic_cast<LammpsPairMeam *>(pt);
                        sprintf(command,
                                "pair_coeff * * %s %s",
                                p->getLibraryFile(),
                                p->getElements());
                        if(strcmp(p->getParameterFile(), "") != 0) {
                            sprintf(command,
                                    "%s %s",
                                    command,
                                    p->getParameterFile());
                        }
                        else {
                            sprintf(command,
                                    "%s %s",
                                    command,
                                    "NULL");
                        }
printf("lammps_command : %s\n", command); fflush(stdout);
                        lammps_command(mSim->getLammpsSim(), command);
                    }
                    else if(typeid(*pt) == typeid(LammpsPairTable)) {
                        LammpsPairTable *table = dynamic_cast<LammpsPairTable *>(pt);
                        char *lookup = table->getLookup();
                        sprintf(command,
                                "pair_coeff %d %d ",
                                pg->getAtomIndex1(j, 0),
                                pg->getAtomIndex2(j, 0));
                        if(pairStyleCount > 1) {
                            strcat(command, table->getBondType());
                            strcat(command, " ");
                        }
                        sprintf(command,
                                "%s %s",
                                command,
                                lookup);
printf("lammps_command : %s\n", command); fflush(stdout);
                        lammps_command(mSim->getLammpsSim(), command);
                    }
                    else {
                        printf("Unknown pair type potential in PotentialGroup.\n"); fflush(stdout);
                    }
                }
            }
            else {
                printf("ERROR : Unknown potential.  Expected a PotentialGroup\n"); fflush(stdout);
            }
        }

    }

    /*
     * getTotalBondCount
     */
    int LammpsPotentialMaster::getTotalBondCount() {
        int count = 0;
        for(int i = 0; i < bondPotentialList.size(); i++) {
            IAPIPotential *pot = bondPotentialList.at(i);
            IAPISpecies *species = speciesList.at(i);
            int molesInSpecies = mSim->getBox(0)->getNMolecules(species);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                for(int j = 0; j < pg->getPotentialCount(); j++) {
                    IAPIPotential *pt = pg->getPotential(j);
                    if(typeid(*pt) == typeid(LammpsBondHarmonic)   ||
                       typeid(*pt) == typeid(LammpsBondFene)       ||
                       typeid(*pt) == typeid(LammpsBondFeneExpand) ||
                       typeid(*pt) == typeid(LammpsBondMorse)      ||
                       typeid(*pt) == typeid(LammpsBondNonlinear)  ||
                       typeid(*pt) == typeid(LammpsBondClass2)     ||
                       typeid(*pt) == typeid(LammpsBondQuartic)) {
                        count += molesInSpecies * pg->getPairCount(j);
                    }
                    else if(typeid(*pt) == typeid(PotentialGroup)) {
                    }
                    else {
                        printf("WARNING : Found an unknown potential type.\n");
                    }
                }
            }
            else {
                printf("ERROR : Potential Master is expected to hold a PotentialGroup.\n");
            }
        }
        return count;
    }

    /*
     * getBondTypeCount
     */
    int LammpsPotentialMaster::getBondTypeCount() {

        int count = 0;
        for(int i = 0; i < bondPotentialList.size(); i++) {
            IAPIPotential *pot = bondPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                count += pg->getPotentialCount();
            }
            else {
                printf("ERROR : Potential Master is expected to hold a PotentialGroup.\n");
            }
        }
        return count;
    }

    /*
     * getPairTypeCount
     */
    int LammpsPotentialMaster::getPairTypeCount(IAPIBox *box) {
        int count = 0;
        for(int i = 0; i < pairPotentialList.size(); i++) {
            IAPIPotential *pot = pairPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                count += pg->getPotentialCount();
            }
            else {
                printf("ERROR : Potential Master is expected to hold a PotentialGroup.\n");
            }
        }
        return count;
    }

    /*
     * setBondStyle()
     */
    int LammpsPotentialMaster::setBondStyle(IAPIBox *box) {

        char command[512];

        int maxUniqueBondTypeCount = getBondTypeCount();
        char **bondStyleList;
        int bondStyleCount = 0;
        bondStyleList = (char **) malloc (maxUniqueBondTypeCount * sizeof(char *));

        for(int i = 0; i < bondPotentialList.size(); i++) {
            IAPIPotential *pot = bondPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                for(int j = 0; j < pg->getPotentialCount(); j++) {
                    IAPIPotential *pt = pg->getPotential(j);

                    if(typeid(*pt) == typeid(LammpsBondHarmonic)   ||
                       typeid(*pt) == typeid(LammpsBondFene)       ||
                       typeid(*pt) == typeid(LammpsBondFeneExpand) ||
                       typeid(*pt) == typeid(LammpsBondMorse)      ||
                       typeid(*pt) == typeid(LammpsBondNonlinear)  ||
                       typeid(*pt) == typeid(LammpsBondClass2)     ||
                       typeid(*pt) == typeid(LammpsBondQuartic)) {

                        char *bondStyle = dynamic_cast<LammpsPotential *>(pt)->getBondType();
                        bool inList = false;
                        for(int k = 0; k < bondStyleCount; k++) {
                            if(strcmp(bondStyleList[k], bondStyle) == 0) {
                                inList = true;
                                break;
                            }
                        }
                        if(inList == false) {
                            bondStyleList[bondStyleCount] = (char *) malloc ((strlen(bondStyle) + 1) * sizeof(char));
                            strcpy(bondStyleList[bondStyleCount], bondStyle);
                            bondStyleCount++;
                        }
                    }
                }
            }
        }

        if(bondStyleCount == 1) {
            sprintf(command,
                    "bond_style %s",
                    bondStyleList[0]);
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSim->getLammpsSim(), command);
        }
        else if(bondStyleCount > 1) {
            sprintf(command,
                    "bond_style hybrid ");
            for(int i = 0; i < bondStyleCount; i++) {
                strcat(command, bondStyleList[i]);
                strcat(command, " ");
            }
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSim->getLammpsSim(), command);
        }

        // Free memory
        for(int i = 0; i < bondStyleCount; i++) {
            free(bondStyleList[i]);
        }
        free(bondStyleList);

        return bondStyleCount;
    }


    /*
     * setPairStyle()
     */
    int LammpsPotentialMaster::setPairStyle(IAPIBox *box) {

        char command[512];

        int maxUniquePairTypeCount = getPairTypeCount(box);
        char **pairStyleList;
        char **cutoffStyleList;
        int pairStyleCount = 0;
        pairStyleList = (char **) malloc (maxUniquePairTypeCount * sizeof(char *));
        cutoffStyleList = (char **) malloc (maxUniquePairTypeCount * sizeof(char *));

        for(int i = 0; i < pairPotentialList.size(); i++) {
            IAPIPotential *pot = pairPotentialList.at(i);
            if(typeid(*pot) == typeid(PotentialGroup)) {
                PotentialGroup *pg = dynamic_cast<PotentialGroup *>(pot);
                for(int j = 0; j < pg->getPotentialCount(); j++) {
                    IAPIPotential *pt = pg->getPotential(j);
                    if(typeid(*pt) == typeid(LammpsPairLennardJonesCutoffCoulombCutoff) ||
                       typeid(*pt) == typeid(LammpsPairLennardJonesCutoff)              ||
                       typeid(*pt) == typeid(LammpsPairLennardJonesExpand)              ||
                       typeid(*pt) == typeid(LammpsPairMeam)                            ||
                       typeid(*pt) == typeid(LammpsPairTable)                           ||
                       typeid(*pt) == typeid(LammpsPairMorse)) {

                        char *pairStyle = dynamic_cast<LammpsPotential *>(pt)->getBondType();
                        bool inList = false;
                        for(int k = 0; k < pairStyleCount; k++) {
                            if(strcmp(pairStyleList[k], pairStyle) == 0) {
                                inList = true;
                                break;
                            }
                        }
                        if(inList == false) {
                            pairStyleList[pairStyleCount] = (char *) malloc ((strlen(pairStyle) + 1) * sizeof(char));
                            strcpy(pairStyleList[pairStyleCount], pairStyle);
                            char *cutoff = dynamic_cast<LammpsPotential *>(pt)->getConstructionString();
                            cutoffStyleList[pairStyleCount] = (char *) malloc ((strlen(cutoff) + 1) * sizeof(char));
                            strcpy(cutoffStyleList[pairStyleCount], cutoff);
                            pairStyleCount++;
                        }
                    }
                }
            }
        }

        if(pairStyleCount == 1) {
            sprintf(command,
                    "pair_style %s %s",
                    pairStyleList[0],
                    cutoffStyleList[0]);
        }
        else {
            sprintf(command,
                    "pair_style hybrid ");
            for(int i = 0; i < pairStyleCount; i++) {
                strcat(command, pairStyleList[i]);
                strcat(command, " ");
                strcat(command, cutoffStyleList[i]);
                strcat(command, " ");
            }
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

        // Free memory
        for(int i = 0; i < pairStyleCount; i++) {
            free(pairStyleList[i]);
            free(cutoffStyleList[i]);
        }
        free(pairStyleList);
        free(cutoffStyleList);

        return pairStyleCount;
    }
}

