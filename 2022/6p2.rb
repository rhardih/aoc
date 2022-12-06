=begin

--- Part Two ---

Your device's communication system is correctly detecting packets, but still
isn't working. It looks like it also needs to look for messages.

A start-of-message marker is just like a start-of-packet marker, except it
consists of 14 distinct characters rather than 4.

Here are the first positions of start-of-message markers for all of the above
examples:

- mjqjpqmgbljsphdztnvjfqwrcgsmlb: first marker after character 19
- bvwbjplbgvbhsrlpgdmjqwftvncz: first marker after character 23
- nppdvjthqldpwncqszvftbrmjlhg: first marker after character 23
- nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg: first marker after character 29
- zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw: first marker after character 26

How many characters need to be processed before the first start-of-message
marker is detected?

=end

input = STDIN.read

samples = {
  "mjqjpqmgbljsphdztnvjfqwrcgsmlb" => 19,
  "bvwbjplbgvbhsrlpgdmjqwftvncz" => 23,
  "nppdvjthqldpwncqszvftbrmjlhg" => 23,
  "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg" => 29,
  "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw" => 26
}

def find_som(signal)
  for i in 13..signal.length do
    tmp = signal[i - 13, 14].chars

    return i + 1 if tmp.uniq == tmp
  end

  return -1
end

samples.each do |signal, c|
  puts "Unexpected marker for #{signal}" if c != find_som(signal)
end

puts "Result: #{find_som(input)}"
