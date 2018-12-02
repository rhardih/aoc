ids = STDIN.read.split("\n")
ids.combination(2) do |a, b|
  tmp = ""
  0.upto(a.length - 1) do |i|
    if a[i] == b[i]
      tmp << a[i]
    end
  end

  if tmp.length == a.length - 1
    puts tmp
  end
end
