=begin

--- Day 22: Monkey Map ---

The monkeys take you on a surprisingly easy trail through the jungle. They're
even going in roughly the right direction according to your handheld device's
Grove Positioning System.

As you walk, the monkeys explain that the grove is protected by a force field.
To pass through the force field, you have to enter a password; doing so involves
tracing a specific path on a strangely-shaped board.

At least, you're pretty sure that's what you have to do; the elephants aren't
exactly fluent in monkey.

The monkeys give you notes that they took when they last saw the password
entered (your puzzle input).

For example:

        ...#
        .#..
        #...
        ....
...#.......#
........#...
..#....#....
..........#.
        ...#....
        .....#..
        .#......
        ......#.

10R5L5R10L4R5L5

The first half of the monkeys' notes is a map of the board. It is comprised of a
set of open tiles (on which you can move, drawn .) and solid walls (tiles which
you cannot enter, drawn #).

The second half is a description of the path you must follow. It consists of
alternating numbers and letters:

A number indicates the number of tiles to move in the direction you are facing.
If you run into a wall, you stop moving forward and continue with the next
instruction.  A letter indicates whether to turn 90 degrees clockwise (R) or
counterclockwise (L). Turning happens in-place; it does not change your current
tile.  So, a path like 10R5 means "go forward 10 tiles, then turn clockwise 90
degrees, then go forward 5 tiles".

You begin the path in the leftmost open tile of the top row of tiles. Initially,
you are facing to the right (from the perspective of how the map is drawn).

If a movement instruction would take you off of the map, you wrap around to the
other side of the board. In other words, if your next tile is off of the board,
you should instead look in the direction opposite of your current facing as far
as you can until you find the opposite edge of the board, then reappear there.

For example, if you are at A and facing to the right, the tile in front of you
is marked B; if you are at C and facing down, the tile in front of you is marked
D:

        ...#
        .#..
        #...
        ....
...#.D.....#
........#...
B.#....#...A
.....C....#.
        ...#....
        .....#..
        .#......
        ......#.

It is possible for the next tile (after wrapping around) to be a wall; this
still counts as there being a wall in front of you, and so movement stops before
you actually wrap to the other side of the board.

By drawing the last facing you had with an arrow on each tile you visit, the
full path taken by the above example looks like this:

        >>v#    
        .#v.    
        #.v.    
        ..v.    
...#...v..v#    
>>>v...>#.>>    
..#v...#....    
...>>>>v..#.    
        ...#....
        .....#..
        .#......
        ......#.

To finish providing the password to this strange input device, you need to
determine numbers for your final row, column, and facing as your final position
appears from the perspective of the original map. Rows start from 1 at the top
and count downward; columns start from 1 at the left and count rightward. (In
the above example, row 1, column 1 refers to the empty space with no tile on it
in the top-left corner.) Facing is 0 for right (>), 1 for down (v), 2 for left
(<), and 3 for up (^). The final password is the sum of 1000 times the row, 4
times the column, and the facing.

In the above example, the final row is 6, the final column is 8, and the final
facing is 0. So, the final password is 1000 * 6 + 4 * 8 + 0: 6032.

Follow the path given in the monkeys' notes. What is the final password?

=end

require 'matrix'

def map_to_s(m)
  tmp = m.dup

  tmp.each_with_index { |el, row, col| tmp[row, col] = " " if el.nil? }

  tmp.to_a.map(&:join).join("\n")
end

def wrap_up(map, col)
  (map.row_count - 1).downto(0) do |row|
    return row if map[row, col] != nil
  end

  throw "wrap_up"
end

def wrap_down(map, col)
  0.upto(map.row_count - 1) do |row|
    return row if map[row, col] != nil
  end

  throw "wrap_down"
end

def wrap_left(map, row)
  (map.column_count - 1).downto(0) do |col|
    return col if map[row, col] != nil
  end

  throw "wrap_left"
end

def wrap_right(map, row)
  0.upto(map.column_count - 1) do |col|
    return col if map[row, col] != nil
  end

  throw "wrap_right"
end

# Facing is 0 for right (>), 1 for down (v), 2 for left (<), and 3 for up (^)
RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3

map, description = STDIN.read.split("\n\n")

# Remove newline at the end of the string
description.strip!

map_lines = map.split("\n").map(&:chars)

rows = map_lines.size
cols = map_lines.map(&:size).max

map = Matrix.build(rows, cols) { |row, col| map_lines[row][col] }

map.each_with_index do |el, row, col|
  # Replace whitespace with nil, so *out-of-bounds* behaviour inside the map is
  # similar to outside the map entirely
  map[row, col] = nil if el == " "
end

current_y = 0
current_x = map[current_y, 0..-1].index(".")
facing = RIGHT

map[current_y, current_x] = ">"

until description.empty?
  case description[0]
  when "R"
    facing = (facing + 1) % 4
    description.slice!("R")
  when "L"
    facing = (facing - 1) % 4
    description.slice!("L")
  else
    tmp = description[/\d+/]

    description.slice!(tmp)

    number = tmp.to_i

    number.times do
      case facing
      when UP
        case map[current_y - 1, current_x]
        when "#"
          # If you run into a wall, you stop moving forward and continue with
          # the next instruction.
          break
        when nil
          wrapped_y = wrap_up(map, current_x)

          if map[wrapped_y, current_x] == "#"
            break
          else
            current_y = wrapped_y
          end
        else
          current_y -= 1
        end

        map[current_y, current_x] = "^"
      when DOWN
        case map[current_y + 1, current_x]
        when "#"
          # If you run into a wall, you stop moving forward and continue with
          # the next instruction.
          break
        when nil
          # If a movement instruction would take you off of the map, you wrap
          # around to the other side of the board.

          wrapped_y = wrap_down(map, current_x)

          if map[wrapped_y, current_x] == "#"
            break
          else
            current_y = wrapped_y
          end
        else
          current_y += 1
        end

        map[current_y, current_x] = "v"
      when LEFT
        case map[current_y, current_x - 1]
        when "#"
          break
        when nil
          wrapped_x = wrap_left(map, current_y)

          if map[current_y, wrapped_x] == "#"
            break
          else
            current_x = wrapped_x
          end
        else
          current_x -= 1
        end

        map[current_y, current_x] = "<"
      when RIGHT
        case map[current_y, current_x + 1]
        when "#"
          break
        when nil
          wrapped_x = wrap_right(map, current_y)

          if map[current_y, wrapped_x] == "#"
            break
          else
            current_x = wrapped_x
          end
        else
          current_x += 1
        end

        map[current_y, current_x] = ">"
      end
    end
  end
end

puts "Stop at #{current_x + 1}, #{current_y + 1} facing #{facing}"
puts "Password: #{1000 * (current_y + 1) + 4 * (current_x + 1) + facing}"
