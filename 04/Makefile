CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -Wextra -Wno-unused-variable

all: my_prog

my_prog: bigint.o test.o
	$(CXX) $(CXXFLAGS) -o my_prog bigint.o test.o

bigint.o: bigint.cpp bigint.hpp
	$(CXX) $(CXXFLAGS) -c bigint.cpp

test:
	./my_prog

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
