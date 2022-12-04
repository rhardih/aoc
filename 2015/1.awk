BEGIN {
  FS=""
}

{
  for (i = 1; i <= NF; ++i) {
    if ($i == "(") {
      floor = floor + 1
    } else {
      floor = floor - 1
    }

    if (floor < 0 && pos == 0) pos = i
  }
}

END {
  print "Part 1 - Final floor: " floor
  print "Part 2 - Position: " pos
}
