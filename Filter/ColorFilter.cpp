#include "ColorFilter.h"

using namespace imaging;

bool ColorFilter::apply(Image & image)
{
	unsigned int width = image.getWidth();
	unsigned int height = image.getHeight();

	if (height > 0 && width > 0)
	{
		for (unsigned i = 0; i < height * width; i++)
		{
			Vec3<float> temp = image.getPixel(i / width, i % width);
			temp *= rgb;
			image.setPixel(i / width, i % width, temp);
		}
	}
	else
		return false;

	return true;
}

ColorFilter::ColorFilter(Vec3<float> c) : rgb(c) {}
