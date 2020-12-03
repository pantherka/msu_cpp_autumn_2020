CXX=g++
CXXFLAGS=-std=c++17 -pthread -Wall -pedantic -Wextra -Wno-unused-variable

all: test.o
	$(CXX) $(CXXFLAGS) -o threadpool test.o

test:
	./threadpool

test.o: test.cpp threadpool.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o threadpool