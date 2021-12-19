all: stringProg

stringProg: Ex3.c
	gcc -Wall Ex3.c -o stringProg

clean:
	rm -f *.o *.a stringProg
