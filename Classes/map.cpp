#include "../proj.win32/main.h"
#include "map.h"

using namespace Tetris;

//TODO: deal with borders

Map::Map()
{
	_map.resize(_height);
	for (auto& it : _map)
	{
		it.resize(_width);
	}

	_borders.top = 0;
	_borders.left = 0;
	_borders.bottom = _height;
	_borders.right = _width;
}

void Map::Init()
{
	for (auto& it : _map)
	{
		it.assign(_width, TileType::empty);
	}

	// Place bottom wall
	for (unsigned int x = 0; x < _width; ++x)
	{
		_map[_height - 1][x] = TileType::wall;
	}

	// Places left and right walls
	for (unsigned int y = 0; y < _height; ++y)
	{
		_map[y][0] = TileType::wall;
		_map[y][_width - 1] = TileType::wall;
	}
};

void Map::SetValueAt(const Point& position, TileType tileType)
{
	_map[position.y][position.x] = tileType;
};

void Map::Draw(vec2d_tetris_color& buffer)
{
	TileType tileType = TileType::empty;

	for (unsigned int y = 0; y < _height; ++y)
	{
		for (unsigned int x = 0; x < _width; ++x)
		{
			tileType = _map[y][x];
			
			switch (tileType)
			{
			case TileType::wall:
				buffer[y][x] = Color::white;
				break;
			case TileType::brick:
				buffer[y][x] = Color::gray;
				break;
			case TileType::empty:
				buffer[y][x] = Color::black;
				break;
			}
		}
	}
}

void Map::RemoveRow(size_t row)
{
	for (size_t x = _borderWidth; x < _width - _borderWidth; ++x)
	{
		for (size_t y = row; y > 0; --y)
		{
			_map[y][x] = _map[y - 1][x];
		}
	}
}

const Borders& Tetris::Map::GetBorders() const
{
	return _borders;
}

void Map::CheckForFilledRow()
{
	TileType tileType;
	bool filled = true;

	size_t right = _width - _borderWidth;
	size_t bottom = _height - _borderWidth;
	for (size_t y = _borderWidth; y < bottom; ++y)
	{
		filled = true;
		for (size_t x = _borderWidth; x < right; ++x)
		{
			tileType = _map[y][x];
			if (tileType == TileType::empty)
			{
				filled = false;
				break;
			}
		}
		if (filled)
		{
			RemoveRow(y);
			notify(this, Event::ROW_FILLED);
		}
	}
}
