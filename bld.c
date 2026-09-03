#include <stdio.h>
#include <stdlib.h>

#define PWD "ANALYSIS"

void cmd (char *prompt) {
	printf(PWD" > %s\n", prompt);
	if (system(prompt)) exit(1);
}

int main (int argc, char** argv) {
	cmd("gcc -Wall -Wextra -lm -o rand_gen rand_gen.c");
	cmd("./rand_gen");
	cmd("gnuplot graph.gp");
	return 0;
}
