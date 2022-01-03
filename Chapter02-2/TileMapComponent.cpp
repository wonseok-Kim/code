#include <fstream>
#include <sstream>
#include <string>

#include "TileMapComponent.h"

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
{
	
}

void TileMapComponent::ImportMap(const char* csvFile, int rowCount, int colCount)
{
	mMapRowCount = rowCount;
	mMapColCount = colCount;

	mMapCells.clear();
	mMapCells.reserve(mMapRowCount * mMapColCount);

	std::ifstream in(csvFile);	
	std::string line;
	
	while (std::getline(in, line))
	{
		std::stringstream ss(line);
		int value;

		while (ss >> value) {
			mMapCells.emplace_back(value);
			if (ss.peek() == ',')
				ss.ignore();
		}
	}
}

void TileMapComponent::SetTileSetInfo(int rowCount, int colCount)
{
	mTileSetRowCount = rowCount;
	mTileSetColCount = colCount;
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		for (int count = 0; count < mMapCells.size(); ++count)
		{
			if (mMapCells[count] == -1)
				continue;

			int mapRow = count / mMapColCount;
			int mapCol = count % mMapColCount;

			int tileRow = mMapCells[count] / mTileSetColCount;
			int tileCol = mMapCells[count] % mTileSetColCount;
			
			SDL_Rect srcRect;
			srcRect.w = 32;
			srcRect.h = 32;
			srcRect.x = 32 * tileCol;
			srcRect.y = 32 * tileRow;

			SDL_Rect dstRect;
			dstRect.w = 32;
			dstRect.h = 32;
			dstRect.x = 32 * mapCol;
			dstRect.y = 32 * mapRow;

			SDL_RenderCopyEx(
				renderer,
				mTexture,
				&srcRect,
				&dstRect,
				0,
				nullptr,
				SDL_FLIP_NONE
			);
		}
	}
}
