@rules = {}

STDIN.read.split("\n").each do |l|
  from, to = l.split(" => ")
  @rules[from] = to
end

@image = ".#...####"
@size = 3

def pgrid(g)
  size = Math.sqrt(g.size).to_i
  g.scan(/.{#{size}}/) { |s| puts s }
end

def hflip2x2(s)
  [
    "#{s[1]}#{s[0]}/",
    "#{s[4]}#{s[3]}"
  ].join
end

def vflip2x2(s)
  [
    "#{s[3]}#{s[4]}/",
    "#{s[0]}#{s[1]}"
  ].join
end

def rot2x2(s)
  [
    "#{s[3]}#{s[0]}/",
    "#{s[4]}#{s[1]}"
  ].join
end

def hflip3x3(s)
  [
    "#{s[2]}#{s[1]}#{s[0]}/",
    "#{s[6]}#{s[5]}#{s[4]}/",
    "#{s[10]}#{s[9]}#{s[8]}"
  ].join
end

def vflip3x3(s)
  [
    "#{s[8]}#{s[9]}#{s[10]}/",
    "#{s[4]}#{s[5]}#{s[6]}/",
    "#{s[0]}#{s[1]}#{s[2]}"
  ].join
end

def rot3x3(s)
  [
    "#{s[8]}#{s[4]}#{s[0]}/",
    "#{s[9]}#{s[5]}#{s[1]}/",
    "#{s[10]}#{s[6]}#{s[2]}",
  ].join
end

def transforms(s)
  if s.size == 5
    [
      s,
      hflip2x2(s),
      vflip2x2(s),
      rot2x2(s),
      hflip2x2(rot2x2(s)),
      vflip2x2(rot2x2(s)),
      rot2x2(rot2x2(s)),
      hflip2x2(rot2x2(rot2x2(s))),
      vflip2x2(rot2x2(rot2x2(s))),
      rot2x2(rot2x2(rot2x2(s))),
      hflip2x2(rot2x2(rot2x2(rot2x2(s)))),
      vflip2x2(rot2x2(rot2x2(rot2x2(s))))
    ].uniq
  else
    [
      s,
      hflip3x3(s),
      vflip3x3(s),
      rot3x3(s),
      hflip3x3(rot3x3(s)),
      vflip3x3(rot3x3(s)),
      rot3x3(rot3x3(s)),
      hflip3x3(rot3x3(rot3x3(s))),
      vflip3x3(rot3x3(rot3x3(s))),
      rot3x3(rot3x3(rot3x3(s))),
      hflip3x3(rot3x3(rot3x3(rot3x3(s)))),
      vflip3x3(rot3x3(rot3x3(rot3x3(s))))
    ].uniq
  end
end

def rule_for(s, block_size)
  slashed = s.scan(/.{#{block_size}}/).join("/")
  match = transforms(slashed).find { |t| !@rules[t].nil? }

  unless @rules.has_key?(match)
    puts "No rule matches: #{slashed}"
    exit 1
  end

  @rules[match]
end

# splits imginto 2x2 or 3x3 blocks depending on size % 2 == 0
def get_blocks(img, size)
  block_size = (size % 2 == 0 ? 2 : 3)
  blocks = []

  0.step(size - 1, block_size) do |i|
   0.step(size - 1, block_size) do |j|
     tmp = ""
     0.upto(block_size - 1) do |k|
       tmp << img[(i + k) * size + j, block_size]
     end
     blocks << tmp
   end 
  end

  blocks
end

def enhance(img)
  enhanced = ""
  size = Math.sqrt(img.size)
  block_size = (size % 2 == 0 ? 2 : 3)

  # Split image into blocks of appropriate size
  blocks = get_blocks(img, size)

  # Then for each block enhance it using the corresponding rule
  blocks = blocks.map do |b|
    rule_for(b, block_size).split("/").join
  end

  # Finally assemble enhanced blocks into a new image
  if blocks.size > 1
    blocks.each_slice(size / block_size) do |slice|
      tmp = slice.map do |e|
        e.scan(/.{#{block_size + 1}}/)
      end

      enhanced << tmp.transpose.map(&:join).join
    end
  else
    enhanced << blocks.join
  end

  enhanced
end

iterations = ARGV[0].to_i

1.upto(iterations) do |i|
  @image = enhance(@image)
  puts "#{i}:"
  pgrid(@image)
  puts
end

puts "Number of pixels that stay on after #{iterations} iterations: #{@image.count("#")}"
