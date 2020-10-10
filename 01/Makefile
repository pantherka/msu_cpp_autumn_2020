CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable
all: my_prog

my_prog: allocator.o test.o
	$(CC) $(FLAGS) -o my_prog test.o allocator.o

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

test: test.o
	./my_prog

test.o: test.cpp allocator.h
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -rf *.o my_prog
