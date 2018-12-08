//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2015 - 2016
//
//

#ifndef _IMAGE
#define _IMAGE

#include "Serializable.h"
#include "Vec3.h"
#include "Array.h"

using namespace math;
/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
namespace imaging
{

//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Image class alone does not provide 
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure. 
	 *
	 * The internal buffer of an image object stores the actual r,g,b values of the color image as
	 * a contiguous sequence of Vec3<float> objects. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Vec3<float>).
	 *
	 * All values stored in each Vec3<float> memory buffer are floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 *
	 * \see Vec3<float>
	 */ 
	class Image : public Serializable,public Array<Vec3<float>>
	{
	public:
		enum channel_t {RED=0,GREEN, BLUE};//! You can use the names RED, GREEN, BLUE instead of 0,1,2 to access individual Color channels.		                                             
	public:
		//override the pure virtual functions of the Serializable base class
		bool operator << (std::string filename);
		bool operator >> (std::string filename);

		// data accessors
		/*! Obtains the color of the image at location (x,y).
		 *
		 *  The method should do any necessary bounds checking. 
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get. 
		 *  \param y is the (zero-based) vertical index of the pixel to get. 
		 *
		 *  \return The color of the (x,y) pixel as a Vec3<float> object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		Vec3<float> getPixel(unsigned int x, unsigned int y) const;

		// data mutators
		
		/*! Sets the RGB values for an (x,y) pixel.
		 * 
		 *  The method should perform any necessary bounds checking.
		 *  
		 *  \param x is the (zero-based) horizontal index of the pixel to set. 
		 *  \param y is the (zero-based) vertical index of the pixel to set. 
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setPixel(unsigned int x, unsigned int y, Vec3<float> & value);
		                                                         
		/*! Copies the image data from an external raw buffer to the internal image buffer. 
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the 
		 *  Image object and that the data buffer has been alreeady allocated. If the image buffer is not allocated or the 
		 *  width or height of the image are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		 */

		void setData(const Vec3 <float> * & data_ptr);
		
		// constructors and destructor
		/*! Default constructor.
		 * 
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Image();											     	
		
		/*! Constructor with width and height specification.
		 * 
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */ 
		Image(unsigned int width, unsigned int height);
		
		/*! Constructor with data initialization.
		 * 
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 * 
		 * \see setData
		 */ 
		Image(unsigned int width, unsigned int height, const Vec3 <float> * data_ptr);
		
		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Image(const Image &src);
		
		/*! The Image destructor.
		 */
		~Image();

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Image & operator = (const Image & right);

	};

} //namespace imaging

#endif
