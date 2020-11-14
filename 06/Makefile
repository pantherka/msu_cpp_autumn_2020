CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -Wno-unused-variable

all: format

format: test.o
	$(CXX) $(CXXFLAGS) -o format test.o

test:
	./format

test.o: test.cpp format.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o format
