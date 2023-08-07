#include <iostream>

#include "Field.h"
#include "SapperLogic.h"

#define HEIGHT 12
#define WIDTH 12

void FrameRendering(Field* field, bool isGameOver)
{
	std::cout << "  ";
	for (int i = 0; i < field->GetWidth(); i++)
	{
		char num;

		if (i < 10)
			num = 48 + i;
		else
			num = 65 + (i - 10);

		std::cout << num << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < field->GetHeight(); i++)
	{
		char num;

		if (i < 10)
			num = 48 + i;
		else
			num = 65 + (i - 10);

		std::cout << num << " ";

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
	SapperLogic sapper(HEIGHT, WIDTH, 500);
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