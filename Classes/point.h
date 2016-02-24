#pragma once

namespace Tetris
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
		Point& operator*=(const int& rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		static const Point UP;
		static const Point DOWN;
		static const Point LEFT;
		static const Point RIGHT;
	};

	inline Point operator+(Point lhs, const Point& rhs)
	{
		lhs += rhs;
		return lhs;
	}
	inline Point operator*(Point lhs, const int& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	inline bool operator==(const Point& lhs, const Point& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};



