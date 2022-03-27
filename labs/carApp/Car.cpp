#include "stdafx.h"
#include "Car.h"

bool Car::IsTurnedOn() const
{
	return false;
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
	return false;
}

bool Car::TurnOffEngine()
{
	return false;
}

bool Car::SetGear(int gear)
{
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}
