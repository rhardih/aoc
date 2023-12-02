=begin

--- Part Two ---

Your cookie recipe becomes wildly popular! Someone asks if you can make another
recipe that has exactly 500 calories per cookie (so they can use it as a meal
replacement). Keep the rest of your award-winning process the same (100
teaspoons, same ingredients, same scoring system).

For example, given the ingredients above, if you had instead selected 40
teaspoons of butterscotch and 60 teaspoons of cinnamon (which still adds to
100), the total calorie count would be 40*8 + 60*3 = 500. The total score would
go down, though: only 57600000, the best you can do in such trying
circumstances.

Given the ingredients in your kitchen and their properties, what is the total
score of the highest-scoring cookie you can make with a calorie total of 500?

=end

Ingredient = Struct.new(
  :name,
  :capacity,
  :durability,
  :flavor,
  :texture,
  :calories
)

ingredients = []

reindeer = STDIN.readlines.map(&:split).map do 
  |name, _, capacity, _, durability,
    _, flavor, _, texture, _, calories|

  ingredients << Ingredient.new(
    name,
    capacity.to_i,
    durability.to_i,
    flavor.to_i,
    texture.to_i,
    calories.to_i
  )
end

highscore = 0

1.upto(97) do |i|
  1.upto(97) do |j|
    1.upto(97) do |k|
      next if i + j + k > 99

      l = 100 - i - j - k

      first = ingredients[0]
      second = ingredients[1]
      third = ingredients[2]
      fourth = ingredients[3]

      capacity =
        i * first.capacity + 
        j * second.capacity +
        k * third.capacity +
        l * fourth.capacity
      durability =
        i * first.durability +
        j * second.durability +
        k * third.durability +
        l * fourth.durability
      flavor =
        i * first.flavor +
        j * second.flavor +
        k * third.flavor +
        l * fourth.flavor
      texture = 
        i * first.texture +
        j * second.texture +
        k * third.texture +
        l * fourth.texture
      calories = 
        i * first.calories +
        j * second.calories +
        k * third.calories +
        l * fourth.calories

      score =
        [capacity, 0].max *
        [durability, 0].max *
        [flavor, 0].max *
        [texture, 0].max

      highscore = [highscore, score].max if calories === 500
    end
  end
end

puts "Total score of the highest-scoring cookie: #{highscore}"
