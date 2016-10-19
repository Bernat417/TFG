MAINFILE= Main.cpp
MYPROGRAMA= Main
TESTALG = GraphAlgorithmsTest
TESTS:= $(wildcard *Test.cpp)
CC=g++
FLAGS = -std=c++11 -fopenmp -O3
AFTERFLAGS = -fopenmp -lpthread

all: main test

test: testpalg testPredM testgalg

main:
	$(CC) $(FLAGS) $(MAINFILE) -o $(MYPROGRAMA) $(AFTERFLAGS)

testgalg: 
	$(CC) $(FLAGS) GraphAlgorithmsTest.cpp -o GraphAlgorithmsTest_	$(AFTERFLAGS)
	
testpalg: 
	$(CC) $(FLAGS) PathAlgorithmsTest.cpp -o PathAlgorithmsTest_ $(AFTERFLAGS)
	
testPredM: 
	$(CC) $(FLAGS) PredictionModuleTest.cpp -o PredictionModuleTest_ $(AFTERFLAGS)	
