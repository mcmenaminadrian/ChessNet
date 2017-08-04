#include <vector>
#include <cstdint>
#include "sys/types.h"
#include "chessinput.hpp"

using namespace std;

ChessInput::ChessInput(const uint& width, const uint& height)
{
	for (uint i = 0; i < height; i++) {
		vector<double> column(width, 0.0);
		inputRows.push_back(column);
	}
}

