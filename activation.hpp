#ifndef ACTIVATION
#define ACTIVATION

using namespace std;

static double activationFunction(const double& input)
{

	return input / (1.0 + abs(input));
}

static double activationDerivative(const double& input)
{
	return 1.0 / ((1.0 + abs(input)) * (1.0 + abs(input)));
}

#endif // ACTIVATION

