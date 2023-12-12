=begin

--- Part Two ---

The galaxies are much older (and thus much farther apart) than the researcher
initially estimated.

Now, instead of the expansion you did before, make each empty row or column one
million times larger. That is, each empty row should be replaced with 1000000
empty rows, and each empty column should be replaced with 1000000 empty columns.

(In the example above, if each empty row or column were merely 10 times larger,
the sum of the shortest paths between every pair of galaxies would be 1030. If
each empty row or column were merely 100 times larger, the sum of the shortest
paths between every pair of galaxies would be 8410. However, your universe will
need to expand far beyond these values.)

Starting with the same initial image, expand the universe according to these new
rules, then find the length of the shortest path between every pair of galaxies.
What is the sum of these lengths?

=end

require 'matrix'

def print(from, to, distances)
  puts "Between galaxy #{from} and galaxy #{to}: #{distances[from - 1][to - 1]}"
end

input = STDIN.read

#input = <<-INPUT
#...#......
#.......#..
##.........
#..........
#......#...
#.#........
#.........#
#..........
#.......#..
##...#.....
#INPUT

image = Matrix.rows(input.split("\n").map(&:chars))

def offsets(vectors)
  offset = 0
  vectors.map do |vector|
    offset += 999999 if vector.all? { |e| e == "." }
    offset
  end
end

row_offsets = offsets(image.row_vectors)
col_offsets = offsets(image.column_vectors)

coordinates = []

(0...image.row_count).each do |row|
  (0...image.column_count).each do |col|
    if image[row, col] == "#"
      coordinates << [row + row_offsets[row], col + col_offsets[col]]
    end
  end
end

# Build up distance matrix for each galaxy pair
distances = coordinates.map do |s_row, s_col|
  coordinates.map do |d_row, d_col|
    (d_row - s_row).abs + (d_col - s_col).abs
  end
end

# print(5, 9, distances)
# print(1, 7, distances)
# print(3, 6, distances)
# print(8, 9, distances)

sum = (0...distances.length).reduce(0) do |i_acc, i|
  i_acc + ((i + 1)...distances.length).reduce(0) do |j_acc, j|
    j_acc + distances[i][j]
  end
end

puts "Sum of lengths: #{sum}"
