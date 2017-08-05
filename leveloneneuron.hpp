#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP


class LevelOneNeuron
{
	std::vector<uint> connections;
	double weight;
	double bias;
public:
	LevelOneNeuron();
	void addConnection(const uint& number);
	void setWeight(const double& weightIn);
	double getWeight() const;
	void setBias(const double& biasIn);
	double getBias() const;

};

#endif // LEVELONENEURON_HPP
