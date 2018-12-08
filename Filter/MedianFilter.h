
#ifndef _MEDIANFILTER_ 
#define _MEDIANFILTER_ 

#include "Image.h"
#include "Filter.h"

using namespace imaging;

/*! Class MedianFilter represents the median filter.
* MedianFilter inherits from the Filter base class and implements the
* apply fuction.This isn't an abstract class.
*/
class MedianFilter : public Filter
{
public:

	/*! This fuction applies the filter to an image.
	* It makes the color values of each pixel equal to the medium 
	* of the nearest 3x3 pixels that are inside the bounds of the image.
	* \param image is the reference of the image that we must applly the filter to.
	* \return true or false whether the filter was applied successfully or not.
	*/
	bool apply(Image & image);
};

#endif 
