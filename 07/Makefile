CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: test.o
	$(CXX) $(CXXFLAGS) -o vector test.o

test:
	./vector

test.o: test.cpp vector.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o vector
