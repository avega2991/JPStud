#pragma once

#include "cocos2d.h"

#include <vector>
#include <fstream>
#include <cmath>


// to prevent memory leaks
#define XPIXEL_BUFFER			2

#define COLOR_WHITE				false
#define COLOR_BLACK				true

typedef int						KANJI_ID;
typedef bool					MONOCHROME_COLOR;


namespace glAddition
{
	struct Pixel
	{
		unsigned short rgb[3];
	};

	void												captureRectToTGA(const cocos2d::Rect&, const std::string& filename);

	std::vector<Pixel>									readPixels(const cocos2d::Rect&);
	void												savePixels(const cocos2d::Rect&, const std::string& filename);
	std::vector<std::vector<MONOCHROME_COLOR>>			loadMonochromeMatrixFromFile(const std::string& filename);

	std::vector<std::vector<MONOCHROME_COLOR>>			pixelsToMonochromeMatrix(const std::vector<Pixel>, const int sectorCountInLine);
}
