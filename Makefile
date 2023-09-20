
# CXX Make variable for compiler
CXX=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -Wall -g3 -c

all: accumSim stackSim

accumSim : accumSim.o Simulator.o
	$(CXX) -o accumSim accumSim.o Simulator.o

stackSim : stackSim.o Simulator.o
	$(CXX) -o stackSim stackSim.o Simulator.o

Simulator.o : Simulator.h Simulator.cpp
	$(CXX) $(CXXFLAGS) Simulator.cpp

accumSim.o : Simulator.h accumSim.cpp
	$(CXX) $(CXXFLAGS) accumSim.cpp

stackSim.o : Simulator.h stackSim.cpp
	$(CXX) $(CXXFLAGS) stackSim.cpp

