#ifndef INPUT_INC
#define INPUT_INC

#include <stdio.h>
#include <stdlib.h>

#define INPUT_OFFSET	2
#define OUTPUT_OFFSET	1

struct input_struct
{
	unsigned char *buffer;
	size_t size;
	size_t index;
};

void loadInput(int argc, char *argv[], struct input_struct *input);

#endif /*INPUT_INC*/
