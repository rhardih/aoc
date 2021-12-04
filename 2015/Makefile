%:
	gcc -o aoc $@.c && ./aoc < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

OSSLFLAGS := `PKG_CONFIG_PATH=/usr/local/opt/openssl/lib/pkgconfig pkg-config --cflags --libs openssl`

4p1:
	gcc $(OSSLFLAGS) -o aoc 4p1.c && ./aoc

4p2:
	gcc $(OSSLFLAGS) -o aoc 4p2.c && ./aoc

# brew install openjdk
# sudo ln -sfn /usr/local/opt/openjdk/libexec/openjdk.jdk
# /Library/Java/JavaVirtualMachines/openjdk.jdk
7p1-observer: 7.in
	javac 7p1-observer.java && java SomeAssemblyRequired < 7.in

7p1-sort: 7.in
	ruby 7p1-sort.rb < 7.in

7p1-queue: 7.in
	ruby 7p1-queue.rb < 7.in

7p1: 7.in
	go run 7p1.go < 7.in

7p2: 7.in
	go run 7p2.go < 7.in

8p1: 8.in
	ruby 8p1.rb < 8.in

9p1: 9.in
	ruby 9p1.rb < 9.in

9p2: 9.in
	ruby 9p2.rb < 9.in

10p1:
	ruby 10p1.rb

10p2:
	ruby 10p2.rb

.PHONY: clean

clean:
	rm -f aoc *.o test *.class
