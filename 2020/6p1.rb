require "set"

groups = STDIN.read.split("\n\n")
sum = 0

groups.each do |g|
  answers = Set.new
  people = g.split("\n")

  people.each { |p| answers = answers.merge(p.chars) }

  sum += answers.count
end

puts "Sum of counts: #{sum}"
