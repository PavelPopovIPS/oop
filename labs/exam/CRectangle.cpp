#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(Point& leftUpperCorner, unsigned int width, unsigned int height)
	: m_leftUpperCorner(leftUpperCorner)
	, m_width(width)
	, m_height(height)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetPoint1().x, GetPoint1().y, GetPoint2().x, GetPoint2().y);

	canvas.DrawLine(GetPoint1().x, GetPoint1().y, GetPoint3().x, GetPoint3().y);

	canvas.DrawLine(GetPoint3().x, GetPoint3().y, GetPoint4().x, GetPoint4().y);

	canvas.DrawLine(GetPoint2().x, GetPoint2().y, GetPoint4().x, GetPoint4().y);
}

Point CRectangle::GetPoint1() const
{
	return {
		m_leftUpperCorner.x,
		m_leftUpperCorner.y
	};
}

Point CRectangle::GetPoint2() const
{
	return {
		m_leftUpperCorner.x + static_cast<int>(m_width),
		m_leftUpperCorner.y
	};
}

Point CRectangle::GetPoint3() const
{
	return {
		m_leftUpperCorner.x,
		m_leftUpperCorner.y - static_cast<int>(m_height)
	};
}

Point CRectangle::GetPoint4() const
{
	return {
		m_leftUpperCorner.x + static_cast<int>(m_width),
		m_leftUpperCorner.y - static_cast<int>(m_height)
	};
}
