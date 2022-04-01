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
		if (m_gear == 0 && m_speed == 0 && m_direction == Direction::Stop) // одна из проверко (Скорость и направление) лишняя
		{
			m_isEngineOn = false;
			return true;
		}
		return false;
	}
	return true;
}

// метод слишком большой, наверняка код дублируется (завести табицу, структуру с диапазонами скоростей) и в ней проверять возможность включения передачи
bool Car::SetGear(int gear)
{
	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}

	// уменьшить вложенность, если проверять на невключенность двигателя и сразу выходить
	if (!m_isEngineOn)
	{
		return false;
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
			if (gear == 1 || gear == 2)
			{
				m_gear = gear;
				return true;
			}
		}

		if (m_speed >= 30 && m_speed <= 40)
		{
			if (gear == 2 || gear == 3)
			{
				m_gear = gear;
				return true;
			}
		}

		if (m_speed >= 40 && m_speed <= 50)
		{
			if (gear == 2 || gear == 3 || gear == 4)
			{
				m_gear = gear;
				return true;
			}
		}

		if (m_speed >= 50 && m_speed <= 60)
		{
			if (gear == 3 || gear == 4 || gear == 5)
			{
				m_gear = gear;
				return true;
			}
		}

		if (m_speed >= 60 && m_speed <= 90)
		{
			if (gear == 4 || gear == 5)
			{
				m_gear = gear;
				return true;
			}
		}

		if (m_speed >= 90 && m_speed <= 150)
		{
			if (gear == 5)
			{
				m_gear = gear;
				return true;
			}
		}
	}

	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

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

		return false;
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
		if (speed >= 20 && speed <= 50)
		{
			m_speed = speed;
			m_direction = Direction::Forward;
			return true;
		}

		return false;
	}

	if (m_gear == 3)
	{
		if (speed >= 30 && speed <= 60)
		{
			m_speed = speed;
			m_direction = Direction::Forward;
			return true;
		}

		return false;
	}

	if (m_gear == 4)
	{
		if (speed >= 40 && speed <= 90)
		{
			m_speed = speed;
			m_direction = Direction::Forward;
			return true;
		}

		return false;
	}

	if (m_gear == 5)
	{
		if (speed >= 50 && speed <= 150)
		{
			m_speed = speed;
			m_direction = Direction::Forward;
			return true;
		}

		return false;
	}

	return false; // передали неправильный номер передачи
}

void Car::print()
{
	for (auto& i : m_GEAR_TABLE_INFO)
	{
		std::cout << i.gear << i.minSpeed << i.maxSpeed << std::endl;
	}
}

GearInfo Car::FindGearInfo(int gear)
{
	return m_GEAR_TABLE_INFO[0];
}

bool Car::CanSetGear(int gear)
{
	return false;
}

bool Car::CanSetSpeed(int speed)
{
	return false;
}
