all:
	gcc -o program main.c
run:
	./program
clean:
	-rm *.o 
