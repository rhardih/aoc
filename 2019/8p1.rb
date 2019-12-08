layers = STDIN.read.chomp.split("").each_slice(6 * 25).sort do |a, b|
  a.count("0") <=> b.count("0")
end

multiple = layers.first.count("1") * layers.first.count("2")
puts "Number of 1 digits multiplied by the number of 2 digits: #{multiple}"
