/**
 * --- Day 9: Explosives in Cyberspace ---
 * 
 * Wandering around a secure area, you come across a datalink port to a new part
 * of the network. After briefly scanning it for interesting files, you find one
 * file in particular that catches your attention. It's compressed with an
 * experimental format, but fortunately, the documentation for the format is
 * nearby.
 * 
 * The format compresses a sequence of characters. Whitespace is ignored. To
 * indicate that some sequence should be repeated, a marker is added to the
 * file, like (10x2). To decompress this marker, take the subsequent 10
 * characters and repeat them 2 times. Then, continue reading the file after the
 * repeated data. The marker itself is not included in the decompressed output.
 * 
 * If parentheses or other characters appear within the data referenced by a
 * marker, that's okay - treat it like normal data, not a marker, and then
 * resume looking for markers after the decompressed section.
 * 
 * For example:
 * 
 * - ADVENT contains no markers and decompresses to itself with no changes,
 *   resulting in a decompressed length of 6.
 * - A(1x5)BC repeats only the B a total of 5 times, becoming ABBBBBC for a
 *   decompressed length of 7.
 * - (3x3)XYZ becomes XYZXYZXYZ for a decompressed length of 9.
 * - A(2x2)BCD(2x2)EFG doubles the BC and EF, becoming ABCBCDEFEFG for a
 *   decompressed length of 11.
 * - (6x1)(1x3)A simply becomes (1x3)A - the (1x3) looks like a marker, but
 *   because it's within a data section of another marker, it is not treated any
 *   differently from the A that comes after it. It has a decompressed length of
 *   6.
 * - X(8x2)(3x3)ABCY becomes X(3x3)ABC(3x3)ABCY (for a decompressed length of
 *   18), because the decompressed data from the (8x2) marker (the (3x3)ABC) is
 *   skipped and not processed further.
 * 
 * What is the decompressed length of the file (your puzzle input)? Don't count
 * whitespace.
 *
 * --- Part Two ---
 * 
 * Apparently, the file actually uses version two of the format.
 * 
 * In version two, the only difference is that markers within decompressed data
 * are decompressed. This, the documentation explains, provides much more
 * substantial compression capabilities, allowing many-gigabyte files to be
 * stored in only a few kilobytes.
 * 
 * For example:
 * 
 * - (3x3)XYZ still becomes XYZXYZXYZ, as the decompressed section contains no
 *   markers.
 * - X(8x2)(3x3)ABCY becomes XABCABCABCABCABCABCY, because the decompressed data
 *   from the (8x2) marker is then further decompressed, thus triggering the
 *   (3x3) marker twice for a total of six ABC sequences.
 * - (27x12)(20x12)(13x14)(7x10)(1x12)A decompresses into a string of A repeated
 *   241920 times.
 * - (25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN becomes 445
 *   characters long.
 * 
 * Unfortunately, the computer you brought probably doesn't have enough memory
 * to actually decompress the file; you'll have to come up with another way to
 * get its decompressed length.
 * 
 * What is the decompressed length of the file using this improved format?
 */

#include "stdio.h"

/**
 * This solution is a bit hairy, so here's an explanation.
 *
 * In short the idea is to give each character in the input a weight, or
 * multiplier if you will. Then for each character, as the input is read,
 * increase its weight according to the decompression markers. This is roughly
 * the steps taken:
 *
 * - Initialise all characters weights to 1
 * - Scan input one character at a time and
 *   - if it's a normal character, count its weight towards the total length
 *   - if it's the beginning of a marker, read the marker and multiply character
 *     weights forward in the input, according to the values of the marker.
 * - Print out the value of length
 *
 * -----------------------------------------------------------------------------
 *
 * Using the second example from the puzzle description
 * as an input; "X(8x2)(3x3)ABCY", the algorithm would run as follows:
 *
 * 1.
 *
 * Weights: [111111111111111], length:  0
 *
 * "X(8x2)(3x3)ABCY"
 *  ^
 *
 * X is a normal character, so we add its weight to length.
 *
 * 2.
 *
 * Weights: [111111111111111], length:  1
 *
 * "X(8x2)(3x3)ABCY"
 *   ^
 *
 * ( is the beginning of a marker, so we read it and update the following
 * weights according to its values.
 *
 * 3.
 *
 * Weights: [111111222222221], length:  1
 *
 * "X(8x2)(3x3)ABCY"
 *        ^
 *
 * ( is the beginning of a marker, so we read it and update the following
 * weights according to its values.
 *
 * 4.
 *
 * Weights: [111111222226661], length:  1
 *
 * "X(8x2)(3x3)ABCY"
 *             ^
 *
 * A is a normal character, so we add its weight to length.
 *
 * 5.
 *
 * Weights: [111111222226661], length:  7
 *
 * "X(8x2)(3x3)ABCY"
 *              ^
 *
 * B is a normal character, so we add its weight to length.
 *
 * 6.
 *
 * Weights: [111111222226661], length:  13
 *
 * "X(8x2)(3x3)ABCY"
 *               ^
 *
 * C is a normal character, so we add its weight to length.
 *
 * 7.
 *
 * Weights: [111111222226661], length:  19
 *
 * "X(8x2)(3x3)ABCY"
 *                ^
 *
 * Y is a normal character, so we add its weight to length.
 *
 * 8.
 *
 * Weights: [111111222226661], length:  20
 *
 * "X(8x2)(3x3)ABCY"
 *                 ^
 *
 * We're at the end of input, so we read out the final result to be 20.
 */

int main(int argc, char const *argv[])
{
  char c;
  int index = 0, a, b;
  long i, pos, length = 0;

  fseek(stdin, 0, SEEK_END);
  long input_size = ftell(stdin);
  int multipliers[input_size], current_multiplier;
  for (i = 0; i < input_size; i++) multipliers[i] = 1;

  rewind(stdin);

  while(scanf("%c", &c) != EOF) {
    pos = ftell(stdin);
    current_multiplier = multipliers[pos - 1];

    if (c == '(') {
      scanf("%dx%d)", &a, &b);
      pos = ftell(stdin);

      for (i = pos; i < pos + a && i < input_size; i++)
      {
        multipliers[i] = current_multiplier * b;
      }
    } else if (c == '\n') {
      // skip whitespace
    } else {
      length += current_multiplier;
    }
  }

  printf("Decompressed length of file: %lu\n", length);

  return 0;
}
