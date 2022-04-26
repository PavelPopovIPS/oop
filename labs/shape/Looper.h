#pragma once

#include "stdafx.h"
#include "Parser.h"
#include "ShapeManager.h"

class CLooper
{
public:
	CLooper(CParser& parser, CShapeManager& manager);
	void Init();

private:
	void PrintUsageInfo();

	using CommonHandler = std::function<bool(std::istream& args)>;
	using CommonActionMap = std::map<std::string, CommonHandler>;
	CommonActionMap m_commonActionMap;

	CParser m_parser;
	CShapeManager m_shapeManager;
};
