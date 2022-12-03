function elf_end() {
  if (calories > most_calories) {
    most_calories = calories
  }

  elfs[i] = calories

  calories = 0

  i = i + 1
}

BEGIN { i = 0 }

/[0-9]+/ { calories = calories + $1 }

/^$/ { elf_end() }

END {
  elf_end()

  asort(elfs, sorted_elfs)
  last = length(sorted_elfs)

  print "Part 1:"
  print "Total calories carried by elf carrying the most:"
  print sorted_elfs[last]

  print "Part 2:"
  print "Total calories carried by the top three most carrying elfs:"

  print sorted_elfs[last] + sorted_elfs[last - 1] + sorted_elfs[last - 2]
}
