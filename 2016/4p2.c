#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
  char expected_checksum[] = ".....";
  char actual_checksum[] = ".....";
  int checksum_index = 0;
  int sector_id, sum = 0;
  int character_frequencies[26] = {0}; // initialize all elements to 0
  int highest_index = 0;
  char encrypted_name[200], unencrypted_name[200];
  int offset = (int)'a';
  char current, i;

  while(scanf("%[^0-9]%d[%5s]\n", encrypted_name, &sector_id, expected_checksum) != EOF) {
    for (i = 0; i < strlen(encrypted_name) - 1; i++) {
      if ((int)(current = encrypted_name[i]) != 45) { // skip dashes
        character_frequencies[(int)current - offset]++;
      }
    }

    while (checksum_index < 5) {
      for (i = 0; i < 26; i++) {
        if (character_frequencies[i] > character_frequencies[highest_index]) {
          highest_index = i;
        }
      }
      
      actual_checksum[checksum_index++] = (char)highest_index + offset;

      character_frequencies[highest_index] = 0; // skip on subsequent searches
      highest_index = 0;
    }

    for (i = 0; i < 26; i++) character_frequencies[i] = 0;
    checksum_index = 0;

    if (strncmp(actual_checksum, expected_checksum, 5) == 0) {
      sum += sector_id;

      for (i = 0; i < strlen(encrypted_name) - 1; i++) {
        if ((int)encrypted_name[i] == 45) { // dashes to spaces
          unencrypted_name[i] = ' ';
        } else {
          unencrypted_name[i] = (((int)encrypted_name[i] - offset + sector_id) % 26) + offset;
        }
      }
      unencrypted_name[i] = '\0';

      printf("Room name: %s, Sector id: %d\n", unencrypted_name, sector_id);
    }
  }

  return 0;
}
