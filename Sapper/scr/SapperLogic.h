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

	inline bool GetGameState() const { return gameOver; }
	inline int GetMineCount() const { return mineCount; }
	inline int GetMarkCount() const { return mineCount - markCount; }

	inline Field* GetField() { return field; }

	void OnChosenCell(int x, int y);

private:
	void OnFirstClick(int x, int y);
	void SpawnRandomMine(int ignore_x, int ignore_y);

	int GetNearbyMines(int x, int y);
};

