twos = 0
threes = 0

STDIN.read.split("\n").each do |id|
  counts = Hash.new(0)

  id.split("").each { |letter| counts[letter] += 1 }

  twos += 1 if counts.select { |k, v| v == 2 }.any?
  threes += 1 if counts.select { |k, v| v == 3 }.any?
end

puts twos * threes
