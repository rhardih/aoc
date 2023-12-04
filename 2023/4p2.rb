cards = STDIN.read.split("\n")

# wsize = 5
# nsize = 8
wsize = 10
nsize = 25

vault = []
processing = []
processed = []

cards.each do |card|
  numbers = card.scan(/\d+/)
  card_number = numbers.first
  winning_numbers = numbers[1, wsize]
  numbers = numbers[wsize + 1, nsize]

  vault << [card_number, winning_numbers, numbers]
  processing << [card_number, winning_numbers, numbers]
end

until processing.empty?
  card = processing.shift
  card_number, winning_numbers, numbers = card
  overlap = winning_numbers & numbers

  if overlap.length > 0
    overlap.length.times do |i|
      new_card = vault[card_number.to_i + i]
      processing << new_card
    end
  else
    0
  end

  processed << card_number

  # pp processing
  # break
end

puts "Total scratch cards: #{processed.length}"
