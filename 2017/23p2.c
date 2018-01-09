/**
 * --- Day 23: Coprocessor Conflagration --- You decide to head directly to the
 *  CPU and fix the printer from there. As you get close, you find an
 *  experimental coprocessor doing so much work that the local programs are
 *  afraid it will halt and catch fire. This would cause serious issues for the
 *  rest of the computer, so you head in and see what you can do.
 *
 * The code it's running seems to be a variant of the kind you saw recently on
 * that tablet. The general functionality seems very similar, but some of the
 * instructions are different:
 *
 * - set X Y sets register X to the value of Y.
 * - sub X Y decreases register X by the value of Y.
 * - mul X Y sets register X to the result of multiplying the value contained in
 *   register X by the value of Y.
 * - jnz X Y jumps with an offset of the value of Y, but only if the value of X
 *   is not zero. (An offset of 2 skips the next instruction, an offset of -1
 *   jumps to the previous instruction, and so on.)
 *
 * Only the instructions listed above are used. The eight registers here, named
 * a through h, all start at 0.
 *
 * The coprocessor is currently set to some kind of debug mode, which allows for
 * testing, but prevents it from doing any meaningful work.
 *
 * If you run the program (your puzzle input), how many times is the mul
 * instruction invoked?
 *
 * --- Part Two ---
 *
 * Now, it's time to fix the problem.
 *
 * The debug mode switch is wired directly to register a. You flip the switch,
 * which makes register a now start at 1 when the program is executed.
 *
 * Immediately, the coprocessor begins to overheat. Whoever wrote this program
 * obviously didn't choose a very efficient implementation. You'll need to
 * optimize the program if it has any hope of completing before Santa needs that
 * printer working.
 *
 * The coprocessor's ultimate goal is to determine the final value left in
 * register h once the program completes. Technically, if it had that... it
 * wouldn't even need to run the program.
 *
 * After setting register a to 1, if the program were to run to completion, what
 * value would be left in register h?
 */

/* In order to properly understand "what" the program does, a pseudo code
 * translation is written down in 23.pseudo.
 *
 * From the looks of it, the main program consists of a triple nested loop,
 * where the outermost loop runs from values of b = 108400 to b = 125400 in
 * steps of 17, setting f to 1 on each iteration as well.
 *
 * For each iteration of the outer loop, there is a double nested loop that each
 * runs from 2 to the current value of b, in increments of 1 stored in d and e
 * respectively.
 *
 * Inside the innermost loop, the instructions loosely translates to a test for
 * d * e == b, which when true sets f to 0.
 *
 * Before b is incremented by 17 in the outermost loop, f is tested against 0,
 * which when true, increments h by 1.
 *
 * The program can then be outlined as follows:
 *
 * For b = 108400 to b = 125400 in steps of 17, count the number of times b is
 * the product of two smaller integers, ie. composite / not prime.
 *
 * Instead of trying to solve this by rewriting the assembly version of the
 * program, this problem can be more easily solved here, where a primality test
 * function can be implemented using modulo arithmetic. An instruction which is
 * missing amongst the specified set for the imaginary coprocessor for this
 * problem.
 */

#include <stdio.h>

int prime(int n)
{
	if (n <= 1)
		return 0;
	else if (n <= 3)
		return 1;
	else if (n % 2 == 0 || n % 3 == 0)
		return 0;

	int i = 5;
	while (i * i <= n)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return 0;
		i = i + 6;
	}

	return 1;
}

int main(int argc, char const *argv[])
{
  int count = 0;

  for (size_t i = 108400; i <= 125400; i += 17)
    if (!prime(i))
      count++;

  printf("If the program ran to completion, h would be: %d\n", count);

  return 0;
}
