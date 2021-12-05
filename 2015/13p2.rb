=begin

--- Part Two ---

In all the commotion, you realize that you forgot to seat yourself. At this
point, you're pretty apathetic toward the whole thing, and your happiness
wouldn't really go up or down regardless of who you sit next to. You assume
everyone else would be just as ambivalent about sitting next to you, too.

So, add yourself to the list, and give all happiness relationships that involve
you a score of 0.

What is the total change in happiness for the optimal seating arrangement that
actually includes yourself?

=end

people = []
gains = {}

STDIN.readlines.map(&:split).each do |_p0, _, lg, _hu, _, _, _, _, _, _, _p1|
  # Input cleanup
  p0 = _p0.tr(".", "")
  hu = _hu.to_i
  p1 = _p1.tr(".", "")

  gains[[p0, p1]] = lg == "gain" ? hu : -hu

  people << p0.tr(".", "")
  people << p1.tr(".", "")
end

people.uniq!

# Add myself to the list of people
people.each do |person|
  gains[["Myself", person]] = 0
  gains[[person, "Myself"]] = 0
end

people << "Myself"

# Go through each possible seating arrangement
arrangements = people.permutation.map do |perm|
  happiness = perm.map.with_index  do |person, i|
    p_left = perm[i - 1]
    p_right = perm[(i + 1) % perm.length]

    [gains[[person, p_left]], gains[[person, p_right]]]
  end.flatten.sum

  [perm, happiness]
end

arrangement, total_change = arrangements.max_by { |_, happiness| happiness }

puts "Total change in happiness for the optimal seating arrangement including myself: #{total_change}"
puts "Arrangement: #{arrangement.join(" -> ")}"
