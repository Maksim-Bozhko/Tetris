#include "../proj.win32/main.h"
#include "menuPanel.h"

//TODO: make a method that draws line
//TODO: rotate other direction
//TODO: check for memoryleaks all project

using namespace Tetris;

MenuPanel::MenuPanel()
{

}

MenuPanel::~MenuPanel()
{
	if (_scoreLabel)
	{
		_scoreLabel->release();
	}
}


void MenuPanel::Draw(vec2d_tetris_color& buffer)
{
	//draw box for next shape
	for (unsigned int x = 0; x < _width + 1; ++x)
	{
		buffer[_position.y + 0][_position.x + x] = Color::white;
		buffer[_position.y + _width + 1][_position.x + x] = Color::white;
		buffer[_position.y + _height - 1][_position.x + 1 + x] = Color::white;
	}

	for (unsigned int y = 0; y < _height; ++y)
	{
		buffer[_position.y + y][_position.x] = Color::white;
		buffer[_position.y + y][_position.x + _width + 1] = Color::white;
	}

	_shape.Draw(buffer);

	std::string scoreString;
	scoreString = "Score: " + std::to_string(_score);
	_scoreLabel->setString(scoreString);
}

void MenuPanel::IncreaseScore()
{
	_score += 1;
}

void MenuPanel::SetUpcomingShape(ShapeType shapeType)
{
	_shape.SetShape(shapeType);
}

void MenuPanel::Init(const Map& map, cocos2d::Node& node)
{
	//TODO: move this to constructor
	_position.SetXY(map.GetWidth(), 0);//top left corner of menupanel
	Point shapePosition = _position + Point(2, 2);//offset for upcoming shape
	_shape.SetPosition(shapePosition);
	_score = 0;

	_width = _shape.GetMatrixSize() + 2 * map.GetBorderWidth();//width of box where upcoming bos is shown
															   //move this to caclulate width, make more obvious
	_height = map.GetHeight();//height of panel is same as height of the map
	
	//TODO: check _scorelabel

	if (_scoreLabel)
	{
		node.removeChild(_scoreLabel);
		_scoreLabel = nullptr;
	}

	if (_scoreLabel == nullptr)
	{
		_scoreLabel = cocos2d::Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 24);

		_scoreLabel->setAnchorPoint(cocos2d::Vec2(0, 1));
		_scoreLabel->setPosition((map.GetWidth() + 2) * (20 + 4), (_height - (_width + 2)) * (20 + 4));
		_scoreLabel->setName("scoreLabel");

		node.addChild(_scoreLabel, 0);
	}
}

void Tetris::MenuPanel::onNotify(Subject * subject, Event event)
{
	if (event == Event::ROW_FILLED)
	{
		IncreaseScore();
	}
}
