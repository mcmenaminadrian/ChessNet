#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP


class FullyConnected
{
private:
	std::vector<std::vector<double> > weights;
	std::vector<double> sums;
	std::vector<double> activations;
	uint multiply;
	uint secondFilterSize;
	uint secondLayerNodeCount;
	uint classesToMatch;
	void assignRandomWeights();

public:
	FullyConnected();
	void setUpVariables(const std::vector<FilterNet>& filters,
		const uint& outputClasses);
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
	const std::vector<double>& calculateSums(
		const std::vector<FilterNet>& filters);

};

#endif // FULLYCONNECTED_HPP
