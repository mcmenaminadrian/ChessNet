#ifndef CHESSNET_HPP
#define CHESSNET_HPP

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;
	std::stringstream allWeights;
	std::vector<double> reversedWeights(std::vector<double> kernel) const;
	std::vector<std::vector<double> > tryFix(
		const std::vector<double>& basicErrors,
		const std::vector<double>& outputDeltas);
public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field,
		const uint& filters, const uint& depth,
		std::ifstream& weightsIn);
	~ChessNet();
	void loadInput(const QImage& img);
	void feedForward(std::__cxx11::string&, uint imageClass);
	void storeWeights();
};
#endif // CHESSNET_HPP
