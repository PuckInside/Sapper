#include "SapperLogic.h"

SapperLogic::SapperLogic(int height, int width, int mine_count)
	:mineCount(mine_count), markCount(0), correctMarkCount(0), 
	fistClick(true), gameOver(false)
{
	field = new Field(height, width);
	srand(time(NULL));
}

SapperLogic::~SapperLogic()
{
	delete field;
}

char SapperLogic::GetCellState(int x, int y)
{
	if (field->GetShowState(x, y) != OPEN) // Скрывает не открытые ячейки
		return SYMBOL_NOT_OPEN;

	if (field->GetMineState(x, y) != MINE) // Показывает открытые ячейки 
		return SYMBOL_ZERO + field->GetNearbyMinesCount(x, y);
	
	return SYMBOL_MINE;
}

int SapperLogic::GetNearbyMines(int x, int y)
{
	int nearby_mines = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int _x = x + i;
			int _y = y + j;

			if (x == i && y == j)
				continue;

			if (_x >= field->GetHeight() || _x < 0) //Фильтр от ложных записей
				continue;
			if (_y >= field->GetWidth() || _y < 0) //Фильтр от ложных записей
				continue;

			if (field->GetMineState(_x, _y) == MINE)
				nearby_mines++;
		}
	}

	return nearby_mines;
}

void SapperLogic::OnFirstClick(int x, int y)
{
	SetRandomMine(x, y);
	fistClick = false;

	for (int i = 0; i < field->GetHeight(); i++)
	{
		for (int j = 0; j < field->GetWidth(); j++)
		{
			int count = GetNearbyMines(i, j);

			field->SetNearbyMinesCount(i, j, count);
		}
	}
}

void SapperLogic::SetRandomMine(int ingore_x, int ingore_y)
{
	while (field->GetMineCount() <= mineCount)
	{
		bool skip = false;
		int x = rand() % field->GetHeight();
		int y = rand() % field->GetWidth();

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (x == (ingore_x + i) && y == (ingore_y + j)) // Защита первого клика от мин
					skip = SKIP;
			}
		}

		if (field->GetMineState(x, y) == MINE)
			skip = SKIP;

		if (skip != SKIP) // Ставит мину на пустую ячейку
			field->SetMineState(x, y, MINE);
	}
}

void SapperLogic::OnChosenCell(int x, int y)
{
	if (fistClick)
		OnFirstClick(x, y);

	if (field->GetMineState(x, y) == MINE) // БАБАХ!!!
		gameOver = END_OF_GAME;

	for (int i = -1; i <= 1; i++) // надо потом в отдельную функцию запилить
	{
		for (int j = -1; j <= 1; j++)
		{
			int m_x = x + i;
			int m_y = y + j;

			if (field->GetMineState(m_x, m_y) == MINE)
				continue;

			field->SetShowState(m_x, m_y, OPEN);
		}
	}
}
