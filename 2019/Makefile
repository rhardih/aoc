# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

4p%:
	gcc -o aoc $@.c && ./aoc

.PHONY: clean

clean:
	rm -f aoc *.o
