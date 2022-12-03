BEGIN {
  FS=""

  # Make a lookup based on numeric value of ASCII characters
  # Uppercase characters start at 65, lowercase at 97
  for(n=97; n <= 122; n++) {
    ord[sprintf("%c", n)] = n - 96 # 1 - 26
  }
  for(n=65; n <= 90; n++) {
    ord[sprintf("%c", n)] = n - 64 + 26 # 27 - 52
  }
}

{
  # Part 1
  for (i = 1; i <= NF / 2; ++i) {
    for (j = NF / 2 + 1; j <= NF; ++j) {
      if ($i == $j) shared = $i
    }
  }

  p1sum = p1sum + ord[shared]

  # Part 2
  group[(NR % 3) + 1] = $0

  # Only act on every group of three lines
  if (NR % 3 == 0) {
    for (i = 0; i <= length(group[1]); ++i) {
      elf_1_item = substr(group[1], i, 1)

      for (j = 0; j <= length(group[2]); ++j) {
        elf_2_item = substr(group[2], j, 1)

        if (elf_1_item != elf_2_item) continue

        for (k = 0; k <= length(group[3]); ++k) {
          elf_3_item = substr(group[3], k, 1)

          if (elf_1_item == elf_3_item) {
            shared = elf_1_item
          }
        }
      }
    }

    p2sum = p2sum + ord[shared]
  }
}

END {
  print "Part 1 sum of the priorities: " p1sum
  print "Part 2 sum of the priorities: " p2sum
}
