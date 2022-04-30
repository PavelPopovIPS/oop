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
	std::shared_ptr<CBody> InitCompoundShapeLooper();
	void PrintUsageInfo();

	using CommonHandler = std::function<bool(std::istream& args)>;
	using CommonActionMap = std::map<std::string, CommonHandler>;
	CommonActionMap m_commonActionMap;

	using ParseShapeHandler = std::function<std::shared_ptr<CBody>(std::istream& args)>;
	using ParseShapeActionMap = std::map<std::string, ParseShapeHandler>;
	ParseShapeActionMap m_createShapeActionMap;

	CShapeFactory m_shapeFactory;
	CShapeManager m_shapeManager;
};
