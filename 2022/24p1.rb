=begin
=end

def layer_to_s(l, w, h)
  top = ("#." + ("#" * (w - 2))).chars
  bottom = top.reverse

  middle = Array.new(h - 2) do
    ("#" + "." * (w - 2) + "#").chars
  end

  tmp = [top, *middle, bottom]

  l.each do |k, v|
    col, row = k

    if v.size > 1
      tmp[row][col] = v.size.to_s
    else
      tmp[row][col] = v.first
    end
  end

  tmp.map(&:join).join("\n")
end

blizzards_layers = [
  Hash.new { |k,v| k[v] = [] }
]
row = 0
map_width = 0
map_height = 0

STDIN.read.split("\n").each do |line|
  map_width = line.size

  line.chars.each_with_index do |char, col|
    next if char == "."
    next if char == "#"

    blizzards_layers[0][[col, row]] << char
  end

  row += 1
end

map_height = row
max_t = [map_width, map_height].max - 2

# From initial configuration, generate each new "layer" where blizzards have
# moved one step according to the rules

puts "Layer 0"
puts layer_to_s(blizzards_layers[0], map_width, map_height)
puts

for t in 1..max_t
  new_layer = Hash.new { |k,v| k[v] = [] }

  blizzards_layers[t - 1].each do |k, v|
    col, row = k

    v.each do |direction|
      case direction
      when ">"
        if col + 1 < map_width - 1
          new_col = col + 1
        else
          new_col = 1
        end

        new_layer[[new_col, row]] << ">"
      when "v"
        if row + 1 < map_height - 1
          new_row = row + 1
        else
          new_row = 1
        end

        new_layer[[col, new_row]] << "v"
      when "<"
        if col - 1 > 0
          new_col = col - 1
        else
          new_col = map_width - 2
        end

        new_layer[[new_col, row]] << "<"
      when "^"
        if row - 1 > 0
          new_row = row - 1
        else
          new_row = map_height - 2
        end

        new_layer[[col, new_row]] << "^"
      end
    end
  end

  blizzards_layers << new_layer

  puts "Layer #{t}"
  puts layer_to_s(new_layer, map_width, map_height)
  puts
end

# Build a graph out of the layers

# pp blizzards_layers[0]
# pp blizzards_layers[1]
