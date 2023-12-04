cards = STDIN.read.split("\n")

# wsize = 5
# nsize = 8
wsize = 10
nsize = 25

points = cards.map do |card|
  numbers = card.scan(/\d+/)
  card_number = numbers.first
  winning_numbers = numbers[1, wsize]
  numbers = numbers[wsize + 1, nsize]

  overlap = winning_numbers & numbers

  overlap.length > 0 ? 2 ** (overlap.length - 1) : 0
end.sum

puts "Points are they worth in total: #{points}"
