all: stringProg

stringProg: main.c
	gcc -Wall main.c -o stringProg

.PHONY = all clean
clean:
	rm -f *.o *.a stringProg
