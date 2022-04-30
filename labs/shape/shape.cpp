// shape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Looper.h"
#include "ShapeFactory.h"
#include "ShapeManager.h"

int main()
{
	CShapeFactory shapeFactory;
	CShapeManager shapeManager;
	CLooper looper(shapeFactory, shapeManager);
	looper.Init();

	return 0;
}
