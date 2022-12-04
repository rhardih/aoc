{
  match($0, /([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)/, pairs)

  if (pairs[1] <= pairs[3] && pairs[2] >= pairs[4] ||
      pairs[3] <= pairs[1] && pairs[4] >= pairs[2]) {
    contained = contained + 1
  }

  if (pairs[3] <= pairs[2] && pairs[1] <= pairs[4]) {
    overlapping = overlapping + 1
  }
}

END {
  print "Part 1 - Assignment pairs fully containing another: " contained
  print "Part 2 - Assignment pairs overlapping: " overlapping
}
