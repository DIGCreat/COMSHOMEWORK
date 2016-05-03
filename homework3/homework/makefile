test:test.o test2.o
	gcc test.o test2.o -o test

test.o: test.c test2.h
	gcc -Wall -O -g -c test.c -o test.o

test2.o:test2.c test2.h
	gcc -Wall -O -g -c test2.c -o test2.o
	
clean:
	rm *.o
