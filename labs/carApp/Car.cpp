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
	if (m_isEngineOn)
	{
		if (gear == 0)
		{
			m_gear = gear;
			return true;
		}

		if (m_speed == 0 && m_direction == Direction::Stop)
		{
			if (gear == -1 || gear == 1)
			{
				m_gear = gear;
				return true;
			}

			return false;
		}

		if (m_direction == Direction::Forward)
		{
			if (m_speed > 0 && m_speed <= 20)
			{

				if (gear == 1)
				{
					m_gear = gear;
					return true;
				}
			}

			if (m_speed >= 20 && m_speed <= 30)
			{
				if (gear == 1)
				{
					m_gear = gear;
					return true;
				}

				if (gear == 2)
				{
					m_gear = gear;
					return true;
				}
			}

			if (m_speed >= 30 && m_speed <= 40)
			{
			}

			if (m_speed >= 40 && m_speed <= 50)
			{
			}

			if (m_speed >= 50 && m_speed <= 60)
			{
			}

			if (m_speed >= 60 && m_speed <= 90)
			{
			}

			if (m_speed >= 90 && m_speed <= 150)
			{
			}
		}

		return false;
	}
	else
	{
		if (gear == 0)
		{
			m_gear = gear;
			return true;
		}
		return false;
	}
}

bool Car::SetSpeed(int speed)
{
	if (m_isEngineOn)
	{
		if (m_gear == -1)
		{
			if (speed == 0)
			{
				m_speed = speed;
				m_direction = Direction::Stop;
				return true;
			}

			if (speed > 0 && speed <= 20)
			{
				m_speed = speed;
				m_direction = Direction::Back;
				return true;
			}
			else
			{
				return false;
			}
		}

		if (m_gear == 0) // Neutral, скорость может только уменьшаться
		{
			if (speed == 0)
			{
				m_speed = speed;
				m_direction = Direction::Stop;
				return true;
			}

			if (speed > 0 && speed <= m_speed)
			{
				m_speed = speed;
				return true;
			}

			return false;
		}

		if (m_gear == 1)
		{
			if (speed == 0)
			{
				m_speed = speed;
				m_direction = Direction::Stop;
				return true;
			}

			if (speed > 0 && speed <= 30)
			{
				m_speed = speed;
				m_direction = Direction::Forward;
				return true;
			}

			return false;
		}

		if (m_gear == 2)
		{
		}

		if (m_gear == 3)
		{
		}

		if (m_gear == 4)
		{
		}

		if (m_gear == 5)
		{
		}

		return false;
	}
	else
	{

		return false;
	}
}
