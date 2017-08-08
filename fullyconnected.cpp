#include <vector>
#include <cstdint>
#include <iostream>
#include <QImage>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"
#include "fullyconnected.hpp"
#include "chessnet.hpp"


using namespace std;


FullyConnected::FullyConnected()
{
	//change this to change output neuron number
	multiply = 2;

}

void FullyConnected::setUpVariables(const vector<FilterNet>& filters,
	const uint& outputClasses)
{
	classesToMatch = outputClasses;
	pair<uint, uint> hiddenLayerSizes = (filters.at(0)).getLayerSizes();
	secondFilterSize = hiddenLayerSizes.second;
	secondLayerNodeCount = secondFilterSize * filters.size();

	//NB: not to use in production
	assignRandomWeights();
}

const vector<double>& FullyConnected::calculateSums(
	const vector<FilterNet>& filters)
{
	for (const auto& smallWeights: weights) {
		auto it = filters.begin();
		uint i = 0;
		double summation = 0.0;
		for (const auto& individualWeight: smallWeights) {
			if (i < secondFilterSize) {
				summation +=
					((*it).getSecActivations(i++)).first *
					individualWeight;
			} else {
				i = 0;
				summation +=
					activationFunction(individualWeight);
				it++;
			}
		}
		sums.push_back(summation);
	}
	return sums;
}


pair<vector<double>&, vector<double>&> FullyConnected::returnActivations()
{
	for (const auto& summations: sums) {
		activations.push_back(activationFunction(summations));
		activationDerivatives.push_back(
			activationDerivative(summations));
	}
	return pair<vector<double>&, vector<double>&>(
		activations, activationDerivatives);
}


ostream& FullyConnected::streamOutWeights(ostream& os) const
{
	for (auto x: weights) {
		for (auto y: x) {
			os << y;
			os << " ";
		}
		os << endl;
	}
	os << endl;
	return os;
}

istream& FullyConnected::streamInWeights(istream& is)
{
	weights.clear();
	for (uint i = 0; i < classesToMatch * multiply; i++) {
		vector<double> smallWeights;
		//loop boundary reflects bias
		for (uint j = 0; j <= secondLayerNodeCount; j++) {
			double x;
			is >> x;
			smallWeights.push_back(x);
		}
		weights.push_back(smallWeights);
	}
	return is;
}

void FullyConnected::assignRandomWeights()
{
	weights.clear();
	double factor = RAND_MAX;
	for (uint i = 0; i < classesToMatch * multiply; i++) {
		vector<double> smallWeights;
		for (uint j = 0; j <= secondLayerNodeCount; j++) {
			double x = rand();
			smallWeights.push_back(x/factor);
		}
		weights.push_back(smallWeights);
	}
}
