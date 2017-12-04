count = 0

STDIN.read.split("\n").each do |l|
  words = l.split(" ")
  valid = true

  words.combination(2) do |w0, w1|
    next if w0.length != w1.length

    p0 = w0.split("").permutation.map(&:join).uniq
    p1 = w1.split("").permutation.map(&:join).uniq

    valid = (p0 & p1).length == 0

    break if !valid
  end

  count += 1 if valid
end

puts count
