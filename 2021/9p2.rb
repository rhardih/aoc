=begin

--- Part Two ---

Next, you need to find the largest basins so you know what areas are most
important to avoid.

A basin is all locations that eventually flow downward to a single low point.
Therefore, every low point has a basin, although some basins are very small.
Locations of height 9 do not count as being in any basin, and all other
locations will always be part of exactly one basin.

The size of a basin is the number of locations within the basin, including the
low point. The example above has four basins.

The top-left basin, size 3:

2199943210
3987894921
9856789892
8767896789
9899965678

The top-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678

The middle basin, size 14:

2199943210
3987894921
9856789892
8767896789
9899965678

The bottom-right basin, size 9:

2199943210
3987894921
9856789892
8767896789
9899965678

Find the three largest basins and multiply their sizes together. In the above
example, this is 9 * 14 * 9 = 1134.

What do you get if you multiply together the sizes of the three largest basins?

=end

require_relative "9"

heightmap = HeightMap.new(
  STDIN.read.split("\n").map { |line| line.split("").map(&:to_i) }
)
risk_levels = heightmap.map { |row| row.map { |value| 1 + value } }

# Fill location and neighboards recursively with value, if not already set
def floodfill(heightmap, basin, row, col)
  # Check if out of bounds or already filled
  if row < 0 || row >= heightmap.height ||
      col < 0 || col >= heightmap.width ||
      heightmap[row][col] > 0 || heightmap[row][col] == -1
    return basin
  end

  heightmap[row][col] = basin

  [[0, -1], [-1, 0], [1, 0], [0, 1]].each do |x_offset, y_offset|
    x = row + x_offset
    y = col + y_offset

    floodfill(heightmap, basin, x, y)
  end

  basin + 1
end

# Pre-fill all locations with -1 if it's not a boundary (9)
heightmap.locations.each do |x, y|
  if heightmap[x][y] == 9
    heightmap[x][y] = -1
  else
    heightmap[x][y] = 0
  end
end

# Try to do a floodfill from each location and keep track of basin number
basin = heightmap.locations.reduce(1) do |basin, location|
  x, y = location
  floodfill(heightmap, basin, x, y)
end

# Count the number of locations that have the values of each basin number
basin_sizes = (1...basin).reduce([]) do |memo, basin_no|
  memo.push(heightmap.map { |row| row.count(basin_no) }.sum)
end

result = basin_sizes.sort.last(3).reduce(&:*)

puts "Product of the sizes of the three largest basins: #{result}"
