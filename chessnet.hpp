#ifndef CHESSNET_HPP
#define CHESSNET_HPP

class ChessNet
{

private:
	std::vector<FilterNet> filters;
	ChessInput inputNet;
	FullyConnected outLayer;
	std::stringstream allWeights;
	void tryFix(const std::vector<double>& outputDeltas,
		    const std::vector<std::vector<double>> &outCorrections, uint fact);
	void _tryFix(const FilterNet& fibre,
		const std::vector<double>& outputDeltas,
		std::vector<std::vector<double>>& fibreCorrections,
		int fibreDepth, bool first);
	void fixThread(FilterNet fibre,
		std::vector<double> outputDeltas,
		std::vector<std::vector<double> >& fibreCorrections);
public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field,
		const uint& filters, const uint& depth,
		std::ifstream& weightsIn);
	~ChessNet();
	void loadInput(const QImage& img);
	void feedForward(std::string&, uint imageClass, uint fact);
	void storeWeights();
};
#endif // CHESSNET_HPP
