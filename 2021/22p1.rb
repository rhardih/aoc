=begin

=end

core = Array.new(101) { Array.new(101) { Array.new(101) { false } } }

STDIN.read.split("\n").each do |line|
  on = nil

  case line
  when /on x=(.+),y=(.+),z=(.+)/
    on = true
  when /off x=(.+),y=(.+),z=(.+)/
    on = false
  end

  x_range = eval($1)
  y_range = eval($2)
  z_range = eval($3)

  next if x_range.begin < -50
  next if x_range.end > 50
  next if y_range.begin < -50
  next if y_range.end > 50
  next if z_range.begin < -50
  next if z_range.end > 50

  x_range.each do |x|
    y_range.each do |y|
      z_range.each do |z|
        core[x + 50][y + 50][z + 50] = on
      end
    end
  end
end

puts "Number of cubes that are on after reboot: #{core.flatten.count(&:itself)}"
