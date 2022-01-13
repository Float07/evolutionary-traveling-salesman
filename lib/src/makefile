SO_FILE = lib.so

all: evo_salesman.o main.o
	gcc -shared -o libevo.so *.o

evo_salesman.o: evo_salesman.c
	gcc -O2 -c -Wall -Werror -fpic evo_salesman.c

main.o: main.c
	gcc -O2 -c -Wall -Werror -fpic main.c

clear: 
	rm *.o *.so
