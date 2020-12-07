rules = STDIN.read.split("\n")
bags = Hash.new

rules.each do |rule|
  color, content = rule.split(" bags contain ")
  bags[color] = []

  content.split(", ").each do |part|
    /^(\d+?) (.+?) bags?\.?$/ =~ part

    bags[color] << { count: $1, color: $2 } unless $1.nil? || $2.nil?
  end
end

contains = -> (color) do
  1 + bags[color].map do |b|
    b[:count].to_i * contains.call(b[:color])
  end.sum
end

puts "Number of individual bags required inside the single " \
  "shiny gold bag: #{contains.call("shiny gold") - 1}"
