ll.o:
	pushd ../util && make ll.o && popd

LLFLAGS := "-I../util"
LLOBJ := "../util/ll.o"

knot.o: knot.c knot.h
	gcc -c knot.c

# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

3p1:
	gcc -o aoc 3p1.c && ./aoc

3p2:
	gcc -o aoc 3p2.c && ./aoc

10p2: knot.o
	gcc -o aoc 10p2.c knot.o && ./aoc < 10.in

12p1: ll.o
	gcc $(LLFLAGS) -o aoc $(LLOBJ) 12p1.c && ./aoc < 12.in

12p2: ll.o
	gcc $(LLFLAGS) -o aoc $(LLOBJ) 12p2.c && ./aoc < 12.in

14p1: knot.o
	gcc -o aoc 14p1.c knot.o && ./aoc

14p2: knot.o
	gcc -o aoc 14p2.c knot.o && ./aoc

15p1:
	gcc -o aoc 15p1.c && ./aoc

15p2:
	gcc -o aoc 15p2.c && ./aoc

17p1: ll.o
	gcc $(LLFLAGS) -o aoc 17p1.c $(LLOBJ) && ./aoc

.PHONY: clean

clean:
	rm -f aoc *.o
