#include <stdio.h>

#define MAX_DEPTH 92

static int scanners[MAX_DEPTH + 1];

int main(int argc, char const *argv[])
{
  int depth, range, ps, sev;

  while(scanf("%d: %d", &depth, &range) != EOF)
    scanners[depth] = range;

  for (ps = 0, sev = 0; ps < MAX_DEPTH + 1; ++ps)
    if (scanners[ps] != 0 && ps % ((scanners[ps] - 1) * 2) == 0)
      sev += ps * scanners[ps];

  printf("Severity of your whole trip: %d\n", sev);

  return 0;
}
