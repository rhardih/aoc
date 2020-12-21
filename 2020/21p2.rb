=begin

--- Part Two ---

Now that you've isolated the inert ingredients, you should have enough
information to figure out which ingredient contains which allergen.

In the above example:

mxmxvkd contains dairy.
sqjhc contains fish.
fvjkl contains soy.

Arrange the ingredients alphabetically by their allergen and separate them by
commas to produce your canonical dangerous ingredient list. (There should not
be any spaces in your canonical dangerous ingredient list.) In the above
example, this would be mxmxvkd,sqjhc,fvjkl.

Time to stock your raft with supplies. What is your canonical dangerous
ingredient list?

=end

lines = STDIN.read.split("\n")

# Possible ingredient candidates for each allergen
candidates = Hash.new
all_ingredients = []

lines.each do |food|
  s0, s1 = food.scan(/([a-z ]+) \(contains ([a-z, ]+)\)/)[0]
  ingredients_list = s0.split(" ")
  allergens = s1.split(", ")

  ingredients_list.each { |i| all_ingredients << i }

  allergens.each do |a|
    if candidates[a].nil?
      candidates[a] = ingredients_list
    else
      candidates[a] &= ingredients_list
    end
  end
end

# Resolved ingredient for each allergen
resolved = {}

until candidates.empty?
  allergen, ingredients = candidates.find { |k,v| v.size == 1 }

  resolved[allergen] = ingredients[0]
  candidates.delete(allergen)
  candidates.each { |k,v| v.delete(ingredients[0]) }
end

dangerous_ingredients = resolved.keys.sort.map { |allergen| resolved[allergen] }

puts "Canonical dangerous ingredient list:\n"
puts dangerous_ingredients.join(",")
