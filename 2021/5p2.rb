=begin

--- Part Two ---

Unfortunately, considering only horizontal and vertical lines doesn't give you
the full picture; you need to also consider diagonal lines.

Because of the limits of the hydrothermal vent mapping system, the lines in
your list will only ever be horizontal, vertical, or a diagonal line at exactly
45 degrees. In other words:

An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.

Considering all lines from the above example would now produce the following
diagram:

1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....

You still need to determine the number of points where at least two lines
overlap. In the above example, this is still anywhere in the diagram with a 2
or larger - now a total of 12 points.

Consider all of the lines. At how many points do at least two lines overlap?

=end

def print(diagram)
  diagram = diagram.transpose

  rows = diagram.map do |row|
    row.map { |value| value == 0 ? '.' : value.to_s }.join
  end

  puts rows.join("\n")
end

segments = []
dimension = 0

STDIN.readlines.map(&:split).each do |from, _, to|
  x1, y1 = from.split(',').map(&:to_i)
  x2, y2 = to.split(',').map(&:to_i)

  segments << [x1, y1, x2, y2]
  dimension = [dimension, x1, y1, x2, y2].max
end

diagram = Array.new(dimension + 1) { Array.new(dimension + 1, 0) }

segments.each do |x1, y1, x2, y2|
  # Generate range of x and y coordinates
  x_range = x1 < x2 ? (x1..x2).to_a : (x2..x1).to_a.reverse
  y_range = y1 < y2 ? (y1..y2).to_a : (y2..y1).to_a.reverse

  # Make x,y tuples
  if x_range.size > y_range.size
    coordinates = x_range.zip(y_range)
  else
    coordinates = y_range.zip(x_range)
  end

  # Backfill nils from zip
  coordinates.each_with_index do |c, i|
    x, y = c
    coordinates[i][0] = coordinates[i - 1][0] if x.nil?
    coordinates[i][1] = coordinates[i - 1][1] if y.nil?
  end

  coordinates.each { |x, y| diagram[x][y] += 1 }
end

# print(diagram)

overlaps = diagram.reduce(0) do |acc, row|
  acc + row.count { |value| value >= 2 }
end

puts "Number of points where at least two lines overlap: #{overlaps}"
