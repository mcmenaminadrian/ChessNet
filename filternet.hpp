#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	std::vector<HiddenNeuron> neurons;
	std::vector<double> topWeights; //last of these is bias
	std::vector<std::pair<double, double> > firstHiddenActivations;
	std::vector<HiddenNeuron> secondNeurons;
	std::vector<double> bottomWeights; //last of these is bias
	std::vector<std::pair<double, double> > secondHiddenActivations;
	uint netCount;
	uint secondLayerSize;
	uint fieldSize;
	uint calculateSecondLayerSize(const uint& secondSpan,
		const uint& secondField) const;
	void assignRandomWeights(const uint& firstFieldSize,
		const uint& secondFieldSize);
	std::pair<double, double> activationFunction(const double& in) const;
	void loadWeights(std::ifstream& inFile, const uint& firstFieldSize,
		const uint& secondFieldSize);
public:
	FilterNet(const uint& height, const uint& width, const int& field,
		const uint& span, const ChessInput& inputLayer,
		std::ifstream& inFile);
	void assignFilterWeights();
	uint getNetCount() const;
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	std::pair<uint, uint> getLayerSizes() const;
	void computeActivations(const ChessInput& inNet);
	std::pair<double, double> getSecActivations(const uint& index) const;
	std::pair<double, double> getFirActivations(const uint& index) const;
};

#endif // FILTERNET_HPP
