DESIGN_NAME=watertank
ABSTRACTION_LEVEL=AMS

EXECUTABLE=bin/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).x

SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME

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

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a \
	   $(SYSC_LIBDIR)/libsystemc.a \
	   -lpthread

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a $(SYSC_LIBDIR)/libsystemc.a -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
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