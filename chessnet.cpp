#include <vector>
#include <cstdint>
#include <iostream>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"
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


ChessNet::ChessNet(const uint& width, const uint& height, const uint& span,
	const uint& field, const uint& filterCount)
{

	ChessInput inputNet(width, height);
	for (uint i = 0; i < filterCount; i++) {
		filters.push_back(FilterNet(width, height, span, field,
			inputNet));
	}

	for (uint i = 0; i < filterCount; i++)
	{
		cout << "Filter " << i << endl;
		cout << filters.at(i);
	}
}

