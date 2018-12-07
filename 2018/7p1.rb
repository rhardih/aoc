dependencies = Hash.new(&-> (h, k) { h[k] = Array.new })

STDIN.read.split("\n").each do |line|
  line.match(/Step (\w) must be finished before step (\w) can begin./) do |m|
    dependencies[m[2]] << m[1]
    dependencies[m[1]] # triggers default proc
  end
end

# Initial steps that are not dependant on others
available = dependencies.select { |_, v| v.empty? }
dependencies.reject! { |_, v| v.empty? }
steps = ""

until available.empty?
  head = available.keys.sort.first
  dependencies.each { |_, v| v.delete(head) }

  available.delete(head)
  steps << head

  available.merge!(dependencies.select { |_, v| v.empty? })
  dependencies.reject! { |_, v| v.empty? }
end

puts "Order the steps should be completed: #{steps}"
