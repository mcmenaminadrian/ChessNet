#include <vector>
#include <sys/types.h>
#include "chessinput.hpp"
#include "leveloneneuron.hpp"


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

void HiddenNeuron::sumInputs(const ChessInput& input)
{
	sum = 0.0;
	for (auto x: connections) {
		sum += (input.getInput(x) * weight);
	}
	sum += getBias();
}

