#include "stdafx.h"
#include "Car.h"

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction Car::GetDirection() const
{
	if (m_speed < 0)
	{
		return Direction::Back;
	}

	if (m_speed == 0)
	{
		return Direction::Stop;
	}

	if (m_speed > 0)
	{
		return Direction::Forward;
	}
}

int Car::GetGear() const
{
	return m_gear;
}

int Car::GetSpeed() const
{
	int currentSpeed = m_speed;

	if (m_speed < 0)
	{
		currentSpeed = abs(m_speed);
	}

	return currentSpeed;
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
		if (m_gear == 0 && m_speed == 0)
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
	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}

	if (!m_isEngineOn)
	{
		return false;
	}

	if (CanSetGear(gear))
	{
		m_gear = gear;
		return true;
	}

	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	if (m_gear == -1 || m_speed < 0) // Пересчитать знак устанавливаемой скорости, если едем назад
	{
		speed *= -1;
	}

	if (CanSetSpeed(speed))
	{
		m_speed = speed;
		return true;
	}

	return false;
}

GearInfo Car::FindGearInfo(int gear) const
{
	for (GearInfo gearInfo : m_GEAR_TABLE_INFO)
	{
		if (gearInfo.gear == gear)
		{
			return gearInfo;
		}
	}
}

bool Car::CanSetGear(int gear) const
{
	if (gear < -1 && gear > 5)
	{
		return false;
	}

	if (m_gear == 0 && GetDirection() == Direction::Back)
	{
		return false;
	}

	GearInfo gearInfo = FindGearInfo(gear);

	if (m_speed >= gearInfo.minSpeed && m_speed <= gearInfo.maxSpeed)
	{
		return true;
	}

	return false;
}

bool Car::CanSetSpeed(int speed) const
{
	if (m_gear == 0) // На нейтрали, скорость может только уменьшаться
	{
		if (speed == 0)
		{
			return true;
		}

		if (speed >= m_speed && speed < 0) // если двигаемся назад
		{
			return true;
		}

		if (speed > 0 && speed <= m_speed) // если двигаемся прямо
		{
			return true;
		}

		return false;
	}

	GearInfo gearInfo = FindGearInfo(m_gear);

	if (speed >= gearInfo.minSpeed && speed <= gearInfo.maxSpeed)
	{
		return true;
	}

	return false;
}
