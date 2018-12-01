bst.o:
	pushd ../util && make bst.o && popd

BSTFLAGS := "-I../util"
BSTOBJ := "../util/bst.o"

# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

1p2: bst.o
	gcc $(BSTFLAGS) -o aoc 1p2.c $(BSTOBJ) && ./aoc < 1.in

.PHONY: clean

clean:
	rm -f aoc *.o
