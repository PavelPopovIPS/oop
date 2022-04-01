#pragma once

struct GearInfo
{
	int gear;
	int minSpeed;
	int maxSpeed;
};

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

	void print();

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
	//Возможно обойтись без переменной Direction, храня направление в знаке скорости
	Direction m_direction = Direction::Stop;

	GearInfo m_gearInfoTable[7] = {
		{ -1, -20, 0 },
		{ 0, -20, 150 },
		{ 1, 0, 30 },
		{ 2, 20, 50 },
		{ 3, 30, 60 },
		{ 4, 40, 90 },
		{ 5, 50, 150 },
	};
};
