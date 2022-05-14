#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../complex/Complex.h"

TEST_CASE("Complex number is zero by default")
{
	WHEN("complex is created without args")
	{
		CComplex complex;

		THEN("real part should equal 0")
		{
			double expectedResult = 0.0;
			REQUIRE(complex.Re() == expectedResult);
		}

		THEN("image part should equal 0")
		{
			double expectedResult = 0.0;
			REQUIRE(complex.Im() == expectedResult);
		}
	}
}

TEST_CASE("Complex number is zero")
{
	WHEN("complex is zero")
	{
		CComplex complex(0, 0);

		THEN("real part should equal 0")
		{
			double expectedResult = 0.0;
			REQUIRE(complex.Re() == expectedResult);
		}

		THEN("image part should equal 0")
		{
			double expectedResult = 0.0;
			REQUIRE(complex.Im() == expectedResult);
		}
	}
}
