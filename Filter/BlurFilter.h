
#ifndef _BLURFILTER_ 
#define _BLURFILTER_ 

#include "Image.h"
#include "Filter.h"



using namespace imaging;

/*! Class BlurFilter represents the blur filter.
* BlurFilter inherits from the Filter base class and implements the
* apply fuction.This isn't an abstract class.
*/
class BlurFilter : public Filter
{
public:

	/*! This fuction applies the blur filter to an image.
	* It makes the color values of each pixel equal to the average of
	* the 3x3 nearest pixels that are inside the bounds of the image.
	* \param iimage is a reference of the image that we will applly the filter to.
	* \return true or false whether the filter was applied successfully or not.
	*/
	bool apply(Image & image) ;
};

#endif 
