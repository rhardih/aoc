=begin

--- Part Two ---

Content with the amount of tree cover available, the Elves just need to know the
best spot to build their tree house: they would like to be able to see a lot of
trees.

To measure the viewing distance from a given tree, look up, down, left, and
right from that tree; stop if you reach an edge or at the first tree that is the
same height or taller than the tree under consideration. (If a tree is right on
the edge, at least one of its viewing distances will be zero.)

The Elves don't care about distant trees taller than those found by the rules
above; the proposed tree house has large eaves to keep it dry, so they wouldn't
be able to see higher than the tree house anyway.

In the example above, consider the middle 5 in the second row:

30373
25512
65332
33549
35390

- Looking up, its view is not blocked; it can see 1 tree (of height 3).
- Looking left, its view is blocked immediately; it can see only 1 tree (of
height 5, right next to it).
- Looking right, its view is not blocked; it can see 2 trees.
- Looking down, its view is blocked eventually; it can see 2 trees (one of
height 3, then the tree of height 5 that blocks its view).

A tree's scenic score is found by multiplying together its viewing distance in
each of the four directions. For this tree, this is 4 (found by multiplying 1 *
1 * 2 * 2).

However, you can do even better: consider the tree of height 5 in the middle of the fourth row:

30373
25512
65332
33549
35390

- Looking up, its view is blocked at 2 trees (by another tree with a height of
5).
- Looking left, its view is not blocked; it can see 2 trees.
- Looking down, its view is also not blocked; it can see 1 tree.
- Looking right, its view is blocked at 2 trees (by a massive tree of height 9).

This tree's scenic score is 8 (2 * 2 * 1 * 2); this is the ideal spot for the
tree house.

Consider each tree on your map. What is the highest scenic score possible for
any tree?

=end

require 'matrix'

def visible?(map, x, y, height)
  return true if y == 0 || y == map.row_count - 1
  return true if x == 0 || x == map.row(0).size - 1

  row_arr = map.row(y).to_a
  left = row_arr[0...x]
  right = row_arr[(x + 1)..-1]
  col_arr = map.column(x).to_a
  up = col_arr[0...y]
  down = col_arr[(y + 1)..-1]

  return true if left.all? { |h| h < height }
  return true if right.all? { |h| h < height }
  return true if up.all? { |h| h < height }
  return true if down.all? { |h| h < height }

  false
end

def scenic_score(map, x, y, height)
  up = 0
  down = 0
  left = 0
  right = 0

  (y - 1).downto(0) do |y|
    up += 1

    break if map[y, x] >= height
  end

  (y + 1).upto(map.row_count - 1) do |y|
    down += 1

    break if map[y, x] >= height
  end

  (x - 1).downto(0) do |x|
    left += 1

    break if map[y, x] >= height
  end

  (x + 1).upto(map.row(0).size - 1) do |x|
    right += 1

    break if map[y, x] >= height
  end

  up * down * left * right
end

data = STDIN.read.split("\n").reduce([]) do |arr, line|
  arr.push([*line.chars.map(&:to_i)])
end

map = Matrix.rows(data)

max = map.each_with_index.reduce(0) do |acc, el|
  height, row, col = el

  score = scenic_score(map, col, row, height)

  acc = score if score > acc

  acc
end

puts "Highest scenic score possible for any tree: #{max}"
