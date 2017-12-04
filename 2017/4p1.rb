count = 0

STDIN.read.split("\n").each do |l|
  words = l.split(" ")

  count += 1 if words.uniq.length == words.length
end

puts count
