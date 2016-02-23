#pragma once

#include "IDrowable.h"
#include "observer.h"

//TODO:: шейп может зацепиться за верхний угол, исправить

namespace Tetris
{	
	enum class TileType
	{
		empty,
		wall,
		shape,
		brick,
	};

	struct Borders
	{
		unsigned int top;
		unsigned int left;
		unsigned int bottom;
		unsigned int right;
		Borders() 
		{
			top = 0;
			left = 0;
			bottom = 0;
			right = 0;
		}
	};

	class Map : public IDrawable, public Observer, public Subject
	{
	private:
		static const unsigned int _width = 12;
		static const unsigned int _height = 22;
		std::vector< std::vector<TileType> > _map;
		const unsigned int _borderWidth = 1;

		Borders _borders;
	public:
		Map();
		unsigned int GetWidth() const { return _width; }; //TODO: make this more private
		unsigned int GetHeight() const { return _height; };
		unsigned int GetBorderWidth() const { return _borderWidth; };

		TileType GetValueAt(const Point& position) const
		{
			return _map[position.y][position.x];
		};

		void SetValueAt(const Point& position, TileType tileType);//this is bad, noone should be able to set value from outside

		void Init();//move this to constructor

		void Draw(vec2d_tetris_color& buffer);
		void RemoveRow(size_t row);

		const Borders& GetBorders() const;

		virtual void onNotify(Subject* subject, Event event);
		void CheckForFilledRow();
	};
};
