#include "Driver.h"
using namespace std::placeholders;

Driver::Driver(Car& car)
	: m_car(car)
	, m_actionMap({
		  { "Info", bind(&Driver::Info, this, std::placeholders::_1) },
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

bool Driver::Info([[maybe_unused]] std::istream& args)
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

	return true;
}

bool Driver::EngineOn([[maybe_unused]] std::istream& args)
{
	m_car.TurnOnEngine();
	return true;
}

bool Driver::EngineOff([[maybe_unused]] std::istream& args)
{
	if (!m_car.TurnOffEngine())
	{
		if (m_car.GetGear() != 0)
		{
			std::cout << "Gear is not equal neutral." << std::endl;
			return false;
		}

		if (m_car.GetSpeed() != 0)
		{
			std::cout << "Speed is not equal 0." << std::endl;
			return false;
		}

		return false;
	}
	return true;
}

bool Driver::SetGear(std::istream& args)
{
	int gear;
	if (!(args >> gear))
	{
		std::cout << "Gear is not number\nUse: SetGear <number>" << std::endl;
		return false;
	}

	if (!m_car.SetGear(gear))
	{
		if (!m_car.IsTurnedOn())
		{
			std::cout << "Engine is not Turned On." << std::endl;
			return false;
		}

		if (gear < -1 || gear > 5)
		{
			std::cout << "Gear is not correct. You should use numbers -1 ... 5" << std::endl;
			return false;
		}

		if (m_car.GetGear() == 0 && m_car.GetDirection() == Direction::Back)
		{
			std::cout << "You can not set Back Gear when direction is Back. Stop your car and try again " << std::endl;
		}

		std::cout << "You can not set gear " + std::to_string(gear)
				+ " when speed is " + std::to_string(m_car.GetSpeed())
				  << std::endl;

		return false;
	}
	return true;
}

bool Driver::SetSpeed(std::istream& args)
{
	int speed;
	if (!(args >> speed))
	{
		std::cout << "Speed is not number.\nUse: SetSpeed <number>" << std::endl;
		return false;
	}

	if (!m_car.SetSpeed(speed))
	{
		if (!m_car.IsTurnedOn())
		{
			std::cout << "Engine is not Turned On." << std::endl;
			return false;
		}

		if (m_car.GetGear() == 0 && speed > m_car.GetSpeed())
		{
			std::cout << "You can not increase speed when gear is neutral." << std::endl;
			return false;
		}

		if (speed < 0 || speed > 150)
		{
			std::cout << "You can not set speed less then 0 and greater then 150." << std::endl;
			return false;
		}

		std::cout << "You can not set speed " + std::to_string(speed)
				+ " when gear is " + std::to_string(m_car.GetGear())
				  << std::endl;

		return false;
	}
	return true;
}
