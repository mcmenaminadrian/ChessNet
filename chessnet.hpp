#ifndef CHESSNET_HPP
#define CHESSNET_HPP

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;
	std::stringstream allWeights;
	void tryFix(const std::vector<double>& outputDeltas);
	void _tryFix(const FilterNet& fibre,
		const std::vector<double>& outputDeltas,
		std::vector<std::vector<double>>& fibreCorrections,
		int fibreDepth, bool first);
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
