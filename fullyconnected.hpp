#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP


class FullyConnected
{
private:
	std::vector<std::vector<double> > weights;
	std::vector<double> sums;
	std::vector<double> activations;
	std::vector<double> activationDerivatives;
	std::vector<double> bias;
	uint multiply;
	uint nodesCount;
	uint classesToMatch;
	uint layersCount;
	void assignRandomWeights();

public:
	FullyConnected(const uint& filterCount);
	void setUpVariables(const std::vector<FilterNet>& filters,
		const uint& count, std::ifstream& weightFile);
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	const std::vector<double>& calculateSums(
		const std::vector<FilterNet>& filters);
	std::pair<std::vector<double>&, std::vector<double>&>
		returnActivations();
	std::vector<std::vector<double>> tryCorrections(
		const std::vector<FilterNet>& filters,
		const std::vector<double>& deltas);
	double getWeight(const uint& in, const uint& out) const;
	void processCorrections(const uint& factor,
		const std::vector<std::vector<double>> &outCorrections,
		const std::vector<double>& deltas);
};

#endif // FULLYCONNECTED_HPP
