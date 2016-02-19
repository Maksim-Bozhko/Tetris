#pragma once

namespace Tetris

{
	enum class Color
	{
		black = 0,
		white,
		gray,
		cyan,
		blue,
		orange,
		yellow,
		green,
		purple,
		red,
		colorCount,
	};
	
	typedef std::vector< std::vector<Color> > vec2d_tetris_color;
	
	class IDrawable
	{
	private:
		bool _stateChanged;
	public:
		IDrawable() { _stateChanged = false;  }
		virtual void Draw(vec2d_tetris_color& buffer) = 0;
	};
};