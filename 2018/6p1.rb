require 'set'

def mdist(x0, y0, x1, y1)
  (x0 - x1).abs + (y0 - y1).abs
end

def closest(x, y, points)
  distances = {}

  # Calculate distance from x,y to all points and store the two closest
  points.each { |k, v| distances[k] = mdist(v[:x], v[:y], x, y) }
  p, q = distances.min_by(2) { |_, v| v }

  # Default to not being closest to any point
  letter = "."

  # Choose a specific point, if it's closer than the second closest
  if p[1] < q[1]
    letter = p[0]
  end

  letter
end

points = {}
letter = "A"

lines = STDIN.read.split("\n")

lines.each do |line|
  a, b = line.split(", ")
  x = a.to_i
  y = b.to_i

  point = { x: x, y: y }
  points[letter] = point
  letter = letter.next
end

size = points.map { |_, p| [p[:x], p[:y]].max }.max + 1
plane = Array.new(size, &-> (_) { Array.new(size, ".") })

# Assign points
points.each do |letter, p|
  plane[p[:y]][p[:x]] = letter
end

areas = Hash.new(0)
edge_points = Set.new

plane.each_with_index do |row, i|
  row.each_with_index do |col, j|
    # Skip source points
    next if plane[j][i] != "."

    # Swap coordinates here, because we traverse in row order, but test in
    # column order
    letter = closest(i, j, points)
    plane[j][i] = letter.downcase

    if i == 0 || i == size - 1 || j == 0 || j == size - 1
      edge_points << letter.upcase
    end
  end
end

plane.each do |row|
  row.each do |letter|
    unless edge_points.include?(letter.upcase)
      areas[letter.upcase] += 1
    end
  end
end

largest = areas.max_by { |k, v| v }
puts "Size of the largest area (#{largest[0]}): #{largest[1]}"
