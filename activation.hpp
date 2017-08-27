#ifndef ACTIVATION
#define ACTIVATION

#include <cmath>

using namespace std;

const static double leakyReluFactor = 0.0001;

static double activationFunction(const double& input)
{

	if (input >= 0) {
		return input;
	} else {
		return input * leakyReluFactor;
	}
}

static double activationDerivative(const double& input)
{
	if (input < 0) {
		return leakyReluFactor;
	} else {
		return 1.0;
	}
}

static double fcActivationFunction(const double& input)
{
	return input / (1.0 + abs(input));
}

static double fcActivationDerivative(const double& input)
{
	return 1.0 / ((1.0 + abs(input)) * (1.0 + abs(input)));
}

#endif // ACTIVATION

