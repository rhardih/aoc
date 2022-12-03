BEGIN {
  scores["A", "X"] = 4
  scores["A", "Y"] = 8
  scores["A", "Z"] = 3
  scores["B", "X"] = 1
  scores["B", "Y"] = 5
  scores["B", "Z"] = 9
  scores["C", "X"] = 7
  scores["C", "Y"] = 2
  scores["C", "Z"] = 6

  choices["A", "X"] = "Z"
  choices["A", "Y"] = "X"
  choices["A", "Z"] = "Y"
  choices["B", "X"] = "X"
  choices["B", "Y"] = "Y"
  choices["B", "Z"] = "Z"
  choices["C", "X"] = "Y"
  choices["C", "Y"] = "Z"
  choices["C", "Z"] = "X"
}

/[A-C] [X-Z]/ {
  p1score = p1score + scores[$1, $2]
  p2score = p2score + scores[$1, choices[$1, $2]]
}

END {
  print "Part 1 total score: " p1score
  print "Part 2 total score: " p2score
}
