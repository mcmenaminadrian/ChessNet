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

double HiddenNeuron::sumInputs(const ChessInput& input)
{
	sum = 0.0;
	for (auto x: connections) {
		sum += (input.getInput(x) * weight);
	}
	sum += filterBias;
	return sum;
}

double HiddenNeuron::sumSecondLayer(FilterNet* ptrFN)
{
	sum = 0.0;
	for (auto x: connections) {
		sum += ptrFN->getFirActivations(x).first * weight;
	}
	sum += filterBias;
	return sum;
}

pair<double, double> HiddenNeuron::setActivation()
{
	activation = pair<double, double>(activationFunction(sum),
		activationDerivative(sum));
	return activation;
}

