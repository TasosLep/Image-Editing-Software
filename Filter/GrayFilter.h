#ifndef _GRAYFILTER_
#define _GRAYFILTER_

#include  "Array.h"
#include "Image.h"
#include "Filter.h"


using namespace imaging;

/*! Class GrayFilter represents the gray filter.
* GrayFilter inherits from the Filter base class and implements the
* apply fuction.This isn't an abstract class.
*/
class GrayFilter : public Filter
{
	public:

		/*! This fuction applies the gray filter to an image.
		* It makes the color values of each pixel equal to the average of the three color values
		* \param image is the reference of the image that we must applly the filter to.
		* \return true or false whether the filter was applied successfully or not.
		*/
		bool apply(Image & image);

};

#endif
