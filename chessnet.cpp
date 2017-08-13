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

	outLayer.setUpVariables(filters, filterCount, weightsIn);
}

void ChessNet::loadInput(const QImage& imgIn)
{
	inputNet.setInput(imgIn);
}

void ChessNet::feedForward() {
	for (auto& filter: filters) {
		filter.computeActivations(inputNet);
	}
	outLayer.calculateSums(filters);
	pair<vector<double>, vector<double>> actives =
			outLayer.returnActivations();
	uint i = 0;
	for (const auto& answers: actives.first) {
		cout << "Neuron " << i++ << " returns ";
		cout << answers << endl;
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
