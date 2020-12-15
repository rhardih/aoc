=begin

--- Part Two ---

Impressed, the Elves issue you a challenge: determine the 30000000th number
spoken. For example, given the same starting numbers as above:

- Given 0,3,6, the 30000000th number spoken is 175594.
- Given 1,3,2, the 30000000th number spoken is 2578.
- Given 2,1,3, the 30000000th number spoken is 3544142.
- Given 1,2,3, the 30000000th number spoken is 261214.
- Given 2,3,1, the 30000000th number spoken is 6895259.
- Given 3,2,1, the 30000000th number spoken is 18.
- Given 3,1,2, the 30000000th number spoken is 362.

Given your starting numbers, what will be the 30000000th number spoken?

=end

numbers = [0,1,4,13,15,12,16]
spoken_count = Hash.new(0)
turn_last_spoken = {}
previous_turn_last_spoken = {}

numbers.each_with_index do |v, i|
  turn_last_spoken[v] = i + 1
  spoken_count[v] = 1
end

(numbers.length + 1).upto(30000000) do |turn|
  last = numbers[-1]

  if spoken_count[last] == 1
    spoken_number = 0
  else
    spoken_number = turn_last_spoken[last] - previous_turn_last_spoken[last]
  end

  numbers << spoken_number
  spoken_count[spoken_number] += 1
  previous_turn_last_spoken[spoken_number] = turn_last_spoken[spoken_number]
  turn_last_spoken[spoken_number] = turn

  if turn % 3000000 == 0
    puts "#{(turn / 30000000.0 * 100).to_i}% done"
  end
end

puts "The 30000000th number spoken: #{numbers[-1]}"
