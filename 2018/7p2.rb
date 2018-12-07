dependencies = Hash.new(&-> (h, k) { h[k] = Array.new })
tasks = []
time = 0
offset = 60
workers = 5
finish = 0

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

loop do
  while tasks.length < workers && available.any?
    head = available.keys.sort.first
    available.delete(head)

    tasks << { step: head, finish: time + head.ord - "A".ord + offset }
  end

  tasks.delete_if do |t|
    (t[:finish] == time).tap do |done|
      if done
        steps << t[:step]
        dependencies.each { |_, v| v.delete(t[:step]) }
      end
    end
  end

  available.merge!(dependencies.select { |_, v| v.empty? })
  dependencies.reject! { |_, v| v.empty? }

  finish = time + 1

  break if available.empty? && tasks.empty?

  time += 1
end

puts "Time to complete all of the steps: #{finish}"
