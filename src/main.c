#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bool.h"
#include "input.h"
#include "options.h"
#include "disassemble.h"

int main(int argc, char *argv[])
{
	struct input_struct input;
	struct jumps_struct jumps;
	struct options_struct options = {FALSE};
	FILE *output_file_pointer;

	/*Get command line options.*/
	parseTerminalOptions(argc, argv, &options);

	/*Check if we're flagged to display help, if there aren't enough arguments, or if the last two arguments aren't options.*/
	if(options.help || argc < 3 || argv[argc - INPUT_OFFSET][0] == '-' || argv[argc - OUTPUT_OFFSET][0] == '-')
	{
		printHelp(argc, argv);
		return EXIT_FAILURE;
	}

	/*Read binary input file into memory.*/
	loadInput(argc, argv, &input);

	output_file_pointer = fopen(argv[argc - OUTPUT_OFFSET], "wb");
	/*Open assembly output file.*/
	if(!output_file_pointer)
	{
		printf("Failed to open file: %s.\n", argv[argc - OUTPUT_OFFSET]);
		exit(EXIT_FAILURE);
	}

	/*Label jumps or use pure hex values?*/
	if(options.label_jumps)
	{
		findPossibleJumps(&input, &jumps);
	}
	else
	{
		saveRelativeJumpMacros(output_file_pointer);
	}

	/*Simple or normal disassembly?*/
	if(options.simple_mode || input.size < 0x150)
	{
		simpleDisassemble(output_file_pointer, &input, &jumps, &options);
	}
	else
	{
		complexDisassemble(output_file_pointer, &input, &jumps, &options);
	}

	/*Cleanup and exit.*/
	fprintf(output_file_pointer, "; End of output.\n");
	fclose(output_file_pointer);
	free(input.buffer);
	printf("Done.\n");
	return EXIT_SUCCESS;
}
