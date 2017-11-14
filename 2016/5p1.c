/**
 * --- Day 5: How About a Nice Game of Chess? ---
 * 
 * You are faced with a security door designed by Easter Bunny engineers that
 * seem to have acquired most of their security knowledge by watching hacking
 * movies.
 * 
 * The eight-character password for the door is generated one character at a
 * time by finding the MD5 hash of some Door ID (your puzzle input) and an
 * increasing integer index (starting with 0).
 * 
 * A hash indicates the next character in the password if its hexadecimal
 * representation starts with five zeroes. If it does, the sixth character in
 * the hash is the next character of the password.
 * 
 * For example, if the Door ID is abc:
 * 
 * - The first index which produces a hash that starts with five zeroes is
 *   3231929, which we find by hashing abc3231929; the sixth character of the
 *   hash, and thus the first character of the password, is 1.
 * - 5017308 produces the next interesting hash, which starts with 000008f82...,
 *   so the second character of the password is 8.
 * - The third time a hash starts with five zeroes is for abc5278568,
 *   discovering the character f.
 *
 * In this example, after continuing this search a total of eight times, the
 * password is 18f47a30.
 * 
 * Given the actual Door ID, what is the password?
 */

#include "stdio.h"
#include "limits.h"
#include "openssl/md5.h"
#include "string.h"

char input[] = "uqwqemis";

int main(int argc, char const *argv[])
{
  char password[] = "01234567";
  char candidate[30];
  char mdString[33];
  unsigned char digest[MD5_DIGEST_LENGTH];
  size_t password_index = 0, i;
  int door_index = 0;
  int hit = 1;

  while (door_index < INT_MAX) {
    sprintf(candidate, "%s%d", input, door_index);

    MD5((const unsigned char *)candidate, strlen(candidate), (unsigned char *)&digest);

    for(int i = 0; i < 16; i++)
      sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    for(i = 0; i < 5; i++) {
      if(mdString[i] != '0') hit = 0;
    }

    if (hit) {
      password[password_index++] = mdString[5];

      if (password_index > 7) break;
    }

    hit = 1;
    door_index++;
  }

  printf("The password is: %s\n", password);

  return 0;
}
