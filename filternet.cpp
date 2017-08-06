#include <vector>
#include <QMessageBox>
#include <QApplication>
#include <cstdlib>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"

using namespace std;

static const uint secondLayerSpan = 1;
static const uint secondLayerField = 3;

FilterNet::FilterNet(const uint& height, const uint& width, const int& span,
	const uint& field, ChessInput& inputLayer)
{
	//connect number = (width - field)/span + 1
	//(assuming no padding)
	netCount = 1 + (width - field) / span;
	fieldSize = field;
	for (uint i = 0; i < netCount; i++) {
		for (uint j = 0; j < netCount; j++) {
			//row by row construct and connect level one neurons
			HiddenNeuron neuro;
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
		netCount);
	for (uint i = 0; i < secondLayerSize; i++) {
		for (uint j = 0; j < secondLayerSize; j++) {
			HiddenNeuron neuro;
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
	//NB only use next line at start up
	assignRandomWeights(fieldSize, secondLayerField);
}

void FilterNet::assignFilterWeights(const vector<double>& weightsTop,
	const vector<double>& weightsBottom)
{
	if (weightsTop.size() != fieldSize * fieldSize ||
		weightsBottom.size() != secondLayerField * secondLayerField) {
		QMessageBox messageBox;
		messageBox.setText(
			"Mismatch of weight vector and filter size.");
		messageBox.exec();
		QApplication::quit();
	}
	for (uint i = 0; i < netCount; i++) {
		uint neuronIndex = i * fieldSize * fieldSize;
		for (uint j = 0; j < fieldSize; j++) {
			uint neuronRow = j * fieldSize;
			for (uint k = 0; k < fieldSize; k++){
				(neurons.at(neuronIndex + neuronRow + k)).
					setWeight(
					topWeights.at(neuronRow + k));
			}
		}
	}
	for (uint i = 0; i < secondLayerSize; i++){
		uint neuronIndex = i * secondLayerField * secondLayerField;
		for (uint j = 0; j < secondLayerField; j++) {
			uint neuronRow = j * secondLayerField;
			for (uint k = 0; k < secondLayerField; k++) {
				(secondNeurons.at(neuronIndex + neuronRow + k)).
					setWeight(
					bottomWeights.at(neuronRow + k));
			}
		}
	}
}


void FilterNet::assignRandomWeights(const uint& firstFieldSize,
	const uint& secondFieldSize)
{
	vector<double> firstLayer;
	vector<double> secondLayer;
	double factor = RAND_MAX;
	for (uint i = 0; i < firstFieldSize * firstFieldSize; i++) {
		double number = rand();
		firstLayer.push_back(number/factor);
	}
	for (uint i = 0; i < secondFieldSize * secondFieldSize; i++) {
		double number = rand();
		secondLayer.push_back(number/factor);
	}
	assignFilterWeights(firstLayer, secondLayer);
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


