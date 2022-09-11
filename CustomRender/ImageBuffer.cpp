#include "ImageBuffer.h"

ImageBuffer::ImageBuffer(int ImageWeight,int ImageHeight)
	:colorBuffer(ImageWeight,ImageHeight, QImage::Format_RGB888), DepthBuffer(ImageWeight*ImageHeight),
	weight(ImageWeight),height(ImageHeight),color(ImageWeight* ImageHeight)

{
	QDefaultBGColor = QColor(DefaultBGColor.r * 255.f, DefaultBGColor.g * 255.f, DefaultBGColor.b * 255.f);
	colorBuffer.fill(QDefaultBGColor);
	
	std::fill(DepthBuffer.begin(), DepthBuffer.end(),101.f);
	std::fill(color.begin(), color.end(), DefaultBGColor);
	

}



QImage ImageBuffer::DrawPixel(int w, int h, Color color)
{
	Frequency++;
	colorBuffer.setPixelColor(w, h, QColor(color.r*255.f,color.g*255.f,color.b*255.f));
	return colorBuffer;
}

QImage ImageBuffer::GetImage()
{
	return colorBuffer;
}

void ImageBuffer::ClearImage()
{
	colorBuffer.fill(QDefaultBGColor);

}

bool ImageBuffer::JudgeDepth(int x, int y, float depth)
{
	if (x + (y * weight) >= weight * height)
	{
		return false;
	}

	if (DepthBuffer[x+(y*weight)]>depth)
	{
		DepthBuffer[x + (y * weight)] = depth;
		return true;
	}
	return false;
}

void ImageBuffer::ResetDepth()
{
	std::fill(DepthBuffer.begin(), DepthBuffer.end(),101.f);
	std::fill(color.begin(), color.end(), DefaultBGColor);

	Frequency = 0;
}

void ImageBuffer::UpdateColor(int x, int y, Color c)
{
	if (x + (y * weight) >= weight * height)
	{
		return ;
	}
	color[x +( y * weight)] = c;
	
}

void ImageBuffer::FillColor()
{
	for (int i = 0; i < weight; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i + (j * weight) >= weight * height)
			{
				return;
			}
			if (color[i + (j * weight)] != DefaultBGColor)
			{
				DrawPixel(i, j, color[i + (j * weight)]);
			}
		}
	}
}

