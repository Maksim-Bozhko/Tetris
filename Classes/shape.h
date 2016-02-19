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

	class Shape : public IDrawable
	{
	private:
		//TODO: make separate class for transformation
		vec2d_unsignedChar _matrixRepresentation;
		unsigned int _boxSize;//actual smallest possible square box where block fits
		static const unsigned int _matrixSize = 4;//all shapes are represented inside 4x4 boxes
		Point _matrixPosition;
		ShapeType _shapeType;
		//cocos2d::Color4F _color;
		Color _color;
	public:
		//TODO: move this to private
		bool _hasLanded;//to know if shape landed

		Shape();
		Shape(ShapeType shapeType);
		void SetShape(ShapeType shapeType);//TODO:move this to constructor
		ShapeType GetShape() const;
		void SetPosition(const Point& newPosition);
		unsigned int GetBoxSize() const { return _boxSize; };
		unsigned int GetMatrixSize() const { return _matrixSize; };
		Point GetMatrixPosition() const { return _matrixPosition; };
		unsigned char GetValueAt(const Point& position) const
		{
			return _matrixRepresentation[position.y][position.x];
		};
		bool RotateClocklWise(Map& map);
		void Draw(vec2d_tetris_color& buffer);
		bool Move(const Point& direction, Map& map);
		bool CheckForCollision(vec2d_unsignedChar& newMatrix, const Point& newPosition, Map& map);
		bool TryToRotate(vec2d_unsignedChar& newMatrix, Point& newPosition, Map& map);
		//void Update(std::chrono::time_point<std::chrono::system_clock>& previousTime);
		void LandShape(Map& map);
	};
};
