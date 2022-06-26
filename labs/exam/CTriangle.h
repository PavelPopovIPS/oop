#include "Interface.h"

// Треугольник, задается координатами трех вершин
class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(Point& p1, Point& p2, Point& p3);
	void Draw(ICanvas& canvas) const override;

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};
