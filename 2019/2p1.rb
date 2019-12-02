opcodes = STDIN.read.split(",").map(&:to_i)

opcodes[1] = 12
opcodes[2] = 2

(0...opcodes.length).step(4).each do |index|
  in0 = opcodes[index + 1]
  in1 = opcodes[index + 2]
  out = opcodes[index + 3]

  case opcodes[index]
  when 1
    opcodes[out] = opcodes[in0] + opcodes[in1]
  when 2
    opcodes[out] = opcodes[in0] * opcodes[in1]
  when 99
    puts "Value at position 0: #{opcodes[0]}"
    exit(0)
  end
end
