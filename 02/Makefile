CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog

my_prog: tokenparser.o test.o
	$(CC) $(FLAGS) -o my_prog test.o tokenparser.o

tokenparser.o: tokenparser.cpp tokenparser.h
	$(CC) $(FLAGS) -c tokenparser.cpp

test: test.o
	./my_prog

test.o: test.cpp tokenparser.h
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
