/**
 * --- Day 7: Amplification Circuit ---
 *
 * Based on the navigational maps, you're going to need to send more power to
 * your ship's thrusters to reach Santa in time. To do this, you'll need to
 * configure a series of amplifiers already installed on the ship.
 * 
 * There are five amplifiers connected in series; each one receives an input
 * signal and produces an output signal. They are connected such that the first
 * amplifier's output leads to the second amplifier's input, the second
 * amplifier's output leads to the third amplifier's input, and so on. The first
 * amplifier's input value is 0, and the last amplifier's output leads to your
 * ship's thrusters.
 * 
 *     O-------O  O-------O  O-------O  O-------O  O-------O
 * 0 ->| Amp A |->| Amp B |->| Amp C |->| Amp D |->| Amp E |-> (to thrusters)
 *     O-------O  O-------O  O-------O  O-------O  O-------O
 *
 * The Elves have sent you some Amplifier Controller Software (your puzzle
 * input), a program that should run on your existing Intcode computer. Each
 * amplifier will need to run a copy of the program.
 * 
 * When a copy of the program starts running on an amplifier, it will first use
 * an input instruction to ask the amplifier for its current phase setting (an
 * integer from 0 to 4). Each phase setting is used exactly once, but the Elves
 * can't remember which amplifier needs which phase setting.
 * 
 * The program will then call another input instruction to get the amplifier's
 * input signal, compute the correct output signal, and supply it back to the
 * amplifier with an output instruction. (If the amplifier has not yet received
 * an input signal, it waits until one arrives.)
 * 
 * Your job is to find the largest output signal that can be sent to the
 * thrusters by trying every possible combination of phase settings on the
 * amplifiers. Make sure that memory is not shared or reused between copies of
 * the program.
 * 
 * For example, suppose you want to try the phase setting sequence 3,1,2,4,0,
 * which would mean setting amplifier A to phase setting 3, amplifier B to
 * setting 1, C to 2, D to 4, and E to 0. Then, you could determine the output
 * signal that gets sent from amplifier E to the thrusters with the following
 * steps:
 * 
 * - Start the copy of the amplifier controller software that will run on
 *   amplifier A. At its first input instruction, provide it the amplifier's
 *   phase setting, 3. At its second input instruction, provide it the input
 *   signal, 0. After some calculations, it will use an output instruction to
 *   indicate the amplifier's output signal.
 * - Start the software for amplifier B. Provide it the phase setting (1) and
 *   then whatever output signal was produced from amplifier A. It will then
 *   produce a new output signal destined for amplifier C.
 * - Start the software for amplifier C, provide the phase setting (2) and the
 *   value from amplifier B, then collect its output signal.
 * - Run amplifier D's software, provide the phase setting (4) and input value,
 *   and collect its output signal.
 * - Run amplifier E's software, provide the phase setting (0) and input value,
 *   and collect its output signal.
 *
 * The final output signal from amplifier E would be sent to the thrusters.
 * However, this phase setting sequence may not have been the best one; another
 * sequence might have sent a higher signal to the thrusters.
 * 
 * Here are some example programs:
 * 
 * - Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
 * 
 *   3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0
 *
 * - Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
 * 
 *   3,23,3,24,1002,24,10,24,1002,23,-1,23,
 *   101,5,23,23,1,24,23,23,4,23,99,0,0
 *
 * - Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
 * 
 *   3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
 *   1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0
 *
 * Try every combination of phase settings on the amplifiers. What is the
 * highest signal that can be sent to the thrusters?
 */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "intcode.h"

