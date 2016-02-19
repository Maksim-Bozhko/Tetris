#include "../proj.win32/main.h"
#include "inputHandler.h"

//TODO:: check if there is two copies of listeners
//TODO: make summary what I have learned

using namespace Tetris;

Tetris::InputHandler::InputHandler()
{
	//_resetCommandAfterSingleExecution = false;
	_stopUntillNextFrame = false;
	_firstExecution = false;
	_currentCommand = nullptr;

	_moveLeft = new MoveLeft;
	_moveRight = new MoveRight;
	_moveDown = new MoveDown;
	_rotate = new Rotate;

	_previousCommandTime = std::chrono::system_clock::now();

	_eventListenerKeyboard = cocos2d::EventListenerKeyboard::create();

	_eventListenerKeyboard->onKeyPressed = CC_CALLBACK_2(InputHandler::onKeyPressed, this);
	_eventListenerKeyboard->onKeyReleased = CC_CALLBACK_2(InputHandler::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListenerKeyboard, this);

	this->resume();

}

InputHandler::InputHandler(Map* map, Shape* shape)
{
	//_resetCommandAfterSingleExecution = false;
	_stopUntillNextFrame = false;
	_firstExecution = false;
	_currentCommand = nullptr;

	_moveLeft = new MoveLeft;
	_moveRight = new MoveRight;
	_moveDown = new MoveDown;
	_rotate = new Rotate;

	_previousCommandTime = std::chrono::system_clock::now();

	_map = map;
	_shape = shape;

	_eventListenerKeyboard = cocos2d::EventListenerKeyboard::create();

	_eventListenerKeyboard->onKeyPressed = CC_CALLBACK_2(InputHandler::onKeyPressed, this);
	_eventListenerKeyboard->onKeyReleased = CC_CALLBACK_2(InputHandler::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListenerKeyboard, this);

	this->resume();
}

InputHandler::~InputHandler()
{
	delete _moveLeft;
	delete _moveRight;
	delete _moveDown;
	delete _rotate;
}

void InputHandler::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		_currentCommand = _rotate;
		//_resetCommandAfterSingleExecution = true;
		_firstExecution = true;
		_lastKeyPressed = keyCode;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_currentCommand = _moveDown;
		_firstExecution = true;
		_lastKeyPressed = keyCode;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_currentCommand = _moveLeft;
		_firstExecution = true;
		_lastKeyPressed = keyCode;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_currentCommand = _moveRight;
		_firstExecution = true;
		_lastKeyPressed = keyCode;
		break;
	}
}
void InputHandler::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == _lastKeyPressed)
	{
		reset();
	}
}

bool InputHandler::updateInput(std::chrono::time_point<std::chrono::system_clock>& previousTime)
{
	bool stateChanged = false;//to know if we need to redraw screen

	auto currentTime = std::chrono::system_clock::now();
	auto deltaTime = (currentTime - _previousCommandTime);

	if (_currentCommand && (deltaTime > _currentCommand->GetMinTimeForSingleCommand()))
	{
		if (_stopUntillNextFrame && deltaTime > _currentCommand->GetDelayBeforeHoldKey())
		{
			_stopUntillNextFrame = false;
		}

		if (!_stopUntillNextFrame)
		{
			stateChanged = _currentCommand->tryToExecute(*_shape, *_map);

			if (stateChanged)
			{
				_previousCommandTime = currentTime;

				if (_currentCommand->GetCanBeRepeated() == false)
				{
					_currentCommand = nullptr;
					//_resetCommandAfterSingleExecution = false;
				}
				else if (_firstExecution)
				{
					_stopUntillNextFrame = true;
					_firstExecution = false;
				}
			}
		}
	}

	return stateChanged;

}

void Tetris::InputHandler::reset()
{
	_currentCommand = nullptr;
	_stopUntillNextFrame = false;
	//_resetCommandAfterSingleExecution = false;
	_firstExecution = false;
}
