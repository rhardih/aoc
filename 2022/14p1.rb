=begin

--- Day 14: Regolith Reservoir ---

The distress signal leads you to a giant waterfall! Actually, hang on - the
signal seems like it's coming from the waterfall itself, and that doesn't make
any sense. However, you do notice a little path that leads behind the
waterfall.

Correction: the distress signal leads you behind a giant waterfall! There seems
to be a large cave system here, and the signal definitely leads further inside.

As you begin to make your way deeper underground, you feel the ground rumble
for a moment. Sand begins pouring into the cave! If you don't quickly figure
out where the sand is going, you could quickly become trapped!

Fortunately, your familiarity with analyzing the path of falling material will
come in handy here. You scan a two-dimensional vertical slice of the cave above
you (your puzzle input) and discover that it is mostly air with structures made
of rock.

Your scan traces the path of each solid rock structure and reports the x,y
coordinates that form the shape of the path, where x represents distance to the
right and y represents distance down. Each path appears as a single line of
text in your scan. After the first point of each path, each point indicates the
end of a straight horizontal or vertical line to be drawn from the previous
point. For example:

498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9

This scan means that there are two paths of rock; the first path consists of
two straight lines, and the second path consists of three straight lines.
(Specifically, the first path consists of a line of rock from 498,4 through
498,6 and another line of rock from 498,6 through 496,6.)

The sand is pouring into the cave from point 500,0.

Drawing rock as #, air as ., and the source of the sand as +, this becomes:


  4     5  5
  9     0  0
  4     0  3
0 ......+...
1 ..........
2 ..........
3 ..........
4 ....#...##
5 ....#...#.
6 ..###...#.
7 ........#.
8 ........#.
9 #########.

Sand is produced one unit at a time, and the next unit of sand is not produced
until the previous unit of sand comes to rest. A unit of sand is large enough
to fill one tile of air in your scan.

A unit of sand always falls down one step if possible. If the tile immediately
below is blocked (by rock or sand), the unit of sand attempts to instead move
diagonally one step down and to the left. If that tile is blocked, the unit of
sand attempts to instead move diagonally one step down and to the right. Sand
keeps moving as long as it is able to do so, at each step trying to move down,
then down-left, then down-right. If all three possible destinations are
blocked, the unit of sand comes to rest and no longer moves, at which point the
next unit of sand is created back at the source.

So, drawing sand that has come to rest as o, the first unit of sand simply
falls straight down and then stops:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
........#.
......o.#.
#########.

The second unit of sand then falls straight down, lands on the first one, and
then comes to rest to its left:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
........#.
.....oo.#.
#########.

After a total of five units of sand have come to rest, they form this pattern:

......+...
..........
..........
..........
....#...##
....#...#.
..###...#.
......o.#.
....oooo#.
#########.

After a total of 22 units of sand:

......+...
..........
......o...
.....ooo..
....#ooo##
....#ooo#.
..###ooo#.
....oooo#.
...ooooo#.
#########.

Finally, only two more units of sand can possibly come to rest:

......+...
..........
......o...
.....ooo..
....#ooo##
...o#ooo#.
..###ooo#.
....oooo#.
.o.ooooo#.
#########.

Once all 24 units of sand shown above have come to rest, all further sand flows
out the bottom, falling into the endless void. Just for fun, the path any new
sand takes before falling forever is shown here with ~:

.......+...
.......~...
......~o...
.....~ooo..
....~#ooo##
...~o#ooo#.
..~###ooo#.
..~..oooo#.
.~o.ooooo#.
~#########.
~..........
~..........
~..........

Using your scan, simulate the falling sand. How many units of sand come to rest
before sand starts flowing into the abyss below?

=end

require 'matrix'

paths = STDIN.read.split("\n").reduce([]) do |acc, line|
  acc << line.split(" -> ").map { |xy| xy.split(",").map(&:to_i) }
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

# normalize x
paths.each do |path|
  path.each do |coordinate|
    coordinate[0] -= min_x
  end
end

drawing = Matrix.build(max_y + 1, max_x - min_x + 1) { "." }

paths.each do |path|
  for i in 1...path.size do
    x0, y0 = path[i - 1]
    x1, y1 = path[i]

    xrange = x0 < x1 ? x0..x1 : x1..x0
    yrange = y0 < y1 ? y0..y1 : y1..y0

    drawing[yrange, xrange] = "#"
  end
end

overflowing = false

until overflowing
  current_x = 500 - min_x
  current_y = 0

  loop do
    if current_x < 0
      overflowing = true
      break
    end

    if drawing[current_y + 1, current_x] == "."
      current_y += 1
    else
      if drawing[current_y + 1, current_x - 1] == "."
        current_x -= 1
        current_y += 1
      elsif drawing[current_y + 1, current_x + 1] == "."
        current_x += 1
        current_y += 1
      else
        drawing[current_y, current_x] = "o"
        break
      end
    end
  end

  puts drawing.to_a.map(&:join).join("\n")
end

puts "Units of sand: #{drawing.to_a.flatten.count("o")}"
