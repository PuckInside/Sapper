#include <iostream>

#include "Field.h"
#include "SapperLogic.h"

#define HEIGHT 12 * 2
#define WIDTH 12 * 3

int main()
{
	SapperLogic sapper(HEIGHT, WIDTH, 150);

	while (!sapper.GetGameState()) // Game rendering
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				char cell_state = sapper.GetCellState(i, j);

				std::cout << cell_state << " ";
			}

			std::cout << std::endl;
		}

		int x = 0;
		int y = 0;

		std::cin >> x;
		std::cin >> y;

		sapper.OnChosenCell(x, y);
	}

	for (int i = 0; i < HEIGHT; i++) // Shows the field after the end of the game
	{
		for (int j = 0; j < WIDTH; j++)
		{
			char cell_state = sapper.GetCellState(i, j);

			std::cout << cell_state << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;

	setlocale(LC_ALL, "rus");
	std::cout << "Конец игры!" << std::endl;
}