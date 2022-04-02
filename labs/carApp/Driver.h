#pragma once
#include "stdafx.h"
#include "Car.h"

class Driver
{
public:
	Driver(Car& car);
	void Init();

private:
	void Info(std::istream& args);
	void EngineOn(std::istream& args);
	void EngineOff(std::istream& args);
	void SetGear(std::istream& args);
	void SetSpeed(std::istream& args);

	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;

	Car m_car;
};
