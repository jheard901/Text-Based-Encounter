
#include "math.h"
#include <stdlib.h> //srand(), rand()

//create a random float between 0 - 1
float frn() {
	float randNum = float(rand());
	return randNum / RAND_MAX;
}

//create a random float between a - b
float GetRandomFloat(float a, float b)
{
	if (a >= b) // bad input
		return a;

	return (frn() * (b - a)) + a;
}

//create a random int between a - b
int GetRandomInt(float a, float b)
{
	if (a >= b) // bad input
		return a;

	return int((frn() * (b - a)) + a);
}

