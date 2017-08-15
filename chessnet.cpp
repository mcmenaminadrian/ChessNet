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
	ifstream& weightsIn):inputNet(width, height)
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
		i++;
		if (i == imageClass) {
			iterationError = 1.0 - answers;
		} else {
			iterationError = -answers;
		}
		basicErrors.push_back(iterationError);
		totalError += (iterationError * iterationError);
	}
	cout << "==========" << endl;
	cout << "FILE out: " << fileName << endl;
	cout << "Average Error is " << totalError / i << endl;

	//now try error correction
	vector<vector<double>> gradients;
	vector<double>::iterator it = basicErrors.begin();
	i = 0;
	for (const auto& derivs: actives.second) {
		gradients.push_back(outLayer.errGrads(filters, *it++, derivs,
		i++));
	}
	outLayer.tryCorrections(0.1, gradients);
	auto layerSizes = filters.begin().getLayerSizes();
	for (uint i = depth - 1; i >= 0; i++) {
		for (uint j = 0; j < filters.size(); j++) {
			vector<double> revKernel = reversedWeights(
				filters.at(j).fibreWeights.at(i));
			tryFix(0.1, revKernel, j, i, basicErrors.at(j), layerSizes)
		}

	}
}

void ChessNet::tryFix(const double& factor, const vector<double>& revKernel,
	uint fibreNumber, uint layerNumber, const vector<uint>& layerSizes)
{
	vector<double>& weightsToFix
}

vector<double> ChessNet::reversedWeights(vector<double> kernel) const
{
	return kernel.reverse(begin(kernel), end(kernel));
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
