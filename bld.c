#include <stdio.h>
#include <stdlib.h>

#define PWD "ANALYSIS"

void cmd (char *prompt) {
	printf(PWD" > %s\n", prompt);
	if (system(prompt)) exit(1);
}

int main (int argc, char** argv) {
	// recompile
	if (argc == 1) {
		cmd("gcc -o bld bld.c");
		cmd("./bld R");
		exit(0);
	}
	// random
	printf("############################\n");
	printf("# Numeros pseudoaleatorios #\n");
	printf("############################\n");
	cmd("gcc -Wall -Wextra -lm -o rand_gen rand_gen.c");
	cmd("./rand_gen");
	cmd("gnuplot rand.gp");
	// taylor
	printf("############################\n");
	printf("# Aproximaciones de Taylor #\n");
	printf("############################\n");
	cmd("gcc -Wall -Wextra -lm -o taylor taylor.c");
	cmd("./taylor");
	cmd("gnuplot taylor.gp");
	// newton rhapson
	printf("#############################\n");
	printf("# Raices por Newton-Rhapson #\n");
	printf("#############################\n");
	cmd("gcc -Wall -Wextra -lm -o newton_rhapson newton_rhapson.c");
	cmd("./newton_rhapson");
	return 0;
}
