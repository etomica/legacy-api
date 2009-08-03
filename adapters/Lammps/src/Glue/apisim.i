/* File: apisim.i */
%module test
%{
#include "lammps.h"
#include "library.h"
#include "atom.h"
#include "group.h"
#include "IAPIFunction.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomList.h"
#include "IAPIMoleculeList.h"
#include "IAPIAtomType.h"
#include "IAPIAtomTypeSphere.h"
#include "IAPIBoundaryEvent.h"
#include "IAPIBoundaryListener.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPIBoundary.h"
#include "IAPIBoxEvent.h"
#include "IAPIBoxAtomEvent.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "IAPIBoxIndexEvent.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPIBoxMoleculeIndexEvent.h"
#include "IAPIBoxListener.h"
#include "IAPIBoxEventManager.h"
#include "IAPIBox.h"
#include "IAPIIntegratorEvent.h"
#include "IAPIIntegratorListener.h"
#include "IAPIIntegratorEventManager.h"
#include "IAPIIntegrator.h"
#include "IAPIMolecule.h"
#include "IAPIPotential.h"
#include "IAPIPotentialAtomic.h"
#include "IAPIPotentialMaster.h"
#include "IAPIRandom.h"
#include "IAPISpecies.h"
#include "IAPISpeciesManager.h"
#include "IAPISimulationEvent.h"
#include "IAPISimulationAtomTypeEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationListener.h"
#include "IAPISimulationEventManager.h"
#include "IAPISimulation.h"
#include "LammpsInterfaceConformation.h"
#include "LammpsInterfaceAtomPositionDefinition.h"
#include "LammpsTemperatureRescale.h"
#include "LammpsMomentum.h"
#include "LammpsNPH.h"
#include "LammpsNPT.h"
#include "LammpsNPTAsphere.h"
#include "LammpsNPTSphere.h"
#include "LammpsNVE.h"
#include "LammpsNVEAsphere.h"
#include "LammpsNVESphere.h"
#include "LammpsNVELimit.h"
#include "LammpsNVENoforce.h"
#include "LammpsNVT.h"
#include "LammpsNVTAsphere.h"
#include "LammpsNVTSphere.h"
#include "LammpsNVTSllod.h"
#include "LammpsAtom.h"
#include "LammpsBoundary.h"
#include "LammpsBox.h"
#include "LammpsBoxEventManager.h"
#include "LammpsMolecule.h"
#include "LammpsSpeciesManager.h"
#include "LammpsSimulationEvent.h"
#include "LammpsSimulationBoxEvent.h"
#include "LammpsSimulationSpeciesEvent.h"
#include "LammpsSimulationSpeciesIndexEvent.h"
#include "LammpsSimulationIndexEvent.h"
#include "LammpsSimulationAtomTypeEvent.h"
#include "LammpsSimulationAtomTypeIndexEvent.h"
#include "LammpsSimulationListenerNative.h"
#include "LammpsSimulationEventManager.h"
#include "LammpsSimulation.h"
#include "LammpsAtomList.h"
#include "LammpsMoleculeList.h"
#include "LammpsVector.h"
#include "LammpsVector2D.h"
#include "LammpsVector3D.h"
#include "LammpsAtomType.h"
#include "LammpsAtomTypeSphere.h"
#include "LammpsConformation.h"
#include "LammpsNativeConformation.h"
#include "LammpsSpecies.h"
#include "LammpsSpeciesSpheres.h"
#include "LammpsBoundaryPeriodic.h"
#include "LammpsBoundaryFixed.h"
#include "LammpsBoundaryShrink.h"
#include "LammpsBoundaryShrinkMin.h"
#include "LammpsBoundaryCustom.h"
#include "LammpsBoundaryDeformable.h"
#include "LammpsAtomPositionDefinition.h"
#include "LammpsNativeAtomPositionDefinition.h"
#include "LammpsRandom.h"
#include "LammpsIntegratorEventManager.h"
#include "LammpsIntegratorListenerNative.h"
#include "LammpsIntegrator.h"
#include "LammpsIntegratorRespa.h"
#include "LammpsIntegratorVerlet.h"
#include "PotentialGroup.h"
#include "LammpsPotential.h"
#include "LammpsPair.h"
#include "LammpsBondHarmonic.h"
#include "LammpsBondFene.h"
#include "LammpsBondFeneExpand.h"
#include "LammpsBondMorse.h"
#include "LammpsBondClass2.h"
#include "LammpsBondNonlinear.h"
#include "LammpsBondQuartic.h"
#include "LammpsPairLennardJonesCutoff.h"
#include "LammpsPairLennardJonesCutoffCoulombCutoff.h"
#include "LammpsPairLennardJonesExpand.h"
#include "LammpsPairMorse.h"
#include "LammpsPairDPD.h"
#include "LammpsPairColloid.h"
#include "LammpsPairMeam.h"
#include "LammpsPairBuck.h"
#include "LammpsPairTable.h"
#include "LammpsPotentialMaster.h"
#include "LammpsNeighborList.h"
#include "LammpsNeighborListBin.h"
#include "LammpsNeighborListMulti.h"
#include "LammpsNeighborListNsq.h"
#include "LammpsLattice.h"
#include "LammpsLatticeHex.h"
#include "LammpsLatticeSQ.h"
#include "LammpsLatticeSQ2.h"
#include "LammpsLatticeSC.h"
#include "LammpsLatticeBCC.h"
#include "LammpsLatticeFCC.h"
#include "LammpsLatticeHCP.h"
#include "LammpsLatticeDiamond.h"
#include "LammpsRegion.h"
#include "LammpsRegionBlock.h"
#include "LammpsRegionPrism.h"
#include "LammpsRegionSphere.h"

using namespace lammpswrappers;
using namespace molesimAPI;
%}

