#include "support\AppLib.h"

USING_NS_CC;

double	geo::Line::length(const Point* a, const Point* b)
{
	return sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}

Rect	geo::getFloorBox(const Rect* boundingBox)
{
	return Rect(boundingBox->getMinX(), boundingBox->getMinY(),
		boundingBox->getMidX() - boundingBox->getMinX(), (boundingBox->getMidY() - boundingBox->getMinY()) * 2 / 3);
}
