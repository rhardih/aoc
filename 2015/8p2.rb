count = STDIN.read.split("\n").inject(0) do |acc, l|
  acc + l.dump.length - l.length
end

puts "Result #{count}"
