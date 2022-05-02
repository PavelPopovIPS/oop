// shape_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../shape/Body.h"
#include "../shape/Compound.h"
#include "../shape/Cone.h"
#include "../shape/Cylinder.h"
#include "../shape/Parallelepiped.h"
#include "../shape/ShapeFactory.h"
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

		WHEN("get sphere weight in water")
		{
			double result = sphere.GetWeightInWater();
			result = round(result * 100) / 100;

			THEN("weight in water should be equal -1124761.48")
			{
				double expectedResult = -1124761.48;
				expectedResult = round(expectedResult * 100) / 100;

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

		WHEN("get parallelepiped weight in water")
		{
			double result = parallelepiped.GetWeightInWater();

			THEN("weight in water should be equal -119760")
			{
				double expectedResult = -119760;
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

		WHEN("get cone weight in water")
		{
			double result = cone.GetWeightInWater();
			result = round(result * 100) / 100;

			THEN("weight in water should be equal -195294.53")
			{
				double expectedResult = -195294.53;
				expectedResult = round(expectedResult * 100) / 100;

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

		WHEN("get cylinder weight in water")
		{
			double result = cylinder.GetWeightInWater();
			result = round(result * 100) / 100;

			THEN("weight in water should be equal -15187.06")
			{
				double expectedResult = -15187.06;
				expectedResult = round(expectedResult * 100) / 100;

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

SCENARIO("Testing Compound shape")
{
	WHEN("combound shape is created")
	{
		CCompound compoundShape;

		THEN("it should be empty")
		{
			REQUIRE(compoundShape.IsEmpty());
		}
	}

	GIVEN("Sphere with density is 1 and radius is 2")
	{
		CCompound compoundShape;
		double density = 1;
		double radius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, radius);

		WHEN("some shape was added to combound shape")
		{
			compoundShape.AddChildBody(sphere);

			THEN("compound shape should not be empty")
			{
				REQUIRE(!compoundShape.IsEmpty());
			}
		}
	}

	GIVEN("Sphere with density is 1 and radius is 2")
	{
		double density = 1;
		double radius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, radius);
		CCompound compoundShape;

		THEN("sphere can be added to compound shape")
		{
			REQUIRE(compoundShape.AddChildBody(sphere));
		}
	}

	GIVEN("parallelepiped with density is 1, width is 2, height is 3 and depth is 4")
	{
		double density = 1;
		double width = 2;
		double height = 3;
		double depth = 4;
		std::shared_ptr<CBody> parallelepiped = std::make_shared<CParalellepiped>(density, width, height, depth);
		CCompound compoundShape;

		THEN("parallelepiped can be added to compound shape")
		{
			REQUIRE(compoundShape.AddChildBody(parallelepiped));
		}
	}

	GIVEN("cone with density is 1, baseRadius is 2, height is 3")
	{
		double density = 1;
		double baseRadius = 2;
		double height = 3;
		std::shared_ptr<CBody> cone = std::make_shared<CCone>(density, baseRadius, height);
		CCompound compoundShape;

		THEN("cone can be added to compound shape")
		{
			REQUIRE(compoundShape.AddChildBody(cone));
		}
	}

	GIVEN("cylinder with density is 1, baseRadius is 2, height is 3")
	{
		double density = 1;
		double baseRadius = 2;
		double height = 3;
		std::shared_ptr<CBody> cylinder = std::make_shared<CCylinder>(density, baseRadius, height);
		CCompound compoundShape;

		THEN("cylinder can be added to compound shape")
		{
			REQUIRE(compoundShape.AddChildBody(cylinder));
		}
	}

	GIVEN("child compound shape contains sphere, parallelepiped, cone, cylinder")
	{
		double density = 1;
		double baseRadius = 2;
		double width = 2;
		double height = 3;
		double depth = 4;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);
		std::shared_ptr<CBody> parallelepiped = std::make_shared<CParalellepiped>(density, width, height, depth);
		std::shared_ptr<CBody> cone = std::make_shared<CCone>(density, baseRadius, height);
		std::shared_ptr<CBody> cylinder = std::make_shared<CCylinder>(density, baseRadius, height);

		std::shared_ptr<CCompound> chiledCompoundShape = std::make_shared<CCompound>();
		chiledCompoundShape->AddChildBody(sphere);
		chiledCompoundShape->AddChildBody(parallelepiped);
		chiledCompoundShape->AddChildBody(cone);
		chiledCompoundShape->AddChildBody(cylinder);

		CCompound parentCompoundShape;

		THEN("child compound shape can be added to parent compound shape")
		{
			REQUIRE(parentCompoundShape.AddChildBody(chiledCompoundShape));
		}
	}

	// Тесты проверки добавления одной фигуры в две составные
	GIVEN("two compound shapes and one solid shape")
	{
		double density = 1;
		double baseRadius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);

		std::shared_ptr<CCompound> compoundShapeOne = std::make_shared<CCompound>();
		std::shared_ptr<CCompound> compoundShapeTwo = std::make_shared<CCompound>();
		WHEN("add solid shape to compoundShapeOne")
		{
			compoundShapeOne->AddChildBody(sphere);

			THEN("can not add this solid shape to compoundShapeTwo")
			{
				try
				{
					compoundShapeTwo->AddChildBody(sphere);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Added shape can not have parent";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}

	GIVEN("two parent compound shapes and one child compound shape")
	{
		double density = 1;
		double baseRadius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);
		std::shared_ptr<CCompound> childcompoundShape = std::make_shared<CCompound>();
		childcompoundShape->AddChildBody(sphere);

		std::shared_ptr<CCompound> parentCompoundShapeOne = std::make_shared<CCompound>();
		std::shared_ptr<CCompound> parentCompoundShapeTwo = std::make_shared<CCompound>();

		WHEN("add child compound shape to parentCompoundShapeOne")
		{
			parentCompoundShapeOne->AddChildBody(childcompoundShape);

			THEN("can not add child compound shape to parentCompoundShapeTwo")
			{
				try
				{
					parentCompoundShapeTwo->AddChildBody(childcompoundShape);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Added shape can not have parent";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}

	// Проверка вложенности составной фигуры саму в себя
	GIVEN("compound shapes")
	{
		double density = 1;
		double baseRadius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);

		std::shared_ptr<CCompound> compoundShape = std::make_shared<CCompound>();
		compoundShape->AddChildBody(sphere);

		WHEN("add compaund shape in itself")
		{
			THEN("should be exception")
			{
				try
				{
					compoundShape->AddChildBody(compoundShape);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Compound shape can not be added in itself";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}

	// TODO Проверка вложения родителя в дочерний объект
	GIVEN("two compound shapes")
	{
		double density = 1;
		double baseRadius = 2;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);

		std::shared_ptr<CCompound> chiledCompoundShape = std::make_shared<CCompound>();
		chiledCompoundShape->AddChildBody(sphere);

		std::shared_ptr<CCompound> parentCompoundShape = std::make_shared<CCompound>();
		parentCompoundShape->AddChildBody(chiledCompoundShape);

		WHEN("add parent to child")
		{
			THEN("should be exception")
			{
				try
				{
					chiledCompoundShape->AddChildBody(parentCompoundShape);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Compound shape can not be added in itself";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}

	// Передаю пустой объект в составную фигуру
	GIVEN("compound shape")
	{
		std::shared_ptr<CCompound> chiledCompoundShape = std::make_shared<CCompound>();
		std::shared_ptr<CBody> someShape;

		WHEN("add nullptr to compound shape as cbody")
		{
			THEN("should be exception")
			{
				try
				{
					chiledCompoundShape->AddChildBody(someShape);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Shape can not be nullptr";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}

	GIVEN("compound shape contains solid shapes: sphere, parallelepiped, cone, cylinder, compound shape")
	{
		CCompound parentCompoundShape;

		double density = 1;
		double baseRadius = 2;
		double width = 2;
		double height = 3;
		double depth = 4;
		std::shared_ptr<CBody> sphere = std::make_shared<CSphere>(density, baseRadius);
		std::shared_ptr<CBody> parallelepiped = std::make_shared<CParalellepiped>(density, width, height, depth);
		std::shared_ptr<CBody> cone = std::make_shared<CCone>(density, baseRadius, height);
		std::shared_ptr<CBody> cylinder = std::make_shared<CCylinder>(density, baseRadius, height);

		std::shared_ptr<CBody> childSphere = std::make_shared<CSphere>(density, baseRadius);
		std::shared_ptr<CBody> childParallelepiped = std::make_shared<CParalellepiped>(density, width, height, depth);
		std::shared_ptr<CBody> childCone = std::make_shared<CCone>(density, baseRadius, height);
		std::shared_ptr<CBody> childCylinder = std::make_shared<CCylinder>(density, baseRadius, height);

		std::shared_ptr<CCompound> childCompoundShape = std::make_shared<CCompound>();
		childCompoundShape->AddChildBody(childSphere);
		childCompoundShape->AddChildBody(childParallelepiped);
		childCompoundShape->AddChildBody(childCone);
		childCompoundShape->AddChildBody(childCylinder);

		parentCompoundShape.AddChildBody(sphere);
		parentCompoundShape.AddChildBody(parallelepiped);
		parentCompoundShape.AddChildBody(cone);
		parentCompoundShape.AddChildBody(cylinder);
		parentCompoundShape.AddChildBody(childCompoundShape);

		THEN("compound shape density is 1")
		{
			double result = parentCompoundShape.GetDensity();
			double expectedResult = 1.0;

			REQUIRE(result == expectedResult);
		}

		THEN("compound shape volume is 215.13")
		{
			double result = parentCompoundShape.GetVolume();
			result = round(result * 100) / 100;

			double expectedResult = 215.13;

			REQUIRE(result == expectedResult);
		}

		THEN("compound shape mass is 215.13")
		{
			double result = parentCompoundShape.GetMass();
			result = round(result * 100) / 100;

			double expectedResult = 215.13;

			REQUIRE(result == expectedResult);
		}

		THEN("compound shape weight in water is -2149175.96")
		{
			double result = parentCompoundShape.GetWeightInWater();
			result = round(result * 100) / 100;

			double expectedResult = -2149175.96;

			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("Use Shape Factory for creating sphere")
{
	GIVEN("shape factory")
	{
		CShapeFactory shapeFactory;

		WHEN("sphere is created with correct arguments")
		{
			std::string args = "1 2";
			std::istringstream strm(args);

			std::shared_ptr<CBody> sphere = shapeFactory.CreateSphere(strm);

			THEN("shape should be created")
			{
				REQUIRE(sphere != nullptr);
			}
		}

		WHEN("sphere is created with incorrect first argument")
		{
			std::string args = "a 2";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> sphere = shapeFactory.CreateSphere(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Density is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("sphere is created with incorrect second argument")
		{
			std::string args = "1 a";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> sphere = shapeFactory.CreateSphere(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Radius is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("sphere is created without arguments")
		{
			std::string args = "";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> sphere = shapeFactory.CreateSphere(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Density is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}
}

SCENARIO("Use Shape Factory for creating parallelepiped")
{
	GIVEN("shape factory")
	{
		CShapeFactory shapeFactory;

		WHEN("parallelepiped is created with correct arguments")
		{
			std::string args = "1 2 3 4";
			std::istringstream strm(args);

			std::shared_ptr<CBody> parallelepiped = shapeFactory.CreateParallelepiped(strm);

			THEN("shape should be created")
			{
				REQUIRE(parallelepiped != nullptr);
			}
		}

		WHEN("parallelepiped is created with incorrect second argument")
		{
			std::string args = "1 a 3 4";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> parallelepiped = shapeFactory.CreateParallelepiped(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Width or height or depth are not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("parallelepiped is created with incorrect third argument")
		{
			std::string args = "1 2 a 4";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> parallelepiped = shapeFactory.CreateParallelepiped(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Width or height or depth are not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("parallelepiped is created with incorrect fourth argument")
		{
			std::string args = "1 2 3 a";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> parallelepiped = shapeFactory.CreateParallelepiped(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Width or height or depth are not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("parallelepiped is created without arguments")
		{
			std::string args = "";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> parallelepiped = shapeFactory.CreateParallelepiped(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Density is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}
}

SCENARIO("Use Shape Factory for creating cone")
{
	GIVEN("shape factory")
	{
		CShapeFactory shapeFactory;

		WHEN("cone is created with correct arguments")
		{
			std::string args = "1 2 3";
			std::istringstream strm(args);

			std::shared_ptr<CBody> cone = shapeFactory.CreateCone(strm);

			THEN("shape should be created")
			{
				REQUIRE(cone != nullptr);
			}
		}

		WHEN("cone is created with incorrect second argument")
		{
			std::string args = "1 a 3";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cone = shapeFactory.CreateCone(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "BaseRadius is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("cone is created with incorrect third argument")
		{
			std::string args = "1 2 a";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cone = shapeFactory.CreateCone(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Height are not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("cone is created without arguments")
		{
			std::string args = "";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cone = shapeFactory.CreateCone(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Density is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}
}

SCENARIO("Use Shape Factory for creating cylinder")
{
	GIVEN("shape factory")
	{
		CShapeFactory shapeFactory;

		WHEN("cylinder is created with correct arguments")
		{
			std::string args = "1 2 3";
			std::istringstream strm(args);

			std::shared_ptr<CBody> cylinder = shapeFactory.CreateCylinder(strm);

			THEN("shape should be created")
			{
				REQUIRE(cylinder != nullptr);
			}
		}

		WHEN("cylinder is created with incorrect second argument")
		{
			std::string args = "1 a 3";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cylinder = shapeFactory.CreateCylinder(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "BaseRadius is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("cylinder is created with incorrect third argument")
		{
			std::string args = "1 2 a";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cylinder = shapeFactory.CreateCylinder(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Height are not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}

		WHEN("cylinder is created without arguments")
		{
			std::string args = "";
			std::istringstream strm(args);

			THEN("should be exception")
			{
				try
				{
					std::shared_ptr<CBody> cylinder = shapeFactory.CreateCylinder(strm);
					REQUIRE(FALSE);
				}
				catch (const std::exception& e)
				{
					std::string expectedResult = "Density is not number\n";
					REQUIRE(e.what() == expectedResult);
				}
			}
		}
	}
}

SCENARIO("Use Shape Factory for creating compound shape")
{
	GIVEN("shape factory")
	{
		CShapeFactory shapeFactory;

		WHEN("compound shape is created")
		{
			std::shared_ptr<CBody> compoundShape = shapeFactory.CreateCompoundShape();

			THEN("pointer should not equal nullptr")
			{
				REQUIRE(compoundShape != nullptr);
			}
		}
	}
}
