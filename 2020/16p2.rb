=begin

--- Part Two ---

Now that you've identified which tickets contain invalid values, discard those
tickets entirely. Use the remaining valid tickets to determine which field is
which.

Using the valid ranges for each field, determine what order the fields appear on
the tickets. The order is consistent between all tickets: if seat is the third
field, it is the third field on every ticket, including your ticket.

For example, suppose you have the following notes:

class: 0-1 or 4-19
row: 0-5 or 8-19
seat: 0-13 or 16-19

your ticket:
11,12,13

nearby tickets:
3,9,18
15,1,5
5,14,9

Based on the nearby tickets in the above example, the first position must be
row, the second position must be class, and the third position must be seat; you
can conclude that in your ticket, class is 12, row is 11, and seat is 13.

Once you work out which field is which, look for the six fields on your ticket
that start with the word departure. What do you get if you multiply those six
values together?

=end

top, ticket, bottom = STDIN.read.split("\n\n")

rules = {}
possible_rules_for_index = {}
ticket_values = ticket.split("\n")[1].split(",").map(&:to_i)
valid_tickets = []

top.split("\n").map do |line|
  name, ranges = line.split(":")
  rules[name] = ranges.scan(/(\d+)-(\d+)/).map { |r| r.map(&:to_i) }
end

valid = top.split("\n").map do |line|
  line.scan(/(\d+)-(\d+)/).map do |tuple|
    low, high = tuple
    "#{low} <= v && v <= #{high}"
  end.join(" || ")
end.join(" || ")

bottom.split("\n")[1..-1].each do |ticket|
  if ticket.split(",").map(&:to_i).all? { |v| eval(valid) }
    valid_tickets << ticket
  end
end

# Create matrix from the valid tickets, then transpose it so the nth row,
# correspond to the previous nth column.
valid_ticket_values = valid_tickets.map { |vt| vt.split(",").map(&:to_i) }
columns = valid_ticket_values.transpose

# Create lists of "possible" rules for each ticket value index
columns.each_with_index do |column, i|
  rules.each do |name, ranges|
    all_valid = column.all? do |value|
      ranges.any? do |range|
        low, high = range
        low <= value && value <= high
      end
    end

    if all_valid
      if possible_rules_for_index.has_key?(i)
        possible_rules_for_index[i] << name
      else
        possible_rules_for_index[i] = [name]
      end
    end
  end
end

# Find where there's only one possible rule and delete it from all other
# candidates. Continue until all candidates only have one possible rule.
until possible_rules_for_index.values.all? { |values| values.size == 1 }
  possible_rules_for_index.each do |_,rule_names0|
    if rule_names0.size == 1
      possible_rules_for_index.each do |k,rule_names1|
        unless rule_names0 == rule_names1 
          possible_rules_for_index[k].delete(rule_names0[0])
        end
      end
    end
  end
end

mult = 1

possible_rules_for_index.each do |k,rule_names|
  mult *= ticket_values[k] if rule_names.first.start_with?("departure")
end

puts "Multiple of the six values starting with 'departure': #{mult}"
