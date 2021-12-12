=begin

--- Part Two ---

After reviewing the available paths, you realize you might have time to visit a
single small cave twice. Specifically, big caves can be visited any number of
times, a single small cave can be visited at most twice, and the remaining
small caves can be visited at most once. However, the caves named start and end
can only be visited exactly once each: once you leave the start cave, you may
not return to it, and once you reach the end cave, the path must end
immediately.

Now, the 36 possible paths through the first example above are:

start,A,b,A,b,A,c,A,end
start,A,b,A,b,A,end
start,A,b,A,b,end
start,A,b,A,c,A,b,A,end
start,A,b,A,c,A,b,end
start,A,b,A,c,A,c,A,end
start,A,b,A,c,A,end
start,A,b,A,end
start,A,b,d,b,A,c,A,end
start,A,b,d,b,A,end
start,A,b,d,b,end
start,A,b,end
start,A,c,A,b,A,b,A,end
start,A,c,A,b,A,b,end
start,A,c,A,b,A,c,A,end
start,A,c,A,b,A,end
start,A,c,A,b,d,b,A,end
start,A,c,A,b,d,b,end
start,A,c,A,b,end
start,A,c,A,c,A,b,A,end
start,A,c,A,c,A,b,end
start,A,c,A,c,A,end
start,A,c,A,end
start,A,end
start,b,A,b,A,c,A,end
start,b,A,b,A,end
start,b,A,b,end
start,b,A,c,A,b,A,end
start,b,A,c,A,b,end
start,b,A,c,A,c,A,end
start,b,A,c,A,end
start,b,A,end
start,b,d,b,A,c,A,end
start,b,d,b,A,end
start,b,d,b,end
start,b,end

The slightly larger example above now has 103 paths through it, and the even
larger example now has 3509 paths through it.

Given these new rules, how many paths through this cave system are there?

=end

require_relative "12.rb"

@paths = []

def dfs(current_cave, visited = Hash.new(0), path = [])
  visited[current_cave] += 1
  path << current_cave.name

  current_cave.connected_caves.each do |cave|
    # Never go back to start
    next if cave.is_start?

    # Stop if next cave is end
    if cave.is_end?
      @paths << path.push(cave.name)
      next
    end

    if cave.is_big? || visited[cave] < 1
      dfs(cave, visited.dup, path.dup)
    else
      # Has any small caves been visited more than once
      visit_limit = visited.any? do |cave, visits|
        !cave.is_big? && visits > 1
      end ? 1 : 2

      if visited[cave] < visit_limit
        dfs(cave, visited.dup, path.dup)
      end
    end
  end
end

caves = Hash.new { |h, k| h[k] = Cave.new(k) }

STDIN.read.split("\n").each do |line|
  from, to = line.split("-")

  from_cave = caves[from]
  to_cave = caves[to]

  from_cave.connected_caves << to_cave
  to_cave.connected_caves << from_cave
end

# puts "Cave paths:"
# caves.each do |name, cave|
#   puts "#{name} -> #{cave.connected_caves.map(&:name).join(", ")}"
# end
# puts

dfs(caves["start"])

# puts "Paths through cave system:"
# puts @paths.map { |path| path.join(" -> ") }.join("\n")
# puts

puts "Number of paths through the cave system,
that visit small caves at most once: #{@paths.count}"
