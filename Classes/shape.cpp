#include "../proj.win32/main.h"
#include "shape.h"

//TODO: make all more independent of y

using namespace Tetris;

Shape::Shape()
{
	_hasLanded = false;


	_matrixRepresentation.resize(_matrixSize);
	for (auto& it : _matrixRepresentation)
	{
		it.resize(_matrixSize);
	}
}

Shape::Shape(Map* map, ShapeType shapeType)
{
	_shapeType = shapeType;
	_hasLanded = false;

	addObserver(map);

	//initialize 2d array with 0
	_matrixRepresentation.resize(_matrixSize);
	for (auto& it : _matrixRepresentation)
	{
		it.resize(_matrixSize);
		it.assign(_matrixSize, 0);
	}

	_boxSize = 3;//most of shapes fit in box of size 3x3

	switch (shapeType)
	{//TODO: read this from json, actually move everything I can outside
	case ShapeType::type_I:
		_boxSize = 4;
		_matrixRepresentation[1][0] = 1;// 0 0 0 0
		_matrixRepresentation[1][1] = 1;// 1 1 1 1
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		_matrixRepresentation[1][3] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(0.0f, 0.75f, 0.75f, 1.0f);//cyan
		_color = Color::cyan;
		break;
	case ShapeType::type_J:
		_matrixRepresentation[0][0] = 1;// 1 0 0 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(0.0f, 0.0f, 0.75f, 1.0f);//blue
		_color = Color::blue;
		break;
	case ShapeType::type_L:
		_matrixRepresentation[0][2] = 1;// 0 0 1 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(1.0f, 165 / 255.0f, 0.0f, 1.0f);//orange
		_color = Color::orange;
		break;
	case ShapeType::type_O:
		_boxSize = 4;
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 1 1 0
		_matrixRepresentation[2][1] = 1;// 0 1 1 0
		_matrixRepresentation[2][2] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(0.75f, 0.75f, 0.0f, 1.0f);//yellow
		_color = Color::yellow;
		break;
	case ShapeType::type_S:
		_matrixRepresentation[0][1] = 1;// 0 1 1 0
		_matrixRepresentation[0][2] = 1;// 1 1 0 0
		_matrixRepresentation[1][0] = 1;// 0 0 0 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(0.0f, 0.75f, 0.0f, 1.0f);//green
		_color = Color::green;
		break;
	case ShapeType::type_T:
		_matrixRepresentation[0][1] = 1;// 0 1 0 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(128 / 255.0f, 0.0f, 128 / 255.0f, 1.0f);//purple
		_color = Color::purple;
		break;
	case ShapeType::type_Z:
		_matrixRepresentation[0][0] = 1;// 1 1 0 0
		_matrixRepresentation[0][1] = 1;// 0 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
										//_color = cocos2d::Color4F(0.75f, 0.0f, 0.0f, 1.0f);//red
		_color = Color::red;
		break;
	}
}

