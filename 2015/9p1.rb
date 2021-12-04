=begin

--- Day 9: All in a Single Night ---

Every year, Santa manages to deliver all of his presents in a single night.

This year, however, he has some new locations to visit; his elves have provided
him the distances between every pair of locations. He can start and end at any
two (different) locations he wants, but he must visit each location exactly
once. What is the shortest distance he can travel to achieve this?

For example, given the following distances:

London to Dublin = 464
London to Belfast = 518
Dublin to Belfast = 141

The possible routes are therefore:

Dublin -> London -> Belfast = 982
London -> Dublin -> Belfast = 605
London -> Belfast -> Dublin = 659
Dublin -> Belfast -> London = 659
Belfast -> Dublin -> London = 605
Belfast -> London -> Dublin = 982

The shortest of these is London -> Dublin -> Belfast = 605, and so the answer is
605 in this example.

What is the distance of the shortest route?

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

shortest_route = route_distances.sort_by! { |_, distance| distance }.first

puts "Shortest route is #{shortest_route[0].join(" -> ")} = #{shortest_route[1]}"
