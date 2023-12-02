=begin

--- Part Two ---

As you're about to send the thank you note, something in the MFCSAM's
instructions catches your eye. Apparently, it has an outdated retroencabulator,
and so the output from the machine isn't exact values - some of them indicate
ranges.

In particular, the cats and trees readings indicates that there are greater than
that many (due to the unpredictable nuclear decay of cat dander and tree
pollen), while the pomeranians and goldfish readings indicate that there are
fewer than that many (due to the modial interaction of magnetoreluctance).

What is the number of the real Aunt Sue?

=end

sue_no = -1

def validate(thing, count)
  ticker_tape = {
    "children" => 3,
    "cats" => 7,
    "samoyeds" => 2,
    "pomeranians" => 3,
    "akitas" => 0,
    "vizslas" => 0,
    "goldfish" => 5,
    "trees" => 3,
    "cars" => 2,
    "perfumes" => 1
  }

  case thing
  when "cats", "trees"
    ticker_tape[thing] < count.to_i
  when "pomeranians","goldfish"
    ticker_tape[thing] > count.to_i
  else
    ticker_tape[thing] == count.to_i
  end
end

STDIN.read.split("\n").each do |line|
  no, thing0, c0, thing1, c1, thing2, c2 =
    line.scan(/Sue (\d+): (\w+): (\d+), (\w+): (\d+), (\w+): (\d+)/).first

  if validate(thing0, c0) && validate(thing1, c1) && validate(thing2, c2)
    sue_no = no
  end
end

puts "Sue that got you the gift: #{sue_no}"
