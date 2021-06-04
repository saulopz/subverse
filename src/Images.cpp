#include "Images.h"

Images::Images()
{
	g = Singleton<Enjin>::getInstance();
	Image *bmp = g->createImage(CELL_SIZE, CELL_SIZE);
	bitmaps["void"] = bmp;
}

void Images::add(string imageName)
{
	string temp = "";
	string temp2 = "";
	for (unsigned int i = 0; i < 16; i++)
	{
		temp = IMAGES_DIR;
		temp += "//" + imageName + Tools::intToString(i) + ".png";
		Image *bmp = g->loadImage(temp.c_str());
		if (!bmp)
		{
			bmp = NULL;
		}

		temp = imageName + Tools::intToString(i);
		bitmaps[temp] = bmp;

		if (bmp == NULL)
		{
			switch (i)
			{
			case 8:
			case 10:
			case 1:
				temp2 = imageName + "0";
				break;
			case 2:
				temp2 = imageName + "0";
				break;
			case 9:
			case 11:
			case 3:
				temp2 = imageName + "1";
				break;
			case 4:
				temp2 = imageName + "0";
				break;
			case 5:
				temp2 = imageName + "1";
				break;
			case 6:
				temp2 = imageName + "2";
				break;
			case 7:
				temp2 = imageName + "3";
				break;
			case 12:
			case 14:
				temp2 = imageName + "4";
				break;
			case 13:
			case 15:
				temp2 = imageName + "5";
				break;
			default:
				temp2 = "void";
			}
			bitmaps[temp] = bitmaps[temp2];
		}
	}
}

Image *Images::get(std::string fileName)
{
	return bitmaps[fileName];
}

Images::~Images()
{
}
