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


FullyConnected::FullyConnected(const uint& filterCount): sums(filterCount, 0.0)
{
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
	fill(sums.begin(), sums.end(), 0.0);
	auto filterIterator = filters.begin();
	for (const auto& filterWeights :weights) {
		uint i = 0;
		uint index = 0;
		for (const auto& individualWeight: filterWeights) {
			sums.at(index) += (*filterIterator).
				getLayerActivations(layersCount - 1,
				i).first * individualWeight;
			index++;
			index %= classesToMatch;
			if (index == 0) {
				i++;
			}
		}
		filterIterator++;
	}
	for (uint i = 0; i < classesToMatch; i++) {
		sums.at(i) += bias.at(i);
	}
	return sums;
}

pair<vector<double>&, vector<double>&> FullyConnected::returnActivations()
{
	activations.clear();
	activationDerivatives.clear();
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
	for (uint i = 0; i < classesToMatch;  i++) {
		vector<double> smallWeights;
		for (uint j = 0; j < classesToMatch; j++) {
			for (uint k = 0; k < nodesCount * nodesCount; k++) {
				double x;
				is >> x;
				smallWeights.push_back(x);
			}
		}
		weights.push_back(smallWeights);
	}
	for (uint i = 0; i < classesToMatch; i++) {
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
	for (uint i = 0; i < classesToMatch; i++) {
		vector<double> smallWeights;
		for (uint j = 0; j < classesToMatch; j++) {
			for (uint k = 0; k < nodesCount * nodesCount; k++) {
				double x = rand();
				smallWeights.push_back(x/factor);
			}
		}
		double x = rand() / 1000;
		bias.push_back(x / factor);
		weights.push_back(smallWeights);
	}
}


vector<vector<double>> FullyConnected::tryCorrections(
	const vector<FilterNet>& filters, const vector<double> &deltas)
{
	uint outNeuronCount = filters.size();
	uint filterLayerSize = filters.at(0).getLayerSizes().back();
	filterLayerSize *= filterLayerSize;
	auto innerCorrections = vector<double>
		(filterLayerSize * outNeuronCount, 0.0);
	auto fullCorrections =
		vector<vector<double>>(outNeuronCount, innerCorrections);
	uint finalLayer = filters.at(0).getDepth() - 1;
	for (uint i = 0; i < outNeuronCount; i++) {
		for (uint j = 0; j < filterLayerSize; j++) {
			double out = -1 * filters.at(i).getLayerActivations
				(finalLayer, j).first;
			for (uint k = 0; k < outNeuronCount; k++) {
				(fullCorrections.at(i))
					.at(j * outNeuronCount + k) =
					out * deltas.at(k);
			}
		}
	}
/*
	for (uint i = 0; i < outNeuronCount; i++) {
		auto corrIt = fullCorrections.at(i).begin();
		for (auto& weight: weights.at(i)) {
			weight -= ((*corrIt) * factor);
			corrIt++;
		}
	}

	for (uint i = 0; i < filters.size(); i++) {
		double biasCorrection = -1 * bias.at(i) * deltas.at(i);
		bias.at(i) = bias.at(i) - (biasCorrection * factor);
	}
*/
	vector<double> biasCorrections;
	for (uint i = 0; i < filters.size(); i++) {
		double correction = -1 * bias.at(i) * deltas.at(i);
		biasConnections.push_back(bias.at(i) - biasCorrection));
	}
	fullCorrections.push_back(biasCorrections);

	return fullCorrections;
}
