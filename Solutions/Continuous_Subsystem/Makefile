<<<<<<< HEAD
DESIGN_NAME=watertank
ABSTRACTION_LEVEL=AMS

EXECUTABLE=bin/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).x

SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME
=======
DESIGN_NAME=xtea
ABSTRACTION_LEVEL=UT

EXECUTABLE=bin/continuous_subsystem.x

SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME
>>>>>>> PSE-univr-project/master

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
SCAMS_LIBDIR := $(SCAMS_LIBDIR)64
endif

<<<<<<< HEAD
LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a \
	   $(SYSC_LIBDIR)/libsystemc.a \
	   -lpthread

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a $(SYSC_LIBDIR)/libsystemc.a -lpthread
=======
LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a   $(SYSC_LIBDIR)/libsystemc.a -lpthread
>>>>>>> PSE-univr-project/master

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
<<<<<<< HEAD
CFLAGS= -c
LD=g++

EXECUTABLE = bin/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).x

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/controller.o obj/tank.o obj/valve.o
	@echo Building $@
	$(CXX) -g $(INCDIR) -o $@ $^ $(LIBS)

obj/main.o: src/main.cpp
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/controller.o: src/controller.cpp include/controller.h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/tank.o: src/tank.cpp include/tank.h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/valve.o: src/valve.cpp include/valve.h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

clean:
	@echo "Cleaning..."
	@rm -rf obj/*.o
	@rm -rf bin/*.x
	@rm -rf *.vcd
	@rm -rf $(EXECUTABLE)
	@echo "Done!"

.PHONY: all clean
=======
CFLAGS= -c -g
LD=g++

all: $(EXECUTABLE)

$(EXECUTABLE): obj/mainC.o obj/ControllerC.o obj/TankC.o obj/ValveC.o

	@echo Building $@
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/mainC.o: src/mainC.cpp
	@echo Building $@
	@$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/ControllerC.o: src/ControllerC.cpp include/ControllerC.h include/commandC.h
	@echo Building $@
	@$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $< 

obj/TankC.o: src/TankC.cpp include/TankC.h
	@echo Building $@
	@$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $<

obj/ValveC.o: src/ValveC.cpp include/ValveC.h
	@echo Building $@
	@$(CXX) -g $(CFLAGS) $(INCDIR) -o $@ $<

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f water.vcd
	@rm -f $(EXECUTABLE)


.PHONY: all clean
>>>>>>> PSE-univr-project/master
