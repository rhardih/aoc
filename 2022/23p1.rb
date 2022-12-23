=begin

--- Day 23: Unstable Diffusion ---

You enter a large crater of gray dirt where the grove is supposed to be. All
around you, plants you imagine were expected to be full of fruit are instead
withered and broken. A large group of Elves has formed in the middle of the
grove.

"...but this volcano has been dormant for months. Without ash, the fruit can't
grow!"

You look up to see a massive, snow-capped mountain towering above you.

"It's not like there are other active volcanoes here; we've looked everywhere."

"But our scanners show active magma flows; clearly it's going somewhere."

They finally notice you at the edge of the grove, your pack almost overflowing
from the random star fruit you've been collecting. Behind you, elephants and
monkeys explore the grove, looking concerned. Then, the Elves recognize the ash
cloud slowly spreading above your recent detour.

"Why do you--" "How is--" "Did you just--"

Before any of them can form a complete question, another Elf speaks up: "Okay,
new plan. We have almost enough fruit already, and ash from the plume should
spread here eventually. If we quickly plant new seedlings now, we can still make
it to the extraction point. Spread out!"

The Elves each reach into their pack and pull out a tiny plant. The plants rely
on important nutrients from the ash, so they can't be planted too close
together.

There isn't enough time to let the Elves figure out where to plant the seedlings
themselves; you quickly scan the grove (your puzzle input) and note their
positions.

For example:

....#..
..###.#
#...#.#
.#...##
#.###..
##.#.##
.#..#..

The scan shows Elves # and empty ground .; outside your scan, more empty ground
extends a long way in every direction. The scan is oriented so that north is up;
orthogonal directions are written N (north), S (south), W (west), and E (east),
while diagonal directions are written NE, NW, SE, SW.

The Elves follow a time-consuming process to figure out where they should each
go; you can speed up this process considerably. The process consists of some
number of rounds during which Elves alternate between considering where to move
and actually moving.

During the first half of each round, each Elf considers the eight positions
adjacent to themself. If no other Elves are in one of those eight positions, the
Elf does not do anything during this round. Otherwise, the Elf looks in each of
four directions in the following order and proposes moving one step in the first
valid direction:

- If there is no Elf in the N, NE, or NW adjacent positions, the Elf proposes
moving north one step.
- If there is no Elf in the S, SE, or SW adjacent positions, the Elf proposes
moving south one step.
- If there is no Elf in the W, NW, or SW adjacent positions, the Elf proposes
moving west one step.
- If there is no Elf in the E, NE, or SE adjacent positions, the Elf proposes
moving east one step.

After each Elf has had a chance to propose a move, the second half of the round
can begin. Simultaneously, each Elf moves to their proposed destination tile if
they were the only Elf to propose moving to that position. If two or more Elves
propose moving to the same position, none of those Elves move.

Finally, at the end of the round, the first direction the Elves considered is
moved to the end of the list of directions. For example, during the second
round, the Elves would try proposing a move to the south first, then west, then
east, then north. On the third round, the Elves would first consider west, then
east, then north, then south.

As a smaller example, consider just these five Elves:

.....
..##.
..#..
.....
..##.
.....

The northernmost two Elves and southernmost two Elves all propose moving north,
while the middle Elf cannot move north and proposes moving south. The middle Elf
proposes the same destination as the southwest Elf, so neither of them move, but
the other three do:

..##.
.....
..#..
...#.
..#..
.....

Next, the northernmost two Elves and the southernmost Elf all propose moving
south. Of the remaining middle two Elves, the west one cannot move south and
proposes moving west, while the east one cannot move south or west and proposes
moving east. All five Elves succeed in moving to their proposed positions:

.....
..##.
.#...
....#
.....
..#..

Finally, the southernmost two Elves choose not to move at all. Of the remaining
three Elves, the west one proposes moving west, the east one proposes moving
east, and the middle one proposes moving north; all three succeed in moving:

