=begin

--- Day 15: Chiton ---

You've almost reached the exit of the cave, but the walls are getting closer
together. Your submarine can barely still fit, though; the main problem is that
the walls of the cave are covered in chitons, and it would be best not to bump
any of them.

The cavern is large, but has a very low ceiling, restricting your motion to two
dimensions. The shape of the cavern resembles a square; a quick scan of chiton
density produces a map of risk level throughout the cave (your puzzle input).
For example:

1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581

You start in the top left position, your destination is the bottom right
position, and you cannot move diagonally. The number at each position is its
risk level; to determine the total risk of an entire path, add up the risk
levels of each position you enter (that is, don't count the risk level of your
starting position unless you enter it; leaving it adds no risk to your total).

Your goal is to find a path with the lowest total risk. In this example, a path
with the lowest total risk is highlighted here:

1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581

The total risk of this path is 40 (the starting position is never entered, so
its risk is not counted).

What is the lowest total risk of any path from the top left to the bottom right?

=end

risk_level_map = Array.new(
  STDIN.read.split("\n").map(&:chars).map do |row|
    row.map(&:to_i)
  end
)

MAX = risk_level_map.sum { |row| row.sum } + 1

def dijkstra(graph, max)
  distances = Array.new(graph.size) { Array.new(graph[0].size) { max } }
  queue = {}

  (0...graph.size).each do |y|           
    (0...graph[0].size).each do |x|           
      queue[[x, y]] = nil
    end
  end

  distances[0][0] = 0
  i = 0

  until queue.empty?
    u = queue.min do |el0, el1|
      l0, _ = el0
      l1, _ = el1

      x0, y0 = l0
      x1, y1 = l1

      distances[y0][x0] <=> distances[y1][x1]
    end

    ux, uy = u[0]
    queue.delete(u[0])

    [
      [0, -1], # up
      [1, 0], # right
      [0, 1], # down
      [-1, 0] #left
    ].each do |x_offset, y_offset|
      vx = ux + x_offset
      vy = uy + y_offset
      v = [vx, vy]

      if queue.include?(v)
        alt = distances[uy][ux] + graph[vy][vx]

        if alt < distances[vy][vx]
          distances[vy][vx] = alt
        end
      end
    end
  end

  return distances
end

distances = dijkstra(risk_level_map, MAX)
lowest = distances[-1][-1]

puts "Lowest total risk of any path: #{lowest}"
