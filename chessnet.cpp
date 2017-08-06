#include <vector>
#include <cstdint>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"
#include "chessnet.hpp"

using namespace std;

ChessNet::ChessNet(const uint& width, const uint& height, const uint& span,
	const uint& field, const uint& filterCount)
{

	ChessInput inputNet(width, height);
	for (uint i = 0; i < filterCount; i++) {
		filters.push_back(FilterNet(width, height, span, field,
			inputNet));
	}
}

