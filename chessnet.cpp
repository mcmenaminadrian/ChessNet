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
	auto layerSizes = filters.front().getLayerSizes();
	auto depth = filters.front().getDepth();

		auto filterCorrections = tryFix(filters, basicErrors,
			layerSizes, depth);
	}
}

vector<vector<double>> ChessNet::tryFix(const vector<double>& basicErrors,
	const vector<double>& outputDeltas)
{


	for (uint i = 0; i < filters.size(); i++) {
		//for fully connected layer
		auto filter = filters.at(i);
		uint finalLayerSize = filter.getLayerSizes().back();
		finalLayerSize *= finalLayerSize;
		uint filterDepth = filter.getDepth();
		for (uint j = 0; j < finalLayerSize; i++)
		{
			double neuroActivation = filter.get
	}

	uint probe = depth - 1;
	auto layersIt = layerSizes.rbegin();
	vector<double>& weight = filter.fibreWeights.at(probe);
	for (auto error: basicErrors) {

	}


}

vector<double> ChessNet::reversedWeights(vector<double> kernel) const
{
	reverse(kernel.begin(), kernel.end());
	return kernel;
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
