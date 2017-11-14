/**
 *
 * --- Day 4: Security Through Obscurity ---
 * 
 * Finally, you come across an information kiosk with a list of rooms. Of
 * course, the list is encrypted and full of decoy data, but the instructions to
 * decode the list are barely hidden nearby. Better remove the decoy data first.
 * 
 * Each room consists of an encrypted name (lowercase letters separated by
 * dashes) followed by a dash, a sector ID, and a checksum in square brackets.
 * 
 * A room is real (not a decoy) if the checksum is the five most common letters
 * in the encrypted name, in order, with ties broken by alphabetization. For
 * example:
 * 
 * - aaaaa-bbb-z-y-x-123[abxyz] is a real room because the most common letters
 *   are a (5), b (3), and then a tie between x, y, and z, which are listed
 *   alphabetically.
 * - a-b-c-d-e-f-g-h-987[abcde] is a real room because although the letters are
 *   all tied (1 of each), the first five are listed alphabetically.
 * - not-a-real-room-404[oarel] is a real room.
 * - totally-real-room-200[decoy] is not.
 *
 * Of the real rooms from the list above, the sum of their sector IDs is 1514.
 * 
 * --- Part Two ---
 *
 *  With all the decoy data out of the way, it's time to decrypt this list and
 *  get moving.
 *
 *  The room names are encrypted by a state-of-the-art shift cipher, which is
 *  nearly unbreakable without the right software. However, the information
 *  kiosk designers at Easter Bunny HQ were not expecting to deal with a master
 *  cryptographer like yourself.
 *
 *  To decrypt a room name, rotate each letter forward through the alphabet a
 *  number of times equal to the room's sector ID. A becomes B, B becomes C, Z
 *  becomes A, and so on. Dashes become spaces.
 *
 *  For example, the real name for qzmt-zixmtkozy-ivhz-343 is very encrypted
 *  name.
 *
 *  What is the sector ID of the room where North Pole objects are stored?
 */

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
