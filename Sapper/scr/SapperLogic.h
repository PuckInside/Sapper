#pragma once

#include <time.h>
#include <stdlib.h>

#include "Field.h"

#define OPEN true
#define MINE true
#define SKIP true
#define END_OF_GAME true

#define SYMBOL_NOT_OPEN 35
#define SYMBOL_MINE 64
#define SYMBOL_ZERO 48

class SapperLogic
{
private:
	Field* field;
	
	bool gameOver;
	bool fistClick;

	int mineCount;
	int markCount;
	int correctMarkCount;

public:
	SapperLogic(int height, int width, int mine_count);
	~SapperLogic();

	bool GetGameState() const { return gameOver; }
	int GetMineCount() const { return mineCount; }
	int GetMarkCount() const { return mineCount - markCount; }

	char GetCellState(int x, int y);
	void OnChosenCell(int x, int y);

private:
	void OnFirstClick(int x, int y);
	void SetRandomMine(int ignore_x, int ignore_y);

	int GetNearbyMines(int x, int y);
};

