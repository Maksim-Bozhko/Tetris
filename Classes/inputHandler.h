#pragma once

#include "../proj.win32/main.h"

#include "shape.h"
//TODO: заменить все for(size_t i...) на for (auto&(!!!) it : container)
//TODO: make sound for rotation and deleting row
//TODO: make original song
//TODO: make menu
//TODO: make score and levels

namespace MyTetris
{

	class Command
	{
	protected:
		std::chrono::duration<float> _minTimeForSingleCommand;//minimal amount of time between command can be repeated
		std::chrono::duration<float> _delayBeforeHoldKey;//when you hold key command is executed once. After _delayBeforeHoldKey amount of time command is executed repeatedly as long as user holds the key
		bool _canBeRepeated;//if command can be repeated by holding the key
	public:
		Command()
		{
			_delayBeforeHoldKey = std::chrono::duration<float>(1 / 2.0f);
			_canBeRepeated = true;
		}
		virtual ~Command() {}
		virtual bool tryToExecute(Shape& shape, Map& map) = 0;
		const bool& GetCanBeRepeated() const { return _canBeRepeated; }
		const std::chrono::duration<float>& GetMinTimeForSingleCommand() const { return _minTimeForSingleCommand; }
		const std::chrono::duration<float>& GetDelayBeforeHoldKey() const { return _delayBeforeHoldKey; }
	};

	class MoveLeft : public Command
	{
		
	public:
		MoveLeft() 
		{
			_minTimeForSingleCommand = std::chrono::duration<float>((1 / 30.0f));
		}
		virtual bool tryToExecute(Shape& shape, Map& map)
		{
			return shape.Move(MyTetris::Point(-1, 0), map);
		}
	};

	class MoveRight : public Command
	{
	public:
		MoveRight()
		{
			_minTimeForSingleCommand = std::chrono::duration<float>((1 / 30.0f));
		}
		virtual bool tryToExecute(Shape& shape, Map& map)
		{
			return shape.Move(Point(1, 0), map);
		}
	};

	class MoveDown : public Command
	{
	public:
		MoveDown()
		{
			_minTimeForSingleCommand = std::chrono::duration<float>((1 / 60.0f));
		}
		virtual bool tryToExecute(Shape& shape, Map& map)
		{
			return shape.Move(Point(0, 1), map);
		}
	};

	class Rotate : public Command
	{
	public:
		Rotate()
		{
			_minTimeForSingleCommand = std::chrono::duration<float>(1 / 30.f);
			_canBeRepeated = false;
		}
		virtual bool tryToExecute(Shape& shape, Map& map)
		{
			return shape.RotateClocklWise(map);
		}
	};

	class InputHandler : public cocos2d::Node
	{
	private:
		Command* _moveLeft;
		Command* _moveRight;
		Command* _moveDown;
		Command* _rotate;

		std::chrono::time_point<std::chrono::system_clock> _previousCommandTime;
		//const  std::chrono::milliseconds _timePerInputUpdate = std::chrono::milliseconds(25);
		//const  std::chrono::milliseconds _timeForSingleAction = std::chrono::milliseconds(500);

		cocos2d::EventListenerKeyboard* _eventListenerKeyboard;
		Shape* _shape;
		Map* _map;

		Command* _currentCommand;

		//bool _resetCommandAfterSingleExecution;
		bool _stopUntillNextFrame;
		bool _firstExecution;
		cocos2d::EventKeyboard::KeyCode _lastKeyPressed;
	public:
		InputHandler();
		InputHandler(Map* map, Shape* shape);
		~InputHandler();
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
		void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
		bool updateInput(std::chrono::time_point<std::chrono::system_clock>& previousTime);
		void reset();
	};
};