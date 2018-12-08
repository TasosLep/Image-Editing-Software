#include "BlurFilter.h"

using namespace imaging;

bool BlurFilter::apply(Image & image)
{
	unsigned int width = image.getWidth();
	unsigned int height = image.getHeight();
	Image im = image;

	if (height > 0 && width > 0)
	{

		for (unsigned i = 0; i < width * height; i++)
		{
			int x = i / width;
			int y = i % width;
			Vec3<float> current = im.getPixel(x, y);

			current[0] = 0;
			current[1] = 0;
			current[2] = 0;

			int count = 0;

			for (int m = -1; m <= 1; m++)
			{
				for (int n = -1; n <= 1; n++)
				{
					if (((x + m >= 0) && (x + m < height)) && ((y + n >= 0) && (y + n < width)))
					{
						Vec3<float> temp = im.getPixel(x + m, y + n);
						current += temp;
						count++;
					}
				}
			}
			current[0] /= count;
			current[1] /= count;
			current[2] /= count;
		
			image.setPixel(x, y, current);
		}

	}
	else
		return false;

	return true;

}
