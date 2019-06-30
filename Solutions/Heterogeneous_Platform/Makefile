DESIGN_NAME=xtea
ABSTRACTION_LEVEL=UT

EXECUTABLE=bin/heterogeneous_platform.x

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

$(EXECUTABLE): obj/main.o \
	obj/Controller.o \
	obj/Tank.o \
	obj/Tank_iface.o \
	obj/Transactor_tank.o \
	obj/Transactor_xtea.o \
	obj/Valve.o \
	obj/Valve_iface.o \
	obj/Wt_system.o \
	obj/Xtea.o

	@echo Building $@
	@$(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/main.o: src/main.cpp
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Controller.o: src/Controller.cpp include/Controller.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Tank.o: src/Tank.cpp include/Tank.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Tank_iface.o: src/Tank_iface.cpp include/Tank_iface.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Transactor_tank.o: src/Transactor_tank.cpp include/Transactor_tank.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Transactor_xtea.o: src/Transactor_xtea.cpp include/Transactor_xtea.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Valve.o: src/Valve.cpp include/Valve.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Valve_iface.o: src/Valve_iface.cpp include/Valve_iface.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Wt_system.o: src/Wt_system.cpp include/Wt_system.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

obj/Xtea.o: src/Xtea.cpp include/Xtea.h
	@echo 'Building file: $<'
	@$(CXX) $(CFLAGS) $(INCDIR) -o $@ $<

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f water.vcd
	@rm -f wave.vcd
	@rm -f $(EXECUTABLE)


.PHONY: all clean