..#..
....#
#....
....#
.....
..#..

At this point, no Elves need to move, and so the process ends.

The larger example above proceeds as follows:

== Initial State ==
..............
..............
.......#......
.....###.#....
...#...#.#....
....#...##....
...#.###......
...##.#.##....
....#..#......
..............
..............
..............

== End of Round 1 ==
..............
.......#......
.....#...#....
...#..#.#.....
.......#..#...
....#.#.##....
..#..#.#......
..#.#.#.##....
..............
....#..#......
..............
..............

== End of Round 2 ==
..............
.......#......
....#.....#...
...#..#.#.....
.......#...#..
...#..#.#.....
.#...#.#.#....
..............
..#.#.#.##....
....#..#......
..............
..............

== End of Round 3 ==
..............
.......#......
.....#....#...
..#..#...#....
.......#...#..
...#..#.#.....
.#..#.....#...
.......##.....
..##.#....#...
...#..........
.......#......
..............

== End of Round 4 ==
..............
.......#......
......#....#..
..#...##......
...#.....#.#..
.........#....
.#...###..#...
..#......#....
....##....#...
....#.........
.......#......
..............

== End of Round 5 ==
.......#......
..............
..#..#.....#..
.........#....
......##...#..
.#.#.####.....
...........#..
....##..#.....
..#...........
..........#...
....#..#......
..............

After a few more rounds...

== End of Round 10 ==
.......#......
...........#..
..#.#..#......
......#.......
...#.....#..#.
.#......##....
.....##.......
..#........#..
....#.#..#....
..............
....#..#..#...
..............

To make sure they're on the right track, the Elves like to check after round 10
that they're making good progress toward covering enough ground. To do this,
count the number of empty ground tiles contained by the smallest rectangle that
contains every Elf. (The edges of the rectangle should be aligned to the N/S/E/W
directions; the Elves do not have the patience to calculate arbitrary
rectangles.) In the above example, that rectangle is:

......#.....
..........#.
.#.#..#.....
.....#......
..#.....#..#
#......##...
....##......
.#........#.
...#.#..#...
............
...#..#..#..

In this region, the number of empty ground tiles is 110.

Simulate the Elves' process and find the smallest rectangle that contains the
Elves after 10 rounds. How many empty ground tiles does that rectangle contain?

=end

require 'matrix'

NORTH = 0
SOUTH = 1
WEST = 2
EAST = 3

class Elf
  attr_accessor :current_x, :current_y
  attr_accessor :proposed_x, :proposed_y

  def initialize(x, y, scan)
    @current_x = x
    @current_y = y
    @proposed_x = x
    @proposed_y = y

    @scan = scan

    check_up = -> {
      # N, NE, or NW
      free = [
        [@current_x, @current_y - 1],
        [@current_x - 1, @current_y - 1],
        [@current_x + 1, @current_y - 1]
      ].none? { |x, y| @scan.key?([y,x]) }

      return [@current_x, @current_y - 1, free]
    }

    check_down = -> {
      # S, SE, or SW
      free = [
        [@current_x, @current_y + 1],
        [@current_x - 1, @current_y + 1],
        [@current_x + 1, @current_y + 1]
      ].none? { |x, y| @scan.key?([y,x]) }

      return [@current_x, @current_y + 1, free]
    }

    check_left = -> {
      # W, NW, or SW
      free = [
        [@current_x - 1, @current_y],
        [@current_x - 1, @current_y - 1],
        [@current_x - 1, @current_y + 1]
      ].none? { |x, y| @scan.key?([y,x]) }

      return [@current_x - 1, @current_y, free]
    }

    check_right = -> {
      # E, NE, or SE
      free = [
        [@current_x + 1, @current_y],
        [@current_x + 1, @current_y - 1],
        [@current_x + 1, @current_y + 1]
      ].none? { |x, y| @scan.key?([y,x]) }

      return [@current_x + 1, @current_y, free]
    }

    @checkers = [check_up, check_down, check_left, check_right]
    @checker_index = 0
  end

  def propose!
    4.times do |i|
      checker = @checkers[(@checker_index + i) % 4]

      x, y, free = checker.call

      if free
        @proposed_x = x
        @proposed_y = y
        break
      end
    end
  end

  def by_himself?
    [
      [current_x - 1, current_y - 1], # NW
      [current_x, current_y - 1],     # N
      [current_x + 1, current_y - 1], # NE
      [current_x + 1, current_y],     # E
      [current_x + 1, current_y + 1], # SE
      [current_x, current_y + 1],     # S
      [current_x - 1, current_y + 1], # SW
      [current_x - 1, current_y]      # W
    ].none? { |x, y| @scan.key?([y,x]) }
  end

  def move!
    # puts "elf at #{@current_x},#{current_y} moving to #{@proposed_x},#{@proposed_y}"

    @scan.delete([current_y, current_x])

    @current_x = @proposed_x
    @current_y = @proposed_y

    @scan[[current_y, current_x]] = self
  end

  def reorder_directions!
    @checker_index += 1
  end
