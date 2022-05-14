#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../complex/Complex.h"

TEST_CASE("Creating complex number without args should be equal zero by default")
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

TEST_CASE("Creating complex number is 0 with args")
{
	WHEN("complex number is zero")
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

TEST_CASE("Creating complex number with args not equal zero")
{
	WHEN("complex number is zero")
	{
		CComplex complex(3, 1);

		THEN("real part should equal 3")
		{
			double expectedResult = 3.0;
			REQUIRE(complex.Re() == expectedResult);
		}

		THEN("image part should equal 1")
		{
			double expectedResult = 1.0;
			REQUIRE(complex.Im() == expectedResult);
		}
	}
}

TEST_CASE("Modul of complex number")
{
	WHEN("complex number is 3+4i")
	{
		CComplex complex(3, 4);

		THEN("module should equal 5")
		{
			double expectedResult = 5.0;
			REQUIRE(complex.GetMagnitude() == expectedResult);
		}
	}
}

TEST_CASE("Argument for zero can not be define")
{
	WHEN("complex number is 0")
	{
		CComplex complex;

		THEN("argument can not be exist")
		{
			try
			{
				complex.GetArgument();
				REQUIRE(FALSE);
			}
			catch (std::exception& e)
			{
				std::string expectedResult = "Complex number can not be 0\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

TEST_CASE("Argument for complex number in first quarter")
{
	WHEN("complex number is 1+1i")
	{
		CComplex complex(1, 1);

		THEN("argument should be equal 0.785")
		{
			double result = complex.GetArgument();
			result = round(result * 1000) / 1000;

			double expectedResult = 0.785;
			REQUIRE(result == expectedResult);
		}
	}
}
