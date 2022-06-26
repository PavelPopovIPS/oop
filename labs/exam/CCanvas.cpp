#include "stdafx.h"
#include "CCanvas.h"

void CCanvas::DrawLine(int x0, int y0, int x1, int y1)
{
	std::cout << " DrawLine: ";
	std::cout << "(<" << x0 << ">, ";
	std::cout << "<" << y0 << ">) - ";
	std::cout << "(<" << x1 << ">, ";
	std::cout << "<" << y1 << ">)" << std::endl;
}
