#ifndef CHESSINPUT_HPP
#define CHESSINPUT_HPP


class ChessInput
{

private:
	std::vector<std::vector<double> > inputRows;
public:
	ChessInput(const uint& width, const uint& height);
};
#endif // CHESSINPUT_HPP
