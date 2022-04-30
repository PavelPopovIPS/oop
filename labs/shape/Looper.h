#pragma once

#include "stdafx.h"
#include "ShapeFactory.h"
#include "ShapeManager.h"

class CLooper
{
public:
	CLooper(CShapeFactory& parser, CShapeManager& manager);
	void Init();

private:
	void PrintUsageInfo();

	using CommonHandler = std::function<bool(std::istream& args)>;
	using CommonActionMap = std::map<std::string, CommonHandler>;
	CommonActionMap m_commonActionMap;

	CShapeFactory m_shapeFactory;
	CShapeManager m_shapeManager;
};
