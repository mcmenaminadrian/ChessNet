#include <vector>
#include <sys/types.h>
#include "leveloneneuron.hpp"


using namespace std;

LevelOneNeuron::LevelOneNeuron()
{
	bias = 1.0;
}

void LevelOneNeuron::addConnection(const uint &number)
{
	connections.push_back(number);
}

void LevelOneNeuron::setWeight(const double& weightIn)
{
	weight = weightIn;
}

double LevelOneNeuron::getWeight() const
{
	return weight;
}

void LevelOneNeuron::setBias(const double& weightIn)
{
	bias = weightIn;
}

double LevelOneNeuron::getBias() const
{
	return bias;
}
