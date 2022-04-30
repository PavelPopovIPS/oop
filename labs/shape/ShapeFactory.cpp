#include "ShapeFactory.h"

std::shared_ptr<CBody> CShapeFactory::CreateSphere(std::istream& args)
{
	double density = ParseDensity(args);

	double radius;
	if (!(args >> radius))
	{
		throw std::runtime_error("Radius is not number\n");
	}

	if (radius <= 0)
	{
		throw std::runtime_error("Radius must be greater then 0\n");
	}

	std::cout << "Sphere was created" << std::endl;
	return std::make_shared<CSphere>(density, radius);
}

std::shared_ptr<CBody> CShapeFactory::CreateParallelepiped(std::istream& args)
{
	double density = ParseDensity(args);
	double width;
	double height;
	double depth;
	if (!(args >> width >> height >> depth))
	{
		throw std::runtime_error("Width or height or depth are not number\n");
	}

	if (width <= 0 || height <= 0 || depth <= 0)
	{
		throw std::runtime_error("Width, height and depth must be greater then 0\n");
	}

	std::cout << "Parallelepiped was created" << std::endl;
	return std::make_shared<CParalellepiped>(density, width, height, depth);
}

std::shared_ptr<CBody> CShapeFactory::CreateCone(std::istream& args)
{
	double density = ParseDensity(args);
	double baseRadius = ParseBaseRadius(args);
	double height = ParseHeight(args);

	std::cout << "Cone was created" << std::endl;
	return std::make_shared<CCone>(density, baseRadius, height);
}

std::shared_ptr<CBody> CShapeFactory::CreateCylinder(std::istream& args)
{
	double density = ParseDensity(args);
	double baseRadius = ParseBaseRadius(args);
	double height = ParseHeight(args);

	std::cout << "Cylinder was created" << std::endl;
	return std::make_shared<CCylinder>(density, baseRadius, height);
}

std::shared_ptr<CCompound> CShapeFactory::CreateCompoundShape()
{
	return std::make_shared<CCompound>();
}

double CShapeFactory::ParseDensity(std::istream& args)
{
	double density;
	args >> density;

	if (!args)
	{
		throw std::runtime_error("CParser is not number\n");
	}

	if (density <= 0)
	{
		throw std::runtime_error("Density can not be zero\n");
	}

	return density;
}

double CShapeFactory::ParseBaseRadius(std::istream& args)
{
	double baseRadius;
	args >> baseRadius;

	if (!args)
	{
		throw std::runtime_error("BaseRadius are not number\n");
	}

	if (baseRadius <= 0)
	{
		throw std::runtime_error("BaseRadius must be greater then 0\n");
	}

	return baseRadius;
}

double CShapeFactory::ParseHeight(std::istream& args)
{
	double height;
	args >> height;
	if (!args)
	{
		throw std::runtime_error("Height are not number\n");
	}

	if (height <= 0)
	{
		throw std::runtime_error("Height must be greater then 0\n");
	}

	return height;
}
