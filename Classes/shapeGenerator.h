#pragma once

#include "shape.h"
#include <random>

namespace MyTetris
{
	class ShapeGenerator
	{
	private:
		ShapeType _nextShapeType;//next shape type showing in top right corner
		std::default_random_engine _randomEngine;
		std::random_device _randomDevice;
	public:
		ShapeGenerator();
		ShapeType GetNextShapeType() const { return _nextShapeType; }
		ShapeType GenerateShape();
		ShapeType NewShape();
	};
};
