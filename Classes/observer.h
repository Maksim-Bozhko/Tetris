#pragma once

//TODO: rename for (auto& it) to for (auto& element)

namespace Tetris
{
	enum class Event
	{
		SHAPE_LANDED,
		eventCount
	};

	class Subject;
	
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(Subject* subject, Event event) = 0;
	};

	class Subject
	{
	private:
		std::vector<Observer*> _observers;
	protected:
		void notify(Subject* subject, Event event)
		{
			for (auto* element : _observers)
			{
				element->onNotify(this, event);
			}
		}
	public: 
		void addObserver(Observer* observer)
		{
			_observers.push_back(observer);
		}

		void removeObserver(Observer* observer)
		{
			int index = 0;
			for (size_t i = 0; i < _observers.size(); ++i)
			{
				if (_observers[i] == observer)
				{
					index = i;
					break;
				}
			}
			_observers.erase(_observers.begin() + index);
		}

		virtual const std::vector<Point>& GetPositions() = 0;
	};
}

