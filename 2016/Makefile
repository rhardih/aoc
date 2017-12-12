ll.o:
	pushd ../util && make ll.o && popd

LLFLAGS := "-I../util"
LLOBJ := "../util/ll.o"

bst.o: bst.c bst.h
	gcc -c bst.c

# Make doesn't provide a real substring text function, hence this ugly sed hack
%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

4p2:
	gcc -o aoc 4p2.c && ./aoc < 4.in | grep "north"

OSSLFLAGS := `PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig pkg-config --cflags --libs openssl`

5p1:
	gcc $(OSSLFLAGS) -o aoc 5p1.c && ./aoc

5p2:
	gcc $(OSSLFLAGS) -o aoc 5p2.c && ./aoc

8p2:
	gcc -o aoc 8p2.c && ./aoc < 8.in | gsed 's/0/ /g'

10p1: ll.o
	gcc $(LLFLAGS) -o aoc 10p1.c $(LLOBJ) && ./aoc < 10.in

10p2: ll.o
	gcc $(LLFLAGS) -o aoc 10p2.c ll.o && ./aoc < 10.in

11p1: ll.o
	gcc $(LLFLAGS) -o aoc 11p1.c $(LLOBJ) && ./aoc

13p1:
	gcc -o aoc 13p1.c && ./aoc

13p2: ll.o
	gcc $(LLFLAGS) -o aoc 13p2.c $(LLOBJ) && ./aoc

14p1:
	gcc $(OSSLFLAGS) -o aoc 14p1.c && ./aoc

14p2:
	gcc $(OSSLFLAGS) -o aoc 14p2.c && ./aoc

16p1:
	gcc -o aoc 16p1.c && ./aoc

17p1:
	gcc $(OSSLFLAGS) -o aoc 17p1.c && ./aoc

17p2:
	gcc $(OSSLFLAGS) -o aoc 17p2.c && ./aoc

19p1:
	gcc -o aoc 19p1.c && ./aoc

19p2:
	gcc -o aoc 19p2.c && ./aoc

20p1: bst.o
	gcc -o aoc 20p1.c bst.o && ./aoc < 20.in

20p2:
	gcc -o aoc 20p2.c && sort -n 20.in | ./aoc

22p2: ll.o
	gcc $(LLFLAGS) -o aoc 22p2.c $(LLOBJ) && ./aoc < 22.in

24p1: ll.o
	gcc $(LLFLAGS) -o aoc 24p1.c $(LLOBJ) && ./aoc < 24.in

24p2: ll.o
	gcc $(LLFLAGS) -o aoc 24p2.c $(LLOBJ) && ./aoc < 24.in

test: ll.o bst.o
	gcc $(LLFLAGS) -o test test.c $(LLOBJ) bst.o && ./test

.PHONY: clean

clean:
	rm -f aoc *.o test
