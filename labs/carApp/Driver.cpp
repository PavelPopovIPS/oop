#include "Driver.h"

Driver::Driver(Car& car)
	: m_car(car)
{
}

void Driver::Init()
{
	std::cout << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string command;

		strm >> command;

		if (command == "Info" || command == "info")
		{
			Driver::Info();
		}
		else if (command == "EngineOn" || command == "engineOn")
		{
			Driver::EngineOn();
		}
		else
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << std::endl;
		std::cout << ">>";
	}
}

void Driver::Info()
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

void Driver::EngineOn()
{
}

void Driver::EngineOff()
{
}

void Driver::SetGear(int gear)
{
}

void Driver::SetSpeed(int speed)
{
}
