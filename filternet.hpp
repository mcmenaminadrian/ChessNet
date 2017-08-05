#ifndef FILTERNET_HPP
#define FILTERNET_HPP


class FilterNet
{
private:
	double weight; //single weight per filter
	std::vector<LevelOneNeuron> neurons;
public:
	FilterNet(const uint& height, const uint& width, const int& field,
		const uint& span, ChessInput& inputLayer);

};

#endif // FILTERNET_HPP
