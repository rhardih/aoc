=begin

--- Part Two ---

The tile floor in the lobby is meant to be a living art exhibit. Every day, the
tiles are all flipped according to the following rules:

Any black tile with zero or more than 2 black tiles immediately adjacent to it
is flipped to white.

Any white tile with exactly 2 black tiles immediately adjacent to it is flipped
to black.

Here, tiles immediately adjacent means the six tiles directly touching the tile
in question.

The rules are applied simultaneously to every tile; put another way, it is first
determined which tiles need to be flipped, then they are all flipped at the same
time.

In the above example, the number of black tiles that are facing up after the
given number of days has passed is as follows:

Day 1: 15
Day 2: 12
Day 3: 25
Day 4: 14
Day 5: 23
Day 6: 28
Day 7: 41
Day 8: 37
Day 9: 49
Day 10: 37

Day 20: 132
Day 30: 259
Day 40: 406
Day 50: 566
Day 60: 788
Day 70: 1106
Day 80: 1373
Day 90: 1844
Day 100: 2208

After executing this process a total of 100 times, there would be 2208 black
tiles facing up.

How many tiles will be black after 100 days?

=end

lines = STDIN.read.split("\n")

GRID_SIZE = 150
DAYS = 100

blacks = 0

grid = Array.new(GRID_SIZE) do
  Array.new(GRID_SIZE) do
    Array.new(GRID_SIZE, :white)
  end
end

lines.each do |line|
  x = y = z = GRID_SIZE / 2

  loop do
    case line
    when /^w/
      x -= 1
      y += 1
      line = line[1..-1]
    when /^e/
      x += 1
      y -= 1
      line = line[1..-1]
    when /^se/
      z += 1
      y -= 1
      line = line[2..-1]
    when /^sw/
      x -= 1
      z += 1
      line = line[2..-1]
    when /^nw/
      z -= 1
      y += 1
      line = line[2..-1]
    when /^ne/
      x += 1
      z -= 1
      line = line[2..-1]
    end

    break if line.empty?
  end

  if grid[x][y][z] == :white
    grid[x][y][z] = :black
    blacks += 1
  else
    grid[x][y][z] = :white
    blacks -= 1
  end
end


adjecent_blacks = lambda do |g,x,y,z|
  b = 0

  if x > 0 && y < GRID_SIZE - 1
    # w
    b += 1 if g[x - 1][y + 1][z] == :black
  end
  if x < GRID_SIZE - 1 && y > 0
    # e
    b += 1 if g[x + 1][y - 1][z] == :black
  end
  if y > 0 && z < GRID_SIZE - 1
    # se
    b += 1 if g[x][y - 1][z + 1] == :black
  end
  if x > 0 && z < GRID_SIZE - 1
    # sw
    b += 1 if g[x - 1][y][z + 1] == :black
  end
  if y < GRID_SIZE - 1 && z > 0
    # nw
    b += 1 if g[x][y + 1][z - 1] == :black
  end
  if x < GRID_SIZE - 1 && z > 0
    # ne
    b += 1 if g[x + 1][y][z - 1] == :black
  end

  b
end

copy = lambda do |g|
  Array.new(GRID_SIZE) do |x|
    Array.new(GRID_SIZE) do |y|
      Array.new(GRID_SIZE) do |z|
        g[x][y][z]
      end
    end
  end
end

DAYS.times do |i|
  grid_copy = copy.call(grid)

  (0...GRID_SIZE).each do |x|
    (0...GRID_SIZE).each do |y|
      (0...GRID_SIZE).each do |z|
        ab = adjecent_blacks.call(grid_copy, x,y,z)

        if grid_copy[x][y][z] == :black && (ab == 0 || ab > 2)
          grid[x][y][z] = :white
          blacks -= 1
        end

        if grid_copy[x][y][z] == :white && ab == 2
          grid[x][y][z] = :black
          blacks += 1
        end
      end
    end
  end

  # puts "Day #{i + 1}: #{blacks}"
end

puts "#{blacks} tiles will be black after 100 days?"
