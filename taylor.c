#define ANALYSIS_IMPL
#include "analysis.h"

#define N 10 + 1

int factorial(int n) {
	int i = 1;
	for (; n > 1; n--) i*=n;
	return i;
}

float taylor (float center, floats terms, float x) {
	float result = 0;
	float xn = 1;
	for (size_t i = 0; i < terms.count; i++) {
		result += terms.data[i] * xn / factorial(i);
		xn *= (x - center);
	}
	return result;
}

void save_values (floats x, floats y, char* path) {
	FILE* f = fopen(path, "w");
	for (size_t i = 0; i < x.count; i++)
		fprintf(f, "%f\t%f%s", x.data[i], y.data[i],i == x.count - 1 ? "" : "\n");
	fclose(f);
}


int main (void) {
	floats exponent_terms = {0};
	floats cos_terms = {0};
	float cos_secuent[] = {1,0,-1,0};
	floats exp_x ={0}, exp_y={0}, cos_x={0}, cos_y={0};
	float x_v;
	char path[32];
	for(int i = 0; i < N; i++) {
		floats_append(&exponent_terms, 1.0);
		floats_append(&cos_terms, cos_secuent[i % 4]);
		exp_x.count =0;
		exp_y.count = 0;
		cos_x.count = 0;
		cos_y.count = 0;
		for(int j = 0; j < 500; j++) {
			x_v = (j / 500.f - 0.5)*4;
			floats_append(&exp_x, x_v);
			floats_append(&exp_y, taylor(0, exponent_terms,x_v));
			x_v = (j / 500.f - 0.5)*12;
			floats_append(&cos_x, x_v);
			floats_append(&cos_y, taylor(0, cos_terms, x_v));
		}
		sprintf(path, "exp%d.dat", i);
		save_values(exp_x, exp_y, path);
		sprintf(path, "cos%d.dat", i);
		save_values(cos_x, cos_y, path);
	}
	printf("# taylor aprox n = %d\ne = %f\ncos(1) = %f\n\n",
			N,
			taylor(0, exponent_terms, 1),
			taylor(0, cos_terms, 1)
	);
	free(exp_x.data);
	free(exp_y.data);
	free(cos_x.data);
	free(cos_y.data);
	free(exponent_terms.data);
	free(cos_terms.data);
	return 0;
}
