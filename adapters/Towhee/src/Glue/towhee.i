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
#include "TowheeInterfaceAtomPositionDefinition.h"
#include "TowheeAtomPositionDefinition.h"
#include "TowheeRandom.h"
#include "TowheeVector.h"
#include "TowheeVector2D.h"
#include "TowheeVector3D.h"
#include "TowheeVector3DAtom.h"
#include "TowheeSpace.h"
#include "TowheeAtomPositionDefinitionNative.h"
#include "TowheeAtomList.h"
#include "TowheeMolecule.h"
#include "TowheeMonatomicMolecule.h"
#include "TowheeMoleculeList.h"
#include "TowheeBoundary.h"
#include "TowheeBoundaryRectangularPeriodic.h"
#include "TowheeBoxEventManager.h"
#include "TowheeBox.h"
#include "TowheeSpeciesManager.h"
#include "TowheeSimulationEventManager.h"
#include "TowheePotential.h"
#include "TowheePotentialLennardJones.h"
#include "TowheeForceField.h"
#include "TowheeBasicConnectivityMap.h"
#include "TowheePotentialMaster.h"
#include "TowheeSimulation.h"
#include "TowheeIntegratorListenerNative.h"
#include "TowheeIntegratorEventManager.h"
#include "TowheeIntegrator.h"
#include "TowheeMCMove.h"
#include "TowheeMCMoveCOMTranslation.h"
#include "TowheeIntegratorMC.h"
#include "TowheeIntegratorNPT.h"
#include "TowheeIntegratorNVT.h"
#include "TowheeIntegratorPseudoBubble.h"
#include "TowheeIntegratorUVT.h"
#include "TowheeAtom.h"
#include "TowheeAtomType.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeSpecies.h"
#include "TowheeSpeciesSpheresMono.h"

using namespace towheewrappers;
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
%include "TowheeInterfaceAtomPositionDefinition.h"
%include "TowheeAtomPositionDefinition.h"
%include "TowheeRandom.h"
%include "TowheeVector.h"
%include "TowheeVector2D.h"
%include "TowheeVector3D.h"
%include "TowheeVector3DAtom.h"
%include "TowheeSpace.h"
%include "TowheeAtomPositionDefinitionNative.h"
%include "TowheeAtomList.h"
%include "TowheeMolecule.h"
%include "TowheeMonatomicMolecule.h"
%include "TowheeMoleculeList.h"
%include "TowheeBoundary.h"
%include "TowheeBoundaryRectangularPeriodic.h"
%include "TowheeBoxEventManager.h"
%include "TowheeBox.h"
%include "TowheeSpeciesManager.h"
%include "TowheeSimulationEventManager.h"
%include "TowheePotential.h"
%include "TowheePotentialLennardJones.h"
%include "TowheeForceField.h"
%include "TowheeBasicConnectivityMap.h"
%include "TowheePotentialMaster.h"
%include "TowheeSimulation.h"
%include "TowheeIntegratorListenerNative.h"
%include "TowheeIntegratorEventManager.h"
%include "TowheeIntegrator.h"
%include "TowheeMCMove.h"
%include "TowheeMCMoveCOMTranslation.h"
%include "TowheeIntegratorMC.h"
%include "TowheeIntegratorNPT.h"
%include "TowheeIntegratorNVT.h"
%include "TowheeIntegratorPseudoBubble.h"
%include "TowheeIntegratorUVT.h"
%include "TowheeAtom.h"
%include "TowheeAtomType.h"
%include "TowheeAtomTypeSphere.h"
%include "TowheeSpecies.h"
%include "TowheeSpeciesSpheresMono.h"

