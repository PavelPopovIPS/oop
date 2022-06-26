#include "Interface.h"

// ѕр€моугольник, обладающий координатами верхнего левого угла, шириной и высотой
class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(Point& leftUpperCorner, unsigned int width, unsigned int height);
	void Draw(ICanvas& canvas) const override;
	Point GetPoint1() const;
	Point GetPoint2() const;
	Point GetPoint3() const;
	Point GetPoint4() const;

private:
	Point m_leftUpperCorner;
	unsigned int m_width;
	unsigned int m_height;
};
