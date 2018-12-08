#include "MedianFilter.h"
#include <vector>
#include <algorithm>

using namespace imaging;

bool MedianFilter::apply(Image & image)
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

			std::vector<float> r;
			std::vector<float> g;
			std::vector<float> b;

			for (int m = -1; m <= 1; m++)
			{
				for (int n = -1; n <= 1; n++)
				{
					if (((x + m >= 0) && (x + m < height)) && ((y + n >= 0) && (y + n < width)))
					{
						Vec3<float> temp = im.getPixel(x + m, y + n);
						r.push_back(temp[0]);
						g.push_back(temp[1]);
						b.push_back(temp[2]);

					}
				}
			}
			std::sort(r.begin(), r.end());
			std::sort(g.begin(), g.end());
			std::sort(b.begin(), b.end());
			Vec3<float> current((r[r.size()/2]), (g[g.size()/2]), (b[b.size()/2]));

			image.setPixel(x, y, current);
		}

	}
	else
		return false;

	return true;

}

