# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

4p%: 4.in
	ruby ${@}.rb < 4.in

6p%: 6.in
	ruby ${@}.rb < 6.in

.PHONY: clean

clean:
	rm -f aoc *.o
