#include "stdio.h"
#include "openssl/md5.h"
#include "string.h"

char input[] = "uqwqemis";

int main(int argc, char const *argv[])
{
  char password[] = "........";
  char count = 0;
  char candidate[30];
  char mdString[33];
  unsigned char digest[MD5_DIGEST_LENGTH];
  int password_index = 0, i;
  int door_index = 0;
  char position;

  while (1) {
    sprintf(candidate, "%s%d", input, door_index);

    MD5((const unsigned char *)candidate, strlen(candidate), (unsigned char *)&digest);

    for(int i = 0; i < 16; i++)
      sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    if (strncmp(mdString, "00000", 5) == 0) {
      sscanf(&mdString[5], "%c", &position);
      sscanf(&position, "%x", &password_index);

      if (password_index < 8) { // skip invalid positions
        if (strncmp(&password[password_index], ".", 1) == 0) // fill only unfilled
          password[password_index] = mdString[6];
          if (count++ > 8) break; // stop when eight chars have been filled in
      }
    }

    door_index++;
  }

  printf("The password is: %s\n", password);

  return 0;
}
