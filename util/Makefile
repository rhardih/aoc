bst.o: bst.c bst.h
	gcc -c bst.c

ll.o: ll.c ll.h
	gcc -c ll.c

test: ll.o bst.o
	gcc -o test test.c ll.o bst.o && ./test

clean:
	rm *.o

.PHONY: clean test
