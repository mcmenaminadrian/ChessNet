#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	std::vector<std::vector<HiddenNeuron>> fibre;
	std::vector<uint> networkSizes;
	uint commonField;
	uint commonSpan;
	uint fibreDepth;
	uint calculateNextLayerSize();
	void assignRandomWeights();
	void loadWeights(std::ifstream& inFile);
	void _computeActivations(const std::vector<double>& inputs,
		std::vector<std::vector<HiddenNeuron>>::iterator& neuronsIt,
		std::vector<std::vector<double>>::iterator& weightsIt);
public:
	std::vector<std::vector<double>> fibreWeights; // last always bias
	FilterNet(const uint& width, const int& field,
		const uint& span, const uint& depth, std::ifstream& inFile);
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	std::vector<uint> getLayerSizes() const;
	void computeActivations(const std::vector<double>& inputs);
	const std::pair<double, double> getLayerActivations(const uint& layer,
		const uint& neuron) const;
	uint getDepth() const {return fibreDepth;}
	const HiddenNeuron& getLayerNeuron(const uint& layer,
		const uint& neuron) const;
};

#endif // FILTERNET_HPP
