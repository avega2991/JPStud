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

std::vector<std::vector<bool>>	math::Matrix::shiftMatrixToCenterOfMass(std::vector<std::vector<bool>> mtx,
	std::pair<int, int> centerOfMass)
{
	std::pair<int, int> mtxCenterOfMass = math::Matrix::findCenterOfMass(mtx);
	int rows = mtx.size();
	int cols = mtx.front().size();
	int xShift = centerOfMass.first - mtxCenterOfMass.first;
	int yShift = centerOfMass.second - mtxCenterOfMass.second;

	// <INIT_RESULT_MTX>
	std::vector<std::vector<bool>> resultMtx;
	for (int i = 0; i < cols; i++)
	{
		std::vector<bool> row(cols);
		resultMtx.push_back(row);
	}
	// </INIT_RESULT_MTX>

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int newX = i - xShift;
			int newY = j - yShift;
			if ((i - xShift) >= 0 && (i - xShift) < rows
				&& (j - yShift) >= 0 && (j - yShift) < cols)
			{
				resultMtx[i][j] = mtx[i - xShift][j - yShift];
			}
			else
			{
				resultMtx[i][j] = 0;
			}
		}
	}

	return resultMtx;
}

std::pair<int, int>	math::Matrix::findCenterOfMass(std::vector<std::vector<bool>> mtx)
{
	int rows = mtx.size();
	int cols = mtx.front().size();
	double xC = 0;
	double yC = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			xC += (i + 1) * mtx[i][j];
			yC += (j + 1) * mtx[i][j];
		}
	}

	xC /= rows;
	yC /= cols;
	
	return std::pair<int, int>(ceil(xC), ceil(yC));
}