orbits = Hash.new
total = 0

STDIN.read.split("\n") do |line|
  object0, object1 = line.split(")")
  orbits[object1] = object0
end

orbits.each do |object, _|
  current = object

  while current != "COM"
    total += 1
    current = orbits[current]
  end
end

puts "Total number of direct and indirect orbits: #{total}"
