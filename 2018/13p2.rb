Position = Struct.new(:x, :y)
Cart = Struct.new(:pos, :sym, :turn)

tracks = []
carts = []

y = 0
STDIN.read.split("\n").each do |line|
  cart_indexes = (0..line.length).find_all do |i|
    ['^', '>', 'v', '<'].include?(line[i, 1])
  end

  cart_indexes.each do |x|
    c = Cart.new(Position.new(x, y), line[x], :left)

    case line[x]
    when '^'
      line[x] = '|'
    when '>'
      line[x] = '-'
    when 'v'
      line[x] = '|'
    when '<'
      line[x] = '-'
    end

    carts << c
  end

  tracks << line

  y += 1
end

one_remaining = false
tick = 0

until tick > 1
  tick += 1 if one_remaining

  carts.each do |c|
    case c.sym
    when '^'
      c.pos.y -= 1

      spot = tracks[c.pos.y][c.pos.x]

      case spot
      when '/'
        c.sym = '>'
      when '\\'
        c.sym = '<'
      when '+'
        case c.turn
        when :left
          c.sym = '<'
          c.turn = :straight
        when :straight
          c.turn = :right
        when :right
          c.sym = '>'
          c.turn = :left
        end
      end

    when '>'
      c.pos.x += 1

      spot = tracks[c.pos.y][c.pos.x]

      case spot
      when '/'
        c.sym = '^'
      when '\\'
        c.sym = 'v'
      when '+'
        case c.turn
        when :left
          c.sym = '^'
          c.turn = :straight
        when :straight
          c.turn = :right
        when :right
          c.sym = 'v'
          c.turn = :left
        end
      end

    when 'v'
      c.pos.y += 1

      spot = tracks[c.pos.y][c.pos.x]

      case spot
      when '/'
        c.sym = '<'
      when '\\'
        c.sym = '>'
      when '+'
        case c.turn
        when :left
          c.sym = '>'
          c.turn = :straight
        when :straight
          c.turn = :right
        when :right
          c.sym = '<'
          c.turn = :left
        end
      end

    when '<'
      c.pos.x -= 1

      spot = tracks[c.pos.y][c.pos.x]

      case spot
      when '/'
        c.sym = 'v'
      when '\\'
        c.sym = '^'
      when '+'
        case c.turn
        when :left
          c.sym = 'v'
          c.turn = :straight
        when :straight
          c.turn = :right
        when :right
          c.sym = '^'
          c.turn = :left
        end
      end

    else
      puts "Uh oh, cart symbol: #{c.sym}"
    end
  end

  carts.each do |c0|
    carts.each do |c1|
      next if c0 == c1

      if c0.pos.x == c1.pos.x && c0.pos.y == c1.pos.y
        carts.delete(c0)
        carts.delete(c1)
      end
    end
  end

  one_remaining = carts.length == 1
end

pos = carts[0].pos
puts "Last cart remaining: #{pos.x},#{pos.y}"
