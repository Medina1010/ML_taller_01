#define ANALYSIS_IMPL
#include "analysis.h"

#define R 3.999999
#define MU 1.9999999

float logistic_seed;
float camp_seed;

float logistic_gen() {
	float value = R*logistic_seed*(1-logistic_seed);
	logistic_seed = value;
	return value;
}
float camp_gen() {
	float value = camp_seed < 0.5 ? MU*camp_seed : MU*(1-camp_seed);
	camp_seed = value;
	return value;
}

void save_values (floats x, char* path) {
	FILE* f = fopen(path, "w");
	for (size_t i = 0; i < x.count; i++)
		fprintf(f, "%f%s", x.data[i], i == x.count - 1 ? "" : "\n");
	fclose(f);
}

int main (void) {
	int n = 100;
	logistic_seed = 0.1415;
	camp_seed = 0.1415;
	floats logistic_list = {0}, camp_list = {0};
	for (int i = 0; i < n; i++) {
		floats_append(&logistic_list, logistic_gen());
		floats_append(&camp_list, camp_gen());
	}
	save_values(logistic_list, "logistic-list.csv");
	save_values(camp_list, "camp-list.csv");
	printf("# logistic map\nmean=%f\nvar=%f\nasymetry=%f\n\n",
			floats_mean(logistic_list),
			floats_var(logistic_list),
			floats_asymetry(logistic_list));
	printf("# tent map\nmean=%f\nvar=%f\nasymetry=%f\n\n",
			floats_mean(camp_list),
			floats_var(camp_list),
			floats_asymetry(camp_list));
	free(logistic_list.data);
	free(camp_list.data);
	return 0;
}
