#include "Field.h"

Field::Field(int x, int y)
	:height(x), width(y), mineCount(0)
{
	fieldArray = new Cell* [height];
	for (int i = 0; i < height; ++i) 
	{
		fieldArray[i] = new Cell[width];
	}
}

Field::~Field()
{
	for (int i = 0; i < height; ++i) 
	{
		delete[] fieldArray[i];
	}
	delete[] fieldArray;
}

int Field::GetNearbyMinesCount(int x, int y)
{
	x = CheckX(x);
	y = CheckY(y);

	int count = fieldArray[x][y].nearbyMines;
	return count;
}

bool Field::GetMineState(int x, int y)
{
	x = CheckX(x);
	y = CheckY(y);

	bool state = fieldArray[x][y].isMine;
	return state;
}

bool Field::GetShowState(int x, int y)
{
	x = CheckX(x);
	y = CheckY(y);

	bool state = fieldArray[x][y].isShowed;
	return state;
}

char Field::GetCellState(int x, int y)
{
	if (GetShowState(x, y) != OPEN) // Hides unopened cells
		return SYMBOL_NOT_OPEN;

	if (GetMineState(x, y) != MINE) // Shows open cells
		return SYMBOL_ZERO + GetNearbyMinesCount(x, y);

	return SYMBOL_MINE;
}

void Field::SetMineState(int x, int y, bool state)
{
	x = CheckX(x);
	y = CheckY(y);

	fieldArray[x][y].isMine = state;
	mineCount++;
}

void Field::SetShowState(int x, int y, bool state)
{
	x = CheckX(x);
	y = CheckY(y);

	fieldArray[x][y].isShowed = state;
}

void Field::SetNearbyMinesCount(int x, int y, int count)
{
	x = CheckX(x);
	y = CheckY(y);

	fieldArray[x][y].nearbyMines = count;
}

void Field::Clear()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fieldArray[i][j].isMine = false;
			fieldArray[i][j].isShowed = false;
			fieldArray[i][j].nearbyMines = 0;
		}
	}
}

int Field::CheckX(int x)
{
	if (x >= height)
		x = height - 1;
	if (x < 0)
		x = 0;

	return x;
}

int Field::CheckY(int y)
{
	if (y >= width)
		y = width - 1;
	if (y < 0)
		y = 0;

	return y;
}

