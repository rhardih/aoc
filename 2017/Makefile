ll.o:
	pushd ../util && make ll.o && popd

LLFLAGS := "-I../util"
LLOBJ := "../util/ll.o"

# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

3p1:
	gcc -o aoc 3p1.c && ./aoc

3p2:
	gcc -o aoc 3p2.c && ./aoc

12p1: ll.o
	gcc $(LLFLAGS) -o aoc $(LLOBJ) 12p1.c && ./aoc < 12.in

12p2: ll.o
	gcc $(LLFLAGS) -o aoc $(LLOBJ) 12p2.c && ./aoc < 12.in

.PHONY: clean

clean:
	rm -f aoc *.o
