#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	std::vector<std::vector<HiddenNeuron>> fibre;
	std::vector<std::vector<std::pair<double, double>>> fibreActivations;
	std::vector<uint> networkSizes;
	uint commonField;
	uint commonSpan;
	uint fibreDepth;
	uint calculateNextLayerSize();
	void assignRandomWeights();
	std::pair<double, double> activationFunction(const double& in) const;
	void loadWeights(std::ifstream& inFile);
public:
	std::vector<std::vector<double>> fibreWeights; // last always bias
	FilterNet(const uint& width, const int& field,
		const uint& span, const uint& depth, std::ifstream& inFile);
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	std::pair<uint, uint> getLayerSizes() const;
	void computeActivations(const ChessInput& inNet);
	std::pair<double, double> getLayerActivations(const uint& layer,
		const uint& neuron);
};

#endif // FILTERNET_HPP