int main() {
  FILE *input;
  int comma_count = 0;
  char *tmp, *line = NULL;
  size_t linecap = 0;
  int result = INT_MIN;

  // Read the input file directly in this case, since we'll be doing weird stuff
  // with stdio/stdout further down
  if ((input = fopen("7.in", "r")) == NULL)
  {
    perror("Failed to open input file.");
    exit(EXIT_FAILURE);
  }

  /* Input handling */
  getline(&line, &linecap, input);
  tmp = line;

  while((tmp = strchr(tmp, ',')) != NULL)
  {
    comma_count++;
    tmp++;
  }

  int opcode_count = comma_count + 1, index = 0;
  int opcodes_size = sizeof(int) * opcode_count;
  int *opcodes = malloc(opcodes_size);
  int *copy = malloc(opcodes_size);

  char *token, *string, *tofree;
  tofree = string = strdup(line);

  while ((token = strsep(&string, ",")) != NULL)
  {
    sscanf(token, "%d", &opcodes[index]);
    index++;
  }

  fclose(input);
  free(line);
  free(tofree);



  // Disclaimer
  //
  // This is purposefully going completely overboard with regards to
  // input/output handling and could b done in a much simpler way.
  //
  // The strategy taken here, is to split into two different processes, where
  // the parent process is responsible for generating combinations of phase
  // settings and then feeding them to a child process, which does the actual
  // running of the intcode.
  //
  // In order to do that with just scanf/print functions, input redirection is
  // needed and that is why the code below is somewhat noisy.



  // Disable buffering on stdout, so as not to have to flush after each printf.
  // This will be inherited in child process as well.
  setbuf(stdout, NULL);

  int fd0[2]; // Used to store two ends of first pipe 
  int fd1[2]; // Used to store two ends of second pipe 

  if (pipe(fd0) == -1 || pipe(fd1) == -1) 
  { 
    perror("Pipe Failed"); 
    return 1; 
  } 

  // Convenience macros, purely for peace of mind
  #define child_read fd0[0]
  #define child_write fd0[1]
  #define parent_read fd1[0]
  #define parent_write fd1[1]

  pid_t p = fork(); 

  if (p < 0) 
  { 
    perror("fork failed");
    return 1; 
  } 
  else if (p > 0) 
  { 
    // Parent process 

    close(child_read);

    // No error checks, rock and roll!
    int _stdin = dup(STDIN_FILENO);
    int _stdout = dup(STDOUT_FILENO);

    dup2(parent_read, STDIN_FILENO);
    dup2(child_write, STDOUT_FILENO);

    // Amplifiers
    int A, B, C, D, E;
    int tmp;
    for(A = 0; A <= 4; A++) {
      for(B = 0; B <= 4; B++) {
        if(B == A) continue;

        for(C = 0; C <= 4; C++) {
          if(C == A || C == B) continue;

          for(D = 0; D <= 4; D++) {
            if(D == A || D == B || D == C) continue;

            for(E = 0; E <= 4; E++) {
              if(E == A || E == B || E == C || E == D) continue;

              // Send phase setting for A, followed by input signal 0
              printf("%d\n0\n", A);

              // Read output signal from A
              assert(scanf("%d", &tmp) == 1);

              // Send phase setting for B, followed by input signal with value
              // set to output signal from A
              printf("%d\n%d\n", B, tmp);

              // Read output signal from B
              assert(scanf("%d", &tmp) > 0);

              // Send phase setting for C, followed by input signal with value
              // set to output signal from B
              printf("%d\n%d\n", C, tmp);

              // Read output signal from C
              assert(scanf("%d", &tmp) > 0);

              // Send phase setting for D, followed by input signal with value
              // set to output signal from C
              printf("%d\n%d\n", D, tmp);

              // Read output signal from D
              assert(scanf("%d", &tmp) > 0);

              // Send phase setting for E, followed by input signal with value
              // set to output signal from D
              printf("%d\n%d\n", E, tmp);

              // Read final output from E
              assert(scanf("%d", &tmp) > 0);

              if (tmp > result) {
                result = tmp;
              }
            }
          }
        }
      }
    }

    // Restore stdin/stdout
    dup2(_stdin, STDIN_FILENO);
    dup2(_stdout, STDOUT_FILENO);

    printf("Highest signal that can be sent to the thrusters: %d\n", result);

    close(_stdout);
    close(_stdin);

    close(child_write); 

    // Wait for child to exit
    wait(NULL); 

    close(parent_write);
    close(parent_read); 

    free(opcodes);
    free(copy);
  } 
  else
  { 
    // child process

    dup2(child_read, STDIN_FILENO);
    dup2(parent_write, STDOUT_FILENO);

    close(child_write);

    // Number of different possible combinations of phase settings, given that
    // there is five, in the range from 0 to 4 and each of the five are
    // non-repeating.
    int i = 5 * 4 * 3 * 2;

    while (i > 0)
    {
      // Run for A
      memcpy(copy, opcodes, opcodes_size);
      intcode_run(copy); // <--

      // Run for B
      memcpy(copy, opcodes, opcodes_size);
      intcode_run(copy); // <--

      // Run for C
      memcpy(copy, opcodes, opcodes_size);
      intcode_run(copy); // <--

      // Run for D
      memcpy(copy, opcodes, opcodes_size);
      intcode_run(copy); // <--

      // Run for E
      memcpy(copy, opcodes, opcodes_size);
      intcode_run(copy); // <--

      i--;
    }

    close(child_read); 
    close(parent_read); 
    close(parent_write); 

    free(opcodes);
    free(copy);

    exit(0); 
  } 

  return 0;
}
