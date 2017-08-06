#ifndef CHESSNET_HPP
#define CHESSNET_HPP

class ChessNet
{

private:
	std::vector<FilterNet> filters;

public:
	explicit ChessNet(const uint& width, const uint& height,
		const uint& span, const uint& field, const uint& filters);
};
#endif // CHESSNET_HPP
