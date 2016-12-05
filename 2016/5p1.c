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
