#ifndef ACTIVATION
#define ACTIVATION

using namespace std;

const static double leakyReluFactor = 0.01;

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

#endif // ACTIVATION

