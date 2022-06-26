#include "stdafx.h"
#include "CCanvas.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "Interface.h"

using namespace std;
const int var = 4;
// Рисует картину picture на холсте canvas
void DrawPicture(ICanvas& canvas, const vector<shared_ptr<const ICanvasDrawable>>& picture)
{
	for (auto element : picture)
	{
		element->Draw(canvas);
	}
}

void Fn()
{
	int n = 42;
}

int main()
{
	Point leftUpperCorner = { 0, 5 };
	unsigned int width = 5;
	unsigned int height = 5;
	shared_ptr<const ICanvasDrawable> rectangle = make_shared<CRectangle>(leftUpperCorner, width, height);

	Point p1 = { 0, 5 };
	Point p2 = { 2, 8 };
	Point p3 = { 5, 5 };
	shared_ptr<const ICanvasDrawable> triangle = make_shared<CTriangle>(p1, p2, p3);

	vector<shared_ptr<const ICanvasDrawable>> picture;
	picture.push_back(rectangle);
	picture.push_back(triangle);

	CCanvas canvas;
	DrawPicture(canvas, picture);

	const CRectangle r{ leftUpperCorner, width, height };
	r.Draw(canvas);

	return 0;
}
