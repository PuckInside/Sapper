#include <iostream>

#include "Field.h"
#include "SapperLogic.h"

#define HEIGHT 8
#define WIDTH 8

bool InputHandler(SapperLogic& sapper)
{
	std::string input;
	std::cin >> input;

	if (input.size() != 3)
	{
		std::cout << "Ошибка ввода!" << std::endl;
		return false;
	}

	if (input[0] != 'c')
	{
		std::cout << "Неправильная команда!" << std::endl;
		return false;
	}

	if (input[1] <= 48 || input[1] >= 57)
	{
		std::cout << "Неравильные число строки!" << std::endl;
		return false;
	}

	if (input[2] <= 48 || input[2] >= 57)
	{
		std::cout << "Неравильные число столбца!" << std::endl;
		return false;
	}

	int x = input[1] - 49;
	int y = input[2] - 49;

	if (input[0] == 'c')
		sapper.OnChosenCell(x, y);

	return true;
}

void FrameRendering(Field* field, bool isGameOver)
{
	std::cout << "N ";
	for (int i = 0; i < field->GetWidth(); i++)
	{
		char num;

		if (i < 10)
			num = 48 + i;
		else
			num = 65 + (i - 10);

		std::cout << ++num << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < field->GetHeight(); i++)
	{
		char num;

		if (i < 10)
			num = 48 + i;
		else
			num = 65 + (i - 10);

		std::cout << ++num << " ";

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
		std::cout << "Конец игры!" << std::endl;
	}
}

int main()
{
	SapperLogic sapper(HEIGHT, WIDTH, 500);
	FrameRendering(sapper.GetField(), sapper.GetGameState());

	while (!sapper.GetGameState()) // Game rendering
	{
		setlocale(LC_ALL, "rus");

		if (InputHandler(sapper))
			FrameRendering(sapper.GetField(), sapper.GetGameState());
	}
}