=begin

--- Part Two ---

Now, you're ready to choose a directory to delete.

The total disk space available to the filesystem is 70000000. To run the
update, you need unused space of at least 30000000. You need to find a
directory you can delete that will free up enough space to run the update.

In the example above, the total size of the outermost directory (and thus the
total amount of used space) is 48381165; this means that the size of the unused
space must currently be 21618835, which isn't quite the 30000000 required by
the update. Therefore, the update still requires a directory with total size of
at least 8381165 to be deleted before it can run.

To achieve this, you have the following options:

- Delete directory e, which would increase unused space by 584.
- Delete directory a, which would increase unused space by 94853.
- Delete directory d, which would increase unused space by 24933642.
- Delete directory /, which would increase unused space by 48381165.

Directories e and a are both too small; deleting them would not free up enough
space. However, directories d and / are both big enough! Between these, choose
the smallest: d, increasing unused space by 24933642.

Find the smallest directory that, if deleted, would free up enough space on the
filesystem to run the update. What is the total size of that directory?

=end

file_system = {}
current_dir = nil
total_disk_space = 70000000
needed_space = 30000000

def total_size(directory)
  directory.reduce(0) do |acc, entry|
    k, v = entry

    if k == :parent
      acc
    else
      if v.is_a?(Integer) # file
        acc + v
      else # dir
        acc + total_size(v)
      end
    end
  end
end

STDIN.read.split("\n").each do |line|
  case line
  when /^\$ cd \//
    new_dir = { parent: nil }
    file_system["/"] = new_dir
    current_dir = new_dir
  when /^\$ cd ([\w\/\.]+)/
    if $1 == ".."
      current_dir = current_dir[:parent]
    else
      current_dir = current_dir[$1]
    end
  when /^dir ([\w\.]+)/
    current_dir[$1] = { parent: current_dir }
  when /^(\d+) ([\w\.]+)/
    current_dir[$2] = $1.to_i
  when /^\$ ls/
  else
    throw "unmatched input line: #{line}"
  end
end

current_used_space = total_disk_space - total_size(file_system["/"])
minimum_size_needed = needed_space - current_used_space

puts "Used space: #{current_used_space}"
puts "Minimum directory size needed for deletion: #{minimum_size_needed}"

queue = Queue.new
queue.push(file_system["/"])

rm_candidate_size = total_size(file_system["/"])

until queue.empty?
  rm_candidate = queue.pop

  ts = total_size(rm_candidate)

	if ts > minimum_size_needed && ts < rm_candidate_size
    rm_candidate_size = ts
  end

  rm_candidate.each do |k, v|
    next if k == :parent
    next if v.is_a?(Integer)

    queue.push(v)
  end
end

puts "Total size of directory to be deleted: #{rm_candidate_size}"
