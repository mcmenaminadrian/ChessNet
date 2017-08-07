#ifndef CHESSINPUT_HPP
#define CHESSINPUT_HPP


class ChessInput
{

private:
	std::vector<std::vector<double> > inputRows;
	const uint rowLength;
public:
	ChessInput(const uint& width, const uint& height);
	const double& getInput(const uint& index) const;
	void setInput(const QImage& imgIn);
};
#endif // CHESSINPUT_HPP
