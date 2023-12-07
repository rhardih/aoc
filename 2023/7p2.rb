=begin

--- Part Two ---

To make things a little more interesting, the Elf introduces one additional
rule. Now, J cards are jokers - wildcards that can act like whatever card would
make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even than
2. The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2,
J.

J cards can pretend to be whatever card is best for the purpose of determining
hand type; for example, QJJQ2 is now considered four of a kind. However, for the
purpose of breaking ties between two hands of the same type, J is always treated
as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J
is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

- 32T3K is still the only one pair; it doesn't contain any jokers, so its
strength doesn't increase.
- KK677 is now the only two pair, making it the second-weakest hand.
- T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3, QQQJA
gets rank 4, and KTJJT gets rank 5.

With the new joker rule, the total winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set. What are the
new total winnings?

=end

class Hand
  attr_reader :cards
  attr_reader :card_values
  attr_reader :counts
  attr_reader :bid
  attr_reader :strength

  def initialize(cards, bid)
    value_map = Hash.new do |h, k|
      case k
      when "T"
        h[k] = 10
      when "J"
        h[k] = 1
      when "Q"
        h[k] = 12
      when "K"
        h[k] = 13
      when "A"
        h[k] = 14
      else
        h[k] = k.to_i
      end
    end

    @cards = cards.split("")
    @card_values = @cards.map { |card| value_map[card] }
    @counts = @cards.each_with_object(Hash.new(0)) { |card, h| h[card] += 1 }
    @bid = bid.to_i

    if five_of_a_kind?
      @strength = 6
    elsif four_of_a_kind?
      @strength = 5
    elsif full_house?
      @strength = 4
    elsif three_of_a_kind?
      @strength = 3
    elsif two_pair?
      @strength = 2
    elsif one_pair?
      @strength = 1
    else
      @strength = 0
    end
  end

  def five_of_a_kind?
    counts.values.first == 5 ||
      (counts.values.include?(4) && cards.count("J") == 1) ||
      (counts.values.include?(3) && cards.count("J") == 2) ||
      (counts.values.include?(2) && cards.count("J") == 3) ||
      cards.count("J") == 4
  end

  def four_of_a_kind?
    counts.values.include?(4) ||
      (counts.values.include?(3) && cards.count("J") == 1) ||
      (counts.values.include?(2) && cards.count("J") == 2) ||
      cards.count("J") == 3
  end

  def full_house?
    # If there's only two different keys, and one has a count of three it must
    # be three of a kind and two of a kind, because the values adds to five.
    (counts.values.include?(3) && counts.values.include?(2)) ||
      (counts.values.count(2) == 2 && cards.count("J") == 1)
  end

  def three_of_a_kind?
    counts.values.include?(3) ||
      (counts.values.include?(2) && cards.count("J") == 1) ||
      cards.count("J") == 2
  end

  def two_pair?
    counts.values.count(2) == 2 || 
      (counts.values.count(2) == 1 && cards.count("J") == 1)
  end

  def one_pair?
    counts.values.count(2) == 1 || cards.count("J") == 1
  end

  def to_s
    cards.join
  end

  def <=>(other)
    if strength != other.strength
      strength <=> other.strength
    else
      # Find the first card in the hand that differs from the other and return
      # the comparison of those
      card_values.zip(other.card_values).each do |this_card, other_card|
				return this_card <=> other_card if this_card != other_card
      end

      # If we get here, the hands must be identical
      return 0
    end
  end
end

input = STDIN.read.split("\n")

example = <<-INPUT
32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
INPUT

# input = example.split("\n")

hands = input.map do |line|
  cards, bid = line.split
  Hand.new(cards, bid)
end

winnings = hands.sort.each.with_index.reduce(0) do |acc, (hand, i)|
  acc += hand.bid * (i + 1)
end

puts "Total winnings: #{winnings}"

# Too high
# 251656295