void Shape::SetShape(ShapeType shapeType)
{
	_shapeType = shapeType;
	_hasLanded = false;

	//initialize 2d array with 0
	for (auto& it : _matrixRepresentation)
	{
		it.assign(_matrixSize, 0);
	}

	_boxSize = 3;//most of shapes fit in box of size 3x3

	switch (shapeType)
	{//TODO: read this from json, actually move everything I can outside
	case ShapeType::type_I:
		_boxSize = 4;
		_matrixRepresentation[1][0] = 1;// 0 0 0 0
		_matrixRepresentation[1][1] = 1;// 1 1 1 1
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		_matrixRepresentation[1][3] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(0.0f, 0.75f, 0.75f, 1.0f);//cyan
		_color = Color::cyan;
		break;
	case ShapeType::type_J:
		_matrixRepresentation[0][0] = 1;// 1 0 0 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(0.0f, 0.0f, 0.75f, 1.0f);//blue
		_color = Color::blue;
		break;
	case ShapeType::type_L:
		_matrixRepresentation[0][2] = 1;// 0 0 1 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(1.0f, 165 / 255.0f, 0.0f, 1.0f);//orange
		_color = Color::orange;
		break;
	case ShapeType::type_O:
		_boxSize = 4;
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 1 1 0
		_matrixRepresentation[2][1] = 1;// 0 1 1 0
		_matrixRepresentation[2][2] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(0.75f, 0.75f, 0.0f, 1.0f);//yellow
		_color = Color::yellow;
		break;
	case ShapeType::type_S:
		_matrixRepresentation[0][1] = 1;// 0 1 1 0
		_matrixRepresentation[0][2] = 1;// 1 1 0 0
		_matrixRepresentation[1][0] = 1;// 0 0 0 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(0.0f, 0.75f, 0.0f, 1.0f);//green
		_color = Color::green;
		break;
	case ShapeType::type_T:
		_matrixRepresentation[0][1] = 1;// 0 1 0 0
		_matrixRepresentation[1][0] = 1;// 1 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(128 / 255.0f, 0.0f, 128 / 255.0f, 1.0f);//purple
		_color = Color::purple;
		break;
	case ShapeType::type_Z:
		_matrixRepresentation[0][0] = 1;// 1 1 0 0
		_matrixRepresentation[0][1] = 1;// 0 1 1 0
		_matrixRepresentation[1][1] = 1;// 0 0 0 0
		_matrixRepresentation[1][2] = 1;// 0 0 0 0
		//_color = cocos2d::Color4F(0.75f, 0.0f, 0.0f, 1.0f);//red
		_color = Color::red;
		break;
	}
}

ShapeType Shape::GetShape() const
{
	return _shapeType;
}

void Shape::SetPosition(const Point& newPosition)
{
	_matrixPosition = newPosition;
}

bool Shape::RotateClocklWise(Map& map)
{
	bool success = false;//to know if we actually changed state of the game
	if (_hasLanded == false)
	{
		vec2d_unsignedChar newMatrix;
		//create new temporary matrix
		newMatrix.resize(_matrixSize);
		for (auto& it : newMatrix)
		{
			it.resize(_matrixSize);
		}
		//transformaton : rotate counterclockwise
		for (size_t i = 0; i < _boxSize; ++i)
		{
			for (size_t j = 0; j < _boxSize; ++j)
			{
				newMatrix[_boxSize - 1 - j][i] = _matrixRepresentation[i][j];//row becomes column and column becomes row backwards
			}
		}

		Point newPosition = _matrixPosition;//we might need to modify position with wall kicks

		success = TryToRotate(newMatrix, newPosition, map);

		//no collisions detected, so we can modify actual matrix
		if (success)
		{
			_matrixPosition = newPosition;
			for (size_t i = 0; i < _boxSize; ++i)
			{
				for (size_t j = 0; j < _boxSize; ++j)
				{
					_matrixRepresentation[i][j] = newMatrix[i][j];
				}
			}
		}
	}

	return success;
}

void Shape::Draw(vec2d_tetris_color& buffer)
{
	Point position;
	TileType tileType = TileType::empty;

	//place shape into the buffer
	for (unsigned int y = 0; y < _boxSize; ++y)
	{
		for (unsigned int x = 0; x < _boxSize; ++x)
		{
			if (_matrixRepresentation[y][x])
			{
				position.SetXY(x, y);
				position += _matrixPosition;
				//make sure we are not out of borders, so shape can start above the screen
				bool yIsInBorders = (0 <= position.y) && (position.y < buffer.size());

				if (yIsInBorders && (0 <= position.x) && (position.x < buffer[position.y].size()))
				{
					buffer[position.y][position.x] = _color;
				}

			}
			//section for debugging purposes to see box around block
			/*else
			{
			position.SetXY(x, y);
			position += _matrixPosition;
			buffer[position.y][position.x] = 'X';
			}*/
		}
	}
}

