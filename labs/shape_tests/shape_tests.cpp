// shape_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../shape/Sphere.h"
#include "../shape/stdafx.h"

SCENARIO("Tests for class Sphere")
{
	GIVEN("sphere with radius 3 and density 13")
	{
		double density = 3;
		double radius = 13;
		CSphere sphere(density, radius);
		WHEN("get sphere radius")
		{
			double result = sphere.GetRadius();

			THEN("radius should be equal 13")
			{
				double expectedResult = 13;
				REQUIRE(result == expectedResult);
			}
		}
	}
}
