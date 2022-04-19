#include "ShapeManager.h"
using namespace std::placeholders;

CShapeManager::CShapeManager()
	: m_actionMap({
		{ "Info", bind(&CShapeManager::Info, this, std::placeholders::_1) },
	})
{
}

void CShapeManager::InitShapeManager()
{
}

void CShapeManager::Info(std::istream& args)
{
}
