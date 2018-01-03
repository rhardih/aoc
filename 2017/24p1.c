/**
 * --- Day 24: Electromagnetic Moat ---
 *
 * The CPU itself is a large, black building surrounded by a bottomless pit.
 * Enormous metal tubes extend outward from the side of the building at regular
 * intervals and descend down into the void. There's no way to cross, but you
 * need to get inside.
 *
 * No way, of course, other than building a bridge out of the magnetic
 * components strewn about nearby.
 *
 * Each component has two ports, one on each end. The ports come in all
 * different types, and only matching types can be connected. You take an
 * inventory of the components by their port types (your puzzle input). Each
 * port is identified by the number of pins it uses; more pins mean a stronger
 * connection for your bridge. A 3/7 component, for example, has a type-3 port
 * on one side, and a type-7 port on the other.
 *
 * Your side of the pit is metallic; a perfect surface to connect a magnetic,
 * zero-pin port. Because of this, the first port you use must be of type 0. It
 * doesn't matter what type of port you end with; your goal is just to make the
 * bridge as strong as possible.
 *
 * The strength of a bridge is the sum of the port types in each component. For
 * example, if your bridge is made of components 0/3, 3/7, and 7/4, your bridge
 * has a strength of 0+3 + 3+7 + 7+4 = 24.
 *
 * For example, suppose you had the following components:
 *
 * 0/2
 * 2/2
 * 2/3
 * 3/4
 * 3/5
 * 0/1
 * 10/1
 * 9/10
 *
 * With them, you could make the following valid bridges:
 *
 * - 0/1
 * - 0/1--10/1
 * - 0/1--10/1--9/10
 * - 0/2
 * - 0/2--2/3
 * - 0/2--2/3--3/4
 * - 0/2--2/3--3/5
 * - 0/2--2/2
 * - 0/2--2/2--2/3
 * - 0/2--2/2--2/3--3/4
 * - 0/2--2/2--2/3--3/5
 *
 * (Note how, as shown by 10/1, order of ports within a component doesn't
 * matter. However, you may only use each port on a component once.)
 *
 * Of these bridges, the strongest one is 0/1--10/1--9/10; it has a strength of
 * 0+1 + 1+10 + 10+9 = 31.
 *
 * What is the strength of the strongest bridge you can make with the components
 * you have available?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 57

typedef struct {
  int p0;
  int p1;
  int used;
} component_t;

int strongest(component_t *components, size_t size, int type)
{
  int res = 0, tmp;
  component_t *copy;

  for (size_t i = 0; i < size; ++i)
  {
    if (components[i].p0 == type && components[i].used == 0)
    {
      copy = malloc(size * sizeof(component_t));
      memcpy(copy, components, size * sizeof(component_t));

      copy[i].used = 1;

      tmp = components[i].p0 + components[i].p1 +
        strongest(copy, size, components[i].p1);

      free(copy);

      if (tmp > res)
        res = tmp;
    }
    else if (components[i].p1 == type && components[i].used == 0)
    {
      copy = malloc(size * sizeof(component_t));
      memcpy(copy, components, size * sizeof(component_t));

      copy[i].used = 1;

      tmp = components[i].p0 + components[i].p1 +
        strongest(copy, size, components[i].p0);

      free(copy);

      if (tmp > res)
        res = tmp;
    }
  }

  return res;
}

int main(int argc, char const *argv[])
{
  char *line = NULL;
  size_t linecap = 0, i = 0;
  component_t *c, *components = malloc(INPUT_SIZE * sizeof(component_t));

  while (getline(&line, &linecap, stdin) > 0)
  {
    c = components + i;
    sscanf(line, "%d/%d", &c->p0, &c->p1);
    i++;
  }

  int s = strongest(components, i, 0);
  printf("Strength of the strongest bridge: %d\n", s);

  free(components);

  return 0;
}
