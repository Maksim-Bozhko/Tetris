#include "../proj.win32/main.h"
#include "map.h"

using namespace Tetris;

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

const Borders & Tetris::Map::GetBorders() const
{
	return _borders;
}

void Tetris::Map::onNotify(Subject* subject, Event event)
{
	if (event == Event::SHAPE_LANDED)
	{
		std::vector<Point> positions = subject->GetPositions();

		for (auto& position : positions)
		{
			bool yIsInBorders = (0 <= position.y) && (position.y < _height);
			bool xIsInBorders = (0 <= position.x) && (position.x < _width);
			if (yIsInBorders && xIsInBorders)
			{
				SetValueAt(position, TileType::brick);
			}
		}
	}
}
