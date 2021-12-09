=begin

--- Day 9: Smoke Basin ---

These caves seem to be lava tubes. Parts are even still volcanically active;
small hydrothermal vents release smoke into the caves that slowly settles like
rain.

If you can model how the smoke flows through the caves, you might be able to
avoid it and be that much safer. The submarine generates a heightmap of the
floor of the nearby caves for you (your puzzle input).

Smoke flows to the lowest point of the area it's in. For example, consider the
following heightmap:

2199943210
3987894921
9856789892
8767896789
9899965678

Each number corresponds to the height of a particular location, where 9 is the
highest and 0 is the lowest a location can be.

Your first goal is to find the low points - the locations that are lower than
any of its adjacent locations. Most locations have four adjacent locations (up,
down, left, and right); locations on the edge or corner of the map have three
or two adjacent locations, respectively. (Diagonal locations do not count as
adjacent.)

In the above example, there are four low points, all highlighted: two are in
the first row (a 1 and a 0), one is in the third row (a 5), and one is in the
bottom row (also a 5). All other locations on the heightmap have some lower
adjacent location, and so are not low points.

The risk level of a low point is 1 plus its height. In the above example, the
risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of
all low points in the heightmap is therefore 15.

Find all of the low points on your heightmap. What is the sum of the risk
levels of all low points on your heightmap?

=end

class HeightMap < Array
  attr_reader :width
  attr_reader :height

  def initialize(*args)
    super

    @width = self[0].size
    @height = self.size
  end

  def locations
    (0...width).to_a.product((0...height).to_a)
  end
end

heightmap = HeightMap.new(
  STDIN.read.split("\n").map { |line| line.split("").map(&:to_i) }
)
risk_levels = heightmap.map { |row| row.map { |value| 1 + value } }

# Gives a list of neighbouring values for a given location
def adj(heightmap, row, col)
  [[0, -1], [-1, 0], [1, 0], [0, 1]].reduce([]) do |acc, offset|
    x_offset, y_offset = offset
    x = row + x_offset
    y = col + y_offset

    if x < 0 || x >= heightmap.width ||
        y < 0 || y >= heightmap.height
      acc
    else
      acc.push(heightmap[x][y])
    end
  end
end

# Whether a given locations value is the lowest among neighbours
def is_lowest?(heightmap, row, col)
  adj(heightmap, row, col).all? do |adj_value|
    heightmap[row][col] < adj_value
  end
end

sum = heightmap.locations.reduce(0) do |acc, location|
  x, y = location
  acc + (is_lowest?(heightmap, x, y) ? risk_levels[x][y] : 0)
end

puts "Sum of the risk of all low points: #{sum}"
