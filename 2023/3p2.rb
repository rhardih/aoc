=begin

--- Part Two ---

The engineer finds the missing part and installs it in the engine! As the
engine springs to life, you jump in the closest gondola, finally ready to
ascend to the water source.

You don't seem to be going very fast, though. Maybe something is still wrong?
Fortunately, the gondola has a phone labeled "help", so you pick it up and the
engineer answers.

Before you can explain the situation, she suggests that you look out the
window. There stands the engineer, holding a phone in one hand and waving with
the other. You're going so slowly that you haven't even left the station. You
exit the gondola.

The missing part wasn't the only issue - one of the gears in the engine is
wrong. A gear is any * symbol that is adjacent to exactly two part numbers. Its
gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all up so
that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. The first is in the top left; it has
part numbers 467 and 35, so its gear ratio is 16345. The second gear is in the
lower right; its gear ratio is 451490. (The * adjacent to 617 is not a gear
because it is only adjacent to one part number.) Adding up all of the gear
ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?

=end

schematic = STDIN.read.split("\n").map { |line| line.split("") }
included = Array.new(schematic.length) do
  Array.new(schematic.first.length) { false }
end

asterisks = []

schematic.each_index do |i|
  line = schematic[i]

  number = ""

  line.each_index do |j|
    case line[j]
    when /\d/

    when "*"
      asterisks << [i, j]

      included[i - 1][j - 1] = i > 0 && j > 0
      included[i - 1][j] = i > 0
      included[i - 1][j + 1] = i > 0 && j < line.length - 1

      included[i][j - 1] = j > 0
      included[i][j] = true
      included[i][j + 1] = j < line.length - 1

      included[i + 1][j - 1] = i < schematic.length - 1 && j > 0
      included[i + 1][j] = i < schematic.length - 1
      included[i + 1][j + 1] = i < schematic.length - 1 && j < line.length - 1
    end
  end
end

numbers = []

schematic.each_index do |i|
  line = schematic[i]

  keep = false
  number = ""
  coords = []

  reset = -> do
    keep = false
    number = ""
    coords = []
  end

  line.each_index do |j|
    case line[j]
    when /\d/
      number << line[j]
      keep = true if included[i][j]
      coords << [i, j]
    else
      numbers << [number.to_i, coords] if number != "" && keep

      reset.call
    end
  end

  numbers << [number.to_i, coords] if number != "" && keep

  reset.call
end

pp numbers

foo = asterisks.map do |i, j|
  candidates = numbers.select do |number, coords|
    # Is any of the numbers coordinates next to an asterisk?
    coords.any? do |row, col|
      (row - 1 == i && col - 1 == j) ||
      (row == i && col - 1 == j) ||
      (row + 1 == i && col - 1 == j) ||

      (row - 1 == i && col == j) ||
      (row == i && col == j) ||
      (row + 1 == i && col == j) ||

      (row - 1 == i && col + 1 == j) ||
      (row == i && col + 1 == j) ||
      (row + 1 == i && col + 1 == j)
    end
  end

  keys = candidates.map(&:first)

  if keys.length == 2
    keys.first.to_i * keys.last.to_i
  else
    0
  end
end

puts "Result: #{foo.sum}"