bool Shape::Move(const Point& direction, Map& map)
{
	bool collisionHappened = true;
	if (_hasLanded == false)
	{
		Point newPosition = _matrixPosition + direction;
		collisionHappened = CheckForCollision(_matrixRepresentation, newPosition, map);

		if (collisionHappened == false)
		{//no collisions detected, we can modify actual position
			_matrixPosition += direction;
		}
		else if (direction == Point::DOWN)//we are trying to move down but we cant, that means shape landed
		{
			_hasLanded = true;
		}
	}

	return !collisionHappened;
}

bool Shape::CheckForCollision(vec2d_unsignedChar& newMatrix, const Point& newPosition, Map& map)
{
	//TODO: move this to map
	//шейп говорит вот он я тут, не влип ли я во что-то
	bool collisionHappened = false;
	Point position;
	TileType tileType;

	for (size_t i = 0; i < _boxSize; ++i)
	{
		for (size_t j = 0; j < _boxSize; ++j)
		{
			if (newMatrix[i][j])
			{
				position.SetXY(j, i);//j is column number, so j is x
				position += newPosition;
				//make sure we are not out of borders
				bool yIsInBorders = (0 <= position.y) && (position.y < map.GetHeight());
				bool xIsInBorders = (0 <= position.x) && (position.x < map.GetWidth());
				if (yIsInBorders && xIsInBorders)
				{
					tileType = map.GetValueAt(position);
					if (tileType == TileType::wall || tileType == TileType::brick)//block section is inside the wall or other block
					{
						collisionHappened = true;
						break;
					}
				}
			}
		}
	}

	return collisionHappened;
}

bool Shape::TryToRotate(vec2d_unsignedChar& newMatrix, Point& newPosition, Map& map)
{
	//check if rotated matrix collides with anything
	bool collisionHappened = CheckForCollision(newMatrix, _matrixPosition, map);
	if (collisionHappened)//now we need to check if there is any wall kicks avaliable
	{
		//try to move to the left
		newPosition = _matrixPosition + Point::LEFT;
		collisionHappened = CheckForCollision(newMatrix, newPosition, map);//if there is no collision function retruns false and we rotate shape
		if (collisionHappened)//cant wall kick to the left, now lets try to the right
		{
			//try to move to the right
			newPosition = _matrixPosition + Point::RIGHT;
			collisionHappened = CheckForCollision(newMatrix, newPosition, map);
		}

		if (collisionHappened && _boxSize == 4)//I shape might need to move 2 tiles for wall kick
		{
			//try to move to the left 2 tiles
			newPosition = _matrixPosition + Point::LEFT * 2;;
			collisionHappened = CheckForCollision(newMatrix, newPosition, map);
			if (collisionHappened)//cant wall kick to the left, now lets try to the right
			{
				//try to move to the right 2 tiles
				newPosition = _matrixPosition + Point::RIGHT * 2;
				collisionHappened = CheckForCollision(newMatrix, newPosition, map);
			}
		}
	}
	return !collisionHappened;
}

void Shape::LandShape(Map& map)
{
	//place landed brick on the map
	Point position;

	notify(this, Event::SHAPE_LANDED);

	/*for (unsigned int y = 0; y < _boxSize; ++y)
	{
		for (unsigned int x = 0; x < _boxSize; ++x)
		{
			if (_matrixRepresentation[y][x])
			{
				position.SetXY(x, y);
				position += _matrixPosition;
				bool yIsInBorders = (0 <= position.y) && (position.y < map.GetHeight());
				bool xIsInBorders = (0 <= position.x) && (position.x < map.GetWidth());
				if (yIsInBorders && xIsInBorders)
				{
					map.SetValueAt(position, TileType::brick);
				}
			}
		}
	}*/
}

const std::vector<Point>& Tetris::Shape::GetPositions()
{
	Point position;
	_positions.clear();

	for (unsigned int y = 0; y < _boxSize; ++y)
	{
		for (unsigned int x = 0; x < _boxSize; ++x)
		{
			if (_matrixRepresentation[y][x])
			{
				position.SetXY(x, y);
				position += _matrixPosition;
				_positions.push_back(position);
			}
		}
	}

	return _positions;
}

