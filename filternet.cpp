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

static const uint secondLayerSpan = 1;
static const uint secondLayerField = 3;

FilterNet::FilterNet(const uint& width, const int& span,
	const uint& field, std::ifstream& inFile)
{
	//connect number = (width - field)/span + 1
	//(assuming no padding)
	netCount = 1 + (width - field) / span;
	fieldSize = field;
	for (uint i = 0; i < netCount; i++) {
		for (uint j = 0; j < netCount; j++) {
			//row by row construct and connect level one neurons
			HiddenNeuron neuro(fieldSize, this);
			uint rowIndex = i * width;
			uint jAdvance = j * span;
			for (uint k = 0; k < field; k++) {
				uint kRow = k * width;
				for (uint l = 0; l < field; l++) {
					neuro.addConnection(rowIndex + jAdvance
						+ kRow + l);
				}
			}
			neurons.push_back(neuro);
		}
	}
	secondLayerSize = calculateSecondLayerSize(secondLayerSpan,
		secondLayerField);
	for (uint i = 0; i < secondLayerSize; i++) {
		for (uint j = 0; j < secondLayerSize; j++) {
			HiddenNeuron neuro(fieldSize, this);
			uint rowIndex = i * netCount;
			uint jAdvance = j * secondLayerSpan;
			for (uint k = 0; k < secondLayerField; k++) {
				uint kRow = k * netCount;
				for (uint l = 0; l < secondLayerField; l++) {
					neuro.addConnection((rowIndex + jAdvance +
					+ kRow +l));
				}
			}
			secondNeurons.push_back(neuro);
		}
	}
	loadWeights(inFile);
	//NB only use next line at start up
	//assignRandomWeights(fieldSize, secondLayerField);
}

void FilterNet::checkFilterWeights()
{
	if (topWeights.size() != 1 + fieldSize * fieldSize ||
		bottomWeights.size() !=
		1 + secondLayerField * secondLayerField) {
		QMessageBox messageBox;
		messageBox.setText(
			"Mismatch of weight vector and filter size.");
		messageBox.exec();
		QApplication::quit();
	}

}

void FilterNet::loadWeights(ifstream& inFile)
{
	streamInWeights(inFile);
}

void FilterNet::assignRandomWeights(const uint& firstFieldSize,
	const uint& secondFieldSize)
{

	double factor = RAND_MAX;
	for (uint i = 0; i < firstFieldSize * firstFieldSize; i++) {
		double number = rand();
		topWeights.push_back(number/factor);
	}

	//bias
	double randomBias = rand();
	randomBias /= factor;
	topWeights.push_back(randomBias);

	for (uint i = 0; i < secondFieldSize * secondFieldSize; i++) {
		double number = rand();
		bottomWeights.push_back(number/factor);
	}
	bottomWeights.push_back(randomBias);
	checkFilterWeights();
}


uint FilterNet::calculateSecondLayerSize(const uint& secondSpan,
	const uint& secondField) const
{
	return 1 + (netCount - secondField)/ secondSpan;
}

uint FilterNet::getNetCount() const
{
	return netCount;
}

ostream& FilterNet::streamOutWeights(ostream& os) const
{
	for (auto x: topWeights) {
		os << x;
		os << " ";
	}
	os << endl;
	for (auto x: bottomWeights) {
		os << x;
		os << " ";
	}
	os << endl;
	return os;

}

istream& FilterNet::streamInWeights(istream& is)
{
	topWeights.clear();
	for (uint i = 0; i <= fieldSize * fieldSize; i++)
	{
		double x;
		is >> x;
		topWeights.push_back(x);
	}
	bottomWeights.clear();
	for (uint i = 0; i <= secondLayerField * secondLayerField; i++)
	{
		double x;
		is >> x;
		bottomWeights.push_back(x);
	}
	checkFilterWeights();
	return is;
}

pair<uint, uint> FilterNet::getLayerSizes() const
{
	return pair<uint, uint>(netCount, secondLayerSize);
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
