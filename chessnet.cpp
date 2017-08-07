#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <QImage>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
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
	const uint& field, const uint& filterCount): inputNet(width, height)
{

	for (uint i = 0; i < filterCount; i++) {
		filters.push_back(FilterNet(width, height, span, field,
			inputNet));
	}

	outLayer.setUpVariables(filters, filterCount);



/*	cout << "WEIGHTS" << endl;
	cout << "Hidden layers" << endl;
	for (auto x: filters) {
		cout << x;
		cout << endl;
	}
	cout << "Fully connected layer" << endl;
	cout << outLayer; */
}

void ChessNet::loadInput(const QImage& imgIn)
{
	inputNet.setInput(imgIn);
}

void ChessNet::feedForward() {
	for (auto& filter: filters) {
		filter.computeActivations(inputNet);
	}
}
