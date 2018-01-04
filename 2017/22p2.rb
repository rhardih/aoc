# Infection map
imap = Hash.new { |h0, k0| h0[k0] = Hash.new { |h1, k1| h1[k1] = '.' } }

left = {
  up: :left,
  right: :up,
  down: :right,
  left: :down
}

right = {
  up: :right,
  right: :down,
  down: :left,
  left: :up
}

reverse = {
  up: :down,
  right: :left,
  down: :up,
  left: :right
}

xmax = 0
ymax = 0
xmin = 0
ymin = 0
x = 0
y = 0

show = Proc.new do
  system("clear")

  puts
  ymin.upto(ymax) do |a|
    xmin.upto(xmax) do |b|
      if a == y && b == x + 1
        print ']'
      elsif a == y && b == x
        print '['
      else
        print ' '
      end

      print imap[a][b]
    end
    puts
  end
  puts

  sleep 0.1
end

STDIN.read.split("\n").each.with_index do |line, y|
  line.split("").each.with_index do |char, x|
    imap[y][x] = char
    xmax = x
  end
  ymax = y
end

x = xmax / 2
y = ymax / 2

dir = :up
bursts = 0
infections = 0

loop do
  #show.call

  case imap[y][x]
  when '.'
    imap[y][x] = 'W'
    dir = left[dir]
  when 'W'
    imap[y][x] = '#'
    infections += 1
  when '#'
    imap[y][x] = 'F'
    dir = right[dir]
  when 'F'
    imap[y][x] = '.'
    dir = reverse[dir]
  end

  bursts += 1

  case dir
  when :up
    y -= 1
  when :right
    x += 1
  when :down
    y += 1
  when :left
    x -= 1
  end

  xmax = x if x > xmax
  ymax = y if y > ymax
  xmin = x if x < xmin
  ymin = y if y < ymin

  break if bursts == 10000000
end

puts "Bursts #{bursts}, infections: #{infections}"
