foo = STDIN.read.split("\n")
frequencies = {}
i = 0
f = 0
duplicate = 0

loop do 
  l = foo[i] 
  i = (i + 1) % foo.length

  f += l.to_i

  if frequencies.has_key?(f)
    duplicate = f
    break
  end

  frequencies[f] = 0
end

puts "The resulting frequency #{duplicate}"
