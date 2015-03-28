#include "support\AppLib.h"

USING_NS_CC;

double	geo::Line::length(const Point* a, const Point* b)
{
	return sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}

std::vector<std::vector<bool>>	math::Matrix::substract(std::vector<std::vector<bool>> firstMtx,
	std::vector<std::vector<bool>> secondMtx)
{
	int mtxHeight = firstMtx.size();
	int mtxWidth = firstMtx.front().size();
	std::vector<std::vector<bool>> mtxResult;

	int i = 0;
	while (i < mtxWidth)
	{
		int j = 0;
		std::vector<bool> mtxLine;
		while (j < mtxHeight)
		{
			mtxLine.push_back(abs((int)firstMtx[i][j] - (int)secondMtx[i][j]));
			j++;
		}
		mtxResult.push_back(mtxLine);
		mtxLine.clear();

		i++;
	}

	return mtxResult;
}

Rect	geo::getFloorBox(const Rect* boundingBox)
{
	return Rect(boundingBox->getMinX(), boundingBox->getMinY(),
		boundingBox->getMidX() - boundingBox->getMinX(), (boundingBox->getMidY() - boundingBox->getMinY()) * 2 / 3);
}
