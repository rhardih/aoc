=begin

--- Part Two ---

Santa's password expired again. What's the next one?

=end

require_relative '11'

# Start from solution to part 1
input = 'hepxxyzz'

password = Password.new(input)

loop do
  password.next!
  break if password.valid?
end

puts "Santas next password should be: #{password}"
