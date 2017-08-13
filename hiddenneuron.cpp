#include <vector>
#include <QImage>
#include <sys/types.h>
#include <algorithm>
#include "activation.hpp"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"

using namespace std;

HiddenNeuron::HiddenNeuron()
{

}

void HiddenNeuron::addConnection(const uint &number)
{
	connections.push_back(number);
}


pair<double, double> HiddenNeuron::setActivation(const double& sum)
{
	activation = pair<double, double>(activationFunction(sum),
		activationDerivative(sum));
	return activation;
}

const pair<double, double> HiddenNeuron::getActivation() const
{
	return activation;
}

