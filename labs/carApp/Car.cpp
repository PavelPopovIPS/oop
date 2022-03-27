#include "stdafx.h"
#include "Car.h"

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction Car::GetDirection() const
{
	Direction direction = Direction::Stop;
	return direction;
}

int Car::GetSpeed() const
{
	return 0;
}

int Car::GetGear() const
{
	return 0;
}

bool Car::TurnOnEngine()
{
	m_isEngineOn = true;
	return m_isEngineOn;
}

bool Car::TurnOffEngine()
{
	m_isEngineOn = false;
	return m_isEngineOn;
}

bool Car::SetGear(int gear)
{
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}
