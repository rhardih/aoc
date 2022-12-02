=begin

--- Part Two ---

The Elf finishes helping with the tent and sneaks back over to you. "Anyway,
the second column says how the round needs to end: X means you need to lose, Y
means you need to end the round in a draw, and Z means you need to win. Good
luck!"

The total score is still calculated in the same way, but now you need to figure
out what shape to choose so the round ends as indicated. The example above now
goes like this:

- In the first round, your opponent will choose Rock (A), and you need the
round to end in a draw (Y), so you also choose Rock. This gives you a score of
1 + 3 = 4.
In the second round, your opponent will choose Paper (B), and you choose Rock
so you lose (X) with a score of 1 + 0 = 1.
In the third round, you will defeat your opponent's Scissors with Rock for a
score of 1 + 6 = 7.
Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of 12.

Following the Elf's instructions for the second column, what would your total
score be if everything goes exactly according to your strategy guide?

=end

choices = {
  "A" => {
    "X" => "Z",
    "Y" => "X",
    "Z" => "Y"
  },
  "B" => {
    "X" => "X",
    "Y" => "Y",
    "Z" => "Z"
  },
  "C" => {
    "X" => "Y",
    "Y" => "Z",
    "Z" => "X"
  },
}

outcomes = {
  "A" => {
    "X" => 1 + 3,
    "Y" => 2 + 6,
    "Z" => 3 + 0,
  },
  "B" => {
    "X" => 1 + 0,
    "Y" => 2 + 3,
    "Z" => 3 + 6,
  },
  "C" => {
    "X" => 1 + 6,
    "Y" => 2 + 0,
    "Z" => 3 + 3,
  }
}

score = STDIN.read.split("\n").map do |line|
  opp, you = line.split(" ")

  choice = choices[opp][you]

  outcomes[opp][choice]
end.sum

puts "Total score: #{score}"
