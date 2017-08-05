#include <vector>
#include <QMessageBox>
#include <QApplication>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"

using namespace std;

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
			LevelOneNeuron neuro;
			uint rowIndex = i * width;
			uint jAdvance = j * span;
			for (uint k = 0; k < field; k++) {
				uint kRow = k * width;
				for (uint l = 0; l < field; l++) {
					neuro.addConnection(rowIndex + jAdvance +
						+ kRow + l);
				}
			}
			neurons.push_back(neuro);
		}
	}
}

void FilterNet::assignFilterWeights(const vector<double>& weights)
{
	if (weights.size() != fieldSize * fieldSize) {
		QMessageBox messageBox;
		messageBox.setText("Mismatch of weight vector and filter size.");
		messageBox.exec();
		QApplication::quit();
	}
	for (uint i = 0; i < netCount; i++) {
		uint neuronIndex = i * fieldSize * fieldSize;
		for (uint j = 0; j < fieldSize; j++) {
			uint neuronRow = j * fieldSize;
			for (uint k = 0; k < fieldSize; k++){
				(neurons.at(neuronIndex + neuronRow + k)).
					setWeight(weights.at(neuronRow + k));
			}
		}
	}
}

uint FilterNet::calculateSecondLayerSize(const uint& secondSpan,
	const uint& secondField) const
{
	return 1 + (netCount - secondField)/ secondSpan
}
