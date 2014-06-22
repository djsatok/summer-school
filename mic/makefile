MKL=/opt/intel/mkl
CXX=icc
CXXFLAGS=-DMKL_ILP64 -openmp -mmic -vec-report -O3
IFLAGS=-I$(MKL)/include
LDFLAGS=-L$(MKL)/lib/mic -lmkl_intel_ilp64 -lmkl_core -lmkl_intel_thread -lpthread -lm


SOURCES = stats.cpp data.cpp operators.cpp linalg.cpp
HEADERS = stats.h   data.h   operators.h   linalg.h
OBJ     = stats.o   data.o   operators.o   linalg.o

.SUFFIXES: .cpp

all: main

stats.o: stats.cpp stats.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c stats.cpp -o stats.o

data.o: data.cpp data.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c data.cpp -o data.o

operators.o: operators.cpp operators.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c operators.cpp -o operators.o

linalg.o: linalg.cpp linalg.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c linalg.cpp -o linalg.o

main: $(OBJ) main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) *.o main.cpp -o main ${LDFLAGS}

clean:
	rm -f main
	rm -f *.o
	rm -f *.i
	rm -f output.*

