#pragma once

#include "stdafx.h"
#include "Body.h"

class CShapeManager
{
public:
	CShapeManager();
	void InitShapeManager();
	void Info(std::istream& args);

private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;
};
