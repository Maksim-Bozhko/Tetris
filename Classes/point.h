#pragma once

namespace MyTetris
{
	struct Point
	{
		int x;
		int y;

		Point() : x(0), y(0) {};
		Point(int newX, int newY) : x(newX), y(newY) {};
		void SetXY(unsigned int newX, unsigned int newY)
		{
			x = newX;
			y = newY;
		};
		Point& operator+=(const Point& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		bool operator==(const Point& rhs)
		{
			return x == rhs.x && y == rhs.y;
		}
	};

	inline Point operator+(Point lhs, const Point& rhs)
	{
		lhs += rhs;
		return lhs;
	}
};



