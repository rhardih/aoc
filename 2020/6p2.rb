require "set"

groups = STDIN.read.split("\n\n")
sum = 0

groups.each do |g|
  answers = []
  people = g.split("\n")

  people.each { |p| answers << p.chars.to_set }
  answers = answers.reduce { |a, b| a & b }

  sum += answers.count
end

puts "Sum of counts: #{sum}"
