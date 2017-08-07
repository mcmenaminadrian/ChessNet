#include <vector>
#include <cstdint>
#include "sys/types.h"
#include "chessinput.hpp"

using namespace std;

ChessInput::ChessInput(const uint& width, const uint& height): rowLength(width)
{
	for (uint i = 0; i < height; i++) {
		vector<double> column(width, 0.0);
		inputRows.push_back(column);
	}
}

const double& ChessInput::getInput(const uint& index) const
{
	uint row = index / rowLength;
	uint col = index % rowLength;
	return (inputRows.at(row)).at(col);
}

