#include <vector>
#include "sys/types.h"
#include "chessinput.hpp"
#include "leveloneneuron.hpp"
#include "filternet.hpp"

using namespace std;

FilterNet::FilterNet(const uint& height, const uint& width, const int& span,
	const uint& field, ChessInput& inputLayer)
{
	//connect number = (width - field)/span + 1
	//(assuming no padding)
	uint netCount = 1 + (width - field) / span;
	for (uint i = 0; i < netCount; i++) {
		for (uint j = 0; j < netCount; j++) {
			//row by row construct and connect level one neurons
			LevelOneNeuron neuro;
			for (uint k = 0; k < field; k++) {
				neuro.addConnection(i * width + j * span + k);
				neuro.addConnection(k * width + j * span +
					i * width);
			}
			neurons.push_back(neuro);
		}
	}

}

