#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <QImage>
#include <QColor>
#include "CustomColor.h"
#include "Configure.h"
#include "vector"

class ImageBuffer
{
public:
	ImageBuffer(int ImageWeight, int ImageHeight);
	QImage DrawPixel(int w, int h, Color color);
	QImage GetImage();
	void ClearImage();
	bool JudgeDepth(int x, int y, float depth);
	void ResetDepth();
	void UpdateColor(int x, int y, Color c);
	void FillColor();

public:
	QImage colorBuffer;
	QColor QDefaultBGColor;
	std::vector<float> DepthBuffer;
	std::vector<Color> color;
	int weight, height;
	int Frequency = 0;//计算调用DrawPixel的次数
	
};

#endif // 

