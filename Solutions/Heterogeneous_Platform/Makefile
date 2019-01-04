DESIGN_NAME=xtea
ABSTRACTION_LEVEL=RTL


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

$(EXECUTABLE): obj/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o obj/$(DESIGN_NAME)_LT_testbench.o obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o obj/$(DESIGN_NAME)_RTL_TLM_transactor.o
	@echo Building $@
	$(CXX) -g $(INCDIR) -o $@ $^ $(LIBS)

obj/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o: src/main_$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).cpp
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(DESIGN_NAME)_LT_testbench.o: src/$(DESIGN_NAME)_LT_testbench.cpp include/$(DESIGN_NAME)_LT_testbench.h
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).o: src/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).cpp include/$(DESIGN_NAME)_$(ABSTRACTION_LEVEL).h
	@echo Building $@
	@$(CXX) $(DEBUG) $(CFLAGS) $(INCDIR) -o $@ $<

obj/$(DESIGN_NAME)_RTL_TLM_transactor.o: src/$(DESIGN_NAME)_RTL_TLM_transactor.cpp include/$(DESIGN_NAME)_RTL_TLM_transactor.h
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