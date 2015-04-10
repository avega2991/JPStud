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

std::vector<Pixel>	glAddition::readPixels(const cocos2d::Rect& area)
{
	GLint width = area.size.width;
	GLint height = area.size.height;

	int imageSize = width * height * 3 * XPIXEL_BUFFER;

	// Массив данных будущего изображения
	// Выделяем необходимую память: ширина * высота * 3 цветовых бита
	unsigned char* imageBuffer = new unsigned char[imageSize];
	memset(imageBuffer, 0, imageSize);

	// Для получения данных экрана используем функцию glReadPixels:
	glReadPixels(area.getMinX(), area.getMinY(), width, height,
		GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);

	std::vector<Pixel> pixelsVector;

	// int pixelNum = 0;
	Pixel pixel;
	for (long i = 0; i <= imageSize / XPIXEL_BUFFER; i++)
	{
		if (!(i % 3) && (i != 0))
		{
			pixelsVector.push_back(pixel);
			// pixelNum++;
		}

		pixel.rgb[i % 3] = imageBuffer[i];
	}

	return pixelsVector;
}

void	glAddition::savePixels(const cocos2d::Rect& area, const std::string& filename)
{
	std::ofstream output("dictionaries/kanji_origins/" + filename);
	std::vector<Pixel> pixels = readPixels(area);
	std::vector<std::vector<MONOCHROME_COLOR>> monochromeMatrix = pixelsToMonochromeMatrix(pixels, 15);

	// TODO : SAVE PIXEL MATRIX INTO BINFILE
	for (std::vector<std::vector<MONOCHROME_COLOR>>::iterator it_mtx = monochromeMatrix.begin(); it_mtx != monochromeMatrix.end(); it_mtx++)
	{
		for (std::vector<MONOCHROME_COLOR>::iterator it_line = (*it_mtx).begin(); it_line != (*it_mtx).end(); it_line++)
		{
			output << *it_line;
		}
		output << "\n";
	}
	//
}

std::vector<std::vector<MONOCHROME_COLOR>>	glAddition::loadMonochromeMatrixFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	std::vector<std::vector<MONOCHROME_COLOR>> monochromeMatrix;

	while (!inputFile.eof())
	{
		std::string inputString;
		std::getline(inputFile, inputString);

		if (inputString[0] < '0' || inputString[0] > '9')
			break;

		std::vector<MONOCHROME_COLOR> matrixLine;
		for (int i = 0; i < inputString.size(); i++)
		{
			bool sign = inputString[i] - '0';
			matrixLine.push_back(sign);
		}

		monochromeMatrix.push_back(matrixLine);
		matrixLine.clear();
	}

	return monochromeMatrix;
}

std::vector<std::vector<MONOCHROME_COLOR>>	glAddition::pixelsToMonochromeMatrix(const std::vector<Pixel> pixelsVector, const int sectorCountInLine)
{
	int imageWidthAndHeight = sqrt(pixelsVector.size());

	// <PIXELVECTOR_TO_PIXELMATRIX>
	std::vector<std::vector<Pixel>> pixelsMatrix;
	for (long i = 0; i < imageWidthAndHeight; i++)
	{
		std::vector<Pixel> pixelsLine;
		for (long j = 0; j < imageWidthAndHeight; j++)
		{
			pixelsLine.push_back(pixelsVector[(i * imageWidthAndHeight) + j]);
		}
		pixelsMatrix.push_back(pixelsLine);
		pixelsLine.clear();
	}
	// </PIXELVECTOR_TO_PIXELMATRIX>


	// <PIXELMATRIX_TO_MONOCHROME_MATRIX>
	std::vector<std::vector<MONOCHROME_COLOR>> monochromeMatrix;
	for (std::vector<std::vector<Pixel>>::iterator it_mtx = pixelsMatrix.begin(); it_mtx != pixelsMatrix.end(); it_mtx++)
	{
		for (std::vector<Pixel>::iterator it_line = it_mtx->begin(); it_line != it_mtx->end(); it_line++)
		{

		}
	}

	int sectorSize = imageWidthAndHeight / sectorCountInLine;
	for (int i = 0; i < sectorCountInLine; i++)
	{
		std::vector<MONOCHROME_COLOR> monochromeMatrixLine;
		for (int j = 0; j < sectorCountInLine; j++)
		{
			// <HANDLE_THE_SECTOR>
			long blackPixels = 0;
			for (int x = (i * sectorSize); x < (i * sectorSize) + sectorSize; x++)
			{
				for (int y = (j * sectorSize); y < (j * sectorSize) + sectorSize; y++)
				{
					// <CHECK_SECTORS_PIXEL>
					if (pixelsMatrix[x][y].rgb[0] < 32)
					{
						blackPixels++;
					}
					// </CHECK_SECTORS_PIXEL>
				}
			}
			MONOCHROME_COLOR sectorColor = COLOR_WHITE;
			if (blackPixels >= (sectorSize * sectorSize) / 2)
			{
				sectorColor = COLOR_BLACK;
			}
			monochromeMatrixLine.push_back(sectorColor);
			// </HANDLE_THE_SECTOR>
		}
		monochromeMatrix.push_back(monochromeMatrixLine);
	}
	// </PIXELMATRIX_TO_MONOCHROME_MATRIX>

	return monochromeMatrix;
}
