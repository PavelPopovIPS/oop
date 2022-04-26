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
	std::shared_ptr<CBody> ParseCompoundShape(std::istream& args);

	using CommonHandler = std::function<bool(std::istream& args)>;
	using CommonActionMap = std::map<std::string, CommonHandler>;
	CommonActionMap m_commonActionMap;

	using ParseShapeHandler = std::function<std::shared_ptr<CBody>(std::istream& args)>;
	using ParseShapeActionMap = std::map<std::string, ParseShapeHandler>;
	ParseShapeActionMap m_parseShapeActionMap;

	CParser m_parser;
	CShapeManager m_shapeManager;
};
