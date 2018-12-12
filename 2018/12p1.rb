plan = Hash.new(".")
sample = true
generations = 20

if sample
  offset = 4
	is = "#..#.#..##......###...###"
	plan["...##"] = "#"
	plan["..#.."] = "#"
	plan[".#..."] = "#"
	plan[".#.#."] = "#"
	plan[".#.##"] = "#"
	plan[".##.."] = "#"
	plan[".####"] = "#"
	plan["#.#.#"] = "#"
	plan["#.###"] = "#"
	plan["##.#."] = "#"
	plan["##.##"] = "#"
	plan["###.."] = "#"
	plan["###.#"] = "#"
	plan["####."] = "#"
else
  offset = 3
	is = "#.####...##..#....#####.##.......##.#..###.#####.###.##.###.###.#...#...##.#.##.#...#..#.##..##.#.##"
	plan[".##.."] = "."
	plan["..##."] = "#"
	plan[".#..#"] = "#"
	plan[".#.#."] = "."
	plan["..#.."] = "#"
	plan["###.."] = "#"
	plan["##..#"] = "."
	plan["##..."] = "#"
	plan["#.###"] = "#"
	plan[".##.#"] = "#"
	plan["#...."] = "."
	plan["###.#"] = "."
	plan["....."] = "."
	plan[".#..."] = "#"
	plan["....#"] = "."
	plan["#.#.."] = "."
	plan["...#."] = "#"
	plan["#...#"] = "."
	plan["##.#."] = "."
	plan[".#.##"] = "#"
	plan["..#.#"] = "#"
	plan["#.#.#"] = "."
	plan[".####"] = "."
	plan["#####"] = "."
	plan["..###"] = "."
	plan["...##"] = "."
	plan["#..##"] = "."
	plan["#.##."] = "."
	plan["#..#."] = "#"
	plan[".###."] = "#"
	plan["##.##"] = "#"
	plan["####."] = "."
end

(0..generations).each do |i|
  tmp0 = is.dup

  # find index of first # in order to figure out if the string needs to be
  # extended
  idx = tmp0.index("#")
  if idx < 3
    pad = "." * (2 - idx)
    tmp0 = "#{pad}#{tmp0}"
  end

  idx = tmp0.rindex("#")
  if idx > tmp0.length - 3
    pad = "." * (idx - (tmp0.length - 3))
    tmp0 = "#{tmp0}#{pad}"
  end

  puts "#{i}: #{tmp0}"

  break if i == generations

  tmp1 = tmp0.dup

  tmp0.split("").each_with_index do |v, i|
    if i < 2
      tmp1[i] = plan["#{"." * (2 - i)}#{tmp0[0..i + 2]}"]
    elsif i > tmp0.length - 3
      tmp1[i] = plan["#{tmp0[i - 2..-1]}#{"." * (i - (tmp0.length - 3))}"]
    else
      tmp1[i] = plan[tmp0[i - 2..i + 2]]
    end
  end

  is = tmp1
end

sum = 0
is.split("").each_with_index do |v, i|
  if v == "#"
    sum += i - offset
  end
end

puts "Sum: #{sum}"
