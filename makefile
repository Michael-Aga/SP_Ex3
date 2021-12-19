FLAGS = -Wall -Werror -g
CC = gcc

all: stringProg

stringProg: Ex3.c
	$(CC) $(FLAGS) Ex3.c -o stringProg
	
.PHONY = all clean
clean:
	rm -f *.o *.a stringProg
