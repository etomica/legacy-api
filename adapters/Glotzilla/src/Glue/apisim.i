/* File: apisim.i */
%module test
%{
#include "glotzmd.h"
#include "IAPIFunction.h"
#include "IAPIRandom.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "IAPIBoundaryEvent.h"
#include "IAPIBoundaryListener.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPIBoundary.h"
#include "IAPIAtomList.h"
#include "IAPIMoleculeList.h"
#include "IAPIAtomType.h"
#include "IAPIAtomTypeSphere.h"
#include "IAPISimulationEvent.h"
#include "IAPISimulationAtomTypeEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationListener.h"
#include "IAPISimulationEventManager.h"
#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomKinetic.h"
#include "IAPIMolecule.h"
#include "IAPISpecies.h"
#include "IAPIIntegrator.h"
#include "IAPIIntegratorEvent.h"
#include "IAPIIntegratorListener.h"
#include "IAPIIntegratorEventManager.h"
#include "IAPIBoxEvent.h"
#include "IAPIBoxAtomEvent.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "IAPIBoxIndexEvent.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIBoxMoleculeIndexEvent.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPIBoxListener.h"
#include "IAPIBoxEventManager.h"
#include "IAPIBox.h"
#include "IAPIPotential.h"
#include "IAPIPotentialAtomic.h"
#include "IAPIPotentialMaster.h"
#include "IAPISpeciesManager.h"
#include "IAPISimulation.h"
#include "GlotzillaInterfaceConformation.h"
#include "GlotzillaInterfaceAtomPositionDefinition.h"
#include "PotentialGroup.h"
#include "GlotzillaAtomType.h"
#include "GlotzillaAtomPositionDefinition.h"
#include "GlotzillaAtomPositionDefinitionSimple.h"
#include "GlotzillaNativeAtomPositionDefinition.h"
#include "GlotzillaAtomTypeSphere.h"
#include "GlotzillaSimulationEvent.h"
#include "GlotzillaSimulationBoxEvent.h"
#include "GlotzillaSimulationSpeciesEvent.h"
#include "GlotzillaSimulationSpeciesIndexEvent.h"
#include "GlotzillaSimulationIndexEvent.h"
#include "GlotzillaSimulationAtomTypeEvent.h"
#include "GlotzillaSimulationAtomTypeIndexEvent.h"
#include "GlotzillaSimulationListenerNative.h"
#include "GlotzillaSimulationEventManager.h"
#include "GlotzillaRandom.h"
#include "GlotzillaVector.h"
#include "GlotzillaVector2D.h"
#include "GlotzillaVector3D.h"
#include "GlotzillaBoundary.h"
#include "GlotzillaBoundaryPeriodic.h"
#include "GlotzillaAtomList.h"
#include "GlotzillaMoleculeList.h"
#include "GlotzillaConformationNative.h"
#include "GlotzillaPotential.h"
#include "GlotzillaPotentialTwelveSixLj.h"
#include "GlotzillaPotentialWCA.h"
#include "GlotzillaPotentialLJ.h"
#include "GlotzillaPotentialDzugutov.h"
#include "GlotzillaSpring.h"
#include "GlotzillaBondHarmonic.h"
#include "GlotzillaBondFene.h"
#include "GlotzillaPotentialMaster.h"
#include "GlotzillaBoundaryEventManager.h"
#include "GlotzillaSpecies.h"
#include "GlotzillaSpeciesSpheresMono.h"
#include "GlotzillaSpeciesSpheresPolymer.h"
#include "GlotzillaAtom.h"
#include "GlotzillaMolecule.h"
#include "GlotzillaMonatomicMolecule.h"
#include "GlotzillaPolymer.h"
#include "GlotzillaIntegrator.h"
#include "GlotzillaIntegratorVelocityVerlet.h"
#include "GlotzillaIntegratorEuler.h"
#include "GlotzillaIntegratorLeapFrog.h"
#include "GlotzillaIntegratorListener.h"
#include "GlotzillaIntegratorListenerNative.h"
#include "GlotzillaIntegratorEventManager.h"
#include "GlotzillaBox.h"
#include "GlotzillaBoxListenerNative.h"
#include "GlotzillaBoxEventManager.h"
#include "GlotzillaBoxEvent.h"
#include "GlotzillaBoxAtomEvent.h"
#include "GlotzillaBoxMoleculeEvent.h"
#include "GlotzillaBoxMoleculeIndexEvent.h"
#include "GlotzillaBoxMoleculeCountEvent.h"
#include "GlotzillaBoxIndexEvent.h"
#include "GlotzillaBoxAtomIndexEvent.h"
#include "GlotzillaSpeciesManager.h"
#include "GlotzillaSpace.h"
#include "GlotzillaSimulation.h"
#include "GlotzillaPotentialMasterBruteForce.h"
#include "GlotzillaPotentialMasterBruteForceShifted.h"
#include "GlotzillaPotentialMasterCellForce.h"
#include "GlotzillaPotentialMasterCellForceMulti.h"
#include "GlotzillaPotentialMasterCellForceShifted.h"
#include "GlotzillaPotentialMasterVerletForce.h"
#include "GlotzillaPotentialMasterVerletForceMulti.h"
#include "GlotzillaPotentialMasterVerletForceMultiShifted.h"
#include "GlotzillaPotentialMasterVerletForceShifted.h"
#include "GlotzillaPotentialMasterVerletCellForce.h"
#include "GlotzillaPotentialMasterVerletCellForceMulti.h"
#include "GlotzillaPotentialMasterVerletCellForceMultiShifted.h"
#include "GlotzillaPotentialMasterVerletCellForceShifted.h"

using namespace glotzwrappers;
using namespace molesimAPI;
%}

