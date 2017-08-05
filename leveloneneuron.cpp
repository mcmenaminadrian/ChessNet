#include <vector>
#include <sys/types.h>
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
