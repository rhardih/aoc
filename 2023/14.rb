=begin

--- Day 14: Parabolic Reflector Dish ---

You reach the place where all of the mirrors were pointing: a massive parabolic
reflector dish attached to the side of another large mountain.

The dish is made up of many small mirrors, but while the mirrors themselves are
roughly in the shape of a parabolic reflector dish, each individual mirror
seems to be pointing in slightly the wrong direction. If the dish is meant to
focus light, all it's doing right now is sending it in a vague direction.

This system must be what provides the energy for the lava! If you focus the
reflector dish, maybe you can go where it's pointing and use the light to fix
the lava production.

Upon closer inspection, the individual mirrors each appear to be connected via
an elaborate system of ropes and pulleys to a large metal platform below the
dish. The platform is covered in large rocks of various shapes. Depending on
their position, the weight of the rocks deforms the platform, and the shape of
the platform controls which ropes move and ultimately the focus of the dish.

In short: if you move the rocks, you can focus the dish. The platform even has
a control panel on the side that lets you tilt it in one of four directions!
The rounded rocks (O) will roll when the platform is tilted, while the
cube-shaped rocks (#) will stay in place. You note the positions of all of the
empty spaces (.) and rocks (your puzzle input). For example:

O....#....
O.OO#....#
.....##...
OO.#O....O
.O.....O#.
O.#..O.#.#
..O..#O..O
.......O..
#....###..
#OO..#....

Start by tilting the lever so all of the rocks will slide north as far as they
will go:

OOOO.#.O..
OO..#....#
OO..O##..O
O..#.OO...
........#.
..#....#.#
..O..#.O.O
..O.......
#....###..
#....#....

You notice that the support beams along the north side of the platform are
damaged; to ensure the platform doesn't collapse, you should calculate the
total load on the north support beams.

The amount of load caused by a single rounded rock (O) is equal to the number
of rows from the rock to the south edge of the platform, including the row the
rock is on. (Cube-shaped rocks (#) don't contribute to load.) So, the amount of
load caused by each rock in each row is as follows:

OOOO.#.O.. 10
OO..#....#  9
OO..O##..O  8
O..#.OO...  7
........#.  6
..#....#.#  5
..O..#.O.O  4
..O.......  3
#....###..  2
#....#....  1

The total load is the sum of the load caused by all of the rounded rocks. In
this example, the total load is 136.

Tilt the platform so that the rounded rocks all roll north. Afterward, what is
the total load on the north support beams?

--- Part Two ---

The parabolic reflector dish deforms, but not in a way that focuses the beam.
To do that, you'll need to move the rocks to the edges of the platform.
Fortunately, a button on the side of the control panel labeled "spin cycle"
attempts to do just that!

Each cycle tilts the platform four times so that the rounded rocks roll north,
then west, then south, then east. After each tilt, the rounded rocks roll as
far as they can before the platform tilts in the next direction. After one
cycle, the platform will have finished rolling the rounded rocks in those four
directions in that order.

Here's what happens in the example above after each of the first few cycles:

After 1 cycle:
.....#....
....#...O#
...OO##...
.OO#......
.....OOO#.
.O#...O#.#
....O#....
......OOOO
#...O###..
#..OO#....

After 2 cycles:
.....#....
....#...O#
.....##...
..O#......
.....OOO#.
.O#...O#.#
....O#...O
.......OOO
#..OO###..
#.OOO#...O

After 3 cycles:
.....#....
....#...O#
.....##...
..O#......
.....OOO#.
.O#...O#.#
....O#...O
.......OOO
#...O###.O
#.OOO#...O

This process should work if you leave it running long enough, but you're still
worried about the north support beams. To make sure they'll survive for a
while, you need to calculate the total load on the north support beams after
1000000000 cycles.

In the above example, after 1000000000 cycles, the total load on the north
support beams is 64.

Run the spin cycle for 1000000000 cycles. Afterward, what is the total load on
the north support beams?

=end

def dputs(*args)
  puts *args if ENV['DEBUG']
end

def tilt_north(positions)
  (1...positions.length).each do |row|
    (0...positions.first.length).each do |col|
      if positions[row][col] == "O"
        previous_row = row - 1
        current_row = row

        while positions[previous_row][col] == "." && previous_row >= 0
          positions[previous_row][col], positions[current_row][col] =
            positions[current_row][col], positions[previous_row][col] 

          previous_row -= 1
          current_row -= 1
        end
      end
    end
  end
end

def tilt_west(positions)
  (0...positions.length).each do |row|
    (1...positions.first.length).each do |col|
      if positions[row][col] == "O"
        previous_col = col - 1
        current_col = col

        while positions[row][previous_col] == "." && previous_col >= 0
          positions[row][previous_col], positions[row][current_col] =
            positions[row][current_col], positions[row][previous_col] 

          previous_col -= 1
          current_col -= 1
        end
      end
    end
  end
end

def tilt_south(positions)
  (positions.length - 2).downto(0) do |row|
    (0...positions.first.length).each do |col|
      if positions[row][col] == "O"
        current_row = row
        next_row = row + 1

        while next_row <= positions.length - 1 && positions[next_row][col] == "."
          positions[next_row][col], positions[current_row][col] =
            positions[current_row][col], positions[next_row][col] 

          current_row += 1
          next_row += 1
        end
      end
    end
  end
end

def tilt_east(positions)
  (0...positions.length).each do |row|
    (positions.first.length - 2).downto(0) do |col|
      if positions[row][col] == "O"
        next_col = col + 1
        current_col = col

        while next_col <= positions.first.length && positions[row][next_col] == "."
          positions[row][next_col], positions[row][current_col] =
            positions[row][current_col], positions[row][next_col] 

          next_col += 1
          current_col += 1
        end
      end
    end
  end
end

input = STDIN.read

#input = <<-INPUT
#O....#....
#O.OO#....#
#.....##...
#OO.#O....O
#.O.....O#.
#O.#..O.#.#
#..O..#O..O
#.......O..
##....###..
##OO..#....
#INPUT

positions = input.split("\n").map(&:chars)

tilt_north(positions)

dputs positions.map(&:join).join("\n")

total_load = positions.each.with_index.reduce(0) do |acc, (row, i)|
  row_load = positions.length - i
  acc + (row.count("O") * row_load)
end

puts "Part 1: Load on the north support beams: #{total_load}"

positions = input.split("\n").map(&:chars)

loads = []
cycle = 1
subsequence_length = nil
subsequence = nil

loop do
  tilt_north(positions)
  tilt_west(positions)
  tilt_south(positions)
  tilt_east(positions)

  dputs "After #{cycle} cycles:"
  dputs positions.map(&:join).join("\n")
  dputs

	total_load = positions.each.with_index.reduce(0) do |acc, (row, i)|
		row_load = positions.length - i
		acc + (row.count("O") * row_load)
	end

  loads << total_load

  cycle += 1

  # If there's a repeating subsequence of loads, it means that we've reached an
  # equilibrium and the loads produced won't change any further by doing more
  # simulations
  subsequence_found = false
  subsequence_length = 2

  until subsequence_found || loads.length < subsequence_length * 2 do
    if loads[-subsequence_length * 2, subsequence_length] ==
        loads[-subsequence_length, subsequence_length]
      subsequence = loads[-subsequence_length, subsequence_length]
      subsequence_found = true
    else
      subsequence_length += 1
    end
  end

  break if subsequence_found
end

sequence_index = loads.length - 2 * subsequence_length + 1
subsequence_index = (1_000_000_000 - sequence_index) % subsequence_length

puts "Part 2: Load on the north support beams: #{subsequence[subsequence_index]}"
