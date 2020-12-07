rules = STDIN.read.split("\n")
bags = Hash.new

rules.each do |rule|
  color, content = rule.split(" bags contain ")
  bags[color] = []

  content.split(", ").each do |part|
    /^(\d+?) (.+?) bags?\.?$/ =~ part

    bags[color] << $2 unless $2.nil?
  end
end

has_path_to_shiny_gold = -> (color) do
  bags[color].include?("shiny gold") ||
    bags[color].any? { |c| has_path_to_shiny_gold.call(c) }
end

colors = []

bags.each do |bag_color, content_color_list|
  next if bag_color == "shiny gold"

  colors << bag_color if has_path_to_shiny_gold.call(bag_color)
end

puts "Bag colors that can eventually contain at least one shiny gold bag: #{colors.count}"
