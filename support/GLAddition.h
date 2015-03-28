#pragma once

#include "cocos2d.h"

#include <vector>
#include <fstream>


// to prevent memory leaks
#define XPIXEL_BUFFER	2

namespace glAddition
{
	struct Pixel
	{
		unsigned char rgb[3];
	};

	void										captureRectToTGA(const cocos2d::Rect&, const std::string&);

	Pixel*										readPixels(const cocos2d::Rect&, const std::string&);

	// only TGA for now
	class ImageAnalyzer
	{
	private:
		unsigned char*							imagePixels;

	public:
		ImageAnalyzer();
		~ImageAnalyzer();

		static int								analyzePixels(Pixel*);

		static bool								cvAnalyzeImage(const std::string&);

		// DEPRECATED
		unsigned char*							loadTGA(const std::string&);
	};
}
