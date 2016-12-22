###################################
# Sampled Makefile for RRAM sample 
###################################

####################################
# SystemC library installation path 
####################################
SYSTEMC_ROOT = /home/jingyang/ProgramFiles/systemc-2.3.1a

###################
# General settings 
###################
CXX = g++
INCDIR = -I$(SYSTEMC_ROOT)/include
LIBDIR = -L$(wildcard $(SYSTEMC_ROOT)/lib-*)
LIBS = -lsystemc -lm
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
CFLAGS = -Wall -O3 -g
EXE = main

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(LIBDIR) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(INCDIR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -fr $(OBJS) $(EXE)
