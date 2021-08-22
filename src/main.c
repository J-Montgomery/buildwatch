#include <ctype.h>
#include <getopt.h>
#include <linux/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUILDWATCH_NAME
#define BUILDWATCH_NAME "buildwatch"
#endif

#ifndef DEFAULT_CMD_SIZE
#define DEFAULT_CMD_SIZE (1024)
#endif

static struct option long_options[] = { { "verbose", no_argument, 0, 'V' },
					{ "version", no_argument, 0, 'v' },
					{ "help", no_argument, 0, 'h' },
					{ "config", required_argument, 0, 'c' },
					{ 0, 0, 0, 0 } };

void print_version(void)
{
	printf("Version 0.0.1\n");
}

void print_help(void)
{
	printf("%s [OPTIONS] [COMMAND]\n", BUILDWATCH_NAME);
}

int main(int argc, char **argv)
{
	int verbose = 0;
	char *config_file = ".bwconf";
	int idx;
	int c;
	size_t cmd_sz = 0;
	size_t cmd_free_space = DEFAULT_CMD_SIZE;

	char *command_str = calloc(DEFAULT_CMD_SIZE, 1);
	if (command_str == NULL)
		exit(EXIT_FAILURE);

	opterr = 0;

	/* Prevent parameter reordering in getopt by passing in '+'
	 * Reordering would cause us to parse the build system's flags accidentally
	 */
	while ((c = getopt_long(argc, argv, "+Vvhc:", long_options, NULL)) !=
	       -1) {
		switch (c) {
		case 'V':
			verbose = 1;
			break;
		case 'v':
			print_version();
			exit(EXIT_SUCCESS);
		case 'h':
			print_help();
			exit(EXIT_SUCCESS);
		case 'c':
			config_file = optarg;
			break;
		case '?':
			if (optopt == 'c')
				fprintf(stderr,
					"Option -%c requires an argument.\n",
					optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n",
					optopt);
			else
				fprintf(stderr,
					"Unknown option character `\\x%x'.\n",
					optopt);
			return 1;
		default:
			exit(EXIT_FAILURE);
		}
	}

	for (idx = optind; idx < argc; idx++) {
		size_t arg_sz = strlen(argv[idx]) + 1;
		printf("Non-option argument %s\n", argv[idx]);
		while (arg_sz >= cmd_free_space) {
			command_str = realloc(command_str, DEFAULT_CMD_SIZE);
			if (command_str == NULL)
				exit(EXIT_FAILURE);
			cmd_sz += DEFAULT_CMD_SIZE;
			cmd_free_space += DEFAULT_CMD_SIZE;
		}

		memcpy(command_str + cmd_sz, *(argv + idx), arg_sz);

		cmd_free_space -= arg_sz;
		cmd_sz += arg_sz;
		command_str[cmd_sz - 1] = ' ';
	}

	printf("len: %zi counted: %zi remaining: %zi\n%s\n",
	       strlen(command_str), cmd_sz, cmd_free_space, command_str);
	printf("Hello, World!\n");
	return 0;
}