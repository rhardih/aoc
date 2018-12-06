def mdist(x0, y0, x1, y1)
  (x0 - x1).abs + (y0 - y1).abs
end

points = []

STDIN.read.split("\n").each do |line|
  a, b = line.split(", ")
  x = a.to_i
  y = b.to_i

  points << { x: x, y: y }
end

size = points.map { |p| [p[:x], p[:y]].max }.max + 1
plane = Array.new(size, &-> _ { Array.new(size, 0) })
area = 0

plane.each_with_index do |row, i|
  row.each_with_index do |col, j|
    sum = 0
    points.each { |p| sum += mdist(p[:x], p[:y], j, i) }
    area += 1 if sum > 0 && sum < 10000
  end
end

puts "Size of the region containing all locations which have a total distance to all given coordinates of less than 10000: #{area}"
