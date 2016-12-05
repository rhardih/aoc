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

OSSLFLAGS := `PKG_CONFIG_PATH=/usr/local/Cellar/openssl/1.0.2j/lib/pkgconfig/ pkg-config --cflags --libs openssl`

5p1:
	gcc $(OSSLFLAGS) -o aoc 5p1.c && ./aoc

clean :
	rm -f aoc *.o
