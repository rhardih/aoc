require "set"

routes = Hash.new { |h, k| h[k] = {} }
cities = Set.new

shortest_route = nil
shortest_route_length = 0

STDIN.read.split("\n").each_with_index do |l, i|
  from, to, distance = l.match(/(^\w+) to (\w+) = (\d+)/).captures

  cities << from << to

  routes[from][to] = distance.to_i
  routes[to][from] = distance.to_i

  shortest_route_length += distance.to_i
end

cities = cities.to_a

# Pick each possible route, where all cities are visited once
cities.permutation(cities.length).each do |route|
  route_length = 0

  # Add up each step on the route
  route.each_cons(2) do |step|
    from, to = step
    route_length += routes[from][to]
  end

  if route_length < shortest_route_length
    shortest_route = route
    shortest_route_length = route_length
  end
end

puts "Shortest route is #{shortest_route.join(" -> ")} = #{shortest_route_length}"
