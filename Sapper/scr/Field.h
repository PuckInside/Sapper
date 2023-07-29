#pragma once

struct Cell
{
	bool isMine = false;
	bool isShowed = false;
	int nearbyMines = 0;
};

class Field
{
private:
	Cell** fieldArray;
	int width;
	int height;
	int mineCount;

public:
	Field(int x, int y);
	~Field();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetMineCount() const { return mineCount; }

	int GetNearbyMinesCount(int x, int y);
	bool GetMineState(int x, int y);
	bool GetShowState(int x, int y);

	void SetMineState(int x, int y, bool state);
	void SetShowState(int x, int y, bool state);
	void SetNearbyMinesCount(int x, int y, int count);

	void Clear();

private:
	int CheckX(int x);
	int CheckY(int y);
};

