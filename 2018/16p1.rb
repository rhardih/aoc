require "scanf"

base_op =  -> (r, i, &block) { block.call(i[1], i[2], i[3]); r }

ops = {
  addr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] + r[b] }
  end,
  addi: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] + b }
  end,
  mulr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] * r[b] }
  end,
  muli: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] * b }
  end,
  banr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] & r[b] }
  end,
  bani: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] & b }
  end,
  borr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] | r[b] }
  end,
  bori: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] | b }
  end,
  setr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] }
  end,
  seti: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = a }
  end,
  gtir: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = a > r[b] ? 1 : 0 }
  end,
  gtri: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] > b ? 1 : 0 }
  end,
  gtrr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] > r[b] ? 1 : 0 }
  end,
  eqir: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = a == r[b] ? 1 : 0 }
  end,
  eqri: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] == b ? 1 : 0 }
  end,
  eqrr: -> (r, i) do
    base_op.call(r, i) { |a, b, c| r[c] = r[a] == r[b] ? 1 : 0 }
  end
}

samples, instructions = STDIN.read.split("\n\n\n")
result = 0

samples.split("\n\n").each do |sample|
  lbefore, linstruction, lafter = sample.split("\n")

  before = lbefore.scanf("Before: [%d, %d, %d, %d]")
  instruction = linstruction.scanf("%d %d %d %d")
  after = lafter.scanf("After: [%d, %d, %d, %d]")

  behaves = 0
  ops.each do |name, op|
    tmp = op.call(before.dup, instruction)
    behaves += 1 if  tmp == after
  end

  result += 1 if behaves >= 3
end

puts "Number of samples in input behaving like three or more opcodes: #{result}"
