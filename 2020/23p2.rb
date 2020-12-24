=begin

--- Part Two ---

Due to what you can only assume is a mistranslation (you're not exactly fluent
in Crab), you are quite surprised when the crab starts arranging many cups in a
circle on your raft - one million (1000000) in total.

Your labeling is still correct for the first few cups; after that, the
remaining cups are just numbered in an increasing fashion starting from the
number after the highest number in your list and proceeding one by one until
one million is reached. (For example, if your labeling were 54321, the cups
would be numbered 5, 4, 3, 2, 1, and then start counting up from 6 until one
million is reached.) In this way, every number from one through one million is
used exactly once.

After discovering where you made the mistake in translating Crab Numbers, you
realize the small crab isn't going to do merely 100 moves; the crab is going to
do ten million (10000000) moves!

The crab is going to hide your stars - one each - under the two cups that will
end up immediately clockwise of cup 1. You can have them if you predict what
the labels on those cups will be when the crab is finished.

In the above example (389125467), this would be 934001 and then 159792;
multiplying these together produces 149245887792.

Determine which two cups will end up immediately clockwise of cup 1. What do
you get if you multiply their labels together?

=end

MOVES = 10_000_000
# INPUT = "389125467"
INPUT = "716892543"

class Cup
	attr_accessor :next
	attr_reader :value

	def initialize(value)
		@value = value
		@next  = nil
	end
end

class CircularList
  attr_reader :current
  attr_reader :head
  attr_reader :tail
  attr_reader :max
  attr_reader :min

	def initialize(input)
    digits = input.split("").map(&:to_i)
    cups = digits.map { |digit| Cup.new(digit) }

    @index = Hash.new

    cups.each_with_index do |cup,i|
      @index[cup.value] = cup

      next if i == 0
      last_cup = cups[i - 1]
      last_cup.next = cup
    end

    10.upto(1_000_000) do |i|
      cup = Cup.new(i)

      @index[cup.value] = cup

      cups.last.next = cup
      cups << cup
    end

    @current = cups.first
    @head = cups.first
    @tail = cups.last
    @tail.next = cups.first
    @max = 1_000_000
    @min = 1
	end

  def pick_up
    @index.delete(@current.next.value)
    @index.delete(@current.next.next.value)
    @index.delete(@current.next.next.next.value)

    tmp = @current.next
    @current.next = @current.next.next.next.next
    tmp
  end

  def place(cup, destination_cup)
    @index[cup.value] = cup
    @index[cup.next.value] = cup.next
    @index[cup.next.next.value] = cup.next.next

    cup.next.next.next = destination_cup.next
    destination_cup.next = cup
  end

	def find(value)
    @index[value]
	end

  def next_current
    @current = @current.next
  end
end

circle = CircularList.new(INPUT)

MOVES.times do |i|
	picked_up = circle.pick_up

  destination = circle.current.value - 1
  destination_cup = nil

  while destination_cup.nil?
    destination_cup = circle.find(destination)
    destination -= 1
    destination = circle.max if destination < circle.min
  end

  circle.place(picked_up, destination_cup)

  circle.next_current
end

one = circle.find(1)

puts "Multiple of two cups immediately clockwise of cup 1: #{one.next.value * one.next.next.value}"
