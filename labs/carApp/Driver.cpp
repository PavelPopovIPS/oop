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
		else if (command == "EngineOff" || command == "engineOff")
		{
			Driver::EngineOff();
		}
		else if (command == "SetGear" || command == "setGear")
		{
			int gear;
			if (strm >> gear)
			{
				Driver::SetGear(gear);
			}
			else
			{
				std::cout << "Gear is not number\n Use: SetGear <number>" << std::endl
						  << std::endl
						  << ">>";
				continue;
			}
		}
		else if (command == "SetSpeed" || command == "setSpeed")
		{
			int speed;
			if (strm >> speed)
			{
				Driver::SetSpeed(speed);
			}
			else
			{
				std::cout << "Speed is not number.\n Use: SetSpeed <number>" << std::endl
						  << std::endl
						  << ">>";
				continue;
			}
		}
		else
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << std::endl
				  << ">>";
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
	m_car.TurnOnEngine();
	std::cout << "Engine is Turned On" << std::endl;
}

void Driver::EngineOff()
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

void Driver::SetGear(int gear)
{
	if (!m_car.SetGear(gear))
	{
		std::cout << "Gear state error" << std::endl;
	}
}

void Driver::SetSpeed(int speed)
{
	if (!m_car.SetSpeed(speed))
	{
		std::cout << "Speed state error" << std::endl;
	}
}
