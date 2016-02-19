#pragma once

#include "IDrowable.h"

namespace Tetris
{
	enum class TileType
	{
		empty,
		wall,
		shape,
		brick,
	};
	
	class Map : public IDrawable
	{
	private:
		static const unsigned int _width = 12;
		static const unsigned int _height = 22;
		std::vector< std::vector<TileType> > _map;
		unsigned int _score;
		const unsigned int _borderWidth = 1;

	public:
		Map();
		unsigned int GetWidth() const { return _width; }; //TODO: make this more private
		unsigned int GetHeight() const { return _height; };
		unsigned int GetBorderWidth() const { return _borderWidth; };

		TileType GetValueAt(const Point& position) const
		{
			return _map[position.y][position.x];
		};

		void SetValueAt(const Point& position, TileType tileType);

		void Init();//move this to constructor

		void Draw(vec2d_tetris_color& buffer);
		void RemoveRow(size_t row);
	};
};
