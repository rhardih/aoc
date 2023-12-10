def find_starting_point(diagram)
  diagram.each.with_index do |row, y|
    row.each.with_index do |col, x|
      return [x, y, 0, nil] if col == "S"
    end
  end

  nil
end

input = STDIN.read

# input = <<-INPUT
# .F----7F7F7F7F-7....
# .|F--7||||||||FJ....
# .||.FJ||||||||L7....
# FJL7L7LJLJ||LJ.L-7..
# L--J.L7...LJS7F-7L7.
# ....F-J..F7FJ|L7L7L7
# ....L7.F7||L7|.L7L7|
# .....|FJLJ|FJ|F7|.LJ
# ....FJL-7.||.||||...
# ....L---J.LJ.LJLJ...
# INPUT

# input = <<-INPUT
# ...........
# .S-------7.
# .|F-----7|.
# .||.....||.
# .||.....||.
# .|L-7.F-J|.
# .|..|.|..|.
# .L--J.L--J.
# ...........
# INPUT

diagram = input.split("\n").map(&:chars)

width = diagram.first.length
height = diagram.length
inout = Array.new(height) { Array.new(width, nil) }

for row in 0...height
  for col in 0...width
    inout[row][col] = diagram[row][col]
  end
end

starting_point = find_starting_point(diagram)

queue = [starting_point]
distances = Array.new(diagram.length) { Array.new(width, nil) }
visited = Array.new(diagram.length) { Array.new(width, false) }

until queue.empty?
  x, y, distance = queue.shift
  distances[y][x] = distance
  visited[y][x] = true

  if y > 0 && ["|", "7", "F"].include?(diagram[y - 1][x]) &&
      distances[y - 1][x].nil?
    queue.push([x, y - 1, distance + 1])
  end

  if x > 0 && ["-", "L", "F"].include?(diagram[y][x - 1]) &&
      distances[y][x - 1].nil?
    queue.push([x - 1, y, distance + 1])
  end

  if x < width - 1 && ["-", "J", "7"].include?(diagram[y][x + 1]) &&
      distances[y][x + 1].nil?
    queue.push([x + 1, y, distance + 1])
  end

  if y < diagram.length - 1 && ["|", "J", "L"].include?(diagram[y + 1][x]) &&
      distances[y + 1][x].nil?
    queue.push([x, y + 1, distance + 1])
  end
end

# For each ground point "." and going in a fixed direction, figure out how many
# intersections will happen with the pipe. If the point is inside the pipe, it
# should be an odd number of times.
for row in 0...height
  for col in 0...width
    next if diagram[row][col] != "."

    j_started = false;
    s_started = false;
    intersections = 0

    for x in (col - 1).downto(0)
      next unless visited[row][x]

      piece = diagram[row][x]

      # Note: Only count "bends" that go in an S shape, U shapes doesn't need to
      # be counted as an intersection, because the point can't change
      # inside/outside status from it. 
      #
      # Not counted
      # - LJ
      # - F7
      #
      # Counted
      # - L7
      # - FJ
      case piece
      when "|"
        intersections += 1
      when "L"
        intersections += 1 if s_started

        j_started = false
        s_started = false
      when "J"
        j_started = true;
      when "7"
        s_started = true
      when "F"
        intersections += 1 if j_started

        j_started = false
        s_started = false
      when "S"
        if j_started
          intersections += 1 if ["|", "L","J"].include?(diagram[row + 1][x])

          j_started = false
        elsif s_started
          intersections += 1 if ["|", "F","7"].include?(diagram[row - 1][x])

          s_started = false
        else
          # S must be a "|"
          intersections += 1
        end
      end
    end

    if intersections.odd?
      inout[row][col] ="I"
    else
      inout[row][col] ="O"
    end
  end
end

puts inout.map(&:join).join("\n")

puts "Tiles which are enclosed by the loop: #{inout.flatten.count("I")}"

# Too low
# 272
# 275
