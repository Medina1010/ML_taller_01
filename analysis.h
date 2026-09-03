#ifndef   ANALYSIS_H
#define   ANALYSIS_H

#include <stdlib.h>

#define GRAPH_WIDTH 80
#define GRAPH_HEIGHT 40

typedef struct {
	float* data;
	size_t count;
	size_t capacity;
} floats;

floats floats_ctr(size_t capacity);
floats floats_ln (floats xs);
float floats_sum_values (floats x);
floats floats_sum (floats x, floats y);
floats floats_sum_float (floats x, float y);
floats floats_mul_float (floats x, float y);
floats floats_mul (floats x, floats y);
float floats_dot (floats x, floats y);

typedef struct {
	float m,
	      b,
	      r,
	      SSe,
	      SSm,
	      SSb;
} lin_reg_t;	

lin_reg_t lin_reg (floats x, floats y);
float map (float xi, float xf, float yi, float yf, float x);
void term_graph (floats x, floats y, float width, float height);

#ifdef   ANALYSIS_IMPL

#include <math.h>

floats floats_ctr(size_t capacity) {
	return (floats) {
		.count = 0,
		.capacity = capacity,
		.data = malloc(capacity * sizeof(float))
	};
}

void floats_append(floats* xs, float x) {
	if (xs->count >= xs->capacity)
		xs->capacity = 2 * (xs->count + 1);
	xs->data = realloc(xs->data, xs->capacity * sizeof(float));
	xs->data[xs->count++] = x;
}

floats floats_ln (floats xs) {
	floats res = floats_ctr(xs.count);
	res.count = res.capacity;
	for (size_t i = 0; i < xs.count; i++)
		res.data[i] = log(xs.data[i]);
	return res;
}

float floats_sum_values (floats x) {
	float sum = 0;
	for (size_t i = 0; i < x.count; i++)
		sum += x.data[i];
	return sum;
}

floats floats_sum (floats x, floats y) {
        floats sum = floats_ctr(x.count > y.count ? y.count : x.count);
	sum.count = sum.capacity;
        for (size_t i = 0; i < sum.count; i++)
                sum.data[i] = x.data[i] + y.data[i];
        return sum;
}

floats floats_sum_float (floats x, float y) {
        floats sum = floats_ctr(x.count);
	sum.count = sum.capacity;
        for (size_t i = 0; i < sum.count; i++)
                sum.data[i] = x.data[i] + y;
        return sum;
}

floats floats_mul_float (floats x, float y) {
        floats mul = floats_ctr(x.count);
        for (size_t i = 0; i < mul.count; i++)
                mul.data[i] = x.data[i] * y;
        return mul;
}

floats floats_mul (floats x, floats y) {
        floats mul = floats_ctr(x.count > y.count ? y.count : x.count);
	mul.count = mul.capacity;
        for (size_t i = 0; i < mul.count; i++)
                mul.data[i] = x.data[i] * y.data[i];
        return mul;
}

float floats_dot (floats x, floats y) {
	floats mul = floats_mul(x, y);
	float dot = floats_sum_values(mul);
	free(mul.data);
	return dot;
}

lin_reg_t lin_reg (floats x, floats y) {
	size_t count = x.count > y.count ? y.count : x.count;
	float X = floats_sum_values(x) / count,
	      Y = floats_sum_values(y) / count,
	      XX = floats_dot(x, x) / count,
	      XY = floats_dot(x, y) / count,
	      YY = floats_dot(y, y) / count,
	      SSX = XX - X * X,
 	     SSY = YY - Y * Y,
	      SXY = XY - X * Y;
	lin_reg_t lr = {
		.m = (XY - X * Y) / (XX - X * X),
        	.b = (XX * Y - X * XY) / (XX - X * X),
		.r = (SXY * SXY) / (SSX * SSY),
        	.SSe = SSY - lr.m * lr.m * SSX,
        	.SSm = lr.SSe / SSX,
        	.SSb = lr.SSm * XX
	};
	return lr;
}

float floats_mean (floats x) {
	return floats_sum_values(x) / x.count;
}

float floats_var (floats x) {
	float X = floats_sum_values(x) / x.count,
	      XX = floats_dot(x, x) / x.count;
	return XX - X * X;
}

float floats_stddev (floats x) {
	return sqrt(floats_var(x));
}

float floats_asymetry (floats x) {
	floats X_c = floats_sum_float (x, -floats_mean(x));
	floats X_c2 = floats_mul(X_c,X_c);
	floats X_c3 = floats_mul(X_c2,X_c);
	float X_c3_mean = floats_mean(X_c3);
	free(X_c.data);
	free(X_c2.data);
	free(X_c3.data);
	float SX = floats_stddev(x);
	return X_c3_mean / (SX * SX * SX);
}

float map (float xi, float xf, float yi, float yf, float x) {
	return yi + (yf - yi) / (xf - xi) * (x - xi);
}

void term_graph (floats x, floats y, float width, float height) {
	char screen[GRAPH_WIDTH * GRAPH_HEIGHT];
	for (size_t i = 0; i < GRAPH_WIDTH * GRAPH_HEIGHT; i++)
		screen[i] = ' ';

	for (size_t i = 0; i < x.count; i++)
		screen[(int)(map(0, width, 0, GRAPH_WIDTH, x.data[i])) +
		       (int)(map(0, height, GRAPH_HEIGHT, 0, y.data[i])) * GRAPH_WIDTH] = '*';
	for (size_t i = 0; i < GRAPH_HEIGHT; i++) {
		printf("%.*s\n", GRAPH_WIDTH, &screen[GRAPH_WIDTH*i]);
	}
}

#endif //ANALYSIS_IMPL

#endif //ANALYSIS_H
