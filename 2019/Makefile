# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

4p%:
	gcc -o aoc $@.c && ./aoc

5p1:
	gcc -o aoc 5p1.c && (cat 5.in; echo 1) | ./aoc

5p2:
	gcc -o aoc 5p2.c && (cat 5.in; echo 5) | ./aoc

.PHONY: clean

clean:
	rm -f aoc *.o
