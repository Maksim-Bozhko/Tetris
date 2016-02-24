#pragma once

#include "IDrowable.h"
#include "map.h"

//TODO: уменьшить связность карты и формы
//TODO: проверить механизм посадки на баги
//TODO: сделать механизм посадки проще и очевиднее

namespace Tetris
{

	typedef std::vector< std::vector<unsigned char> > vec2d_unsignedChar;
	
	enum class ShapeType
	{
		type_I = 0,
		type_J,
		type_L,
		type_O,
		type_S,
		type_T,
		type_Z,
		typeCount,
	};

	class Shape : public IDrawable, public Subject
	{
	private:
		//TODO: make separate class for transformation
		vec2d_unsignedChar _matrixRepresentation;
		unsigned int _boxSize;//actual smallest possible square box where block fits
		static const unsigned int _matrixSize = 4;//all shapes are represented inside 4x4 boxes
		Point _matrixPosition;
		ShapeType _shapeType;
		Color _color;

		bool _hasLanded;//to know if shape landed

		bool CheckForCollision(vec2d_unsignedChar& newMatrix, const Point& newPosition, Map& map);
		bool TryToRotate(vec2d_unsignedChar& newMatrix, Point& newPosition, Map& map);
	public:
		bool hasLanded() const { return _hasLanded; };

		Shape();
		void SetShape(ShapeType shapeType);//TODO:move this to constructor
		void SetPosition(const Point& newPosition);
		unsigned int GetMatrixSize() const { return _matrixSize; };
		bool RotateCounterClocklwise(Map& map);//TODO:rotate both directions, direction as argument
		void Draw(vec2d_tetris_color& buffer);
		bool Move(const Point& direction, Map& map);
		
		void LandShape(Map& map);
	};
};
