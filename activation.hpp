#ifndef ACTIVATION
#define ACTIVATION

using namespace std;

double activationFunction(const double& input)
{

	return input / (1.0 + abs(input));
}

double activationDerivative(const double& input)
{
	return 1.0 / ((1.0 + abs(input)) * (1.0 + abs(input)));
}

#endif // ACTIVATION

