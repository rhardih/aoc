#include <stdio.h>
#include <string.h>

#define TARGET_LENGTH 272
#define INPUT "01110110101001000"

void swap(char *a, char *b) {
  char c = *a;
  *a = *b;
  *b = c;
}

void reverse(char *s) {
  size_t len = strlen(s);
  for (int i = 0; i < (len / 2) + 1; i++) {
    swap(&s[i], &s[len - i - 1]);
  }
}

void flip(char *s) {
  int offset = (int)'0';
  for (int i = 0; i < strlen(s); i++) {
    s[i] = !(s[i] - offset) + offset;
  }
}

int main(int argc, char const *argv[])
{
  int i, j, len;

  char a[2 * TARGET_LENGTH];
  char b[2 * TARGET_LENGTH];
  char data[2 * TARGET_LENGTH];
  char checksum[2 * TARGET_LENGTH];
  sprintf(data, "%s", INPUT);

  while (strlen(data) < TARGET_LENGTH) {
    strcpy(a, data);
    strcpy(b, a);
    len = strlen(b);

    reverse(b);
    flip(b);

    sprintf(data, "%s0%s", a, b);
  }

  data[TARGET_LENGTH] = '\0';
  strcpy(checksum, data);

  do {
    for (i = 0, j = 1; j < strlen(checksum); i++, j += 2) {
      if (checksum[j - 1] == checksum[j]) {
        checksum[i] = '1';
      } else {
        checksum[i] = '0';
      }
    }
    checksum[i] = '\0';
  } while (strlen(checksum) % 2 == 0);

  printf("Correct checksum: %s\n", checksum);

  return 0;
}
