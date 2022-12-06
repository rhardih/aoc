function deduplicate(string) {
  result = ""
  delete deduped

  split(string, chars, "")

  for (c in chars) deduped[chars[c]] = c
  for (c in deduped) result = result c

  return result
}

{
  # Part 1
  for (i = 4; i <= length($0); ++i) {
    group = substr($0, i - 3, 4)

    if (length(group) == length(deduplicate(group))) {
      print i
      break
    }
  }

  # Part 2
  for (i = 14; i <= length($0); ++i) {
    group = substr($0, i - 13, 14)

    if (length(group) == length(deduplicate(group))) {
      print i
      break
    }
  }
}
