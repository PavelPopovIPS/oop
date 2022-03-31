#pragma once

enum class Direction
{
	Forward,
	Back,
	Stop,
};

class Car
{
public:
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
	//Возможно обойтись без переменной Direction, храня направление в знаке скорости
	Direction m_direction = Direction::Stop;
};
