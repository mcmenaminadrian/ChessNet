#ifndef ACTIVATION
#define ACTIVATION

using namespace std;

double activationFunction(const double& input)
{
	return max(0.0, input);
}

double activationDerivative(const double& input)
{
	if (input < 0) {
		return 0.0;
	} else {
		return 1.0;
	}
}

#endif // ACTIVATION

