ll.o:
	pushd ../util && make ll.o && popd

LLFLAGS := "-I../util"
LLOBJ := "../util/ll.o"

bst.o:
	pushd ../util && make bst.o && popd

BSTFLAGS := "-I../util"
BSTOBJ := "../util/bst.o"

# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

1p2: bst.o
	gcc $(BSTFLAGS) -o aoc 1p2.c $(BSTOBJ) && ./aoc < 1.in

4p1: ll.o
	gcc $(LLFLAGS) -o aoc 4p1.c $(LLOBJ) && sort 4.in | ./aoc

4p2: ll.o
	gcc $(LLFLAGS) -o aoc 4p2.c $(LLOBJ) && sort 4.in | ./aoc

11p1:
	gcc -o aoc 11p1.c && ./aoc

11p2:
	gcc -o aoc 11p2.c && ./aoc

.PHONY: clean

clean:
	rm -f aoc *.o
