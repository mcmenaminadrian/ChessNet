#include <vector>
#include <cstdint>
#include <iostream>
#include <QImage>
#include <sstream>
#include <fstream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"
#include "fullyconnected.hpp"
#include "chessnet.hpp"
#include "activation.hpp"


using namespace std;


FullyConnected::FullyConnected()
{
	//change this to change output neuron number
	multiply = 1;
}

void FullyConnected::setUpVariables(const vector<FilterNet>& filters,
	const uint& count, std::ifstream& weightFile)
{
	//one to one correspondence between number of filter fibres and classes
	classesToMatch = filters.size();
	nodesCount = count;
	layersCount = filters.front().getLayerSizes().size();
	streamInWeights(weightFile);
	//NB: not to use in production
	//assignRandomWeights();
}

const vector<double>& FullyConnected::calculateSums(
	const vector<FilterNet>& filters)
{
	sums.clear();
	auto biasIndex = bias.begin();
	for (const auto& filterWeights :weights) {
		auto filterIterator = filters.begin();
		uint i = 0;
		double summation = 0.0;
		for (const auto& individualWeight: filterWeights) {
			if (i < (*filterIterator).getLayerSizes().back()) {
				summation += (*filterIterator).
					getLayerActivations(layersCount - 1,
					i++).first * individualWeight;
			} else {
				i = 0;
				summation += *biasIndex++;
				filterIterator++;
			}
		}
		sums.push_back(summation);
	}
	return sums;
}


pair<vector<double>&, vector<double>&> FullyConnected::returnActivations()
{
	activations.clear();
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
	}
	os << endl;
	for (auto x: bias) {
		os << x;
		os << " ";
	}
	os << endl;
	return os;
}

istream& FullyConnected::streamInWeights(istream& is)
{
	weights.clear();
	for (uint i = 0; i < classesToMatch * multiply; i++) {
		vector<double> smallWeights;
		for (uint j = 0; j < nodesCount; j++) {
			double x;
			is >> x;
			smallWeights.push_back(x);
		}
		weights.push_back(smallWeights);
	}
	for (uint i = 0; i < classesToMatch * multiply; i++) {
		double x;
		is >> x;
		bias.push_back(x);
	}
	return is;
}

void FullyConnected::assignRandomWeights()
{
	weights.clear();
	double factor = RAND_MAX;
	for (uint i = 0; i < classesToMatch * multiply; i++) {
		vector<double> smallWeights;
		for (uint j = 0; j < nodesCount; j++) {
			double x = rand();
			smallWeights.push_back(x/factor);
		}
		double x = rand();
		bias.push_back(x / factor);
		weights.push_back(smallWeights);
	}
}
