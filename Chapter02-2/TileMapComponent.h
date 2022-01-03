#pragma once

#include <vector>

#include "SpriteComponent.h"

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 100);
		
	void ImportMap(const char* csvFile, int rowCount, int colCount);
	void SetTileSetInfo(int rowCount, int colCount);
	void Draw(SDL_Renderer* renderer) override;

protected:	
	std::vector<int> mMapCells;
	int mMapRowCount;
	int mMapColCount;
	int mTileSetRowCount;
	int mTileSetColCount;
};

