#ifndef _DIFFFILTER_ 
#define _DIFFFILTER_ 

#include "Image.h"
#include "Filter.h"


using namespace imaging;

/*! Class DiffFilter represents the diff filter.
* DiffFilter inherits from the Filter base class and implements the
* apply fuction.This isn't an abstract class.
*/
class DiffFilter : public Filter
{
public:

	/*! This fuction applies the diff filter to an image.
	* It makes the color values of each pixel equal to the difference between the maximum and
	* the minimum color values of the nearest 3x3 pixels that are inside the bounds of the image.
	* \param image is a reference of the image that we will applly the filter to.
	* \return true or false whether the filter was applied successfully or not.
	*/
	
	bool apply(Image & image);
};

#endif 
