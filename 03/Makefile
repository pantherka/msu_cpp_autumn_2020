CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: my_prog

my_prog: matrix.o test.o
	$(CXX) $(CXXFLAGS) -o my_prog matrix.o test.o

matrix.o: matrix.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -c matrix.cpp

test:
	./my_prog

test.o: test.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
