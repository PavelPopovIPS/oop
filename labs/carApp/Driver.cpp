#include "Driver.h"
using namespace std::placeholders;

Driver::Driver(Car& car)
	: m_car(car)
	, m_actionMap({
		  { "Info", bind(&Driver::Info, this, std::placeholders::_1) }, //зачем биндить? зачем this передавать?
		  { "EngineOn", bind(&Driver::EngineOn, this, std::placeholders::_1) },
		  { "EngineOff", bind(&Driver::EngineOff, this, std::placeholders::_1) },
		  { "SetGear", bind(&Driver::SetGear, this, std::placeholders::_1) },
		  { "SetSpeed", bind(&Driver::SetSpeed, this, std::placeholders::_1) },
	  })
{
}

void Driver::Init()
{
	std::cout << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		auto it = m_actionMap.find(action);
		if (it != m_actionMap.end())
		{
			it->second(strm);
		}
		else
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << "\n>>";
	}
}

void Driver::Info([[maybe_unused]] std::istream& args)
{
	std::cout << "Engine is Turned ";
	std::string state = (m_car.IsTurnedOn())
		? "On"
		: "Off";
	std::cout << state << std::endl;

	std::cout << "Direction is ";
	Direction direction = m_car.GetDirection();
	if (direction == Direction::Back)
	{
		std::cout << "Back" << std::endl;
	}
	else if (direction == Direction::Stop)
	{
		std::cout << "Stop" << std::endl;
	}
	else if (direction == Direction::Forward)
	{
		std::cout << "Forward" << std::endl;
	}

	std::cout << "Gear is " << m_car.GetGear() << std::endl;
	std::cout << "Speed is " << m_car.GetSpeed() << std::endl;
}

void Driver::EngineOn([[maybe_unused]] std::istream& args)
{
	m_car.TurnOnEngine();
	std::cout << "Engine is Turned On" << std::endl;
}

void Driver::EngineOff([[maybe_unused]] std::istream& args)
{
	if (m_car.TurnOffEngine())
	{
		std::cout << "Engine is Turned Off" << std::endl;
	}
	else
	{
		std::cout << "Engine state error" << std::endl;
	}
}

void Driver::SetGear(std::istream& args)
{
	int gear;
	if (!(args >> gear))
	{
		std::cout << "Gear is not number\nUse: SetGear <number>" << std::endl
				  << std::endl;
	}

	if (!m_car.SetGear(gear))
	{
		std::cout << "Gear state error" << std::endl;
	}
}

void Driver::SetSpeed(std::istream& args)
{
	int speed;
	if (!(args >> speed))
	{
		std::cout << "Speed is not number.\nUse: SetSpeed <number>" << std::endl
				  << std::endl;
	}

	if (!m_car.SetSpeed(speed))
	{
		std::cout << "Speed state error" << std::endl;
	}
}
