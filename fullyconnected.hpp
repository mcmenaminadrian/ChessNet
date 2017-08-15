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
	FullyConnected();
	void setUpVariables(const std::vector<FilterNet>& filters,
		const uint& count, std::ifstream& weightFile);
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	const std::vector<double>& calculateSums(
		const std::vector<FilterNet>& filters);
	std::pair<std::vector<double>&, std::vector<double>&>
		returnActivations();
	std::vector<double> errGrads(const std::vector<FilterNet>& filters,
		const double& error, const double& deriv,
		const uint& index) const;
	void tryCorrections(const double &factor,
		const std::vector<std::vector<double>> &gradients);
};

#endif // FULLYCONNECTED_HPP
