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

map = STDIN.read.split("\n").map { |line| line.split("").map(&:to_i) }
risk_levels = map.map { |row| row.map { |value| 1 + value } }

@rows = map.size
@cols = map[0].size
@basin = 1

def flow(map, row, col)
  return false if row < 0 || row >= @rows || col < 0 || col >= @cols
  return false if map[row][col] > 0 || map[row][col] == -1 # already marked

  # Up, left, right, down
  coords = [[0, -1], [-1, 0], [1, 0], [0, 1]]

  map[row][col] = @basin

  coords.each do |x_offset, y_offset|
    x = row + x_offset
    y = col + y_offset

    flow(map, x, y)
  end

  true
end

def is_lowest?(map, row, col)
  adj(map, row, col).all? { |adj_value| map[row][col] < adj_value }
end

(0...@rows).each do |x|
  (0...@cols).each do |y|
    if map[x][y] == 9
      map[x][y] = -1
    else
      map[x][y] = 0
    end
  end
end

(0...@rows).each do |x|
  (0...@cols).each do |y|
    @basin += 1 if flow(map, x, y)
  end
end

basin_sizes = []

(1...@basin).each do |basin_no|
  basin_sizes << map.map { |row| row.count(basin_no) }.sum
end

result = basin_sizes.sort[-3..-1].reduce(&:*)

puts "Product of the sizes of the three largest basins: #{result}"