%include "std_string.i"
%include "arrays_java.i"
/*%javaconst(1)*/

%include "IAPIFunction.h"
%include "IAPIVector.h"
%include "IAPIVectorMutable.h"
%include "IAPIAtom.h"
%include "IAPIAtomPositioned.h"
%include "IAPIAtomList.h"
%include "IAPIMoleculeList.h"
%include "IAPIAtomType.h"
%include "IAPIAtomTypeSphere.h"
%include "IAPIBoundaryEvent.h"
%include "IAPIBoundaryListener.h"
%include "IAPIBoundaryEventManager.h"
%include "IAPIBoundary.h"
%include "IAPIBoxAtomEvent.h"
%include "IAPIBoxEvent.h"
%include "IAPIBoxAtomIndexEvent.h"
%include "IAPIBoxIndexEvent.h"
%include "IAPIBoxMoleculeEvent.h"
%include "IAPIBoxMoleculeCountEvent.h"
%include "IAPIBoxMoleculeIndexEvent.h"
%include "IAPIBoxListener.h"
%include "IAPIBoxEventManager.h"
%include "IAPIBox.h"
%include "IAPIIntegratorEvent.h"
%include "IAPIIntegratorListener.h"
%include "IAPIIntegratorEventManager.h"
%include "IAPIIntegrator.h"
%include "IAPIMolecule.h"
%include "IAPIPotential.h"
%include "IAPIPotentialAtomic.h"
%include "IAPIPotentialMaster.h"
%include "IAPIRandom.h"
%include "IAPISpecies.h"
%include "IAPISpeciesManager.h"
%include "IAPISimulationEvent.h"
%include "IAPISimulationAtomTypeEvent.h"
%include "IAPISimulationSpeciesEvent.h"
%include "IAPISimulationAtomTypeIndexEvent.h"
%include "IAPISimulationSpeciesIndexEvent.h"
%include "IAPISimulationBoxEvent.h"
%include "IAPISimulationIndexEvent.h"
%include "IAPISimulationListener.h"
%include "IAPISimulationEventManager.h"
%include "IAPISimulation.h"
%include "LammpsInterfaceConformation.h"
%include "LammpsInterfaceAtomPositionDefinition.h"
%include "LammpsSimulationEvent.h"
%include "LammpsSimulationBoxEvent.h"
%include "LammpsSimulationSpeciesEvent.h"
%include "LammpsSimulationSpeciesIndexEvent.h"
%include "LammpsSimulationIndexEvent.h"
%include "LammpsSimulationAtomTypeEvent.h"
%include "LammpsSimulationAtomTypeIndexEvent.h"
%include "LammpsSimulationListenerNative.h"
%include "LammpsSimulationEventManager.h"
%include "LammpsSimulation.h"
%include "LammpsTemperatureRescale.h"
%include "LammpsMomentum.h"
%include "LammpsNPH.h"
%include "LammpsNPT.h"
%include "LammpsNPTAsphere.h"
%include "LammpsNPTSphere.h"
%include "LammpsNVE.h"
%include "LammpsNVEAsphere.h"
%include "LammpsNVESphere.h"
%include "LammpsNVELimit.h"
%include "LammpsNVENoforce.h"
%include "LammpsNVT.h"
%include "LammpsNVTAsphere.h"
%include "LammpsNVTSphere.h"
%include "LammpsNVTSllod.h"
%include "LammpsAtom.h"
%include "LammpsBoundary.h"
%include "LammpsBox.h"
%include "LammpsBoxEventManager.h"
%include "LammpsMolecule.h"
%include "LammpsSpeciesManager.h"
%include "LammpsAtomList.h"
%include "LammpsMoleculeList.h"
%include "LammpsVector.h"
%include "LammpsVector2D.h"
%include "LammpsVector3D.h"
%include "LammpsAtomType.h"
%include "LammpsAtomTypeSphere.h"
%include "LammpsConformation.h"
%include "LammpsNativeConformation.h"
%include "LammpsSpecies.h"
%include "LammpsSpeciesSpheres.h"
%include "LammpsBoundaryPeriodic.h"
%include "LammpsBoundaryFixed.h"
%include "LammpsBoundaryShrink.h"
%include "LammpsBoundaryShrinkMin.h"
%include "LammpsBoundaryCustom.h"
%include "LammpsBoundaryDeformable.h"
%include "LammpsAtomPositionDefinition.h"
%include "LammpsNativeAtomPositionDefinition.h"
%include "LammpsRandom.h"
%include "LammpsIntegratorEventManager.h"
%include "LammpsIntegratorListenerNative.h"
%include "LammpsIntegrator.h"
%include "LammpsIntegratorRespa.h"
%include "LammpsIntegratorVerlet.h"
%include "PotentialGroup.h"
%include "LammpsPotential.h"
%include "LammpsPair.h"
%include "LammpsBondHarmonic.h"
%include "LammpsBondFene.h"
%include "LammpsBondFeneExpand.h"
%include "LammpsBondMorse.h"
%include "LammpsBondClass2.h"
%include "LammpsBondNonlinear.h"
%include "LammpsBondQuartic.h"
%include "LammpsPairLennardJonesCutoff.h"
%include "LammpsPairLennardJonesCutoffCoulombCutoff.h"
%include "LammpsPairLennardJonesExpand.h"
%include "LammpsPairMorse.h"
%include "LammpsPairDPD.h"
%include "LammpsPairColloid.h"
%include "LammpsPairMeam.h"
%include "LammpsPairBuck.h"
%include "LammpsPairTable.h"
%include "LammpsPotentialMaster.h"
%include "LammpsNeighborList.h"
%include "LammpsNeighborListBin.h"
%include "LammpsNeighborListMulti.h"
%include "LammpsNeighborListNsq.h"
%include "LammpsLattice.h"
%include "LammpsLatticeHex.h"
%include "LammpsLatticeSQ.h"
%include "LammpsLatticeSQ2.h"
%include "LammpsLatticeSC.h"
%include "LammpsLatticeBCC.h"
%include "LammpsLatticeFCC.h"
%include "LammpsLatticeHCP.h"
%include "LammpsLatticeDiamond.h"
%include "LammpsRegion.h"
%include "LammpsRegionBlock.h"
%include "LammpsRegionPrism.h"
%include "LammpsRegionSphere.h"

