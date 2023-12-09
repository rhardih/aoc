=begin

--- Part Two ---

Of course, it would be nice to have even more history included in your report.
Surely it's safe to just extrapolate backwards as well, right?

For each history, repeat the process of finding differences until the sequence
of differences is entirely zero. Then, rather than adding a zero to the end and
filling in the next values of each previous sequence, you should instead add a
zero to the beginning of your sequence of zeroes, then fill in new first values
for each previous sequence.

In particular, here is what the third example history looks like when
extrapolating back in time:

5  10  13  16  21  30  45
  5   3   3   5   9  15
   -2   0   2   4   6
      2   2   2   2
        0   0   0

Adding the new values on the left side of each sequence from bottom to top
eventually reveals the new left-most history value: 5.

Doing this for the remaining example data above results in previous values of
-3 for the first history and 0 for the second history. Adding all three new
values together produces 2.

Analyze your OASIS report again, this time extrapolating the previous value for
each history. What is the sum of these extrapolated values?

=end

input = STDIN.read.split("\n")

example = <<-INPUT
0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45
INPUT

# input = example.split("\n")

e_values = input.map do |line|
  history = line.scan(/-?\d+/).map(&:to_i)

  histories = [history]
  current_history = history

  until current_history.all?(&:zero?)
    new_history = []

    for i in 0...current_history.length - 1 do
      new_history << current_history[i + 1] - current_history[i]
    end

    current_history = new_history
    histories << new_history
  end

  # Add the "extra" zero
  histories.last.unshift(0)

  for i in (histories.length - 2).downto(0)
    histories[i].unshift(histories[i].first - histories[i + 1].first)
  end

  histories.first.first
end

puts "The sum of extrapolated values: #{e_values.sum}"
