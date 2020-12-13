# Ok... had to give up on writing a proper solver for now. The solution has been
# found by inputting the output of this program into the solver on:
#
#   https://www.dcode.fr/chinese-remainder
#
# I had a hunch that this problem might be a Chinese Remainder Theorem thing,
# after looking at the input and noticing that all bus IDs are prime.
#
# The CRT can find a solution for x to a system of equations like this:
#
# x ≡ 2 (mod 7)
# x ≡ 4 (mod 5)
# x ≡ 0 (mod 11)
#
# crt([2, 4, 0], [7, 5, 11]) = 44
#
# This fits perfectly with the problem. E.g. the initial example:
#
# t ≡ 0 (mod 7) 
# t ≡ 6 (mod 13)
# t ≡ 3 (mod 59)
# t ≡ 1 (mod 31)
# t ≡ 0 (mod 19)

one, two = STDIN.read.split("\n")
earliest_bus_estimate = one.to_i
bus_ids = two.split(",").map { |bi| bi == "x" ? bi : bi.to_i }
remainders = bus_ids.dup

bus_ids.each_with_index do |d, i|
  next if d == "x"
  remainders[i] = remainders.length - 1 - i
end

# [7, 6, 3, 1, 0]
# [7, 13, 59, 31, 19]
# 1068788 - 1068781 = 7
#
# [3, 1, 0]
# [17, 13, 19]
# 3420 - 3417 = 3
#
# [3, 2, 1, 0]
# [67, 7, 59, 61]
# 754021 - 754018 = 3
#
# [4, 2, 1, 0]
# [67, 7, 59, 61]
# 779214 - 779210 = 4
#
# [4, 3, 1, 0]
# [67, 7, 59, 61]
# 1261480 - 1261476 = 4
#
# [3, 2, 1, 0]
# [1789, 37, 47, 1889]
# 1202161489 - 1202161486 = 3
#
# [73, 64, 60, 54, 41, 37, 25, 23, 0]
# [19, 41, 37, 821, 13, 17, 29, 463, 23]
# 554865447501172 - 554865447501099 = 73

puts "Remainders: #{remainders.filter { |e| e != "x" }.inspect}"
puts "Moduli: #{bus_ids.filter { |e| e != "x" }.inspect}"
