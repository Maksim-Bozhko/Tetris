#pragma once
#include "../proj.win32/main.h"

#include "shape.h"
#include "shapeGenerator.h"
#include "menuPanel.h"
#include "inputHandler.h"


//TODO: разместить методы более логично
//TODO: use namespaces
//TODO: asserts
//TODO: выбрать какой указатель использовать для _currentShape ???
//TODO: сделать уровни сложности, увеличивать скорость
//TODO: сделать цвета настраиваемыми, а также их яркость
//TODO: observers
//TODO: (optional)настраиваемое управление, по две кнопки на команду
//TODO: pause, rotate both ways, 
//TODO: сделать лучше drop
//TODO: (optional) следать тень шейп по ней в месте приземления

class TetrisScene;

namespace Tetris
{
	class GameController
	{
	private:
		Map _map;
		Shape _currentShape;//current block controlled by player
		ShapeGenerator _shapeGenerator;
		//TetrisScene* _scene;
		MenuPanel _menuPanel;
		std::chrono::time_point<std::chrono::system_clock> _time;
		const  std::chrono::milliseconds _timePerFrame = std::chrono::milliseconds(1000);//1 frame per second
																						 //TODO: move this to render
		std::vector<IDrawable*> _objectsToDraw;//vector of all drawable objects
											   //TODO: убрать сырой указатель, weak ссылка
		InputHandler _inputHandler;
		const Tetris::Point _newShapePosition = Tetris::Point(4, -2);//starting point of new blocks

		void CheckForFilledRow();//TODO: this shoud be done by map
		cocos2d::Node* _tetrisNode;

		bool _stateChanged;
	public:
		GameController();
		~GameController();
		void GameLoop(TetrisScene* scene);
		bool Update(std::chrono::time_point<std::chrono::system_clock>& previousTime);
		void NewShape();

		bool CheckIfGameIsOver();
		void NewGame(cocos2d::Node& node);

		std::vector<IDrawable*>& GetObjectsToDraw();

		bool GetStateChanged() const;
	};
};


//TODO read about delegate, observer, callback for CheckForFilledRow

