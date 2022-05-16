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

TEST_CASE("Adding complex numbers")
{
	WHEN("adding two complex numbers")
	{
		CComplex complex1(1, 1);
		CComplex complex2(3, 4);

		CComplex result = complex1 + complex2;

		THEN("real part should be equal 4")
		{
			double expectedResult = 4;
			REQUIRE(result.Re() == expectedResult);
		}

		THEN("image part should be equal 5")
		{
			double expectedResult = 5;
			REQUIRE(result.Im() == expectedResult);
		}
	}
	
	WHEN("adding complex number and real number")
	{
		CComplex complex(1, 1);
		double n = 3.1;

		CComplex result = complex + n;

		THEN("real part should be equal 4.1")
		{
			double expectedResult = 4.1;
			REQUIRE(result.Re() == expectedResult);
		}

		THEN("image part should be equal 1")
		{
			double expectedResult = 1;
			REQUIRE(result.Im() == expectedResult);
		}
	}	

	WHEN("adding real number and complex number")
	{
		double n = 5;
		CComplex complex(1, 0.1);

		CComplex result = n + complex;

		THEN("real part should be equal 6")
		{
			double expectedResult = 6;
			REQUIRE(result.Re() == expectedResult);
		}

		THEN("image part should be equal 0.1")
		{
			double expectedResult = 0.1;
			REQUIRE(result.Im() == expectedResult);
		}
	}
}

TEST_CASE("Compair complex numbers")
{
	WHEN("compair two equal complex numbers")
	{
		CComplex complex1(1, 3);
		CComplex complex2(1, 3);

		bool result = (complex1 == complex2);

		THEN("return true")
		{
			bool expectedResult = true;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("compair two NOT equal complex numbers by real part")
	{
		CComplex complex1(1, 3);
		CComplex complex2(2, 3);

		bool result = (complex1 == complex2);

		THEN("compair should return false")
		{
			bool expectedResult = false;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("compair two NOT equal complex numbers by image part")
	{
		CComplex complex1(2, 4);
		CComplex complex2(2, 3);

		bool result = (complex1 == complex2);

		THEN("compair should return false")
		{
			bool expectedResult = false;
			REQUIRE(result == expectedResult);
		}
	}
}
