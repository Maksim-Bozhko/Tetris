#pragma once

#include "../proj.win32/main.h"

#include "map.h"
#include "shape.h"

//TODO: optimize drawing process

namespace MyTetris
{
	class Render
	{
	private:
		const unsigned int _screenWidth = 60;//TODO: make this more obvious , make this width of console, dont draw out of borders
		const unsigned int _screenHeight = 22;
	public:
		void Draw(std::vector<IDrawable*>& objectsToDrow, cocos2d::Layer* layer);
	};
};
