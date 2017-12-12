groups = Hash.new([])

STDIN.read.split("\n").each do |l|
  tmp = l.tr(',', '')
  id, _, *other = tmp.split(" ")

  groups[id] = [id]

  other.each do |oid|
    groups[id] << oid
    groups[oid] << id
  end
end

tmp = groups.select do |k, v|
  v.include?("0")
end

# connections of 1st degree
zero, *stack = tmp.values.flatten.uniq
count = 1
counted = ["0"]

while stack.any?
  current = stack.pop

  next if counted.include?(current)

  count += 1
  counted << current

  _self, *connections = groups[current]

  connections.each { |c| stack.push(c) }
end

puts "Programs in group that contains program 0: #{count}"
