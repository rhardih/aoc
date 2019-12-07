orbits = Hash.new

STDIN.read.split("\n") do |line|
  object0, object1 = line.split(")")
  orbits[object1] = object0
end

youpath = []
current = orbits["YOU"]

while current != "COM"
  youpath << current
  current = orbits[current]
end

sanpath = []
current = orbits["SAN"]

while current != "COM"
  sanpath << current
  current = orbits[current]
end

common_ancestors = youpath & sanpath
transfers = youpath.index(common_ancestors.first) +
  sanpath.index(common_ancestors.first)

puts "Minimum number of orbital transfers required: #{transfers}"
