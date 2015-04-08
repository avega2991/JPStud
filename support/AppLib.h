#pragma once

#include "cocos2d.h"

#include <math.h>


namespace applib
{
	// TODO : REPLACE ALL WITHIN
}

namespace geo
{
	class Line
	{
	public:
		static double								length(const cocos2d::Point*, const cocos2d::Point*);
	};

	cocos2d::Rect									getFloorBox(const cocos2d::Rect*);
	int												getFloorOY(const cocos2d::Rect*);
}

namespace math
{
	class Matrix
	{
	public:
		static std::vector<std::vector<bool>>			substract(std::vector<std::vector<bool>> firstMtx, std::vector<std::vector<bool>> secondMtx);
	};
}

template<typename T1, typename T2, typename T3>
class Triad
{
public:
	T1 first;
	T2 second;
	T3 third;

public:
	Triad()
	{};

	Triad(T1 _first, T2 _second, T3 _third) : first(_first), second(_second), third(_third)
	{};

};