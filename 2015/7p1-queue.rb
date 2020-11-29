MAX_INT = 2**16
circuit = {}
queue = Queue.new

STDIN.read.split("\n").each { |i| queue.push i }

def bound(n)
  if n > MAX_INT
    n - MAX_INT
  elsif n < 0
    n + MAX_INT
  else
    n
  end
end

until queue.empty?
  instruction = queue.pop

  case instruction
  when /^(\d+) -> ([a-z]+)$/
    circuit[$2] = $1.to_i
    next
  when /^([a-z]+) -> ([a-z]+)$/
    if circuit.key?($1)
      circuit[$2] = circuit[$1]
      next
    end
  when /^([a-z]+) AND ([a-z]+) -> ([a-z]+)$/
    if circuit.key?($1) && circuit.key?($2)
      circuit[$3] = bound(circuit[$1] & circuit[$2])
      next
    end
  when /^(\d+) AND ([a-z]+) -> ([a-z]+)$/
    if circuit.key?($2)
      circuit[$3] = $1.to_i & circuit[$2]
      next
    end
  when /^([a-z]+) OR ([a-z]+) -> ([a-z]+)$/
    if circuit.key?($1) && circuit.key?($2)
      circuit[$3] = bound(circuit[$1] | circuit[$2])
      next
    end
  when /^([a-z]+) LSHIFT (\d+) -> ([a-z]+)$/
    if circuit.key?($1)
      circuit[$3] = bound(circuit[$1] << $2.to_i)
      next
    end
  when /^([a-z]+) RSHIFT (\d+) -> ([a-z]+)$/
    if circuit.key?($1)
      circuit[$3] = bound(circuit[$1] >> $2.to_i)
      next
    end
  when /^NOT ([a-z]+) -> ([a-z]+)$/
    if circuit.key?($1)
      circuit[$2] = bound(~circuit[$1])
      next
    end
  end

  queue.push(instruction)
end

puts "Signal ultimately provided to wire a: #{circuit["a"]}"
