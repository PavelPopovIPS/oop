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

		WHEN("get sphere density")
		{
			double result = sphere.GetDensity();

			THEN("density should be equal 3")
			{
				double expectedResult = 3;
				REQUIRE(result == expectedResult);
			}
		}

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

SCENARIO("Tests for class Sphere volume and mass")
{
	GIVEN("sphere with radius 3 and density 3")
	{
		double density = 3;
		double radius = 3;
		CSphere sphere(density, radius);

		WHEN("get sphere volume")
		{
			double result = sphere.GetVolume();
			result = round(result * 10) / 10;

			THEN("volume should be equal 112.8")
			{
				double expectedResult = 112.8;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get sphere mass")
		{
			double result = sphere.GetMass();
			result = round(result * 10) / 10;

			THEN("mass should be equal 338.4")
			{
				double expectedResult = 338.4;
				REQUIRE(result == expectedResult);
			}
		}
	}
}
