%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

OSSLFLAGS := `PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig pkg-config --cflags --libs openssl`

4p1:
	gcc $(OSSLFLAGS) -o aoc 4p1.c && ./aoc

4p2:
	gcc $(OSSLFLAGS) -o aoc 4p2.c && ./aoc

7p1: 7.in
	go run 7p1.go < 7.in

7p2: 7.in
	go run 7p2.go < 7.in

.PHONY: clean

clean:
	rm -f aoc *.o test
