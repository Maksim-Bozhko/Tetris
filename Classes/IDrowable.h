#pragma once

namespace MyTetris

{
	typedef std::vector< std::vector<cocos2d::Color4F> > vec2d_cocos2d_Color4F;
	
	class IDrawable
	{
	public:
		virtual void Draw(vec2d_cocos2d_Color4F& buffer) = 0;
	};
};