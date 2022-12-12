=begin

--- Day 12: Hill Climbing Algorithm ---

You try contacting the Elves using your handheld device, but the river you're
following must be too low to get a decent signal.

You ask the device for a heightmap of the surrounding area (your puzzle input).
The heightmap shows the local area from above broken into a grid; the elevation
of each square of the grid is given by a single lowercase letter, where a is
the lowest elevation, b is the next-lowest, and so on up to the highest
elevation, z.

Also included on the heightmap are marks for your current position (S) and the
location that should get the best signal (E). Your current position (S) has
elevation a, and the location that should get the best signal (E) has elevation
z.

You'd like to reach E, but to save energy, you should do it in as few steps as
possible. During each step, you can move exactly one square up, down, left, or
right. To avoid needing to get out your climbing gear, the elevation of the
destination square can be at most one higher than the elevation of your current
square; that is, if your current elevation is m, you could step to elevation n,
but not to elevation o. (This also means that the elevation of the destination
square can be much lower than the elevation of your current square.)

For example:

Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi

Here, you start in the top-left corner; your goal is near the middle. You could
start by moving down or right, but eventually you'll need to head toward the e
at the bottom. From there, you can spiral around to the goal:

v..v<<<<
>v.vv<<^
.>vv>E^^
..v>>>^^
..>>>>>^

In the above diagram, the symbols indicate whether the path exits each square
moving up (^), down (v), left (<), or right (>). The location that should get
the best signal is still E, and . marks unvisited squares.

This path reaches the goal in 31 steps, the fewest possible.

What is the fewest steps required to move from your current position to the
location that should get the best signal?

=end

require 'set'

def min(a, b)
  return a if b.nil?
  return b if a.nil?
  a < b ? a : b
end

height_map = STDIN.read.split("\n").reduce([]) do |arr, line|
  arr.push(line.chars.map(&:ord))
end

width = height_map[0].size
height = height_map.size

Point = Struct.new(:x, :y)

s = nil
e = nil

for row in 0...height
  for col in 0...width
    if height_map[row][col] == 'S'.ord
      s = Point.new(col, row)
      height_map[row][col] = 'a'.ord
    end

    if height_map[row][col] == 'E'.ord
      e = Point.new(col,row)
      height_map[row][col] = 'z'.ord
    end
  end
end

queue = [s]

visited = Set.new()

distances = { s => 0 }

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

puts "Fewest steps required to move from current position location with the best signal: #{distances[e]}"
