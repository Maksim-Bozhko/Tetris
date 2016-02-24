#include "TetrisScene.h"

#include "../proj.win32/main.h"

//TODO:решить проблему, сцене нужен объект чтобы рисовать его, геймконтроллер нужен объект чтобы управлять его логикой 

USING_NS_CC;

void TetrisScene::Draw(std::vector<Tetris::IDrawable*>& objectsToDrow)
{
	//make empty buffer
	Tetris::vec2d_tetris_color buffer;
	buffer.resize(_screenHeight);
	for (size_t j = 0; j < buffer.size(); ++j)
	{
		buffer[j].resize(_screenWidth);
		buffer[j].assign(_screenWidth, Tetris::Color::black);
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
	cocos2d::Color4F engineColor;
	Tetris::Color tetrisColor;

	auto blocksNode = this->getChildByName("blocksNode");
	blocksNode->removeAllChildren();

	for (size_t i = 0; i < buffer.size(); ++i)
	{
		for (size_t j = 0; j < buffer[i].size(); ++j)
		{
			tetrisColor = buffer[buffer.size() - 1 - i][j];
			engineColor = GetEngineColorFromTetrisColor(tetrisColor);
			if (engineColor != cocos2d::Color4F::BLACK)//TODO: make empty color
			{
				position = cocos2d::Vec2(j*(blockSize + 4) + 10, i*(blockSize + 4) + 10);//10 is offset
				rectangle[0] = cocos2d::Vec2(position.x, position.y);
				rectangle[1] = cocos2d::Vec2(position.x + blockSize, position.y);
				rectangle[2] = cocos2d::Vec2(position.x + blockSize, position.y + blockSize);
				rectangle[3] = cocos2d::Vec2(position.x, position.y + blockSize);
				rectNode = cocos2d::DrawNode::create();
				if (engineColor == cocos2d::Color4F::WHITE)
				{
					rectNode->drawPolygon(rectangle, 4, cocos2d::Color4F::GRAY, 2, engineColor);
					blocksNode->addChild(rectNode);
				}
				else
				{
					rectNode->drawPolygon(rectangle, 4, cocos2d::Color4F::BLACK, 2, engineColor);
					blocksNode->addChild(rectNode);
				}
			}
		}
	}
}
cocos2d::Color4F TetrisScene::GetEngineColorFromTetrisColor(const Tetris::Color color)
{
	cocos2d::Color4F engineColor;

	switch (color)
	{
	case Tetris::Color::black:
		engineColor = cocos2d::Color4F::BLACK;
		break;
	case Tetris::Color::white:
		engineColor = cocos2d::Color4F::WHITE;
		break;
	case Tetris::Color::gray:
		engineColor = cocos2d::Color4F::GRAY;
		break;
	case Tetris::Color::cyan:
		engineColor = cocos2d::Color4F(0.0f, 0.75f, 0.75f, 1.0f);//cyan
		break;
	case Tetris::Color::blue:
		engineColor = cocos2d::Color4F(0.0f, 0.0f, 0.75f, 1.0f);//blue
		break;
	case Tetris::Color::orange:
		engineColor = cocos2d::Color4F(1.0f, 165 / 255.0f, 0.0f, 1.0f);//orange
		break;
	case Tetris::Color::yellow:
		engineColor = cocos2d::Color4F(0.75f, 0.75f, 0.0f, 1.0f);//yellow
		break;
	case Tetris::Color::green:
		engineColor = cocos2d::Color4F(0.0f, 0.75f, 0.0f, 1.0f);//green
		break;
	case Tetris::Color::purple:
		engineColor = cocos2d::Color4F(128 / 255.0f, 0.0f, 128 / 255.0f, 1.0f);//purple
		break;
	case Tetris::Color::red:
		engineColor = cocos2d::Color4F(0.75f, 0.0f, 0.0f, 1.0f);//red
		break;
	}

	return engineColor;
}

Scene* TetrisScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TetrisScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TetrisScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tetrisNode = cocos2d::Node::create();
	tetrisNode->setName("tetrisNode");
	this->addChild(tetrisNode, 0);

	auto blocksNode = cocos2d::Node::create();
	blocksNode->setName("blocksNode");
	this->addChild(blocksNode, 0);

	_gameController.NewGame(*tetrisNode);

	Draw(_gameController.GetObjectsToDraw());

	this->scheduleUpdate();

	return true;
}


void TetrisScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void TetrisScene::update(float delta)
{
	if (_gameController.GameLoop())
	{
		Draw(_gameController.GetObjectsToDraw());
	}
}
