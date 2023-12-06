=begin

--- Part Two ---

As the race is about to start, you realize the piece of paper with race times
and record distances you got earlier actually just has very bad kerning. There's
really only one race - ignore the spaces between the numbers on each line.

So, the example from before:

Time:      7  15   30
Distance:  9  40  200
...now instead means this:

Time:      71530
Distance:  940200

Now, you have to figure out how many ways there are to win this single race. In
this example, the race lasts for 71530 milliseconds and the record distance you
need to beat is 940200 millimeters. You could hold the button anywhere from 14
to 71516 milliseconds and beat the record, a total of 71503 ways!

=end

example = <<-INPUT
Time:      7  15   30
Distance:  9  40  200
INPUT

time_distance_pair = STDIN.read.split("\n").map do |line|
  numbers = line.scan(/\d+/)
end.map(&:join).map(&:to_i)

result = [time_distance_pair].reduce(1) do |acc, i_element|
  i_time, i_distance = i_element

  acc * 1.upto(i_time - 1).map do |time|
    speed = i_time - time
    distance = speed * time
  end.select { |distance| distance > i_distance }.count
end

puts "Ways to beat the longer race: #{result}"
