#include <vector>
#include <QMessageBox>
#include <QApplication>
#include <cstdlib>
#include <iostream>
#include <fstream>
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
	fieldSize = field;
	fibreDepth = depth;
	for (uint i = 0; i < fibreDepth; i++) {
		vector<double> neurons;
		uint networkSize = 1 + (effectiveWidth - fieldSize) / span;
		networkSizes.push_back(networkSize);
		for (uint j = 0; j < networkSize; j++) {
			for (uint k = 0; k < networkSize; k++) {
				HiddenNeuron neuro(fieldSize, this);
				uint rowIndex = j * width;
				uint kAdvance = k * span;
				for (uint l = 0; l < fieldSize; l++) {
					uint lRow = l * effectiveWidth;
					for (uint m = 0; m < fieldSize; m++) {
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
		for (uint j = 0; j <= fieldSize; j++) {
			double number = rand();
			number /= factor;
			weights.push_back(number - 0.5);
		}
		fibreWeights.push_back(weights);
	}
	checkFilterWeights();
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
		for (uint j = 0; j <= fieldSize * fieldSize; j++)
		{
			double x;
			is >> x;
			weights.push_back(x);
		}
		fibreWeights.push_back(weights);
	}
	return is;
}

void FilterNet::computeActivations(const ChessInput& inNet)
{



	for (auto& neuro: neurons) {
		neuro.sumInputs(inNet);
		firstHiddenActivations.push_back(neuro.setActivation());
	}
	for (auto& neuro: secondNeurons) {
		neuro.sumSecondLayer();
		secondHiddenActivations.push_back(neuro.setActivation());
	}

}

pair<double, double> FilterNet::getSecActivations(const uint &index) const
{
	return secondHiddenActivations.at(index);
}

pair<double, double> FilterNet::getFirActivations(const uint &index) const
{
	return firstHiddenActivations.at(index);
}
