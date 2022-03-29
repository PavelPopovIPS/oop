#pragma once
#include "stdafx.h"
#include "Car.h"

class Driver
{
public:
	Driver(Car& car);
	void Init();

private:
	void Info();
	void EngineOn();
	void EngineOff();
	void SetGear(int gear);
	void SetSpeed(int speed);

	Car m_car;
};
