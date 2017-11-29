# :christmas_tree: :santa: :star2: aoc :star2: :santa: :christmas_tree: 

Advent of Code solutions.

http://adventofcode.com/

---

Compile and run a puzzle like so: `make 2016 3p2`, or `make 3p2` if already in
the folder of a specific year. The first digit represents day of the puzzle and
second digit is which part to run. Each make target handles piping of the
correct input to its resulting executable.

---

## Notes

### 2016

Day 5 and 14 uses md5 from libssl and thus relies on openssl being installed, as
well as pkg-config to set flags.

### 2015

Day 4 uses md5 from libssl and thus relies on openssl being installed, as well
as pkg-config to set flags.
