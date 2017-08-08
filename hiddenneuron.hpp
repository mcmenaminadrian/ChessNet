#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP

class FilterNet;

class HiddenNeuron
{
private:
	std::vector<uint> connections;
	double weight;
	double sum;
	std::pair<double, double> activation;
	double filterBias;
public:
	HiddenNeuron();
	void addConnection(const uint& number);
	void setWeight(const double& weightIn);
	double getWeight() const;
	double sumInputs(const ChessInput& in);
	double sumSecondLayer(FilterNet* fn);
	std::pair<double, double> setActivation();
	void setFilterBias(const double& fB){filterBias = fB;}

};

#endif // LEVELONENEURON_HPP
