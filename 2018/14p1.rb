e0, e1 = [0, 1]
recipies = [3, 7]
original_size = recipies.size
input = 330121

until recipies.size == input + 10
  sum = recipies[e0] + recipies[e1]
  recipies += sum.to_s.split("").map(&:to_i)
  e0 = (e0 + recipies[e0] + 1) % recipies.length
  e1 = (e1 + recipies[e1] + 1) % recipies.length
end

puts recipies.last(10).join
