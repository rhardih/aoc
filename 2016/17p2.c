/**
 * --- Day 17: Two Steps Forward ---
 *
 * You're trying to access a secure vault protected by a 4x4 grid of small rooms
 * connected by doors. You start in the top-left room (marked S), and you can
 * access the vault (marked V) once you reach the bottom-right room:
 *
 * #########
 * #S| | | #
 * #-#-#-#-#
 * # | | | #
 * #-#-#-#-#
 * # | | | #
 * #-#-#-#-#
 * # | | |
 * ####### V
 *
 * Fixed walls are marked with #, and doors are marked with - or |.
 *
 * The doors in your current room are either open or closed (and locked) based
 * on the hexadecimal MD5 hash of a passcode (your puzzle input) followed by a
 * sequence of uppercase characters representing the path you have taken so far
 * (U for up, D for down, L for left, and R for right).
 *
 * Only the first four characters of the hash are used; they represent,
 * respectively, the doors up, down, left, and right from your current position.
 * Any b, c, d, e, or f means that the corresponding door is open; any other
 * character (any number or a) means that the corresponding door is closed and
 * locked.
 *
 * To access the vault, all you need to do is reach the bottom-right room;
 * reaching this room opens the vault and all doors in the maze.
 *
 * For example, suppose the passcode is hijkl. Initially, you have taken no
 * steps, and so your path is empty: you simply find the MD5 hash of hijkl
 * alone. The first four characters of this hash are ced9, which indicate that
 * up is open (c), down is open (e), left is open (d), and right is closed and
 * locked (9). Because you start in the top-left corner, there are no "up" or
 * "left" doors to be open, so your only choice is down.
 *
 * Next, having gone only one step (down, or D), you find the hash of hijklD.
 * This produces f2bc, which indicates that you can go back up, left (but that's
 * a wall), or right. Going right means hashing hijklDR to get 5745 - all doors
 * closed and locked. However, going up instead is worthwhile: even though it
 * returns you to the room you started in, your path would then be DU, opening a
 * different set of doors.
 *
 * After going DU (and then hashing hijklDU to get 528e), only the right door is
 * open; after going DUR, all doors lock. (Fortunately, your actual passcode is
 * not hijkl).
 *
 * Passcodes actually used by Easter Bunny Vault Security do allow access to the
 * vault if you know the right path. For example:
 *
 * - If your passcode were ihgpwlah, the shortest path would be DDRRRD.
 * - With kglvqrro, the shortest path would be DDUDRLRRUDRD.
 * - With ulqzkmiv, the shortest would be DRURDRUDDLLDLUURRDULRLDUUDDDRR.
 *
 * Given your vault's passcode, what is the shortest path (the actual path, not
 * just the length) to reach the vault?

 * --- Part Two ---
 *
 * You're curious how robust this security solution really is, and so you decide
 * to find longer and longer paths which still provide access to the vault. You
 * remember that paths always end the first time they reach the bottom-right
 * room (that is, they can never pass through it, only end in it).
 *
 * For example:
 *
 * - If your passcode were ihgpwlah, the longest path would take 370 steps.
 * - With kglvqrro, the longest path would be 492 steps long.
 * - With ulqzkmiv, the longest path would be 830 steps long.
 *
 * What is the length of the longest path that reaches the vault?
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

#include "openssl/md5.h"

#define INPUT "veumntbg"

#define MD5_LEN 33

enum { UP = -6, DOWN = 6, LEFT = -1, RIGHT = 1 };

int grid[36] = {
  0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0
};

#define STARTPOS 7
#define ENDPOS 28

void md5(char *s, char *res) {
  unsigned char digest[MD5_DIGEST_LENGTH];

  MD5((const unsigned char *)s, strlen((const char *)s), (unsigned char *)&digest);

  for(int i = 0; i < 16; i++)
    sprintf(&res[i*2], "%02x", (unsigned int)digest[i]);
}

int find_path(int pos, char *path, int steps) {
  int lp = 0, tmp;
  char md5h[MD5_LEN];
  char *buf = malloc((steps + 8 + 1) * sizeof(char));
  int up_ok, down_ok, left_ok, right_ok, only_down, only_right;

  sprintf(buf, "%s%s", INPUT, path);
  md5(buf, md5h);

  up_ok = grid[pos + UP] && md5h[0] >= 'b' && md5h[0] <= 'f';
  down_ok = grid[pos + DOWN] && md5h[1] >= 'b' && md5h[1] <= 'f';
  left_ok = grid[pos + LEFT] && md5h[2] >= 'b' && md5h[2] <= 'f';
  right_ok = grid[pos + RIGHT] && md5h[3] >= 'b' && md5h[3] <= 'f';

  only_down = down_ok && !(up_ok || left_ok || right_ok);

  if (pos == ENDPOS + UP && only_down) return steps + 1;

  only_right = right_ok && !(up_ok || down_ok || left_ok);

  if (pos == ENDPOS + LEFT && only_right) return steps + 1;

  if (up_ok) {
    sprintf(buf, "%s%c", path, 'U');

    if ((tmp = find_path(pos + UP, buf, steps + 1)) > lp)
      lp = tmp;
  }

  if (pos + DOWN != ENDPOS && down_ok) {
    sprintf(buf, "%s%c", path, 'D');

    if ((tmp = find_path(pos + DOWN, buf, steps + 1)) > lp)
      lp = tmp;
  }

  if (left_ok) {
    sprintf(buf, "%s%c", path, 'L');

    if ((tmp = find_path(pos + LEFT, buf, steps + 1)) > lp)
      lp = tmp;
  }

  if (pos + RIGHT != ENDPOS && right_ok) {
    sprintf(buf, "%s%c", path, 'R');

    if ((tmp = find_path(pos + RIGHT, buf, steps + 1)) > lp)
      lp = tmp;
  }

  // All above was dead ends and moving to the exit is still a possibility
  if (lp == 0) {
    if ((pos + DOWN == ENDPOS && down_ok) ||
        (pos + RIGHT == ENDPOS && right_ok)) {
      return steps + 1;
    }
  }

  free(buf);

  return lp;
}

int main(int argc, char const *argv[])
{
  int steps = find_path(STARTPOS, "", 0);

  printf("The longest path is %d steps\n", steps);

  return 0;
}
