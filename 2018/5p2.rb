pol = STDIN.read.chomp.split("")

shortest = pol.length

'a'.upto('z') do |l|
  tmp = ""
  new_pol = pol.reject { |u| u == l || u == l.upcase }

  loop do
    tmp = new_pol.reduce do |acc, a|
      if !acc.empty? && (acc[-1].ord - a.ord).abs == 32
        acc[0..-2]
      else
        acc + a
      end
    end

    break if tmp.length == new_pol.length

    new_pol = tmp.split("")
  end

  if tmp.length < shortest
    shortest = tmp.length
  end
end

puts "Shortest producible polymer: #{shortest}"
