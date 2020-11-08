CXX=g++
CXXFLAGS=-std=c++17 -pedantic -Wall -Wno-unused-variable -Wextra

all: my_prog

my_prog: test.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o

test:
	./my_prog

test.o: test.cpp serializer.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
