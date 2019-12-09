#include <stdio.h>

int intcode_run(int *opcodes) {
  int value, opcode, i = 0, param0, param1, output_index;
  while ((value = opcodes[i]) != 99) {
    opcode = value % 100;
    int parameter_modes[] = {
      value / 100 % 10,
      value / 1000 % 10
    };

    switch(opcode) {
      case 1: // add
        param0 = parameter_modes[0] ? opcodes[i + 1] : opcodes[opcodes[i + 1]];
        param1 = parameter_modes[1] ? opcodes[i + 2] : opcodes[opcodes[i + 2]];
        output_index = opcodes[i + 3];

        opcodes[output_index] = param0 + param1;

        i += 4;

        break;
      case 2: // multiply
        param0 = parameter_modes[0] ? opcodes[i + 1] : opcodes[opcodes[i + 1]];
        param1 = parameter_modes[1] ? opcodes[i + 2] : opcodes[opcodes[i + 2]];
        output_index = opcodes[i + 3];

        opcodes[output_index] = param0 * param1;

        i += 4;

        break;
      case 3: // input
        output_index = opcodes[i + 1];

        if (scanf("%d", &opcodes[output_index]) == EOF) {
          fprintf(stderr, "No input provided for scanf, stopping.\n");
          return 1;
        }

        i += 2;

        break;
      case 4: // ouput
        output_index = opcodes[i + 1];

        printf("%d\n", opcodes[output_index]);
        i += 2;

        break;
      case 5: // jump-if-true
      case 6: // jump-if-false
        param0 = parameter_modes[0] ? opcodes[i + 1] : opcodes[opcodes[i + 1]];

        if (opcode == 5 ? param0 : !param0) {
          param1 = parameter_modes[1] ? opcodes[i + 2] : opcodes[opcodes[i + 2]];

          i = param1;
        } else {
          i += 3;
        }

        break;
      case 7: // less than
        param0 = parameter_modes[0] ? opcodes[i + 1] : opcodes[opcodes[i + 1]];
        param1 = parameter_modes[1] ? opcodes[i + 2] : opcodes[opcodes[i + 2]];
        output_index = opcodes[i + 3];

        opcodes[output_index] = param0 < param1 ? 1 : 0;

        i += 4;

        break;
      case 8: // equals
        param0 = parameter_modes[0] ? opcodes[i + 1] : opcodes[opcodes[i + 1]];
        param1 = parameter_modes[1] ? opcodes[i + 2] : opcodes[opcodes[i + 2]];
        output_index = opcodes[i + 3];

        opcodes[output_index] = param0 == param1 ? 1 : 0;

        i += 4;

        break;
      default:
        fprintf(stderr, "Unknown opcode value at location %d: %d\n", i, value);
        return 1;
    }
  }

  return 0;
}
