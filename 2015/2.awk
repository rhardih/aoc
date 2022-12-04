BEGIN {  FS="x" }

{
  l = $1
  w = $2
  h = $3

  lw = l * w
  wh = w * h
  hl = h * l

  min_side = lw

  if (wh < min_side) min_side = wh
  if (hl < min_side) min_side = hl

  area = 2*lw + 2*wh + 2*hl + min_side

  sq_paper = sq_paper + area

  if (l < w) {
    if (w < h) {
      smallest_perimeter = 2 * l + 2 * w
    } else {
      smallest_perimeter = 2 * l + 2 * h
    }
  } else {
    if (l < h) {
      smallest_perimeter = 2 * w + 2 * l
    } else {
      smallest_perimeter = 2 * w + 2 * h
    }
  }

  bow = l * w * h

  ft_ribbon = ft_ribbon + smallest_perimeter + bow
}

END {
  print "Part 1 - Total square feet of wrapping paper: " sq_paper
  print "Part 2 - Feet or ribbon to order: " ft_ribbon
}
