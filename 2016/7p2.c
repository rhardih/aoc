#include "stdio.h"
#include "regex.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
  char buf[200];
  int sum = 0;
  regex_t match_right, match_left;

  regcomp(&match_right, "\\([a-z]\\)\\([^\\1]\\)\\1[a-z]*\\[\\([a-z]*\\][a-z]*\\[\\)*[a-z]*\\2\\1\\2", REG_BASIC);
  regcomp(&match_left, "\\([a-z]\\)\\([^\\1]\\)\\1[a-z]*\\]\\([a-z]*\\[[a-z]*\\]\\)*[a-z]*\\2\\1\\2", REG_BASIC);

  while(fgets(buf, 200, stdin) != NULL) {
    if (!(regexec(&match_right, buf, 0, NULL, 0) &&
          regexec(&match_left, buf, 0, NULL, 0))) sum++; 
  }

  printf("IPs that support TLS: %d\n", sum);

  return 0;
}
