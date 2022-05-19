#include "Complex.h"

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(Re(), 2) + pow(Im(), 2));
}

double CComplex::GetArgument() const
{
	if (Re() == 0 && Im() == 0)
	{
		throw std::runtime_error("Complex number can not be 0\n");
	}

	if (Re() > 0 && Im() > 0)
	{
		return atan(Im() / Re());
	}

	if (Re() > 0 && Im() < 0)
	{
		return -atan(Im() / Re());
	}

	if (Re() < 0 && Im() > 0)
	{
		return M_PI - atan(Im() / Re());
	}

	if (Re() < 0 && Im() < 0)
	{
		return -M_PI + atan(Im() / Re());
	}

	if (Re() == 0 && Im() > 0)
	{
		return M_PI / 2;
	}

	if (Re() == 0 && Im() < 0)
	{
		return -M_PI / 2;
	}

	if (Re() > 0 && Im() == 0)
	{
		return 0;
	}

	if (Re() < 0 && Im() == 0)
	{
		return M_PI;
	}

	throw std::runtime_error("Complex number position was not define\n");
}

CComplex CComplex::operator+(const CComplex& complex) const
{
	return CComplex(Re() + complex.Re(), Im() + complex.Im());
}

CComplex CComplex::operator-(const CComplex& complex) const
{
	return CComplex(Re() - complex.Re(), Im() - complex.Im());
}

CComplex CComplex::operator*(const CComplex& complex) const
{
	return CComplex(Re() * complex.Re() - Im() * complex.Im(), Im() * complex.Re() + Re() * complex.Im());
}

CComplex CComplex::operator/(const CComplex& complex) const
{
	if (complex == 0)
	{
		throw std::runtime_error("Denominator can not be zero\n");
	}

	double tmpDenominator = pow(complex.Re(), 2) + pow(complex.Im(), 2);
	double tmpRe = (Re() * complex.Re() + Im() * complex.Im()) / tmpDenominator;
	double tmpIm = (Im() * complex.Re() - Re() * complex.Im()) / tmpDenominator;

	return CComplex(tmpRe, tmpIm);
}

//Тут точно вернет ссылку на тот же объект?
CComplex const CComplex::operator+() const
{
	return *this;
}

CComplex const CComplex::operator-() const
{
	return CComplex(-Re(), -Im());
}

CComplex& CComplex::operator+=(const CComplex& complex)
{
	m_real += complex.m_real;
	m_image += complex.m_image;

	return *this;
}

CComplex& CComplex::operator-=(const CComplex& complex)
{
	m_real -= complex.m_real;
	m_image -= complex.m_image;

	return *this;
}

CComplex& CComplex::operator*=(const CComplex& complex)
{
	*this = *this * complex;

	return *this;
}

CComplex& CComplex::operator/=(const CComplex& complex)
{
	*this = *this / complex;

	return *this;
}

bool CComplex::operator==(const CComplex& complex) const
{
	bool reAreEqual = (fabs(Re() - complex.Re()) < DBL_EPSILON);
	bool imAreEqual = (fabs(Im() - complex.Im()) < DBL_EPSILON);
	return (reAreEqual && imAreEqual);
}

bool CComplex::operator!=(const CComplex& complex) const
{
	return !(*this == complex);
}

CComplex operator+(double number, const CComplex& complex)
{
	CComplex n(number);
	return n + complex;
}

CComplex operator-(double number, const CComplex& complex)
{
	CComplex n(number);
	return n - complex;
}

CComplex operator*(double number, const CComplex& complex)
{
	CComplex n(number);
	return n * complex;
}

CComplex operator/(double number, const CComplex& complex)
{
	CComplex n(number);
	return n / complex;
}

bool operator==(double number, const CComplex& complex)
{
	CComplex n(number);
	bool reAreEqual = (fabs(n.Re() - complex.Re()) < DBL_EPSILON);
	bool imAreEqual = (fabs(n.Im() - complex.Im()) < DBL_EPSILON);

	return (reAreEqual && imAreEqual);
}

bool operator!=(double number, const CComplex& complex)
{
	CComplex n(number);
	bool reAreEqual = (fabs(n.Re() - complex.Re()) < DBL_EPSILON);
	bool imAreEqual = (fabs(n.Im() - complex.Im()) < DBL_EPSILON);

	return !(reAreEqual && imAreEqual);
}

std::ostream& operator<<(std::ostream& stream, const CComplex& complex)
{
	stream << complex.Re();

	if (complex.Im() >= 0)
	{
		stream << "+";
	}
	stream << complex.Im() << "i" << std::endl;

	return stream;
}

std::istream& operator>>(std::istream& stream, CComplex& complex)
{
	double re = 0;
	double im = 0;
	std::string a = "";

	stream >> a;

	if (a.length() == 0)
	{
		throw std::runtime_error("String can not be empty\n");
	}

	size_t lastCh = a.length() - 1;
	if (a[lastCh] != 'i')
	{
		throw std::runtime_error("Complex number should have i at the end and looks like a+bi\n");
	}

	a.erase(lastCh);

	size_t pos = 0;
	if (a[0] == '-')
	{
		pos++;
	}

	size_t center = a.find("+", pos);
	if (center == std::string::npos)
	{
		center = a.find("-", pos);
		if (center == std::string::npos)
		{
			throw std::runtime_error("There is no center. Complex number should look like a+bi\n");
		}
	}

	std::string re_str = a.substr(0, center);
	std::string im_str = a.substr(center);

	try
	{
		re = std::stod(re_str);
		im = std::stod(im_str);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}

	complex = CComplex(re, im);
	return stream;
}
