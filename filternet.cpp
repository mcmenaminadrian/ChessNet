#include <QMessageBox>
#include <QApplication>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"

using namespace std;



FilterNet::FilterNet(const uint& width, const int& span,
	const uint& field, const uint& depth,
	std::ifstream& inFile)
{
	uint effectiveWidth = width;
	commonField = field;
	fibreDepth = depth;
	for (uint i = 0; i < fibreDepth; i++) {
		vector<double> neurons;
		uint networkSize = 1 + (effectiveWidth - commonField) / span;
		networkSizes.push_back(networkSize);
		for (uint j = 0; j < networkSize; j++) {
			for (uint k = 0; k < networkSize; k++) {
				HiddenNeuron neuro(commonField, this);
				uint rowIndex = j * width;
				uint kAdvance = k * span;
				for (uint l = 0; l < commonField; l++) {
					uint lRow = l * effectiveWidth;
					for (uint m = 0; m < commonField; m++){
						neuro.addConnection(rowIndex +
							kAdvance + lRow + m);
					}
				}
				neurons.push_back(neuro);
			}
		}
		fibre.push_back(neurons);
		effectiveWidth = networkSize;
	}

	//loadWeights(inFile);
	//NB only use next line at start up
	assignRandomWeights();
}

void FilterNet::loadWeights(ifstream& inFile)
{
	streamInWeights(inFile);
}

void FilterNet::assignRandomWeights()
{
	double factor = RAND_MAX;
	for (uint i = 0; i < fibreDepth; i++) {
		vector<double> weights;
		for (uint j = 0; j <= commonField; j++) {
			double number = rand();
			number /= factor;
			weights.push_back(number - 0.5);
		}
		fibreWeights.push_back(weights);
	}
}

ostream& FilterNet::streamOutWeights(ostream& os) const
{
	for (const auto& weightVec: fibreWeights) {
		for (const auto weight: weightVec) {
			os << weight;
			os << " ";
		}
		os << endl;
	}
	return os;

}

istream& FilterNet::streamInWeights(istream& is)
{
	fibreWeights.clear();
	for (uint i = 0; i < fibreDepth; i++) {
		vector<double> weights;
		for (uint j = 0; j <= commonField * commonField; j++)
		{
			double x;
			is >> x;
			weights.push_back(x);
		}
		fibreWeights.push_back(weights);
	}
	return is;
}

void FilterNet::computeActivations(const vector<double>& inputs)
{
	_computeActivations(inputs, fibre.begin())
}

void FilterNet::_computeActivations(const vector<double>& inputs,
	vector<vector<HiddenNeuron>>::iterator& neuronsIt)
{
	if (neuronsIt = fibre.end()) {
		return;
	}
	vector<HiddenNeuron> neurons = *neuronsIt;
	vector<double> nextInputs;
	for (auto neuro: neurons) {
		double sum = 0.0;
		for (auto numb: neuro.getConnections()) {
			sum += inputs.at(numb);
		}
		pair<double, double> actives = neuro.setActivation(sum);
		nextIn.push_back(actives.first);
	}
	neuronsIt++;
	return computeActivations(nextIn, neuronsIt);
}
