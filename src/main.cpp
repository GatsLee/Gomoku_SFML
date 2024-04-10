#include <Gomoku.hpp>

int main(const int ac, const char **av)
{
	if (ac != 1)
	{
		std::cerr << "Usage: ./gomoku" << std::endl;
		return 1;
	}
	try
	{
		Gomoku gomoku;
		gomoku.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
