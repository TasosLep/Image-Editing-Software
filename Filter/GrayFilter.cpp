#include "GrayFilter.h"

using namespace imaging;

bool GrayFilter::apply(Image & image)
{
	unsigned int width = image.getWidth();
	unsigned int height = image.getHeight();

	if (height > 0 && width > 0)
	{
		for (unsigned i = 0; i < height * width; i++)
		{
			Vec3<float> temp = image.getPixel(i / width, i % width);
			float m = (temp[0] + temp[1] + temp[2]) / 3;
			temp[0] = m;
			temp[1] = m;
			temp[2] = m;
			image.setPixel(i / width, i % width, temp);

		}
	}
	else
		return false;

	return true;
}
