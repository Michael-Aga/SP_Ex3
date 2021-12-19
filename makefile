all: stringProg

stringProg: main.c
	gcc -Wall -g main.c -o stringProg
clean:
	rm -f *.o *.a stringProg