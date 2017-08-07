#ifndef CHESSNET_HPP
#define CHESSNET_HPP


extern double activationDerivative(const double& input);
extern double activationFunction(const double& input);

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;

public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field, const uint& filters);
	void loadInput(const QImage& img);
	void feedForward();
};
#endif // CHESSNET_HPP
