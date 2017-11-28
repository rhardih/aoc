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
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "openssl/md5.h"

#define MD5_LEN 33
#define min(a, b) ((a) < (b) ? (a) : (b))

enum { UP = -6, DOWN = 6, LEFT = -1, RIGHT = 1 } direction;

int grid[36] = {
  0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0
};

void md5(char *s, char *res) {
  unsigned char digest[MD5_DIGEST_LENGTH];

  MD5((const unsigned char *)s, strlen((const char *)s), (unsigned char *)&digest);

  for(int i = 0; i < 16; i++)
    sprintf(&res[i*2], "%02x", (unsigned int)digest[i]);
}

int find_path(int pos, const char *code, char *path, int steps, char **shortest) {
  int sp = INT_MAX, tmp;
  char md5hash[MD5_LEN];
  char *newpath;
  int plen = strlen(path), slen;
  char cat[plen + 8 + 1]; // code length is 8 + \0

  if (pos == 28) {
    slen = strlen(*shortest);
    if (slen == 0 || plen < slen)
      *shortest = path;
    return steps;
  }

  sprintf(cat, "%s%s", code, path);
  md5(cat, md5hash);

  if (grid[pos + UP] && md5hash[0] >= 'b' && md5hash[0] <= 'f') {
    newpath = malloc((plen + 2) * sizeof(char));
    sprintf(newpath, "%s%c", path, 'U');

    if ((tmp = find_path(pos + UP, code, newpath, steps + 1, shortest)) < sp)
      sp = tmp;
  }

  if (grid[pos + DOWN] && md5hash[1] >= 'b' && md5hash[1] <= 'f') {
    newpath = malloc((plen + 2) * sizeof(char));
    sprintf(newpath, "%s%c", path, 'D');

    if ((tmp = find_path(pos + DOWN, code, newpath, steps + 1, shortest)) < sp)
      sp = tmp;
  }

  if (grid[pos + LEFT] && md5hash[2] >= 'b' && md5hash[2] <= 'f') {
    newpath = malloc((plen + 2) * sizeof(char));
    sprintf(newpath, "%s%c", path, 'L');

    if ((tmp = find_path(pos + LEFT, code, newpath, steps + 1, shortest)) < sp)
      sp = tmp;
  }

  if (grid[pos + RIGHT] && md5hash[3] >= 'b' && md5hash[3] <= 'f') {
    newpath = malloc((plen + 2) * sizeof(char));
    sprintf(newpath, "%s%c", path, 'R');

    if ((tmp = find_path(pos + RIGHT, code, newpath, steps + 1, shortest)) < sp)
      sp = tmp;
  }

  return sp;
}

int main(int argc, char const *argv[])
{
  char *path = malloc(sizeof(char));
  path[0] = '\0';
  char md5[MD5_LEN];
  int steps = INT_MAX;
  int start = 7;

  steps = find_path(start, "veumntbg", "", 0, &path);

  printf("The shortest path is %d steps: %s\n", steps, path);

  return 0;
}
