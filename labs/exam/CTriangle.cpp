#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(Point& p1, Point& p2, Point& p3)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_p1.x, m_p1.y, m_p2.x, m_p2.y);
	canvas.DrawLine(m_p2.x, m_p2.y, m_p3.x, m_p3.y);
	canvas.DrawLine(m_p3.x, m_p3.y, m_p1.x, m_p1.y);
}
