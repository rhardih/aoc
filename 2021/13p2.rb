=begin

--- Part Two ---

Finish folding the transparent paper according to the instructions. The manual
says the code is always eight capital letters.

What code do you use to activate the infrared thermal imaging camera system?

=end

require_relative "13"

paper, fold_instructions = handle_input

fold(paper, fold_instructions, false)

puts "Activation code:\n\n"
puts paper.minor(0..5, 0..80)
