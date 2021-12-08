=begin

--- Part Two ---

Through a little deduction, you should now be able to determine the remaining
digits. Consider again the first example above:

acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab |
cdfeb fcadb cdfeb cdbaf

After some careful analysis, the mapping between signal wires and segments only
make sense in the following configuration:

 dddd
e    a
e    a
 ffff
g    b
g    b
 cccc

So, the unique signal patterns would correspond to the following digits:

acedgfb: 8
cdfbe: 5
gcdfa: 2
fbcad: 3
dab: 7
cefabd: 9
cdfgeb: 6
eafb: 4
cagedb: 0
ab: 1

Then, the four digits of the output value can be decoded:

cdfeb: 5
fcadb: 3
cdfeb: 5
cdbaf: 3

Therefore, the output value for this entry is 5353.

Following this same process for each entry in the second, larger example above,
the output value of each entry can be determined:

fdgacbe cefdb cefbgd gcbe: 8394
fcgedb cgb dgebacf gc: 9781
cg cg fdcagb cbg: 1197
efabcd cedba gadfec cb: 9361
gecf egdcabf bgf bfgea: 4873
gebdcfa ecba ca fadegcb: 8418
cefg dcbef fcge gbcadfe: 4548
ed bcgafe cdgba cbgef: 1625
gbdfcae bgc cg cgb: 8717
fgae cfgab fg bagce: 4315

Adding all of the output values in this larger example produces 61229.

For each entry, determine all of the wire/segment connections and decode the
four-digit output values. What do you get if you add up all of the output
values?

=end

known = {}

sum = STDIN.read.split("\n").map do |line|
  signal_patterns, output_values = line.split(" | ")
  signal_patterns = signal_patterns.split
  output_values = output_values.split

  signal_patterns.each do |pattern|
    known[1] = pattern if pattern.length == 2
    known[4] = pattern if pattern.length == 4
    known[7] = pattern if pattern.length == 3
    known[8] = pattern if pattern.length == 7
  end

  signal_patterns -= [known[1], known[4], known[7], known[8]]

  c069 = []

  signal_patterns.each do |pattern|
    # Only 0, 6 & 9 have one segment difference from 8
    c069 << pattern if (known[8].chars - pattern.chars).length == 1
  end

  c069.each do |pattern|
    # Only 9 completely contains 4
    known[9] = pattern if (known[4].chars - pattern.chars).empty?
  end

  # Reduce to 0 or 6
  c06 = c069 - [known[9]]

  c06.each do |pattern|
    # Only 0 completely contains 7
    if (known[7].chars - pattern.chars).empty?
      known[0] = pattern
    else
      known[6] = pattern
    end
  end

  signal_patterns -= [known[0], known[6], known[9]]

  signal_patterns.each do |pattern|
    # Only 3 completely contains 1
    known[3] = pattern if (known[1].chars - pattern.chars).empty?
  end

  signal_patterns -= [known[3]]

  # Only 2 and 5 remain
  signal_patterns.each do |pattern|
    # Only 5 has three segments in common with 5
    if (known[4].chars & pattern.chars).length == 3
      known[5] = pattern
    else
      known[2] = pattern
    end
  end

  sknown = known.reduce({}) do |h, el|
    key, value = el
    h[value.chars.sort.join] = key
    h
  end

  result = output_values.map do |pattern|
    so = pattern.chars.sort.join
    sknown[so]
  end.join

  # puts "#{output_values.join(" ")}: #{result}"

  result 
end.map(&:to_i).sum

puts "Sum of all output values: #{sum}"
