=begin

Neat, right? You might also enjoy hearing John Conway talking about this
sequence (that's Conway of Conway's Game of Life fame).

Now, starting again with the digits in your puzzle input, apply this process 50
times. What is the length of the new result?

=end

input = "1113222113"

50.times do
  # chunk is basically run-length coding, it returns the value being chunked by,
  # as well as the sub-array that has the values
  input = input.chars.chunk(&:itself).map do |char, arr|
    [arr.length, char]
  end.flatten.join
end

puts "Length of the result: #{input.length}"
