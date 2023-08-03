#include <iostream>

#include "Field.h"
#include "SapperLogic.h"

#define HEIGHT 12 * 2
#define WIDTH 12 * 3

void FrameRendering(Field* field, bool isGameOver)
{
	for (int i = 0; i < field->GetHeight(); i++)
	{
		for (int j = 0; j < field->GetWidth(); j++)
		{
			char cell_state = field->GetCellState(i, j);

			std::cout << cell_state << " ";
		}

		std::cout << std::endl;
	}

	if (isGameOver)
	{
		std::cout << std::endl;
		setlocale(LC_ALL, "rus");
		std::cout << "Конец игры!" << std::endl;
	}
}

int main()
{
	SapperLogic sapper(HEIGHT, WIDTH, 150);
	FrameRendering(sapper.GetField(), sapper.GetGameState());

	while (!sapper.GetGameState()) // Game rendering
	{
		int x = 0;
		int y = 0;

		std::cin >> x;
		std::cin >> y;

		sapper.OnChosenCell(x, y);
		FrameRendering(sapper.GetField(), sapper.GetGameState());
	}
}