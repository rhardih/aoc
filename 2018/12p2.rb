# Deduced by printing the sum every 1000 iterations from 12p1 and noticing the
# pattering:
#
#   0 sum: 2509
#   20 sum: 3258
#   1000 sum: 74022
#   2000 sum: 146022
#   3000 sum: 218022
#   4000 sum: 290022
#   5000 sum: 362022
def equation(generations)
  ((generations / 1000) - 1) * 72000 + 74022
end

puts "Sum of the numbers of all pots which contain a plant: #{equation(50000000000)}"
