=begin

--- Part Two ---

Something seems off about your calculation. The cooling rate depends on exterior
surface area, but your calculation also included the surface area of air pockets
trapped in the lava droplet.

Instead, consider only cube sides that could be reached by the water and steam
as the lava droplet tumbles into the pond. The steam will expand to reach as
much as possible, completely displacing any air on the outside of the lava
droplet but never expanding diagonally.

In the larger example above, exactly one cube of air is trapped within the lava
droplet (at 2,2,5), so the exterior surface area of the lava droplet is 58.

What is the exterior surface area of your scanned lava droplet?

=end

space_magnitude = 30 # found by guess

# 0 - Air
# 1 - Lava
# 2 - Steam

space = Array.new(space_magnitude) do
  Array.new(space_magnitude) do
    Array.new(space_magnitude) { 0 }
  end
end

STDIN.read.split("\n").each do |line|
  x, y, z = line.split(",").map(&:to_i)

  space[x][y][z] = 1
end

# Flood fill from outside the droplet, such that we can just count the number of
# sides facing steam (2).

space[0][0][0] = 2

# This is just lazy ... this flood fill should really be recursive or queue
# based, so the steam "flows" into air pockets
# 
# I just guessed at the number of passes here and the results are stable around
# this number of passes
5.times do
  for x in 0...space_magnitude do
    for y in 0...space_magnitude do
      for z in 0...space_magnitude do
        next if space[x][y][z] == 1

        if space[x - 1][y][z] == 2 ||
            space[x + 1][y][z] == 2 ||
            space[x][y - 1][z] == 2 ||
            space[x][y + 1][z] == 2 ||
            space[x][y][z - 1] == 2 ||
            space[x][y][z + 1] == 2
          space[x][y][z] = 2
        end
      end
    end
  end
end

surface_area = 0

for x in 0...space_magnitude do
  for y in 0...space_magnitude do
    for z in 0...space_magnitude do
      next if space[x][y][z] != 1

      if space[x - 1][y][z] == 2
        surface_area += 1
      end

      if space[x + 1][y][z] == 2
        surface_area += 1
      end

      if space[x][y - 1][z] == 2
        surface_area += 1
      end

      if space[x][y + 1][z] == 2
        surface_area += 1
      end

      if space[x][y][z - 1] == 2
        surface_area += 1
      end

      if space[x][y][z + 1] == 2
        surface_area += 1
      end
    end
  end
end

puts "Exterior surface area of scanned lava droplet: #{surface_area}"
