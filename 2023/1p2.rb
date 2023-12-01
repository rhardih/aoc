=begin

Your calculation isn't quite right. It looks like some of the digits are
actually spelled out with letters: one, two, three, four, five, six, seven,
eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last
digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
Adding these together produces 281.

=end

convert = {
  "zero" => "0",
  "0" => "0",
  "one" => "1",
  "1" => "1",
  "two" => "2",
  "2" => "2",
  "three" => "3",
  "3" => "3",
  "four" => "4",
  "4" => "4",
  "five" => "5",
  "5" => "5",
  "six" => "6",
  "6" => "6",
  "seven" => "7",
  "7" => "7",
  "eight" => "8",
  "8" => "8",
  "nine" => "9",
  "9" => "9",
}

result = STDIN.read.split("\n").map do |line|
  # It's necessary to use a positive lookahead assertion here, because otherwise
  # e.g. "twone" would be ["two"] instead of ["two", "one"]
  # https://ruby-doc.org/3.2.2/Regexp.html#class-Regexp-label-Anchors
  digits = line.scan(/(?=(\d|one|two|three|four|five|six|seven|eight|nine))/).map(&:first)
  number = convert[digits.first] + convert[digits.last]
  number.to_i
end.sum

puts "Sum of all of the calibration values: #{result}"
