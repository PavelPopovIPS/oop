// shape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Looper.h"
#include "Parser.h"
#include "ShapeManager.h"

int main()
{
	CParser parser;
	CShapeManager shapeManager;
	CLooper looper(parser, shapeManager);
	looper.Init();

	return 0;
}
