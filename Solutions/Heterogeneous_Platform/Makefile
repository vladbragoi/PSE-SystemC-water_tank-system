DESIGN_NAME=watertank_system
ABSTRACTION_LEVEL=HP


SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME

SYS=wt_system
CONTR=controller
TANK=tank
TANK_IF=tank_iface
VALVE=valve
VALVE_IF=valve_iface
XTEA=xtea
XTEA_TRANS=transactor_xtea
WT_TRANS=transactor_watertank


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

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a $(SYSC_LIBDIR)/libsystemc.a -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
CFLAGS= -c
LD=g++

EXECUTABLE = bin/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).x

all: $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/$(SYS).o obj/$(CONTR).o obj/$(TANK_IF).o \
				obj/$(CONTR).o obj/$(WT_TRANS).o obj/$(XTEA_TRANS).o \
				obj/$(VALVE_IF).o obj/$(VALVE).o obj/$(XTEA).o
	@echo Building $@
	$(CXX) -o $@ $(INCDIR) $^ $(LIBS)

obj/main.o: src/main.cpp
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(SYS).o: src/$(SYS).cpp include/$(SYS).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(CONTR).o: src/$(CONTR).cpp include/$(CONTR).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(TANK).o: src/$(TANK).cpp include/$(TANK).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(TANK_IF).o: src/$(TANK_IF).cpp include/$(TANK_IF).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(VALVE).o: src/$(VALVE).cpp include/$(VALVE).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(VALVE_IF).o: src/$(VALVE_IF).cpp include/$(VALVE_IF).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(XTEA).o: src/$(XTEA).cpp include/$(XTEA).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(WT_TRANS).o: src/$(WT_TRANS).cpp include/$(WT_TRANS).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(XTEA_TRANS).o: src/$(XTEA_TRANS).cpp include/$(XTEA_TRANS).h
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