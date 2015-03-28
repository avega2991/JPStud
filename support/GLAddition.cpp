#include "support\GLAddition.h"

using namespace glAddition;


void	glAddition::captureRectToTGA(const cocos2d::Rect& area, const std::string& filename)
{
	GLint width = area.size.width;
	GLint height = area.size.height;

	int imageSize = width * height * 3 * 3;

	// Массив данных будущего изображения
	// Выделяем необходимую память: ширина*высота*3 цветовых бита
	unsigned char* imageBuffer = new unsigned char[imageSize];
	memset(imageBuffer, 0, imageSize);

	// Для получения данных экрана используем функцию glReadPixels:
	glReadPixels(area.getMinX(), area.getMinY(), width, height,
		GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);
	
	//
	// Теперь нужно записать полученные данные в файл .tga.
	//
	
	FILE *sFile = 0;        // Дескриптор файла
	
	// Обьявляем переменные, которые понадобятся нам в дальнейшем:
	unsigned char tgaHeader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char header[6];
	unsigned char bits = 0;
	int colorMode = 0;
	unsigned char tempColors = 0;
	
	// Открываем файл скриншота
	sFile = fopen(filename.c_str(), "wb");
	
	// Устанавливаем цветовой режим и глубину цвета:
	colorMode = 3;
	bits = 24;
	
	// Записываем ширину и высоту:
	header[0] = width % 256;
	header[1] = width / 256;
	header[2] = height % 256;
	header[3] = height / 256;
	header[4] = bits;
	header[5] = 0;
	
	// Записываем хидеры в начало файла:
	fwrite(tgaHeader, sizeof(tgaHeader), 1, sFile);
	fwrite(header, sizeof(header), 1, sFile);
	
	// Поскольку в формате TGA цвета хранятся не в RGB, а в BRG, нам нужно
	// поменять местами наши данные:
	for (int i = 0; i < width * height * colorMode; i += colorMode)
	{
		tempColors = imageBuffer[i];
		imageBuffer[i] = imageBuffer[i + 2];
		imageBuffer[i + 2] = tempColors;
	}
	
	// Записываем данные изображения:
	fwrite(imageBuffer, width * height * colorMode, 1, sFile);
	
	// Закрываем файл
	fclose(sFile);
	// Удаляем ненужные теперь данные
	delete[] imageBuffer;
}

Pixel*	glAddition::readPixels(const cocos2d::Rect& area, const std::string& filename)
{
	GLint width = area.size.width;
	GLint height = area.size.height;

	int imageSize = width * height * 3 * XPIXEL_BUFFER;

	// Массив данных будущего изображения
	// Выделяем необходимую память: ширина*высота*3 цветовых бита
	unsigned char* imageBuffer = new unsigned char[imageSize];
	memset(imageBuffer, 0, imageSize);

	// Для получения данных экрана используем функцию glReadPixels:
	glReadPixels(area.getMinX(), area.getMinY(), width, height,
		GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);

	Pixel* imagePixelated = new Pixel[width * height];

	int pixelNum = 0;
	for (long i = 0; i < imageSize / XPIXEL_BUFFER; i++)
	{
		if (!(i % 3) && (i != 0))
			pixelNum++;

		imagePixelated[pixelNum].rgb[i % 3] = imageBuffer[i];
	}

	return imagePixelated;
}

int	glAddition::ImageAnalyzer::analyzePixels(Pixel* pPixels)
{
	// TODO
	const int width = 240, height = 240;
	long imageSize = width * height;

	long blackPixels = 0;
	
	Pixel maxPixel = pPixels[0];
	long maxCount = 1;

	// put [] pixel array into [][]
	Pixel image[width][height];
	
	for (long i = 0; i < width; i++)
	{
		for (long j = 0; j < height; j++)
			image[i][j] = pPixels[(i * height) + j];
	}
	//

	// count black pixels (for now only)
	// CHECK BY SECTORS!!!
	const int sectorCount = 10;
	bool bSector[sectorCount][sectorCount]; // false = white, true = black

	for (int i = 0; i < sectorCount; i++)
	{
		for (int j = 0; j < sectorCount; j++)
		{
			// handle sector
			long blackPixels = 0;

			for (int x = (i * 24); x < (i * 24) + 24; x++)
			{
				for (int y = (j * 24); y < (j * 24) + 24; y++)
				{
					//handle pixel
					bool blackPixel = true;

					for (char k = 0; k < 3; k++)
					{
						if (image[x][y].rgb[k] > 40)
						{
							blackPixel = false;
							break;
						}
					}

					if (blackPixel)
						blackPixels++;
					//
				}
			}
			//

			if (blackPixels > (width / sectorCount) * (height / sectorCount) / 2)
				bSector[i][j] = true;
		}
	}

	// analyze sectors and construct output
	// for every ethalon compare sectors and output all approximately equals

	//

	return NULL;
}

bool	glAddition::ImageAnalyzer::cvAnalyzeImage(const std::string& filename)
{
	return true;
}

unsigned char*	glAddition::ImageAnalyzer::loadTGA(const std::string& filename)
{
	//TODO IF COULDN'T ANALYZE WITHOUT IT
	return nullptr;
}
