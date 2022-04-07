#pragma once
#include <optional>

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

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;

	const GearInfo m_GEAR_TABLE_INFO[7] = {
		{ -1, -20, 0 },
		{ 0, -20, 150 },
		{ 1, 0, 30 },
		{ 2, 20, 50 },
		{ 3, 30, 60 },
		{ 4, 40, 90 },
		{ 5, 50, 150 },
	};

	GearInfo FindGearInfo(int gear) const;
	std::optional<GearInfo> TryFindGearInfo1(int gear) const;
	bool CanSetGear(int gear) const;
	bool CanSetSpeed(int speed) const;
};
