MAX_INT = 2**16
circuit = {}
instructions = STDIN.read.split("\n")
resolved = []

def bound(n)
  if n > MAX_INT
    n - MAX_INT
  elsif n < 0
    n + MAX_INT
  else
    n
  end
end

# Seed the sorted instructions with the initial direct value assignments
sorted, instructions = instructions.partition do |ins|
  val = /^(\d+) -> ([a-z]+)$/.match(ins)
  resolved << $~[2] unless $~.nil?
  val
end

until instructions.empty?
  tmp = []

  plucked, instructions = instructions.partition do |ins|
    exp, out = ins.split(" -> ")
    val = false

    case exp
    when /^([a-z]+)$/
      val = resolved.include?($1)
    when /^([a-z]+) AND ([a-z]+)$/
      val = resolved.include?($1) && resolved.include?($2)
    when /^(\d+) AND ([a-z]+)$/
      val = resolved.include?($2)
    when /^([a-z]+) OR ([a-z]+)$/
      val = resolved.include?($1) && resolved.include?($2)
    when /^([a-z]+) LSHIFT (\d+)$/
      val = resolved.include?($1)
    when /^([a-z]+) RSHIFT (\d+)$/
      val = resolved.include?($1)
    when /^NOT ([a-z]+)$/
      val = resolved.include?($1)
    end

    tmp << out if val

    val
  end

  resolved += tmp
  sorted += plucked
end

sorted.each do |instruction|
  case instruction
  when /^(\d+) -> ([a-z]+)$/
    circuit[$2] = $1.to_i
  when /^([a-z]+) -> ([a-z]+)$/
    circuit[$2] = circuit[$1]
  when /^([a-z]+) AND ([a-z]+) -> ([a-z]+)$/
    circuit[$3] = bound(circuit[$1] & circuit[$2])
  when /^(\d+) AND ([a-z]+) -> ([a-z]+)$/
    circuit[$3] = $1.to_i & circuit[$2]
  when /^([a-z]+) OR ([a-z]+) -> ([a-z]+)$/
    circuit[$3] = bound(circuit[$1] | circuit[$2])
  when /^([a-z]+) LSHIFT (\d+) -> ([a-z]+)$/
    circuit[$3] = bound(circuit[$1] << $2.to_i)
  when /^([a-z]+) RSHIFT (\d+) -> ([a-z]+)$/
    circuit[$3] = bound(circuit[$1] >> $2.to_i)
  when /^NOT ([a-z]+) -> ([a-z]+)$/
    circuit[$2] = bound(~circuit[$1])
  end
end

puts "Signal ultimately provided to wire a: #{circuit["a"]}"
