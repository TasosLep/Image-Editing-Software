//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include "Array.h"
#include <cstring>//memcpy

namespace math
{

	//--------------------------------------------------------------------------------------------
	// This file is included from the templated Array class header.
	// TODO: Provide its member function implementations here:
	//--------------------------------------------------------------------------------------------

	//implementation
	template<typename T>
	void * const Array<T>::getRawDataPtr()
	{
		return buffer;
	}

	template<typename T>
	T & Array<T>::operator () (int x, int y)
	{
		return buffer[width*x + y];
	}

	template<typename T>
	const T & Array<T>::operator () (int x, int y) const
	{
		return buffer[width*x + y];
	}

	template<typename T>
	Array<T>::Array(unsigned int w, unsigned int h)
		:buffer(new T[w*h]),width(w), height(h) {}

	template<typename T>
	Array<T>::Array(const Array<T> & source)
		:width(source.width),height(source.height)
	{
		buffer = new T[width * height];
		//deep copy of the data
		memcpy(buffer,source.buffer,sizeof(T)*width*height); 
	}

	//destructor
	template<typename T>
	Array<T>::~Array()
	{
		if (buffer != nullptr)
		{
			delete[] buffer;
			buffer = nullptr;
		}
	}

	//copy assignement operator
	template<typename T>
	Array<T> & Array<T>::operator = (const Array<T> & source)
	{
		if (source == *this) return *this;
		if (buffer != nullptr) delete[] buffer;
		width = source.width;
		height = source.height;
		buffer = new T[width*height];
		memcpy(buffer, source.buffer, sizeof(T)*width*height);
		return *this;
	}

	template<typename T>
	bool Array<T>::operator == (const Array<T> & right) const
	{
		if (width != right.width || height != right.height)return false;
		
		for (unsigned i = 0; i < width*height; ++i)
			if (buffer[i] != right.buffer[i]) return false;
		return true;
	}

	template<typename T>
	//use memset and default initializer
	void Array<T>::resize(unsigned int new_width, unsigned int new_height)
	{
		T *new_buffer = new T[new_width*new_height];//the new buffer
		if (width == 0 && height == 0)//not yet allocated
		{

			width = new_width;
			height = new_height;
			buffer = new_buffer;
			return;
		}
		else if (new_width <= width && new_height <= height)
		{
			//make the new_buffer black
			for (unsigned i = 0; i < new_height*new_width; ++i)
				new_buffer[i] = T();//default initializer
			//copy the correct bytes from the old buffer to the new one
			for (unsigned i = 0; i < new_height; ++i)
				memcpy(new_buffer+i*new_width,buffer+i*width, new_width*sizeof(T));
		}
		else if (new_width <= width && new_height>height)
		{
			//make the new_buffer black
			for (unsigned i = 0; i < new_width*new_height; ++i)
				new_buffer[i] = T();//default initializer
			//copy the correct bytes from the old buffer to the new one
			for (unsigned i = 0; i < height; ++i)
				memcpy(new_buffer + i*new_width, buffer + i*width, new_width*sizeof(T));
		}
		else if (new_width > width && new_height <= height)
		{
			//make the new_buffer black
			for (unsigned i = 0; i < new_height*new_width; ++i)
				new_buffer[i] = T();//default initializer
			//copy the correct bytes from the old buffer to the new one
			for (unsigned i = 0; i < new_height; ++i)
				memcpy(new_buffer + i*new_width, buffer + i*width, width*sizeof(T));
		}
		else if (new_width > width && new_height > height)
		{
			//make the new_buffer black
			for (unsigned i = 0; i < new_height*new_width; ++i)
				new_buffer[i] = T();//default initializer
			//copy the correct bytes from the old buffer to the new one	
			for (unsigned i = 0; i < height; ++i)
				memcpy(new_buffer + i*new_width, buffer + i*width, width*sizeof(T));

		}



		//change width, height and replace the old buffer
		width = new_width;
		height = new_height;
		delete[] buffer;
		buffer = new_buffer;
	}
	
} // namespace math

#endif
