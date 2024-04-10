#include <Gomoku.hpp>

int main(const int ac, const char **av)
{
	if (ac != 1)
	{
		std::cerr << "Usage: ./gomoku" << std::endl;
		return EXIT_FAILURE;
	}
	Gomoku gomoku;
	gomoku.run();

	return EXIT_SUCCESS;
}
