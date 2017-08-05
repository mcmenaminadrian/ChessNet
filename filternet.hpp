#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	double weight; //single weight per filter
	std::vector<LevelOneNeuron> neurons;
	uint netCount;
	uint fieldSize;
public:
	FilterNet(const uint& height, const uint& width, const int& field,
		const uint& span, ChessInput& inputLayer);
	void assignFilterWeights(const std::vector<double>& weights);

};

#endif // FILTERNET_HPP
