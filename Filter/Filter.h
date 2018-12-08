
#ifndef _FILTER_ 
#define _FILTER_ 


#include "Image.h"

/*! Interface for ppm image filters.
* Provides a pure virtual function called apply.Each Derived class
* must override/implement the apply function.
*/
using namespace imaging;
class Filter
{
	public :

		/*! Pure virtual function.
		* \param image is a reference of the image that we will applly the filter to.
		* \return true or false whether the filter was applied successfully or not. 
		*/
		virtual bool apply (Image & image) = 0 ;
}; 

#endif 