%include "std_string.i"
%include "arrays_java.i"

//%include "std_vector.i"
//namespace std {
//   %template(vectorBead) vector<glotzilla::MdBead>;
//   %template(vectorAtom) vector<Atom>;
//};

//%pragma(java) jniclassinterfaces="JNIPRAGMA"
//%pragma(java) moduleinterfaces="MODULEPRAGMA"

%include exception.i

//%exception {
//  try {
//    $action
//  }
//  catch(int) {
//    SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, "Hello");
//  }
//}

typedef double gfloat;
%include "IAPIFunction.h"
//%include "somedeps.i"
%include "IAPIRandom.h"
%include "IAPIVector.h"
%include "IAPIVectorMutable.h"
%include "IAPIBoundaryEvent.h"
%include "IAPIBoundaryListener.h"
%include "IAPIBoundaryEventManager.h"
%include "IAPIBoundary.h"
%include "IAPIAtomList.h"
%include "IAPIMoleculeList.h"
%include "IAPIAtomType.h"
%include "IAPIAtomTypeSphere.h"
%include "IAPISimulationEvent.h"
%include "IAPISimulationAtomTypeEvent.h"
%include "IAPISimulationSpeciesEvent.h"
%include "IAPISimulationAtomTypeIndexEvent.h"
%include "IAPISimulationSpeciesIndexEvent.h"
%include "IAPISimulationBoxEvent.h"
%include "IAPISimulationIndexEvent.h"
%include "IAPISimulationListener.h"
%include "IAPISimulationEventManager.h"
%include "IAPIAtom.h"
%include "IAPIAtomPositioned.h"
%include "IAPIAtomKinetic.h"
%include "IAPIMolecule.h"
%include "IAPISpecies.h"
%include "IAPIIntegrator.h"
%include "IAPIIntegratorEvent.h"
%include "IAPIIntegratorListener.h"
%include "IAPIIntegratorEventManager.h"
%include "IAPIBoxEvent.h"
%include "IAPIBoxAtomEvent.h"
%include "IAPIBoxAtomIndexEvent.h"
%include "IAPIBoxIndexEvent.h"
%include "IAPIBoxMoleculeEvent.h"
%include "IAPIBoxMoleculeIndexEvent.h"
%include "IAPIBoxMoleculeCountEvent.h"
%include "IAPIBoxListener.h"
%include "IAPIBoxEventManager.h"
%include "IAPIBox.h"
%include "IAPIPotential.h"
%include "IAPIPotentialAtomic.h"
%include "IAPIPotentialMaster.h"
%include "IAPISpeciesManager.h"
%include "IAPISimulation.h"
%include "GlotzillaInterfaceConformation.h"
%include "GlotzillaInterfaceAtomPositionDefinition.h"
%include "PotentialGroup.h"
%include "GlotzillaAtomPositionDefinition.h"
%include "GlotzillaAtomPositionDefinitionSimple.h"
%include "GlotzillaNativeAtomPositionDefinition.h"
%include "GlotzillaAtomType.h"
%include "GlotzillaAtomTypeSphere.h"
%include "GlotzillaSimulationEvent.h"
%include "GlotzillaSimulationBoxEvent.h"
%include "GlotzillaSimulationSpeciesEvent.h"
%include "GlotzillaSimulationSpeciesIndexEvent.h"
%include "GlotzillaSimulationIndexEvent.h"
%include "GlotzillaSimulationAtomTypeEvent.h"
%include "GlotzillaSimulationAtomTypeIndexEvent.h"
%include "GlotzillaSimulationListenerNative.h"
%include "GlotzillaSimulationEventManager.h"
%include "GlotzillaRandom.h"
%include "GlotzillaVector.h"
%include "GlotzillaVector2D.h"
%include "GlotzillaVector3D.h"
%include "GlotzillaBoundary.h"
%include "GlotzillaBoundaryPeriodic.h"
%include "GlotzillaAtomList.h"
%include "GlotzillaMoleculeList.h"
%include "GlotzillaConformationNative.h"
%include "GlotzillaPotential.h"
%include "GlotzillaPotentialTwelveSixLj.h"
%include "GlotzillaPotentialWCA.h"
%include "GlotzillaPotentialLJ.h"
%include "GlotzillaSpring.h"
%include "GlotzillaBondHarmonic.h"
%include "GlotzillaBondFene.h"
%include "GlotzillaPotentialDzugutov.h"
%include "GlotzillaPotentialMaster.h"
%include "GlotzillaBoundaryEventManager.h"
%include "GlotzillaSpecies.h"
%include "GlotzillaSpeciesSpheresMono.h"
%include "GlotzillaSpeciesSpheresPolymer.h"
%include "GlotzillaAtom.h"
%include "GlotzillaMolecule.h"
%include "GlotzillaMonatomicMolecule.h"
%include "GlotzillaPolymer.h"
%include "GlotzillaIntegrator.h"
%include "GlotzillaIntegratorVelocityVerlet.h"
%include "GlotzillaIntegratorEuler.h"
%include "GlotzillaIntegratorLeapFrog.h"
%include "GlotzillaIntegratorListener.h"
%include "GlotzillaIntegratorListenerNative.h"
%include "GlotzillaIntegratorEventManager.h"
%include "GlotzillaBox.h"
%include "GlotzillaBoxListenerNative.h"
%include "GlotzillaBoxEventManager.h"
%include "GlotzillaBoxEvent.h"
%include "GlotzillaBoxAtomEvent.h"
%include "GlotzillaBoxMoleculeEvent.h"
%include "GlotzillaBoxMoleculeIndexEvent.h"
%include "GlotzillaBoxMoleculeCountEvent.h"
%include "GlotzillaBoxIndexEvent.h"
%include "GlotzillaBoxAtomIndexEvent.h"
%include "GlotzillaSpeciesManager.h"
%include "GlotzillaSpace.h"
%include "GlotzillaSimulation.h"
%include "GlotzillaPotentialMasterBruteForce.h"
%include "GlotzillaPotentialMasterBruteForceShifted.h"
%include "GlotzillaPotentialMasterCellForce.h"
%include "GlotzillaPotentialMasterCellForceMulti.h"
%include "GlotzillaPotentialMasterCellForceShifted.h"
%include "GlotzillaPotentialMasterVerletForce.h"
%include "GlotzillaPotentialMasterVerletForceMulti.h"
%include "GlotzillaPotentialMasterVerletForceMultiShifted.h"
%include "GlotzillaPotentialMasterVerletForceShifted.h"
%include "GlotzillaPotentialMasterVerletCellForce.h"
%include "GlotzillaPotentialMasterVerletCellForceMulti.h"
%include "GlotzillaPotentialMasterVerletCellForceMultiShifted.h"
%include "GlotzillaPotentialMasterVerletCellForceShifted.h"

