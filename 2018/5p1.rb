pol = STDIN.read.chomp.split("")
tmp = ""

loop do
  tmp = pol.reduce do |acc, a|
    if !acc.empty? && (acc[-1].ord - a.ord).abs == 32
      acc[0..-2]
    else
      acc + a
    end
  end

  break if tmp.length == pol.length

  pol = tmp.split("")
end

puts "Units remaining after fully reacting the polymer: #{tmp.length}"
