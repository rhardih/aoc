gen0 = Proc.new { |h, k| h[k] = Hash.new(0) }
gen1 = Proc.new { |h, k| h[k] = Hash.new(&gen0) }
grids = Hash.new(&gen1)

combined = 2**64

STDIN.read.split("\n").each_with_index do |line, index|
  x = 0
  y = 0
  steps = 1

  grids[index][0][0] = 1

  line.split(",").each do |step|
    direction = step[0]
    distance = step[1..-1].to_i

    while distance > 0
      case direction
      when "U"
        y += 1
      when "R"
        x += 1
      when "D"
        y -= 1
      when "L"
        x -= 1
      end

      grids[index][x][y] = steps

      if index == 1 && x != 0 && y != 0 &&
          grids[0][x][y] > 0 &&
          grids[1][x][y] > 0

        tmp = grids[0][x][y] + grids[1][x][y]
        combined = tmp if tmp < combined
      end

      steps += 1
      distance -= 1
    end
  end
end

puts "Manhattan distance from the central port to the closest intersection: #{combined}"
