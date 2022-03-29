// carApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Car.h"
#include "Driver.h"

int main()
{
	Car car;
	Driver driver(car);

	driver.Init();
}
