#include <vector>
#include <QImage>
#include <sys/types.h>
#include <algorithm>
#include "activation.hpp"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"

using namespace std;

HiddenNeuron::HiddenNeuron(const uint& field, FilterNet* FN):
	fieldSize(field), ptrFN(FN)
{

}

void HiddenNeuron::addConnection(const uint &number)
{
	connections.push_back(number);
}

double HiddenNeuron::sumInputs(const ChessInput& input)
{
	sum = 0.0;
	vector<double>::iterator it = ptrFN->topWeights.begin();
	for (auto x: connections) {
		double rawNumber = input.getInput(x);
		rawNumber *= *it++;
		sum += rawNumber;
	}
	sum += *it;
	return sum;
}

double HiddenNeuron::sumSecondLayer()
{
	sum = 0.0;
	vector<double>::iterator it = ptrFN->bottomWeights.begin();
	for (auto x: connections) {
		double rawNumber = ptrFN->getFirActivations(x).first;
		rawNumber *= *it++;
		sum += rawNumber;
	}
	sum += *it;
	return sum;
}

pair<double, double> HiddenNeuron::setActivation(const double& sum)
{
	activation = pair<double, double>(activationFunction(sum),
		activationDerivative(sum));
	return activation;
}

