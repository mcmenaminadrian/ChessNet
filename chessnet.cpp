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
	const uint& field, const uint& filterCount, ifstream& weightsIn):
	inputNet(width, height)
{

	for (uint i = 0; i < filterCount; i++) {
		filters.push_back(FilterNet(width, height, span, field,
			inputNet, weightsIn));
	}

	outLayer.setUpVariables(filters, filterCount, weightsIn);
}

void ChessNet::loadInput(const QImage& imgIn)
{
	inputNet.setInput(imgIn);
}

void ChessNet::feedForward() {
	vector<double> soughtResult = {1.0, 1,0, 0.0,
		0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
	for (auto& filter: filters) {
		filter.computeActivations(inputNet);
	}
	outLayer.calculateSums(filters);
	pair<vector<double>, vector<double>> actives =
			outLayer.returnActivations();
	uint i = 0;
	vector<double> errors;
	double totalError = 0.0;
	for (const auto& answers: actives.first) {
		double basicErr = answers - soughtResult.at(i);
		double sqError = basicErr * basicErr;
		errors.push_back(sqError);
		totalError += sqError;
		cout << "Neuron " << i << " returns ";
		cout << answers << endl;
		cout << "Error is " << errors.at(i++) << endl;
	}
	cout << "Average Error was " << totalError/i << endl;

	vector<vector<double>> gradients;
	for (uint i = 0; i < actives.first.size(); i++) {
		gradients.push_back(outLayer.errGrads(i, errors.at(i)));

	}


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
