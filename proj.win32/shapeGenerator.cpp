#include "../proj.win32/main.h"
#include "shapeGenerator.h"

using namespace Tetris;

ShapeGenerator::ShapeGenerator()
{
	_randomEngine = std::default_random_engine(_randomDevice());

	_nextShapeType = GenerateShape();
}

ShapeType ShapeGenerator::GenerateShape()
{
	size_t numberOfTypes = static_cast<int>(ShapeType::typeCount);

	std::uniform_int_distribution<size_t> distribution(0, numberOfTypes - 1);
	size_t id = distribution(_randomEngine);
	
	ShapeType shapeType = static_cast<ShapeType>(id);
	
	return shapeType;
}

ShapeType ShapeGenerator::NewShape()
{
	ShapeType shapeType = _nextShapeType;

	_nextShapeType = GenerateShape();

	return shapeType;
}
