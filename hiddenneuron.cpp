#include <vector>
#include <QImage>
#include <sys/types.h>
#include <algorithm>
#include "activation.hpp"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"


using namespace std;

HiddenNeuron::HiddenNeuron()
{
	bias = 1.0;
}

void HiddenNeuron::addConnection(const uint &number)
{
	connections.push_back(number);
}

void HiddenNeuron::setWeight(const double& weightIn)
{
	weight = weightIn;
}

double HiddenNeuron::getWeight() const
{
	return weight;
}

void HiddenNeuron::setBias(const double& weightIn)
{
	bias = weightIn;
}

double HiddenNeuron::getBias() const
{
	return bias;
}

double HiddenNeuron::sumInputs(const ChessInput& input)
{
	sum = 0.0;
	for (auto x: connections) {
		sum += (input.getInput(x) * weight);
	}
	sum += getBias();
	return sum;
}

pair<double, double> HiddenNeuron::setActivation()
{
	activation = pair<double, double>(activationFunction(sum),
		activationDerivative(sum));
	return activation;
}

