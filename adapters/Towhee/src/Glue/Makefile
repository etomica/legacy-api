

USER_INCLUDES =  -I/usr/users/rrassler/API/api/C++ -I/usr/users/rrassler/towhee/towhee-6.2.5/Source
TOWHEE_LIB = -L/usr/users/rrassler/API/lib -ltowhee
LIBFLAG = -shared
TOWHEE_INSTALL_DIR = /usr/users/rrassler/API/lib

SRC =  TowheeAtom.cpp \
	TowheeAtomList.cpp \
	TowheeAtomType.cpp \
	TowheeAtomTypeSphere.cpp \
	TowheeBoundary.cpp \
	TowheeBoundaryRectangularPeriodic.cpp \
	TowheeBox.cpp \
	TowheeBoxEventManager.cpp \
	TowheeIntegrator.cpp \
	TowheeIntegratorEventManager.cpp \
	TowheeIntegratorListenerNative.cpp \
	TowheeIntegratorMC.cpp \
	TowheeIntegratorNPT.cpp \
	TowheeIntegratorNVT.cpp \
	TowheeIntegratorPseudoBubble.cpp \
	TowheeIntegratorUVT.cpp \
	TowheeMolecule.cpp \
	TowheeMCMove.cpp \
	TowheeMCMoveCOMTranslation.cpp \
	TowheeMoleculeList.cpp \
	TowheeMonatomicMolecule.cpp \
	TowheeRandom.cpp \
	TowheeSimulation.cpp \
	TowheeSimulationEventManager.cpp \
	TowheeSpace.cpp \
	TowheeSpecies.cpp \
	TowheeSpeciesManager.cpp \
	TowheeSpeciesSpheresMono.cpp \
	TowheeVector.cpp \
	TowheeVector2D.cpp \
	TowheeVector3D.cpp \
	TowheeVector3DAtom.cpp \
	IndexManager.cpp \
	towhee_wrap.cpp

LIB = libtowhee_adapter.so
INCLUDES = $(USER_INCLUDES)
OBJ =	$(SRC:.cpp=.o)

CCFLAGS =	-O1 -fPIC -g -v
ARCHIVE =	ar
ARCHFLAG =	-rc
DEPFLAGS =	-M
LINK =		g++
LINKFLAGS =	-O1
USRLIBS =	$(TOWHEE_LIB)

all:	lib

lib:	$(OBJ)
	$(CXX) $(LIBFLAG) -o $(LIB) $(INCLUDES) $(USRLIBS) $(OBJ)

clean:
	rm *.o *.so

install: lib
	mv *.so $(TOWHEE_INSTALL_DIR)

%.o:%.cpp
	$(CXX) $(CCFLAGS) $(INCLUDES) -c $<

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
