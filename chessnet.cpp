#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <QImage>
#include <sstream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "hiddenneuron.hpp"
#include "filternet.hpp"
#include "fullyconnected.hpp"
#include "chessnet.hpp"

using namespace std;



ostream& operator<<(ostream& os, const FilterNet& filter)
{
	return filter.streamOutWeights(os);
}

istream& operator>>(istream& is, FilterNet& filter)
{
	return filter.streamInWeights(is);
}

ostream& operator<<(ostream& os, const FullyConnected& fc)
{
	return fc.streamOutWeights(os);
}

istream& operator>>(istream& is, FullyConnected& fc)
{
	return fc.streamInWeights(is);
}


ChessNet::ChessNet(const uint& width, const uint& height, const uint& span,
	const uint& field, const uint& filterCount, const uint& depth,
	ifstream& weightsIn):inputNet(width, height), outLayer(filterCount)
{

	for (uint i = 0; i < filterCount; i++) {
		filters.push_back(FilterNet(width, span, field, depth,
			weightsIn));
	}

	uint count = filters.front().getLayerSizes().back();
	outLayer.setUpVariables(filters,  count, weightsIn);
}

void ChessNet::loadInput(const QImage& imgIn)
{
	inputNet.setInput(imgIn);
}

void ChessNet::feedForward(string& fileName, uint imageClass)
{

	const vector<double> inputVector = inputNet.getInputs();
	for (auto& filter: filters) {
		filter.computeActivations(inputVector);
	}

	outLayer.calculateSums(filters);
	pair<vector<double>, vector<double>> actives =
			outLayer.returnActivations();
	uint i = 0;
	double totalError = 0.0;
	vector<double> basicErrors;
	for (const auto& answers: actives.first) {
		double iterationError = 0.0;
		if (i == imageClass) {
			iterationError = 1 - answers;
		} else {
			iterationError = -1 - answers;
		}
		basicErrors.push_back(iterationError);
		totalError += (iterationError * iterationError) / 2;
		i++;
		cout << iterationError << ":" << answers << ", ";
	}
	cout << endl;
	cout << "==========" << endl;
	cout << "FILE: " << fileName << " Class: " << imageClass << endl;
	cout << "Average Error is " << totalError / i << endl;

	//now try error correction
	vector<double> deltas;
	vector<double>::iterator it = basicErrors.begin();
	i = 0;
	for (const auto& derivs: actives.second) {
		deltas.push_back(derivs * (*it++));
	}

	//fix up fully connected layer
	auto outCorrections = outLayer.tryCorrections(filters, deltas);

	//fix up filters


	tryFix(deltas);
}

void ChessNet::tryFix(const vector<double> &outputDeltas)
{
	vector<vector<vector<double>>> corrections;
	for (const auto& fibre: filters) {
		uint fibreDepth = fibre.getDepth() - 1;
		vector<vector<double>> fibreCorrections;
		_tryFix(fibre, outputDeltas, fibreCorrections,
			fibreDepth, true);
		corrections.push_back(fibreCorrections);
	}
}

void ChessNet::_tryFix(const FilterNet& fibre, const vector<double>& upperDeltas,
	vector<vector<double>>& fibreCorrections, uint fibreDepth, bool first)
{
	if (fibreDepth < 0) {
		return;
	}

	uint upperLayerSize = fibre.getLayerSizes().at(fibreDepth);
	upperLayerSize *= upperLayerSize;
		// i -> j -> k
		//calculate delta j
		//sum deltas_k * weights_kj for each neuron in k
	vector<double> delta_j(upperLayerSize, 0.0);
	if (!first) {
		uint revConv = 0;
		auto weightsAbove = fibre.fibreWeights.at(fibreDepth + 1);
		uint weightsCountAbove =
			weightsAbove.size() - 1;
		for (uint k = 0; k < upperDeltas.size(); k++) {
			auto connex =
				fibre.getLayerNeuron(fibreDepth + 1, k).
				getConnections();
			uint l = 0;
			for (const auto& link: connex) {
				delta_j.at(link) += upperDeltas.at(k) *
					weightsAbove.at(l++);
				l %= weightsCountAbove;
			}
		}
	} else {
		for (uint j = 0; j < upperLayerSize; j++) {
			for (uint k = 0; k < upperDeltas.size(); k++) {
				delta_j.at(j) += upperDeltas.at(k) *
					outLayer.getWeight(j, k);
			}
		}
	}
	for (uint j = 0; j < upperLayerSize; j++) {
		//multiply by activation function deriv for each in j
		delta_j.at(j) *= fibre.
			getLayerActivations(fibreDepth, j).second;
	}
	uint weightsCount = fibre.fibreWeights.at(fibreDepth).size() - 1;
	pair<double, uint> dummyCorrection(0.0, 0);
	vector<pair<double, uint>> summedCorrections(weightsCount, dummyCorrection);
	//calculate deriv
	//multiply by output in i
	for (uint j = 0; j < upperLayerSize; j++)
	{
		const HiddenNeuron& neuron =
			fibre.getLayerNeuron(fibreDepth, j);
		const auto& connex = neuron.getConnections();
		for (uint k = 0; k < weightsCount; k++)
		{
			double currentCorrection =
				summedCorrections.at(k).first;
			uint currentCount = summedCorrections.at(k).second;
			double newCorrection = delta_j.at(j) *
				fibre.getLayerActivations(
				fibreDepth, connex.at(k)).first;
			summedCorrections.at(k) = pair<double, uint>(
				currentCorrection + newCorrection,
				++currentCount);
		}
	}
	vector<double> averageCorrections(weightsCount, 0.0);
	for (uint k = 0; k < weightsCount; k++)
	{
		averageCorrections.at(k) =
			(summedCorrections.at(k).first)/
			(summedCorrections.at(k).second);
	}
	fibreCorrections.push_back(averageCorrections);
	_tryFix(fibre, delta_j, fibreCorrections, --fibreDepth, false);

}

void ChessNet::storeWeights()
{
	for (auto x: filters) {
		allWeights << x;
	}
	allWeights << outLayer;
}

ChessNet::~ChessNet()
{
	ofstream weightsFile;
	weightsFile.open("weights.txt");
	weightsFile << allWeights.str();
	weightsFile.close();
}
