count = STDIN.read.split("\n").inject(0) do |acc, l|
  acc + l.length - l.undump.length
end

puts "Result #{count}"
