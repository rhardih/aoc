=begin

--- Day 23: Crab Cups ---

The small crab challenges you to a game! The crab is going to mix up some cups,
and you have to predict where they'll end up.

The cups will be arranged in a circle and labeled clockwise (your puzzle
input). For example, if your labeling were 32415, there would be five cups in
the circle; going clockwise around the circle from the first cup, the cups
would be labeled 3, 2, 4, 1, 5, and then back to 3 again.

Before the crab starts, it will designate the first cup in your list as the
current cup. The crab is then going to do 100 moves.

Each move, the crab does the following actions:

- The crab picks up the three cups that are immediately clockwise of the
current cup. They are removed from the circle; cup spacing is adjusted as
necessary to maintain the circle.
- The crab selects a destination cup: the cup with a label equal to the current
cup's label minus one. If this would select one of the cups that was just
picked up, the crab will keep subtracting one until it finds a cup that wasn't
just picked up. If at any point in this process the value goes below the lowest
value on any cup's label, it wraps around to the highest value on any cup's
label instead.
- The crab places the cups it just picked up so that they are immediately
clockwise of the destination cup. They keep the same order as when they were
picked up.
- The crab selects a new current cup: the cup which is immediately clockwise of
the current cup.

For example, suppose your cup labeling were 389125467. If the crab were to do
merely 10 moves, the following changes would occur:

-- move 1 --
cups: (3) 8  9  1  2  5  4  6  7 
pick up: 8, 9, 1
destination: 2

-- move 2 --
cups:  3 (2) 8  9  1  5  4  6  7 
pick up: 8, 9, 1
destination: 7

-- move 3 --
cups:  3  2 (5) 4  6  7  8  9  1 
pick up: 4, 6, 7
destination: 3

-- move 4 --
cups:  7  2  5 (8) 9  1  3  4  6 
pick up: 9, 1, 3
destination: 7

-- move 5 --
cups:  3  2  5  8 (4) 6  7  9  1 
pick up: 6, 7, 9
destination: 3

-- move 6 --
cups:  9  2  5  8  4 (1) 3  6  7 
pick up: 3, 6, 7
destination: 9

-- move 7 --
cups:  7  2  5  8  4  1 (9) 3  6 
pick up: 3, 6, 7
destination: 8

-- move 8 --
cups:  8  3  6  7  4  1  9 (2) 5 
pick up: 5, 8, 3
destination: 1

-- move 9 --
cups:  7  4  1  5  8  3  9  2 (6)
pick up: 7, 4, 1
destination: 5

-- move 10 --
cups: (5) 7  4  1  8  3  9  2  6 
pick up: 7, 4, 1
destination: 3

-- final --
cups:  5 (8) 3  7  4  1  9  2  6 

In the above example, the cups' values are the labels as they appear moving
clockwise around the circle; the current cup is marked with ( ).

After the crab is done, what order will the cups be in? Starting after the cup
labeled 1, collect the other cups' labels clockwise into a single string with
no extra characters; each number except 1 should appear exactly once. In the
above example, after 10 moves, the cups clockwise from 1 are labeled 9, 2, 6,
5, and so on, producing 92658374. If the crab were to complete all 100 moves,
the order after cup 1 would be 67384529.

Using your labeling, simulate 100 moves. What are the labels on the cups after
cup 1?

=end

DEBUG = false
MOVES = 100
# INPUT = "389125467"
INPUT = "716892543"

def debug(*args)
  puts *args if DEBUG
end

class Cup
	attr_accessor :next
	attr_reader :value

	def initialize(value)
		@value = value
		@next  = nil
	end

	def to_s(n = 1)
    values = []
    node = self

    n.times do
      values << node.value.to_s
      node = node.next
    end

    values.join(", ")
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

    cups.each_with_index do |cup,i|
      next if i == 0
      last_cup = cups[i - 1]
      last_cup.next = cup
    end

    @current = cups.first
    @head = cups.first
    @tail = cups.last
    @tail.next = cups.first
    @max = digits.max
    @min = digits.min
	end

  def pick_up
    tmp = @current.next
    @current.next = @current.next.next.next.next
    tmp
  end

	def find(value)
		node = @current

    9.times do
      return node if node.value == value
      node = node.next
		end

    nil
	end

  def next_current
    @current = @current.next
  end

  def order
    node = find(1)

    8.times.reduce("") do |s|
      node = node.next
      s << node.value.to_s
    end
  end

	def to_s
		node = @head
    nodes = []

    9.times do
      nodes << node
      node = node.next
    end

    nodes.map { |n| @current == n ? "(#{n})" : n }.join(" ")
	end
end

circle = CircularList.new(INPUT)

MOVES.times do |i|
	debug "-- move #{i + 1} --"
	debug "cups: #{circle}"

	picked_up = circle.pick_up

  destination = circle.current.value - 1
  destination_cup = nil

  while destination_cup.nil?
    destination_cup = circle.find(destination)
    destination -= 1
    destination = circle.max if destination < circle.min
  end

  # place cups
  picked_up.next.next.next = destination_cup.next
  destination_cup.next = picked_up

	debug "pick up: #{picked_up.to_s(3)}"
  debug "destination: #{destination_cup.value}"
  debug

  circle.next_current
end

debug "-- final --"
debug "cups:  #{circle}"

puts "Labels on the cups after cup 1: #{circle.order}"
