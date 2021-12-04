=begin

--- Part Two ---

The next year, just to show off, Santa decides to take the route with the
longest distance instead.

He can still start and end at any two (different) locations he wants, and he
still must visit each location exactly once.

For example, given the distances above, the longest route would be 982 via (for
example) Dublin -> London -> Belfast.

What is the distance of the longest route?

=end

require "set"

cities = Set.new
distances = {}

STDIN.readlines.map(&:split).each do |from, _, to, _, distance|
  distances[[from, to].sort] = distance.to_i

  cities << from << to
end

# Pick each possible route, where all cities are visited once
route_distances = cities.to_a.permutation.map do |route|
  # Add up each step on the route
  distance = route.each_cons(2).reduce(0) do |acc, step|
    acc + distances[step.sort]
  end

  [route, distance]
end

longest_route = route_distances.sort_by! { |_, distance| distance }.last

puts "Longest route is #{longest_route[0].join(" -> ")} = #{longest_route[1]}"
