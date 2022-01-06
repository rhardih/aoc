=begin

--- Part Two ---

The resulting polymer isn't nearly strong enough to reinforce the submarine.
You'll need to run more steps of the pair insertion process; a total of 40 steps
should do it.

In the above example, the most common element is B (occurring 2192039569602
times) and the least common element is H (occurring 3849876073 times);
subtracting these produces 2188189693529.

Apply 40 steps of pair insertion to the polymer template and find the most and
least common elements in the result. What do you get if you take the quantity of
the most common element and subtract the quantity of the least common element?

=end

template, tmp = STDIN.read.split("\n\n")

element_counts = template.chars.reduce(Hash.new(0)) do |memo, char|
  memo[char] += 1
  memo
end

rules = tmp.split("\n").reduce({}) do |memo, rule|
  from, to = rule.split(" -> ")
  memo[from] = to
  memo
end

pairs = template.chars.each_cons(2).reduce(Hash.new(0)) do |memo, pair|
  memo[pair.join] = 1
  memo
end

40.times do |step|
  tmp = Hash.new(0)

  pairs.each do |pair, count|
    new_el = rules[pair]

    # Create the two new pairs which will be formed by inserting an element in
    # the middle of the current pair
    el0, el1 = pair.chars
    p0 = [el0, new_el].join
    p1 = [new_el, el1].join

    # These new pairs, will be inserted exactly the number of times the previous
    # pair was there
    tmp[p0] += pairs[pair]
    tmp[p1] += pairs[pair]
  end

  pairs = tmp
end

element_counts = pairs.reduce(Hash.new(0)) do |memo, entry|
  key, value = entry
  memo[key[0]] += value
  memo
end

# Since we only count the first letter in each pair, we'll miss a single
# instance of the last letter of the string, therefor we add one to the count of
# that letter
element_counts[template[-1]] += 1

min, max = element_counts.minmax_by { |_, v| v }.map(&:last)

puts "Most common - least common: #{max - min}"