end

def first_half(elves)
  elves.each do |elf|
    # Each elf considers the eight positions adjacent to themself - If no other
    # Elves are in one of those eight positions, the Elf does not do anything
    # during this round
    if elf.by_himself?
      # puts "elf by himself at #{elf.current_x},#{elf.current_y}"
      next
    end

    # Otherwise, the Elf looks in each of four directions in the following order
    # and proposes moving one step in the first valid direction
    elf.propose!
  end
end

def second_half(elves)
  proposals = Hash.new { |k,v| k[v] = [] }

  elves.each do |elf|
    proposals[[elf.proposed_x, elf.proposed_y]] << elf
  end

  proposals.each do |coordinates, elves|
    if elves.size > 1 # two elves suggested the same spot
      x, y = coordinates

      # puts "#{elves.size} elves wanted to move to #{x},#{y}"
      next
    end

    elf = elves.last

    elf.move!
  end

  elves.each(&:reorder_directions!)
end

def limits(elves)
  # Find dimensions of rectangle
  limit = 100_000
  min_x = limit
  min_y = limit
  max_x = -limit
  max_y = -limit

  elves.each do |elf|
    min_x = elf.current_x if elf.current_x < min_x
    min_y = elf.current_y if elf.current_y < min_y
    max_x = elf.current_x if elf.current_x > max_x
    max_y = elf.current_y if elf.current_y > max_y
  end

  [min_x, min_y, max_x, max_y]
end

def scan_dimensions(elves)
  min_x, min_y, max_x, max_y = limits(elves)
  
  [(min_x..max_x).size, (min_y..max_y).size]
end

def number_of_empty_tiles(elves)
  width, height = scan_dimensions(elves)

  rectangle_area = width * height

  rectangle_area - elves.size
end

def print_scan(elves, dim, offset)
  scan = Array.new(dim) { Array.new(dim) { "." } }

  elves.each do |elf|
    scan[elf.current_y + offset][elf.current_x + offset] = "#"
  end

  puts scan.map(&:join).join("\n")
end

scan = Hash.new
row = 0
dim = 0
offset = 10

STDIN.read.split("\n").each do |line|
  dim = line.size + offset * 2
  col = 0

  line.chars.each do |char|
    if char == "#"
      elf = Elf.new(col, row, scan)

      scan[[row, col]] = elf
    end

    col += 1
  end

  row += 1
end

height = row

print_scan(scan.values, dim, offset) 
puts

10.times do |i|
  first_half(scan.values)
  second_half(scan.values)
  puts "== End of Round #{i + 1} =="
  print_scan(scan.values, dim, offset)
  puts
end

# Wrong guess
#
# 4044 - Too high

puts "Empty ground tiles the rectangle contains: #{ number_of_empty_tiles(scan.values)}"
