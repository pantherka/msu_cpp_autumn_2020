CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: my_prog

my_prog: tokenparser.o test.o
	$(CXX) $(CXXFLAGS) -o my_prog test.o tokenparser.o

tokenparser.o: tokenparser.cpp tokenparser.h
	$(CXX) $(CXXFLAGS) -c tokenparser.cpp

test: test.o
	./my_prog

test.o: test.cpp tokenparser.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
