=begin

--- Part Two ---

You manage to answer the child's questions and they finish part 1 of their
homework, but get stuck when they reach the next section: advanced math.

Now, addition and multiplication have different precedence levels, but they're
not the ones you're familiar with. Instead, addition is evaluated before
multiplication.

For example, the steps to evaluate the expression 1 + 2 * 3 + 4 * 5 + 6 are now
as follows:

1 + 2 * 3 + 4 * 5 + 6
  3   * 3 + 4 * 5 + 6
  3   *   7   * 5 + 6
  3   *   7   *  11
     21       *  11
         231

Here are the other examples from above:

- 1 + (2 * 3) + (4 * (5 + 6)) still becomes 51.
- 2 * 3 + (4 * 5) becomes 46.
- 5 + (8 * 3 + 9 + 3 * 4 * 3) becomes 1445.
- 5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4)) becomes 669060.
- ((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 23340.

What do you get if you add up the results of evaluating the homework problems
using these new rules?

=end

lines = STDIN.read.split("\n").map { |l| l.gsub(/\s/, "") }

result = 0

lines.each do |l|
  nests = Hash.new { |h,k| h[k] = [] }
  nesting = 0

  tokens = l.split("")

  reduce_additions = lambda do |n|
    until nests[n].none? { |t| t == :+ }
      idx = nests[n].find_index(:+)

      a = nests[n][idx - 1]
      b = nests[n][idx + 1]

      nests[n][idx] = a + b

      nests[n].delete_at(idx - 1)
      nests[n].delete_at(idx)
    end
  end

  reduce_multiplications = lambda do |n|
    until nests[n].size == 1
      a = nests[n].shift
      op = nests[n].shift
      b = nests[n].shift

      nests[n].unshift a * b
    end
  end

  until tokens.empty?
    token = tokens.shift

    case token
    when /\d/
      nests[nesting].push token.to_i
    when /\(/
      nesting += 1
    when /\)/
      reduce_additions.call(nesting)
      reduce_multiplications.call(nesting)

      nests[nesting - 1].push nests[nesting].pop

      nesting -= 1
    when /\+/
      nests[nesting].push :+
    when /\*/
      nests[nesting].push :*
    end
  end

  reduce_additions.call(0)
  reduce_multiplications.call(0)

  result += nests[0].first
end

puts "Sum of the results using new rules: #{result}"
