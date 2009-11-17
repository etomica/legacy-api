
SHELL = /bin/sh


# ------ FILES ------

SRC =	TowheeAtom.cpp \
	TowheeAtomList.cpp \
	TowheeNativeAtomPositionDefinition.cpp \
	TowheeAtomType.cpp \
	TowheeAtomTypeSphere.cpp \
	TowheeBoundaryEventManager.cpp \
	TowheeBoundary.cpp \
	TowheeBoundaryPeriodic.cpp \
	TowheeBoundaryRectangularPeriodic.cpp \
	TowheeBoxAtomEvent.cpp \
	TowheeBoxAtomIndexEvent.cpp \
	TowheeBox.cpp \
	TowheeBoxEvent.cpp \
	TowheeBoxEventManager.cpp \
	TowheeBoxIndexEvent.cpp \
	TowheeBoxListenerNative.cpp \
	TowheeBoxMoleculeCountEvent.cpp \
	TowheeBoxMoleculeEvent.cpp \
	TowheeBoxMoleculeIndexEvent.cpp \
	TowheeConformationNative.cpp \
	TowheeIntegratorListenerNative.cpp \
	TowheeIntegratorEventManager.cpp \
	TowheeIntegrator.cpp \
	TowheeMolecule.cpp \
	TowheeMoleculeList.cpp \
	TowheeMonatomicMolecule.cpp \
	TowheeRandom.cpp \
	TowheeSimulationAtomTypeEvent.cpp \
	TowheeSimulationAtomTypeIndexEvent.cpp \
	TowheeSimulationBoxEvent.cpp \
	TowheeSimulation.cpp \
	TowheeSimulationEvent.cpp \
	TowheeSimulationEventManager.cpp \
	TowheeSimulationIndexEvent.cpp \
	TowheeSimulationListenerNative.cpp \
	TowheeSimulationSniffer.cpp \
	TowheeSimulationSpeciesEvent.cpp \
	TowheeSimulationSpeciesIndexEvent.cpp \
	TowheeSpace.cpp \
	TowheeSpecies.cpp \
	TowheeSpeciesManager.cpp \
	TowheeSpeciesSpheresMono.cpp \
	TowheeVector2D.cpp \
	TowheeVector3D.cpp \
	TowheeVector3DAtom.cpp \
	TowheeVector.cpp \
	IndexManager.cpp \
	towhee_wrap.cpp

INCDIR = -I/usr/users/rrassler/API/api/C++ \
	-I/usr/users/rrassler/towhee/towhee-6.2.5/Source

FILES = $(SRC) Makefile

# ------ DEFINITIONS ------

LIB = libtowhee_sniffer.so
ALIB = libtowhee_sniffer.a
OBJ =   $(SRC:.cpp=.o)

# ------ SETTINGS ------

CC =	        g++ -v
CCFLAGS =       -O1 -fPIC -g #-Wno-deprecated
ARCHIVE =	ar
ARCHFLAG =	-rc
DEPFLAGS =      -M
LINK =         	g++
LINKFLAGS =	-O
USRLIB =	-L/usr/users/rrassler/API/lib -ltowhee
SYSLIB =

# ------ MAKE PROCEDURE ------

lib: 	$(OBJ)
	$(CC) -shared -o$(LIB) $(INCDIR) $(USRLIB) $(OBJ)
	cp $(LIB) /usr/users/rrassler/API/lib
#	$(ARCHIVE) $(ARFLAGS) $(LIB) $(OBJ)

archive:	$(OBJ)
	ar -r $(ALIB) $(OBJ)
	cp $(ALIB) /usr/users/rrassler/API/lib
# ------ COMPILE RULES ------

%.o:%.cpp
	$(CC) $(CCFLAGS) $(INCDIR) $(USRLIB) -c $<
%.d:%.cpp
	$(CC) $(CCFLAGS) $(DEPFLAGS) $< > $@		

# ------ DEPENDENCIES ------

DEPENDS = $(OBJ:.o=.d)

# ------ CLEAN ------

clean:
	-rm *.o $(LIB)

