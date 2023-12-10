def find_starting_point(diagram)
  diagram.each.with_index do |row, y|
    row.each.with_index do |col, x|
      return [x, y, 0] if col == "S"
    end
  end

  nil
end

example = <<-INPUT
..F7.
.FJ|.
SJ.L7
|F--J
LJ...
INPUT

diagram = STDIN.read.split("\n").map(&:chars)
# diagram = example.split("\n").map(&:chars)

starting_point = find_starting_point(diagram)

queue = [starting_point]
distances = Array.new(diagram.length) { Array.new(diagram.first.length, nil) }

until queue.empty?
  x, y, distance = queue.shift
  distances[y][x] = distance

  if y > 0 && ["|", "7", "F"].include?(diagram[y - 1][x]) &&
      distances[y - 1][x].nil?
    queue.push([x, y - 1, distance + 1])
  end

  if x > 0 && ["-", "L", "F"].include?(diagram[y][x - 1]) &&
      distances[y][x - 1].nil?
    queue.push([x - 1, y, distance + 1])
  end

  if x < diagram.first.length - 1 && ["-", "J", "7"].include?(diagram[y][x + 1]) &&
      distances[y][x + 1].nil?
    queue.push([x + 1, y, distance + 1])
  end

  if y < diagram.length - 1 && ["|", "J", "L"].include?(diagram[y + 1][x]) &&
      distances[y + 1][x].nil?
    queue.push([x, y + 1, distance + 1])
  end
end

puts "Steps: #{distances.flatten.map { |d| d.nil? ? 0 : d }.max}"
