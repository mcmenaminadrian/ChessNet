#ifndef ACTIVATION
#define ACTIVATION

#include <cmath>

using namespace std;

const static double leakyReluFactor = 0.9;

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
	return input / (1.0 + fabs(input));
}

static double fcActivationDerivative(const double& input)
{
	return 1.0 / ((1.0 + fabs(input)) * (1.0 + fabs(input)));
}

#endif // ACTIVATION

