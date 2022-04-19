#pragma once

#include "stdafx.h"
#include "Body.h"

class CShapeManager
{
public:
	CShapeManager();
	void InitShapeManager();
	bool Info(std::istream&);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;

	bool SetSphereToCollection(std::istream& args);
	std::vector<std::shared_ptr<CBody>> m_shapeCollection;
};
