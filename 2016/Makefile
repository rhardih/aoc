1p1:
	gcc -o aoc 1p1.c && ./aoc < 1.in

1p2:
	gcc -o aoc 1p2.c && ./aoc < 1.in

2p1:
	gcc -o aoc 2p1.c && ./aoc < 2.in

2p2:
	gcc -o aoc 2p2.c && ./aoc < 2.in

3p1:
	gcc -o aoc 3p1.c && ./aoc < 3.in

3p2:
	gcc -o aoc 3p2.c && ./aoc < 3.in

4p1:
	gcc -o aoc 4p1.c && ./aoc < 4.in

4p2:
	gcc -o aoc 4p2.c && ./aoc < 4.in | grep "north"

OSSLFLAGS := `PKG_CONFIG_PATH=/usr/local/Cellar/openssl/1.0.2j/lib/pkgconfig/ pkg-config --cflags --libs openssl`

5p1:
	gcc $(OSSLFLAGS) -o aoc 5p1.c && ./aoc

5p2:
	gcc $(OSSLFLAGS) -o aoc 5p2.c && ./aoc

6p1:
	gcc -o aoc 6p1.c && ./aoc < 6.in

6p2:
	gcc -o aoc 6p2.c && ./aoc < 6.in

7p1:
	gcc -o aoc 7p1.c && ./aoc < 7.in

7p2:
	gcc -o aoc 7p2.c && ./aoc < 7.in

8p1:
	gcc -o aoc 8p1.c && ./aoc < 8.in

8p2:
	gcc -o aoc 8p2.c && ./aoc < 8.in | gsed 's/0/ /g'

9p1:
	gcc -o aoc 9p1.c && ./aoc < 9.in

9p2:
	gcc -o aoc 9p2.c && ./aoc < 9.in

10p1:
	gcc -o aoc 10p1.c && ./aoc < 10.in

12p1:
	gcc -o aoc 12p1.c && ./aoc < 12.in

12p2:
	gcc -o aoc 12p2.c && ./aoc < 12.in

13p1:
	gcc -o aoc 13p1.c && ./aoc

clean :
	rm -f aoc *.o
