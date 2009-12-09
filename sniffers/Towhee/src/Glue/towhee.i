/* File: towhee.i */
%module towhee
%{
#include <typeinfo>
#include "IAPIFunction.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPIMoleculeList.h"
#include "IAPIElement.h"
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
#include "TowheeConformationNative.h"
#include "TowheeMolecule.h"
#include "TowheeMoleculeList.h"
#include "TowheeAtomList.h"
#include "TowheeAtomType.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeAtom.h"
#include "TowheeSpecies.h"
#include "TowheeSpeciesSpheresMono.h"
#include "TowheeSpeciesSpheresHetero.h"
#include "TowheeSpeciesManager.h"
#include "TowheeBoundaryEventManager.h"
#include "TowheeBoundary.h"
#include "TowheeBoundaryPeriodic.h"
#include "TowheeBoundaryRectangularPeriodic.h"
#include "TowheeBoxEvent.h"
#include "TowheeBoxIndexEvent.h"
#include "TowheeBoxAtomEvent.h"
#include "TowheeBoxAtomIndexEvent.h"
#include "TowheeBoxMoleculeEvent.h"
#include "TowheeBoxMoleculeCountEvent.h"
#include "TowheeBoxMoleculeIndexEvent.h"
#include "TowheeBoxListenerNative.h"
#include "TowheeBoxEventManager.h"
#include "TowheeBox.h"
#include "TowheeIntegratorListenerNative.h"
#include "TowheeIntegratorEventManager.h"
#include "TowheeIntegrator.h"
#include "TowheeInterfaceAtomPositionDefinition.h"
#include "TowheeNativeAtomPositionDefinition.h"
#include "TowheeInterfaceConformation.h"
#include "TowheeMonatomicMolecule.h"
#include "TowheeRandom.h"
#include "TowheeSimulationEvent.h"
#include "TowheeSimulationAtomTypeEvent.h"
#include "TowheeSimulationAtomTypeIndexEvent.h"
#include "TowheeSimulationBoxEvent.h"
#include "TowheeSimulationIndexEvent.h"
#include "TowheeSimulationSpeciesEvent.h"
#include "TowheeSimulationSpeciesIndexEvent.h"
#include "TowheeSimulationListenerNative.h"
#include "TowheeSimulationEventManager.h"
#include "TowheeSimulation.h"
#include "TowheeSimulationSniffer.h"
#include "TowheeSpace.h"
#include "TowheeVector.h"
#include "TowheeVector2D.h"
#include "TowheeVector3D.h"
#include "TowheeVector3DAtom.h"

using namespace towheesnifferwrappers;
using namespace molesimAPI;
%}

%include "std_string.i"
%include "arrays_java.i"

%include "IAPIFunction.h"
%include "IAPIVector.h"
%include "IAPIVectorMutable.h"
%include "IAPIAtom.h"
%include "IAPIAtomList.h"
%include "IAPIMoleculeList.h"
%include "IAPIElement.h"
%include "IAPIAtomType.h"
%include "IAPIAtomTypeSphere.h"
%include "IAPIBoundaryEvent.h"
%include "IAPIBoundaryListener.h"
%include "IAPIBoundaryEventManager.h"
%include "IAPIBoundary.h"
%include "IAPIBoxEvent.h"
%include "IAPIBoxAtomEvent.h"
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
%include "TowheeConformationNative.h"
%include "TowheeMolecule.h"
%include "TowheeMoleculeList.h"
%include "TowheeAtomList.h"
%include "TowheeAtomType.h"
%include "TowheeAtomTypeSphere.h"
%include "TowheeAtom.h"
%include "TowheeSpecies.h"
%include "TowheeSpeciesSpheresMono.h"
%include "TowheeSpeciesSpheresHetero.h"
%include "TowheeSpeciesManager.h"
%include "TowheeBoundaryEventManager.h"
%include "TowheeBoundary.h"
%include "TowheeBoundaryPeriodic.h"
%include "TowheeBoundaryRectangularPeriodic.h"
%include "TowheeBoxEvent.h"
%include "TowheeBoxIndexEvent.h"
%include "TowheeBoxAtomEvent.h"
%include "TowheeBoxAtomIndexEvent.h"
%include "TowheeBoxMoleculeEvent.h"
%include "TowheeBoxMoleculeCountEvent.h"
%include "TowheeBoxMoleculeIndexEvent.h"
%include "TowheeBoxListenerNative.h"
%include "TowheeBoxEventManager.h"
%include "TowheeBox.h"
%include "TowheeIntegratorListenerNative.h"
%include "TowheeIntegratorEventManager.h"
%include "TowheeIntegrator.h"
%include "TowheeInterfaceAtomPositionDefinition.h"
%include "TowheeNativeAtomPositionDefinition.h"
%include "TowheeInterfaceConformation.h"
%include "TowheeMonatomicMolecule.h"
%include "TowheeRandom.h"
%include "TowheeSimulationEvent.h"
%include "TowheeSimulationAtomTypeEvent.h"
%include "TowheeSimulationAtomTypeIndexEvent.h"
%include "TowheeSimulationBoxEvent.h"
%include "TowheeSimulationIndexEvent.h"
%include "TowheeSimulationSpeciesEvent.h"
%include "TowheeSimulationSpeciesIndexEvent.h"
%include "TowheeSimulationListenerNative.h"
%include "TowheeSimulationEventManager.h"
%include "TowheeSimulation.h"
%include "TowheeSimulationSniffer.h"
%include "TowheeSpace.h"
%include "TowheeVector.h"
%include "TowheeVector2D.h"
%include "TowheeVector3D.h"
%include "TowheeVector3DAtom.h"
