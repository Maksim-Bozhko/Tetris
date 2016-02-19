//#ifndef __HELLOWORLD_SCENE_H__
//#define __HELLOWORLD_SCENE_H__
#pragma once

#include "cocos2d.h"
#include "gameController.h"

class TetrisScene : public cocos2d::Layer
{
private:
	Tetris::GameController _gameController;

	const unsigned int _screenWidth = 20;//TODO: make this more obvious
	const unsigned int _screenHeight = 22;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float delta) override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TetrisScene);

	void Draw(std::vector<Tetris::IDrawable*>& objectsToDrow);

	bool _stateChanged;

	cocos2d::Color4F GetEngineColorFromTetrisColor(const Tetris::Color color);
};

//#endif // __HELLOWORLD_SCENE_H__
