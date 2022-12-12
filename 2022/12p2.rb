=begin

--- Part Two ---

As you walk up the hill, you suspect that the Elves will want to turn this into
a hiking trail. The beginning isn't very scenic, though; perhaps you can find a
better starting point.

To maximize exercise while hiking, the trail should start as low as possible:
elevation a. The goal is still the square marked E. However, the trail should
still be direct, taking the fewest steps to reach its goal. So, you'll need to
find the shortest path from any square at elevation a to the square marked E.

Again consider the example from above:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Now, there are six choices for starting position (five marked a, plus the
square marked S that counts as being at elevation a). If you start at the
bottom-left square, you can reach the goal most quickly:

...v<<<<
...vv<<^
...v>E^^
.>v>>>^^
>^>>>>>^

This path reaches the goal in only 29 steps, the fewest possible.

What is the fewest steps required to move starting from any square with
elevation a to the location that should get the best signal?

=end

require 'set'

def min(a, b)
  return a if b.nil?
  return b if a.nil?
  a < b ? a : b
end

def shortest_path(from, to, height_map)
  queue = [from]

  visited = Set.new()

  distances = { from => 0 }

  until queue.empty?
    current = queue.shift

    next if visited.include?(current)

    visited.add(current)

    cx = current.x
    cy = current.y
    lx = cx - 1
    ly = cy
    rx = cx + 1
    ry = cy
    ux = cx
    uy = cy - 1
    dx = cx
    dy = cy + 1

    ch = height_map[cy][cx]
    lh = height_map[ly] && height_map[ly][lx]
    rh = height_map[ry] && height_map[ry][rx]
    uh = height_map[uy] && height_map[uy][ux]
    dh = height_map[dy] && height_map[dy][dx]

    unless lh.nil? || lh > ch + 1
      lp = Point.new(lx, ly)

      distances[lp] = min(distances[lp], distances[current] + 1)

      queue.push(lp)
    end

    unless rh.nil? || rh > ch + 1
      rp = Point.new(rx, ry)

      distances[rp] = min(distances[rp], distances[current] + 1)

      queue.push(rp)
    end

    unless uh.nil? || uh > ch + 1
      up = Point.new(ux, uy)

      distances[up] = min(distances[up], distances[current] + 1)

      queue.push(up)
    end

    unless dh.nil? || dh > ch + 1
      dp = Point.new(dx, dy)

      distances[dp] = min(distances[dp], distances[current] + 1)

      queue.push(dp)
    end
  end

  distances[to]
end

height_map = STDIN.read.split("\n").reduce([]) do |arr, line|
  arr.push(line.chars.map(&:ord))
end

width = height_map[0].size
height = height_map.size

Point = Struct.new(:x, :y)

e = nil

for row in 0...height
  for col in 0...width
    if height_map[row][col] == 'E'.ord
      e = Point.new(col,row)
      height_map[row][col] = 'z'.ord
    end
  end
end

shortest_all_paths = nil

for row in 0...height
  for col in 0...width
    if height_map[row][col] == 'a'.ord
      shortest_all_paths = min(shortest_all_paths, shortest_path(Point.new(col, row), e, height_map))
    end
  end
end

puts "Fewest steps required to move from current position location with the best signal: #{shortest_all_paths}"
