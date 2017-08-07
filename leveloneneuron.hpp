#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP


class HiddenNeuron
{
private:
	std::vector<uint> connections;
	double weight;
	double bias;
	double sum;
	double activation;
public:
	HiddenNeuron();
	void addConnection(const uint& number);
	void setWeight(const double& weightIn);
	double getWeight() const;
	void setBias(const double& biasIn);
	double getBias() const;
	double sumInputs(const ChessInput& in);
	double setActivation();

};

#endif // LEVELONENEURON_HPP
