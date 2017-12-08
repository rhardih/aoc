@registers = Hash.new(0)

evaluator = -> (reg, cond, val) {
  eval %Q{@registers["#{reg}"] #{cond} #{val}}
}

STDIN.read.split("\n").each do |l|
  reg0, instruction, val0, _, reg1, cond, val1 = l.split

  if evaluator.call(reg1, cond, val1)
    case instruction
    when "inc"
      @registers[reg0] += val0.to_i
    when "dec"
      @registers[reg0] -= val0.to_i
    end
  end
end

max = @registers.max_by { |k, v| v }

puts %Q{Register of maximum value is "#{max[0]}": #{max[1]}"}
