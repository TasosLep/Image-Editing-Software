//Μάριος Προκοπάκης, p3150141
//Αναστάσιος Λεπίπας, p3150091

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "ppm_format.h"
#include "GrayFilter.h"
#include "ColorFilter.h"
#include "BlurFilter.h"
#include "DiffFilter.h"
#include "MedianFilter.h"

using namespace std;
using namespace imaging;

double averagecolor(unsigned int num, Image * img);

int main(int argc, char* argv[])
{
	//filters
	GrayFilter gray;
	BlurFilter blur;
	DiffFilter diff;
	MedianFilter med;
	//empty image file
	Image * userinputimage = new Image(0, 0);//initializing a pointer

	if (argc > 1)//checking if the user gave me the filename of the file from the terminal 
	{
		*userinputimage << argv[argc - 1];
		string s = argv[argc - 1];
		size_t dot_index = s.find(".");
		if (dot_index == string::npos)
		{
			std::cout << "Invalid image!\n";
			return 0;
		}
		s = s.substr(0, dot_index);
		string p = ".filtered.ppm";
		s += p;
		cout << "Please wait to check the arguments.If they are correct we will write the image!" << endl;
		float r = 0, g = 0, b = 0;
		bool good = true;
		
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "blur") == 0)) i++;
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "diff") == 0)) i++;
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "median") == 0)) i++;
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "gray") == 0)) i++;
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "color") == 0)){
				r = atof(argv[i + 2]);
				g = atof(argv[i + 3]);
				b = atof(argv[i + 3]);
				i++;
				i += 3;
				if ((r >= 0.f && r <= 1) && (g >= 0.f && g <= 1) && (b >= 0.f && b <= 1)) continue;
				else{
					cout << "Please check again the arguments you use !" << endl;
					good = false;
					break;}
			}
			else 
			{
				if (i == argc - 1)
					break;
				good = false;
				break;

			}

		}

		if (good == false)
		{
			cout << "The arguments are wrong!" << endl;
			return 0;
		}
		
		cout << "Writing..." << endl;
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "blur") == 0))
			{
				i++;
				blur.apply(*userinputimage);
			}
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "diff") == 0))
			{
				i++;
				diff.apply(*userinputimage);
			}
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "median") == 0))
			{
				i++;
				med.apply(*userinputimage);

			}
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "gray") == 0))
			{
				i++;
				gray.apply(*userinputimage);
			}
			else if (strcmp(argv[i], "-f") == 0 && (strcmp(argv[i + 1], "color") == 0))
			{
				r = atof(argv[i + 2]);
				g = atof(argv[i + 3]);
				b = atof(argv[i + 3]);

				i++;
				i += 3;
				Vec3<float> inColor(r, g, b);
				ColorFilter color(inColor);
				color.apply(*userinputimage);
				
			}
			
		}
		if (good)
			*userinputimage >> s; //Writng the new image;

	}
	else//asking the user to give me the filename of the file inside the program
	{
		const char * photo;
		string s = "";
		cout << "File name of the image to load : ";
		cin >> s;
		cout << "We are loading " << s << " file" << endl;
		photo = s.c_str(); // converting the string to const char*
		*userinputimage << (photo);

	}
	double red, green, blue;
	if (userinputimage != nullptr)
	{
		red = averagecolor(0, userinputimage);//calculating the average color of red
		green = averagecolor(1, userinputimage);//calculating the average color of green
		blue = averagecolor(2, userinputimage);//calculating the average color of blue
		cout << "Image dimensions are: " << userinputimage->getWidth() << " X " << userinputimage->getHeight() << endl;
		cout << "The average color of the image is " << "(" << red << ", " << green << ", " << blue << ")" << endl;
	}
	else
	{
		cout << "The image doesn't exist!" << endl;
	}
	delete userinputimage;
	return 0;
}

double averagecolor(unsigned int num, Image * img)//calculating the average color of a color
{
	double avercol = 0;
	for (unsigned i = 0; i < (img->getWidth()*img->getHeight()); i++)
	{
		Vec3<float> temp = img->getPixel(i / img->getWidth(), i%img->getWidth());//temp contains a specific pixel
																				 //which is represented by a Vec3<float>
		avercol += temp[num];

	}
	avercol = avercol / (img->getWidth()*img->getHeight());
	return avercol;
}
