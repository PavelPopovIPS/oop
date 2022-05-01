// shape_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../shape/Body.h"
#include "../shape/Cone.h"
#include "../shape/Cylinder.h"
#include "../shape/Parallelepiped.h"
#include "../shape/SolidBody.h"
#include "../shape/Sphere.h"
#include "../shape/stdafx.h"

// void CheckDensity(const CBody& shape, double expectedResult)
//{
//	REQUIRE(shape.GetDensity() == expectedResult);
// }

SCENARIO("Create Sphere with valod params")
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

SCENARIO("Creat Sphere with invalid parameters")
{
	WHEN("density is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.0;
				double radius = 0.1;
				CSphere sphere(density, radius);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("density less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = -0.1;
				double radius = 0.1;
				CSphere sphere(density, radius);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("radius is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double radius = 0;
				CSphere sphere(density, radius);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Radius can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("radius less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double radius = -0.1;
				CSphere sphere(density, radius);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Radius can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

SCENARIO("Creat Parallelepiped with valid parameters")
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

SCENARIO("Creat Parallelepiped with invalid parameters")
{
	WHEN("density is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.0;
				double width = 0.1;
				double height = 0.1;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("density less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = -0.1;
				double width = 0.1;
				double height = 0.1;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("width is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = 0.0;
				double height = 0.1;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("width less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = -0.1;
				double height = 0.1;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = 0.1;
				double height = 0.0;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = 0.1;
				double height = -0.1;
				double depth = 0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("depth is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = 0.1;
				double height = 0.1;
				double depth = 0.0;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("depth less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double width = 0.1;
				double height = 0.1;
				double depth = -0.1;
				CParalellepiped paralellepiped(density, width, height, depth);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Width, height and depth can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

SCENARIO("Creat Cone with valid parameters")
{
	GIVEN("cone with density is 3.3, base radius is 3 and height is 2.1")
	{
		double density = 3.3;
		double baseRadius = 3;
		double height = 2.1;

		CCone cone(density, baseRadius, height);

		WHEN("get density")
		{
			double result = cone.GetDensity();

			THEN("density should be equal 3.3")
			{
				double expectedResult = 3.3;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get baseRadius")
		{
			double result = cone.GetBaseRadius();

			THEN("baseRadius should be equal 3")
			{
				double expectedResult = 3;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get height")
		{
			double result = cone.GetHeight();

			THEN("height should be equal 2.1")
			{
				double expectedResult = 2.1;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get volume")
		{
			double result = cone.GetVolume();
			result = round(result * 10) / 10;

			THEN("volume should be equal 19.6")
			{
				double expectedResult = 19.6;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get mass")
		{
			double result = cone.GetMass();
			result = round(result * 10) / 10;

			THEN("mass should be equal 64.7")
			{
				double expectedResult = 64.7;
				REQUIRE(result == expectedResult);
			}
		}
	}
}
SCENARIO("Creat Cone with invalid parameters")
{
	WHEN("density is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.0;
				double baseRadius = 0.1;
				double height = 0.1;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("density less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = -0.1;
				double baseRadius = 0.1;
				double height = 0.1;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("baseRadius is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.0;
				double height = 0.1;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("baseRadius less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = -0.1;
				double height = 0.1;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.1;
				double height = 0.0;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.1;
				double height = -0.1;
				CCone cone(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

SCENARIO("Creat Cylinder with valid parameters")
{
	GIVEN("cylinder with density is 1.2, base radius is 2.2 and height is 0.1")
	{
		double density = 1.2;
		double baseRadius = 2.2;
		double height = 0.1;

		CCylinder cylinder(density, baseRadius, height);

		WHEN("get density")
		{
			double result = cylinder.GetDensity();

			THEN("density should be equal 1.2")
			{
				double expectedResult = 1.2;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get baseRadius")
		{
			double result = cylinder.GetBaseRadius();

			THEN("baseRadius should be equal 2.2")
			{
				double expectedResult = 2.2;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get height")
		{
			double result = cylinder.GetHeight();

			THEN("height should be equal 0.1")
			{
				double expectedResult = 0.1;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get volume")
		{
			double result = cylinder.GetVolume();
			result = round(result * 10) / 10;

			THEN("volume should be equal 1.5")
			{
				double expectedResult = 1.5;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("get mass")
		{
			double result = cylinder.GetMass();
			result = round(result * 10) / 10;

			THEN("mass should be equal 1.8")
			{
				double expectedResult = 1.8;
				REQUIRE(result == expectedResult);
			}
		}
	}
}

SCENARIO("Creat Cylinder with invalid parameters")
{
	WHEN("density is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.0;
				double baseRadius = 0.1;
				double height = 0.1;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("density less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = -0.1;
				double baseRadius = 0.1;
				double height = 0.1;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Density can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("baseRadius is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.0;
				double height = 0.1;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("baseRadius less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = -0.1;
				double height = 0.1;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height is 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.1;
				double height = 0.0;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("height less then 0")
	{
		THEN("should be exception with masages")
		{
			try
			{
				double density = 0.1;
				double baseRadius = 0.1;
				double height = -0.1;
				CCylinder cylinder(density, baseRadius, height);
				REQUIRE(FALSE);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "BaseRadius, height can not be equal zero or less then zero";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}
