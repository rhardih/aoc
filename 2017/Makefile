# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

3p1:
	gcc -o aoc 3p1.c && ./aoc

3p2:
	gcc -o aoc 3p2.c && ./aoc

.PHONY: clean

clean:
	rm -f aoc *.o
