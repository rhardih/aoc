=begin

--- Part Two ---

Suppose the lanternfish live forever and have unlimited food and space. Would
they take over the entire ocean?

After 256 days in the example above, there would be a total of 26984457539
lanternfish!

How many lanternfish would there be after 256 days?

=end

fish = STDIN.read.split(",").map(&:to_i).reduce(Hash.new(0)) do |h, fish|
  h[fish] += 1
  h
end

day = 0

loop do
  tmp = fish[6]

  -1.upto(7) do |i|
    next unless fish.key?(i + 1)

    fish[i] = fish[i + 1]
    fish.delete(i + 1)
  end

  if fish.key?(-1)
    fish[8] += fish[-1]
    fish[6] += fish[-1]
  end

  fish.delete(-1)

  day += 1

  break if day == 256
end

puts "Number of lanternfish afer 256 days: #{fish.values.sum}"
