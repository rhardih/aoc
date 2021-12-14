template, tmp = STDIN.read.split("\n\n")

rules = tmp.split("\n").reduce({}) do |memo, rule|
  from, to = rule.split(" -> ")

  memo[from] = to

  memo
end

puts "Template:     #{template}"

10.times do |step|
  template = template.chars.each_cons(2).map do |pair|
    insert = rules[pair.join]

    [pair.first, insert, pair.last]
  end.reduce("") do |memo, triple|
    if memo.empty?
      triple.join
    else
      memo << triple.join[1..-1]
    end
  end

  puts "After step #{step + 1}: #{template}"
end

counts = template.chars.group_by { |char| [char, template.count(char)] }.keys.
  sort_by { |char, count| count }

least_common = counts.first
most_common = counts.last

puts "Most common - least common: #{most_common[1] - least_common[1]}"
