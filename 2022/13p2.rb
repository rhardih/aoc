=begin

--- Part Two ---

Now, you just need to put all of the packets in the right order. Disregard the
blank lines in your list of received packets.

The distress signal protocol also requires that you include two additional
divider packets:

[[2]]
[[6]]

Using the same rules as before, organize all packets - the ones in your list of
received packets as well as the two divider packets - into the correct order.

For the example above, the result of putting the packets in the correct order
is:

[]
[[]]
[[[]]]
[1,1,3,1,1]
[1,1,5,1,1]
[[1],[2,3,4]]
[1,[2,[3,[4,[5,6,0]]]],8,9]
[1,[2,[3,[4,[5,6,7]]]],8,9]
[[1],4]
[[2]]
[3]
[[4,4],4,4]
[[4,4],4,4,4]
[[6]]
[7,7,7]
[7,7,7,7]
[[8,7,6]]
[9]

Afterward, locate the divider packets. To find the decoder key for this
distress signal, you need to determine the indices of the two divider packets
and multiply them together. (The first packet is at index 1, the second packet
is at index 2, and so on.) In this example, the divider packets are 10th and
14th, and so the decoder key is 140.

Organize all of the packets into the correct order. What is the decoder key for
the distress signal?

=end

def compare(left, right, indent = 0)
  if left.is_a?(Array) && right.is_a?(Array)
    size = left.size < right.size ? left.size : right.size

    for i in 0..size do # go one past smallest array size
      if left[i].nil? && right[i].nil? # both ran out
        return 0
      elsif left[i].nil? # left ran out
        return -1
      elsif right[i].nil? # right ran out
        return 1
      end

      tmp = compare(left[i], right[i], indent + 1)

      if tmp < 0
        return tmp
        break
      elsif  tmp == 0
        next
      else
        return tmp
        break
      end
    end
  elsif left.is_a?(Integer) && right.is_a?(Array)
    return compare([left], right, indent + 1)
  elsif left.is_a?(Array) && right.is_a?(Integer)
    return compare(left, [right], indent + 1)
  elsif left.is_a?(Integer) && right.is_a?(Integer)
    return left <=> right
  end
end

pairs = []

STDIN.read.split("\n\n").each do |pair|
  lefts, rights = pair.split("\n")
  left = eval(lefts)
  right = eval(rights)

  pairs << left
  pairs << right
end

pairs << [[2]]
pairs << [[6]]

pairs.sort! { |a, b| compare(a, b) }

key = (pairs.index([[2]]) + 1) * (pairs.index([[6]]) + 1)

puts "Decoder key for the distress signal: #{key}"
