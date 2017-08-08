#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP

class FilterNet;

class HiddenNeuron
{
private:
	std::vector<uint> connections;
	double weight;
	double bias;
	double sum;
	std::pair<double, double> activation;
public:
	HiddenNeuron();
	void addConnection(const uint& number);
	void setWeight(const double& weightIn);
	double getWeight() const;
	void setBias(const double& biasIn);
	double getBias() const;
	double sumInputs(const ChessInput& in);
	double sumSecondLayer(FilterNet* fn);
	std::pair<double, double> setActivation();

};

#endif // LEVELONENEURON_HPP
