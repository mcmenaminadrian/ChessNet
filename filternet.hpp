#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	double weight; //single weight per filter
	std::vector<HiddenNeuron> neurons;
	std::vector<double> topWeights;
	std::vector<HiddenNeuron> secondNeurons;
	std::vector<double> bottomWeights;
	uint netCount;
	uint secondLayerSize;
	uint fieldSize;
	uint calculateSecondLayerSize(const uint& secondSpan,
		const uint& secondField) const;
	void assignRandomWeights(const uint& firstFieldSize,
		const uint& secondFieldSize);
public:
	FilterNet(const uint& height, const uint& width, const int& field,
		const uint& span, ChessInput& inputLayer);
	void assignFilterWeights(const std::vector<double>& weightsTop,
		const std::vector<double>& weightsBottom);
	uint getNetCount() const;
	std::ostream& streamOutWeights(std::ostream& os) const;
	std::istream& streamInWeights(std::istream& is);
};

#endif // FILTERNET_HPP
