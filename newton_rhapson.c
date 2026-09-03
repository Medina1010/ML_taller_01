#include <math.h>
#include <stdio.h>

typedef float(*func)(float);

float newton_rhapson(func f, func df, float x, float e) {
	while(-e > f(x) || f(x) > e) {
		x -= f(x)/df(x);
	}
	return x;
}

float f1(float x) {
	return x*x - 612;
}
float df1(float x) {
	return 2*x;
}

float f2(float x) {
	return cos(x) - x*x*x;
}
float df2(float x) {
	return -sin(x)-3*x*x;
}

int main(void){
	float f1_root = newton_rhapson(f1, df1, 30, 0.01);
	printf("# raiz de x^2 - 612\nraiz: sqrt(612) = %f\ndelta: %f\nepsilon: %f\n\n",
		f1_root,
		0-f1(f1_root),
		0.01);
	float f2_root = newton_rhapson(f2, df2, 0.5, 0.01);
	printf("# raiz de cos(x) - x^3\nraiz: %f\ndelta: %f\nepsilon: %f\n\n",
		f2_root,
		0-f2(f2_root),
		0.01);
	return 0;
}
