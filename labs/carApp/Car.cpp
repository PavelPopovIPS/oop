#include "stdafx.h"
#include "Car.h"

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	return m_speed;
}

bool Car::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
	}
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_isEngineOn)
	{
		if (m_gear == 0 && m_speed == 0 && m_direction == Direction::Stop)
		{
			m_isEngineOn = false;
			return true;
		}
		return false;
	}
	return true;
}

bool Car::SetGear(int gear)
{
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}
