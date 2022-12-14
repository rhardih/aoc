=begin

--- Part Two ---

You realize you misread the scan. There isn't an endless void at the bottom of
the scan - there's floor, and you're standing on it!

You don't have time to scan the floor, so assume the floor is an infinite
horizontal line with a y coordinate equal to two plus the highest y coordinate
of any point in your scan.

In the example above, the highest y coordinate of any point is 9, and so the
floor is at y=11. (This is as if your scan contained one extra rock path like
-infinity,11 -> infinity,11.) With the added floor, the example above now looks
like this:

        ...........+........
        ....................
        ....................
        ....................
        .........#...##.....
        .........#...#......
        .......###...#......
        .............#......
        .............#......
        .....#########......
        ....................
<-- etc #################### etc -->

To find somewhere safe to stand, you'll need to simulate falling sand until a
unit of sand comes to rest at 500,0, blocking the source entirely and stopping
the flow of sand into the cave. In the example above, the situation finally
looks like this after 93 units of sand come to rest:

............o............
...........ooo...........
..........ooooo..........
.........ooooooo.........
........oo#ooo##o........
.......ooo#ooo#ooo.......
......oo###ooo#oooo......
.....oooo.oooo#ooooo.....
....oooooooooo#oooooo....
...ooo#########ooooooo...
..ooooo.......ooooooooo..
#########################

Using your scan, simulate the falling sand until the source of the sand becomes
blocked. How many units of sand come to rest?

=end

require 'matrix'

paths = []

STDIN.read.split("\n").each do |line|
  paths << line.split(" -> ").map { |xy| xy.split(",").map(&:to_i) }
end

min_x = 10_000
max_x = 0
max_y = 0

# Find bounds 
paths.each do |path|
  path.each do |coordinate|
    min_x = coordinate[0] if coordinate[0] < min_x
    max_x = coordinate[0] if coordinate[0] > max_x
    max_y = coordinate[1] if coordinate[1] > max_y
  end
end

# This time around, just make the drawing bigger and move the whole thing to the
# right
offset = 100

# normalize x
paths.each do |path|
  path.each do |coordinate|
    coordinate[0] = coordinate[0] - min_x + offset
  end
end

# Add some more 
drawing = Matrix.build(max_y + 1 + 2, max_x - min_x + 1 + 300) { "." }

paths.each do |path|
  for i in 1...path.size do
    x0, y0 = path[i - 1]
    x1, y1 = path[i]

    xrange = x0 < x1 ? x0..x1 : x1..x0
    yrange = y0 < y1 ? y0..y1 : y1..y0

    drawing[yrange, xrange] = "#"
  end
end

drawing[drawing.row_count - 1, 0..-1] = "#"

overflowing = false

# Add grain of sand
until overflowing
  current_x = 500 - min_x + offset
  current_y = 0

  loop do
    if current_x < 0
      overflowing = true
      break
    end

    if drawing[current_y + 1, current_x] == "."
      current_y += 1
    else
      # must be either rock or sand

      if drawing[current_y + 1, current_x - 1] == "."
        # try one step down and to the left

        current_x -= 1
        current_y += 1
      elsif drawing[current_y + 1, current_x + 1] == "."
        # try one step down and to the right

        current_x += 1
        current_y += 1
      else
        # nowhere to go rest here

        drawing[current_y, current_x] = "o"
        break
      end
    end
  end

  break if current_y == 0
end

puts "Units of sand: #{drawing.to_a.flatten.count("o")}"

