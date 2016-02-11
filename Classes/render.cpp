#include "../proj.win32/main.h"
#include "render.h"

using namespace MyTetris;

void Render::Draw(std::vector<IDrawable*>& objectsToDrow, cocos2d::Layer* layer)
{
	//make empty buffer
	vec2d_cocos2d_Color4F buffer;
	buffer.resize(_screenHeight);
	for (size_t j = 0; j < buffer.size(); ++j)
	{
		buffer[j].resize(_screenWidth);
		buffer[j].assign(_screenWidth, cocos2d::Color4F::BLACK);
	}

	for (auto& it : objectsToDrow)
	{
		it->Draw(buffer);
	}

	//draw buffer on screen
	int blockSize = 20;
	cocos2d::DrawNode* rectNode;
	cocos2d::Vec2 rectangle[4];
	cocos2d::Vec2 position;
	cocos2d::Color4F color;

	auto blocksNode = layer->getChildByName("blocksNode");
	blocksNode->removeAllChildren();
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		for (size_t j = 0; j < buffer[i].size(); ++j)
		{
			color = buffer[buffer.size() - 1 - i][j];
			if (color != cocos2d::Color4F::BLACK)
			{
				position = cocos2d::Vec2(j*(blockSize + 4) + 10, i*(blockSize + 4) + 10);//10 is offset
				rectangle[0] = cocos2d::Vec2(position.x, position.y);
				rectangle[1] = cocos2d::Vec2(position.x + blockSize, position.y);
				rectangle[2] = cocos2d::Vec2(position.x + blockSize, position.y + blockSize);
				rectangle[3] = cocos2d::Vec2(position.x, position.y + blockSize);
				rectNode = cocos2d::DrawNode::create();
				if (color == cocos2d::Color4F::WHITE)
				{
					rectNode->drawPolygon(rectangle, 4, cocos2d::Color4F::GRAY, 2, color);
				}
				else
				{ 
					rectNode->drawPolygon(rectangle, 4, cocos2d::Color4F::BLACK, 2, color);
				}
				blocksNode->addChild(rectNode);
			}
		}
	}
};
