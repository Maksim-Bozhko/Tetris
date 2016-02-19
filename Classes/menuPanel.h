#pragma once
#include "IDrowable.h"
#include "shape.h"

//TODO: typedef for complicated types

namespace Tetris
{
	class MenuPanel : public IDrawable, public cocos2d::Node
	{
	private:
		Point _position;
		unsigned int _score;
		Shape _shape;
		const unsigned int _maxWidth = 50;
		unsigned int _width;
		unsigned int _height;
		cocos2d::Label* _scoreLabel;
	public:
		MenuPanel();
		void Draw(vec2d_tetris_color& buffer);
		void IncreaseScore();
		void SetUpcomingShape(ShapeType shapeType);
		void Init(const Map& map, cocos2d::Node& node);
	};
};

//TODO: make xml with objects hierarchy
