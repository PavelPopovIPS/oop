#include "ShapeFactory.h"

CShapeFactory::CShapeFactory()
	: m_parseShapeActionMap({
		{ "Sphere", bind(&CShapeFactory::CreateSphere, this, std::placeholders::_1) },
		{ "Parallelepiped", bind(&CShapeFactory::CreateParallelepiped, this, std::placeholders::_1) },
		{ "Cone", bind(&CShapeFactory::CreateCone, this, std::placeholders::_1) },
		{ "Cylinder", bind(&CShapeFactory::CreateCylinder, this, std::placeholders::_1) },
	})
{
}

// create shape
std::optional<std::shared_ptr<CBody>> CShapeFactory::ParseShape(std::string& parseShapeAction, std::istream& args)
{
	auto itShapeAction = m_parseShapeActionMap.find(parseShapeAction);

	if (itShapeAction != m_parseShapeActionMap.end())
	{
		std::shared_ptr<CBody> shape = itShapeAction->second(args);
		return shape;
	}

	if (parseShapeAction == "CompoundStart")
	{
		std::shared_ptr<CBody> shape = CreateCompoundShape();
		return shape;
	}

	return std::nullopt; // Unknown command!
}

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

std::shared_ptr<CBody> CShapeFactory::CreateCompoundShape()
{
	std::shared_ptr<CCompound> compoundShape = std::make_shared<CCompound>();
	std::cout << "Add shapes or CompoundEnd for close compound shape\n\n"
			  << ">>";

	// попробовать перенести цикл в лупер, сделать его дочерним от родительского
	// разделить метод на меньшие функции
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string parseShapeAction;
		strm >> parseShapeAction;

		auto itShapeAction = m_parseShapeActionMap.find(parseShapeAction);
		if (itShapeAction != m_parseShapeActionMap.end())
		{
			try
			{
				std::shared_ptr<CBody> shape = itShapeAction->second(strm);
				compoundShape->AddChildBody(shape);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (parseShapeAction == "CompoundStart")
		{
			try
			{
				std::shared_ptr<CBody> shape = CreateCompoundShape();
				compoundShape->AddChildBody(shape);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (parseShapeAction == "CompoundEnd")
		{
			if (compoundShape->IsEmpty())
			{
				throw std::runtime_error("Compound Shape was not created. Id should contain one or more solid shapes");
			}

			std::cout << "Compound Shape was created" << std::endl;
			return compoundShape;
		}

		if (itShapeAction == m_parseShapeActionMap.end() && parseShapeAction != "CompoundStart")
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}

	return compoundShape;
}
