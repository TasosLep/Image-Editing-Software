#ifndef _COLORFILTER_
#define _COLORFILTER_


#include  "Array.h"
#include "Image.h"
#include "Filter.h"

using namespace imaging;

/*! Class ColorFilter represents the color filter.
* ColorFilter inherits from the Filter base class and implements the
* apply fuction.This isn't an abstract class.
*/
class ColorFilter : public Filter
{
	public:

		/*! This fuction applies the color filter to an image.
		* It makes the color values of each pixel equal to the multiple between 
		* the rgb values corresponding to the input color.
		* \param image is a reference of the image that we will applly the filter to.
		* \return true or false whether the filter was applied successfully or not. 
		*/
		bool apply(Image & image);

		/*! Constructor with the input color.
		*/
		ColorFilter(Vec3<float> c);

	private:

		//! Input color r,g,b values.
		Vec3<float> rgb;
};

#endif
