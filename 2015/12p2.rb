=begin

--- Part Two ---

Uh oh - the Accounting-Elves have realized that they double-counted everything
red.

Ignore any object (and all of its children) which has any property with the
value "red". Do this only for objects ({...}), not arrays ([...]).

- [1,2,3] still has a sum of 6.
- [1,{"c":"red","b":2},3] now has a sum of 4, because the middle object is
  ignored.
- {"d":"red","e":[1,2,3,4],"f":5} now has a sum of 0, because the entire
  structure is ignored.
- [1,"red",5] has a sum of 6, because "red" in an array has no effect.

=end

require 'json'

document = JSON.parse(STDIN.read)

def sum(object)
  case object
  when Array
    object.reduce(0) { |acc, el| acc + sum(el) }
  when Hash
    return 0 if object.any? { |_, value| value == 'red' }

    object.reduce(0) do |acc, el|
      _, value = el
      acc + sum(value)
    end
  when Integer
    object
  when String
    object.to_i
  end
end

puts "Sum of all numbers in the document: #{sum(document)}"
