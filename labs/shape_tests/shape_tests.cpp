// shape_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../shape/Body.h"
#include "../shape/Parallelepiped.h"
#include "../shape/Sphere.h"
#include "../shape/stdafx.h"

// void CheckDensity(const CBody& shape, double expectedResult)
//{
//	REQUIRE(shape.GetDensity() == expectedResult);
// }

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

			THEN("volume should be equal 113.1")
			{
				double expectedResult = 113.1;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get sphere mass")
		{
			double result = sphere.GetMass();
			result = round(result * 10) / 10;

			THEN("mass should be equal 339.3")
			{
				double expectedResult = 339.3;
				REQUIRE(result == expectedResult);
			}
		}
	}
}

SCENARIO("Tests for class Parallelepiped")
{
	GIVEN("parallelepiped with density is 2, width is 1, height is 4, depth is 3")
	{
		double density = 2;
		double width = 1;
		double height = 4;
		double depth = 3;

		CParalellepiped parallelepiped(density, width, height, depth);

		WHEN("get density")
		{
			double result = parallelepiped.GetDensity();

			THEN("density should be equal 2")
			{
				double expectedResult = 2;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get width")
		{
			double result = parallelepiped.GetWidth();

			THEN("width should be equal 1")
			{
				double expectedResult = 1;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get height")
		{
			double result = parallelepiped.GetHeight();

			THEN("height should be equal 4")
			{
				double expectedResult = 4;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get depth")
		{
			double result = parallelepiped.GetDepth();

			THEN("depth should be equal 3")
			{
				double expectedResult = 3;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get volume")
		{
			double result = parallelepiped.GetVolume();

			THEN("volume should be equal ")
			{
				double expectedResult = 12.0;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get mass")
		{
			double result = parallelepiped.GetMass();

			THEN("mass should be equal ")
			{
				double expectedResult = 24.0;
				REQUIRE(result == expectedResult);
			}
		}
	}
}
