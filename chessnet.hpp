#ifndef CHESSNET_HPP
#define CHESSNET_HPP

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;
	std::stringstream allWeights;

public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field,
		const uint& filters, const uint& depth,
		std::ifstream& weightsIn);
	~ChessNet();
	void loadInput(const QImage& img);
	void feedForward();
	void storeWeights();
};
#endif // CHESSNET_HPP
