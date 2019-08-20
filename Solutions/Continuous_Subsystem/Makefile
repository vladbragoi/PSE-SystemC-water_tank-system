DESIGN_NAME=xtea
ABSTRACTION_LEVEL=UT

EXECUTABLE=bin/continuous_subsystem.x

SYSTEMC=$$SYSTEMC_HOME
SYSTEMC_AMS=$$SCAMS_HOME

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

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a   $(SYSC_LIBDIR)/libsystemc.a -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
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
