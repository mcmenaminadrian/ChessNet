#include <vector>
#include <cstdint>
#include <QImage>
#include <QRgb>
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

void ChessInput::setInput(const QImage& imgIn)
{
	for (uint i = 0; i < rowLength; i++) {
		const uchar *scanLine = imgIn.constScanLine(i);
		for (uint j = 0; j < inputRows.at(i).size(); j++) {
			inputRows.at(i).at(j) = *(scanLine + j);
			inputRows.at(i).at(j);
		}
	}
}

vector<double> ChessInput::getInputs() const
{
	vector<double> flattenedImage;
	for (auto row: inputRows) {
		flattenedImage.insert(flattenedImage.end(),
			row.begin(), row.end());
	}
	return flattenedImage;
}

