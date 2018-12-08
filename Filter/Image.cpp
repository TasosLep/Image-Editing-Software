
#include "Image.h"
#include <cstring>//for memcopy
#include <fstream>
#include "ppm_format.h"

namespace imaging
{
	Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const
	{
		//check if x,y are in bounds
		return (x >= 0 && x < height && y >= 0 && y < width) ? Array<Vec3<float>>::operator()(x,y) : Vec3<float>();
	}

	void Image::setPixel(unsigned int x, unsigned int y, Vec3<float> & value)
	{
		if (x >= 0 && x < height && y >= 0 && y < width)
		{
			Array<Vec3<float>>::operator()(x,y) = value;
		}
	}

	//deep copy
	void Image::setData(const Vec3 <float> * & data_ptr)
	{

		if (width == 0 || height == 0 || buffer == nullptr)return;
		delete[] buffer;
		//asume that the buffer has the correct size
		buffer = new Vec3<float>[width*height];
		memcpy(buffer,data_ptr,width*height*sizeof(Vec3<float>));
	}

	//Constructors
	Image::Image()//dafault
		:Array<Vec3<float>>(0,0) {}

	Image::Image(unsigned int width, unsigned int height)
		:Array<Vec3<float>>(width,height){}

	Image::Image(unsigned int width, unsigned int height, const Vec3 <float> * data_ptr)
		: Array<Vec3<float>>(width,height)
	{
		setData(data_ptr);
	}

	//Copy Constructor
	Image::Image(const Image &src)
		:Array<Vec3<float>>(src)
	{
	}

	//Destructor
	Image::~Image()
	{
		//nothing
	}

	//Copy assignment operator
	Image & Image::operator =(const Image & right)
	{
		if (right == *this) return *this;
		Array<Vec3<float>>::operator=(right);
		return *this;
	}

	bool Image :: operator << (std::string filename)
	{
		Image *read = nullptr;
		read = ReadPPM(filename.c_str());//creating an Image object
		if (read != nullptr)
		{
			*this = *read;
			delete read;
			return true;//if the ReadPPM was successful run return true
		}
		return false;
	}

	bool Image :: operator >> (std::string filename)
	{
		return WritePPM(*this, filename.c_str());//if the WritePPM was successful run return true,or else return false
	}
}
