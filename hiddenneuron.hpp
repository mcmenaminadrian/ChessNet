#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP

class FilterNet;

class HiddenNeuron
{
private:
	std::vector<uint> connections;
	std::pair<double, double> activation;
	const uint fieldSize;
	FilterNet *ptrFN;
public:
	HiddenNeuron(const uint& field, FilterNet* FN);
	void addConnection(const uint& number);
	std::pair<double, double> setActivation(const double& sum);
	const std::vector<uint>& getConnections() const { return connections;}
};

#endif // LEVELONENEURON_HPP
