#pragma once
#include "../proj.win32/main.h"

#include "shape.h"
#include "shapeGenerator.h"
#include "menuPanel.h"
#include "inputHandler.h"


//TODO: ���������� ������ ����� �������
//TODO: use namespaces
//TODO: asserts
//TODO: ������� ����� ��������� ������������ ��� _currentShape ???
//TODO: ������� ������ ���������, ����������� ��������
//TODO: ������� ����� ��������������, � ����� �� �������
//TODO: observers
//TODO: (optional)������������� ����������, �� ��� ������ �� �������
//TODO: pause, rotate both ways, 
//TODO: ������� ����� drop
//TODO: (optional) ������� ���� ���� �� ��� � ����� �����������

class TetrisScene;

namespace Tetris
{	
	class GameController
	{
	private:
		Map _map;
		Shape _currentShape;//current block controlled by player
		ShapeGenerator _shapeGenerator;
		MenuPanel _menuPanel;
		InputHandler _inputHandler;
		std::chrono::time_point<std::chrono::system_clock> _time;
		const  std::chrono::milliseconds _timePerFrame = std::chrono::milliseconds(1000);//1 frame per second
		std::vector<IDrawable*> _objectsToDraw;//vector of all drawable objects
		const Tetris::Point _newShapePosition = Tetris::Point(4, -2);//starting point of new blocks
		cocos2d::Node* _tetrisNode;

		bool Update(std::chrono::time_point<std::chrono::system_clock>& previousTime);
		void NewShape();
		bool CheckIfGameIsOver();
	public:
		GameController();
		~GameController();
		
		void NewGame(cocos2d::Node& node);
		bool GameLoop();
		std::vector<IDrawable*>& GetObjectsToDraw();
	};
};


//TODO read about delegate, observer, callback for CheckForFilledRow

