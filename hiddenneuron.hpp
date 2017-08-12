#ifndef LEVELONENEURON_HPP
#define LEVELONENEURON_HPP

class FilterNet;

class HiddenNeuron
{
private:
	std::vector<uint> connections;
	double sum;
	std::pair<double, double> activation;
	const uint fieldSize;
	FilterNet *ptrFN;
public:
	HiddenNeuron(const uint& field, FilterNet* FN);
	void addConnection(const uint& number);
	double sumInputs(const ChessInput& in);
	double sumSecondLayer();
	std::pair<double, double> setActivation();
};

#endif // LEVELONENEURON_HPP
