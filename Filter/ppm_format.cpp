#include "ppm_format.h"
#include "Serializable.h"
#include <string>
#include <fstream>

namespace imaging {
	Image * ReadPPM(const char * filename)
	{
		Image *im = nullptr;
		std::string formatppm;//format of the ppm photo
		int width = 0, height = 0;//dimensions of the photo
		int colorvalue = 0;//maximum color value of the photo
		bool widthfail, heigthfail, colorvaluefail;//checking if we read the width,height,colorvalue right


		std::ifstream readfile(filename, std::ios::in | std::ios::binary);
		if (!readfile)//checking if the file can open or not
		{
			std::cerr << filename << " cannot be opened!" << std::endl;
			return nullptr;
		}

		readfile >> formatppm;//reading the format off ppm photo
		if (formatppm.compare("P6"))
		{
			std::cerr << "Image isn't in P6 format!" << std::endl;
			return nullptr;
		}

		readfile >> width;//reading the width of the ppm photo
		widthfail = readfile.fail();
		readfile >> height;//reading the height of the ppm photo
		heigthfail = readfile.fail();

		if ((widthfail || heigthfail) || (width < 1 || height < 1))
		{
			std::cerr << "Dimensions are not correct!" << std::endl;
			return nullptr;
		}

		im = new Image(width, height);

		readfile >> colorvalue;// reading the color value of the ppm photo
		colorvaluefail = readfile.fail();
		if (colorvaluefail && colorvalue != 255)
		{
			std::cerr << "We only support 24 bit images!" << std::endl;
			return nullptr;
		}

		unsigned char * bufferr = new  unsigned char[width * height * 3];
		readfile.get();
		readfile.read((char *)bufferr, width*height * 3);//reading all the rest bytes
		unsigned j = 0;
		for (unsigned i = 0; i < im->getWidth()*im->getHeight(); i++)
		{
			Vec3<float> temp(bufferr[j] / 255.0f, bufferr[j + 1] / 255.0f, bufferr[j + 2] / 255.0f);//temp contains a specific pixel
																									//which is represented by a Vec3<float>
			im->setPixel(i / width, i % width, temp);//setting specific pixel
			j += 3;
		}
		
		delete[] bufferr;
		readfile.close();//closing the file
		return im;
	}

	bool WritePPM(Image & image, const char * filename)
	{
		std::ofstream writefile(filename, std::ios::out | std::ios::binary);//writing a new file with name 'writefile'
		if (!writefile)
		{
			std::cerr << filename << " cannot be opened!" << std::endl;
			return false;
		}
		//header
		writefile << "P6 ";
		writefile << image.getWidth() << " " << image.getHeight() << " ";
		writefile << "255 ";
		//data segment(bitmap)
		for (unsigned i = 0; i < image.getWidth() * image.getHeight(); i++)
		{
			Vec3<float> temp = image.getPixel(i / image.getWidth(), i % image.getWidth());//temp contains a specific pixel
																					      //which is represented by a Vec3<float>
			writefile << (unsigned char)(temp[0] * 255.0f);
			writefile << (unsigned char)(temp[1] * 255.0f);
			writefile << (unsigned char)(temp[2] * 255.0f);
		}
		writefile.close();//closing the file
		return true;
	}
}