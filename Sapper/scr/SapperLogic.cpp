#include "SapperLogic.h"

SapperLogic::SapperLogic(int height, int width, int mine_count)
	:fistClick(true), gameOver(false)
{
	field = new Field(height, width);
	srand(time(NULL));

	SetMineCount(mine_count, height, width);
}

SapperLogic::~SapperLogic()
{
	delete field;
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

			if (_x >= field->GetHeight() || _x < 0) //Filter against false entries
				continue;
			if (_y >= field->GetWidth() || _y < 0) //Filter against false entries
				continue;

			if (field->GetMineState(_x, _y) == MINE)
				nearby_mines++;
		}
	}

	return nearby_mines;
}

void SapperLogic::SetMineCount(int mine_count, int height, int width)
{
	int allowableMineCount = (height * width) / DENSITY; 

	if (mine_count > allowableMineCount)
		mineCount = allowableMineCount;
	else
		mineCount = mine_count;
}

void SapperLogic::OnFirstClick(int x, int y)
{
	SpawnRandomMine(x, y);
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

void SapperLogic::SpawnRandomMine(int ignore_x, int ignore_y)
{
	while (field->GetMineCount() <= mineCount)
	{
		bool isSkip = false;
		int x = rand() % field->GetHeight();
		int y = rand() % field->GetWidth();

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (x == (ignore_x + i) && y == (ignore_y + j)) // First click protection against mines
					isSkip = SKIP;
			}
		}

		if (field->GetMineState(x, y) == MINE)
			isSkip = SKIP;

		if (isSkip != SKIP) // Places a mine on an empty cell
			field->SetMineState(x, y, MINE);
	}
}

void SapperLogic::OnChosenCell(int x, int y)
{
	if (fistClick)
		OnFirstClick(x, y);

	if (field->GetMineState(x, y) == MINE) // BOOM!!!
		gameOver = END_OF_GAME;

	for (int i = -1; i <= 1; i++) // then you need to write it into a separate function
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
