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


static uint imageNumber = 0;

FilterNet::FilterNet(const uint& width, const int& span,
	const uint& field, const uint& depth,
	std::ifstream& inFile)
{
	uint effectiveWidth = width;
	commonField = field;
	fibreDepth = depth;
	commonSpan = span;
	for (uint i = 0; i < fibreDepth; i++) {
		vector<HiddenNeuron> neurons;
		uint networkSize = 1 + (effectiveWidth - commonField) /
			commonSpan;
		networkSizes.push_back(networkSize);
		for (uint j = 0; j < networkSize; j++) {
			for (uint k = 0; k < networkSize; k++) {
				HiddenNeuron neuro;
				uint rowIndex = j * effectiveWidth;
				uint kAdvance = k * commonSpan;
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
		for (uint j = 0; j <= commonField * commonField; j++) {
			double number = rand();
			number /= factor;
			weights.push_back(number / 1000);
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
	vector<vector<HiddenNeuron>>::iterator fibreIt = fibre.begin();
	vector<vector<double>>::iterator weightsIt = fibreWeights.begin();
	_computeActivations(inputs, fibreIt, weightsIt);
}

void FilterNet::_computeActivations(const vector<double>& inputs,
	vector<vector<HiddenNeuron>>::iterator& neuronsIt,
	vector<vector<double>>::iterator& weightsIt)
{
	if (neuronsIt == fibre.end()) {
		return;
	}
	vector<HiddenNeuron>& neurons = *neuronsIt;
	vector<double> weights = *weightsIt;
	vector<double> nextIn;
	uint weightCounter = 0;
	for (auto& neuro: neurons) {
		double sum = 0.0;
		for (const auto& numb: neuro.getConnections()) {
			sum += inputs.at(numb) * weights.at(weightCounter);
			weightCounter++;
			weightCounter = weightCounter % (weights.size() - 1);
		}
		sum += weights.back();
		pair<double, double> actives = neuro.setActivation(sum);
		nextIn.push_back(actives.first);
	}

#ifdef FILTEREDIMAGES
	//output filtered Image
	uint numb = neurons.size();
	uint iSize = sqrt(numb);
	QImage filteredImage(iSize, iSize, QImage::Format_Grayscale8);
	uint i = 0;
	uint j = 0;
	for (auto neuro: neurons) {
		uint pixVal = neuro.getActivation().first;
		filteredImage.setPixel(i++, j, qRgb(pixVal, pixVal, pixVal));
		if (i >= iSize) {
			i = 0;
			j++;
		}
	}
	//int randomValue = qrand()%100000;
	QString fileN = QString::number(imageNumber++) + QString(".jpg");
	filteredImage.save(fileN);
#endif

	neuronsIt++;
	weightsIt++;
	_computeActivations(nextIn, neuronsIt, weightsIt);
}

vector<uint> FilterNet::getLayerSizes() const
{
	return networkSizes;
}

const pair<double, double> FilterNet::getLayerActivations(const uint& layer,
	const uint& neuron) const
{
	const vector<HiddenNeuron>& layerRequested = fibre.at(layer);
	return layerRequested.at(neuron).getActivation();
}

const HiddenNeuron& FilterNet::getLayerNeuron(const uint &layer,
	const uint &neuron) const
{
	const vector<HiddenNeuron>& layerRequested = fibre.at(layer);
	return layerRequested.at(neuron);
}
