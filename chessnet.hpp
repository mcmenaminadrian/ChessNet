#ifndef CHESSNET_HPP
#define CHESSNET_HPP


double activationDerivative(const double& input);
double activationFunction(const double& input);

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;

public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field, const uint& filters);
};
#endif // CHESSNET_HPP
