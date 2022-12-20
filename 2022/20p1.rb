=begin

--- Day 20: Grove Positioning System ---

It's finally time to meet back up with the Elves. When you try to contact them,
however, you get no reply. Perhaps you're out of range?

You know they're headed to the grove where the star fruit grows, so if you can
figure out where that is, you should be able to meet back up with them.

Fortunately, your handheld device has a file (your puzzle input) that contains
the grove's coordinates! Unfortunately, the file is encrypted - just in case
the device were to fall into the wrong hands.

Maybe you can decrypt it?

When you were still back at the camp, you overheard some Elves talking about
coordinate file encryption. The main operation involved in decrypting the file
is called mixing.

The encrypted file is a list of numbers. To mix the file, move each number
forward or backward in the file a number of positions equal to the value of the
number being moved. The list is circular, so moving a number off one end of the
list wraps back around to the other end as if the ends were connected.

For example, to move the 1 in a sequence like 4, 5, 6, 1, 7, 8, 9, the 1 moves
one position forward: 4, 5, 6, 7, 1, 8, 9. To move the -2 in a sequence like 4,
-2, 5, 6, 7, 8, 9, the -2 moves two positions backward, wrapping around: 4, 5,
6, 7, 8, -2, 9.

The numbers should be moved in the order they originally appear in the
encrypted file. Numbers moving around during the mixing process do not change
the order in which the numbers are moved.

Consider this encrypted file:

1
2
-3
3
-2
0
4

Mixing this file proceeds as follows:

Initial arrangement:
1, 2, -3, 3, -2, 0, 4

1 moves between 2 and -3:
2, 1, -3, 3, -2, 0, 4

2 moves between -3 and 3:
1, -3, 2, 3, -2, 0, 4

-3 moves between -2 and 0:
1, 2, 3, -2, -3, 0, 4

3 moves between 0 and 4:
1, 2, -2, -3, 0, 3, 4

-2 moves between 4 and 1:
1, 2, -3, 0, 3, 4, -2

0 does not move:
1, 2, -3, 0, 3, 4, -2

4 moves between -3 and 0:
1, 2, -3, 4, 0, 3, -2

Then, the grove coordinates can be found by looking at the 1000th, 2000th, and
3000th numbers after the value 0, wrapping around the list as necessary. In the
above example, the 1000th number after 0 is 4, the 2000th is -3, and the 3000th
is 2; adding these together produces 3.

Mix your encrypted file exactly once. What is the sum of the three numbers that
form the grove coordinates?

=end

DEBUG = false

def debug(s = "")
  puts s if DEBUG
end

class Node
	attr_accessor :value, :prev, :next

	def initialize(value)
		@value = value
		@prev = nil
		@next = nil
	end

  def to_s
    value
  end
end

class DoublyLinkedList
	attr_reader :head, :tail

	def initialize
		@head = nil
		@tail = nil
	end

	def append(value)
		new_node = Node.new(value)

		if @tail.nil?
			@head = new_node
			@tail = new_node
		else
			new_node.prev = @tail
			@tail.next = new_node
			@tail = new_node
		end
	end

	def delete(node)
    node.prev.next = node.next
    node.next.prev = node.prev

		if node == @head
			@head = node.next
		elsif node == @tail
      @tail = node.prev
		end
	end

  # Insert a new node before a target node
  def insert(node, at_node)
    node.prev = at_node.prev
    node.next = at_node
    at_node.prev.next = node
    at_node.prev = node

    if at_node == @head
      @tail = node
    end
  end

  def move_node(node)
    tmp = node

    if node.value < 0
      node.value.abs.times { tmp = tmp.prev }
    elsif node.value == 0
      debug "#{node.to_s} does not move:"
      return
    else
      (node.value + 1).times { tmp = tmp.next }
    end

    debug "#{node.to_s} moves between #{tmp.prev.to_s} and #{tmp.to_s}:"

    delete(node)

    insert(node, tmp)
  end

  def to_s
    nodes = []
    current_node = head

    until current_node == tail
      nodes << current_node.to_s
      current_node = current_node.next
    end

    nodes << tail.to_s

    "#{nodes.join(", ")}"
  end
end

list = DoublyLinkedList.new
original_ordering = []

STDIN.read.split("\n").each do |line|
  list.append(line.to_i)
  original_ordering << list.tail
end

# Make the list circular
list.head.prev = list.tail
list.tail.next = list.head

debug "Initial arrangement:"
debug list
debug

original_ordering.each do |node|
  list.move_node(node)
  debug list
  debug
end

current_node = list.head
current_node = current_node.next until current_node.value == 0

sum = 0

3.times do
	1000.times { current_node = current_node.next }

  sum += current_node.value
end

puts "Sum of the three numbers: #{sum}"

# Wrong answer
# 3992 - Too low
# 13724 - Too high
