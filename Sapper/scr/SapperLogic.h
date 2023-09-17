#pragma once

#include <time.h>
#include <stdlib.h>

#include "Field.h"

#define OPEN true
#define MINE true
#define SKIP true
#define END_OF_GAME true

#define DENSITY 5

class SapperLogic
{
private:
	Field* field;
	
	bool gameOver;
	bool fistClick;

	int mineCount;

public:
	SapperLogic(int height, int width, int mine_count);
	~SapperLogic();

	inline bool GetGameState() const { return gameOver; }
	inline int GetMineCount() const { return mineCount; }

	inline Field* GetField() { return field; }

	void OnChosenCell(int x, int y);

private:
	void OnFirstClick(int x, int y);
	void SpawnRandomMine(int ignore_x, int ignore_y);

	int GetNearbyMines(int x, int y);

	void SetMineCount(int mine_count, int height, int width);
	void SetMarkCount(int count);
};

