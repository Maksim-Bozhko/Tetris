#pragma once
#include "IDrowable.h"
#include "shape.h"

//TODO: typedef for complicated types
//TODO: draw static objects 1 time, draw changing objects on update

namespace Tetris
{
	class MenuPanel : public IDrawable, public Observer
	{
	private:
		Point _position;
		unsigned int _score;
		Shape _upcomingShape;
		unsigned int _width;
		unsigned int _height;
		cocos2d::Label* _scoreLabel;

		void IncreaseScore();
	public:
		MenuPanel();
		~MenuPanel();
		void Draw(vec2d_tetris_color& buffer);
		void SetUpcomingShape(ShapeType shapeType);
		void Init(const Map& map, cocos2d::Node& node);
		void onNotify(Subject* subject, Event event);
	};
};

//TODO: make xml with objects hierarchy
