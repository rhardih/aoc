# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

4p%:
	gcc -o aoc $@.c && ./aoc

5p1:
	gcc -o aoc 5p1.c && (cat 5.in; echo 1) | ./aoc

intcode.o: intcode.h intcode.c
	gcc -c intcode.c

5p2: intcode.o
	gcc -o aoc intcode.o 5p2.c && ./aoc < 5.in

.PHONY: clean

clean:
	rm -f aoc *.o
