#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP

class FilterNet;

class HiddenNeuron
{
private:
	std::vector<uint> connections;
	std::pair<double, double> activation;

public:
	HiddenNeuron();
	void addConnection(const uint& number);
	std::pair<double, double> setActivation(const double& sum);
	const std::vector<uint>& getConnections() const { return connections;}
	const std::pair<double, double> getActivation() const;
};

#endif // LEVELONENEURON_HPP
