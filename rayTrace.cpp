
#include <fstream.h>
#include "essentials.h"

// IMAGE SETTINGS (resolution)
#define RES_X 160 //image width
#define RES_Y 120 //image height

#define MAX_RAY_BOUNCES 3

int main()
{
	// initialize the image data to be written out
	Vector3<float> *img, *img_tmp;
	img = new Vector3<float>[RES_X * RES_Y];
	img_tmp = img;

	// Loop through each pixel from 0,0 to RES_X,RES_Y
    for (int j = 0; j < RES_Y; j++)
    {
    	for (int i = 0; i < RES_X; i++)
    	{

    		//TO_DO: Write the actual tracing code which would calculate
    		// the ray's starting point (from eye to middle of the pixel) and 
    		// the direction in to the scene. Will be creating only a single sphere

    		*img = Vector3<float> (255, 255, 255);
    		img++;
    	}
    }

    // Write out the image data to binary ppm format
    // .ppm files can be viewed using gimp on linux
    // or photoshop on windows
    ofstream output("sphere_traced.ppm", ios::out | ios::binary);
    output << "P6\n" << RES_X << "\n" << RES_Y << "\n" << UCHAR_MAX << "\n";

    img = img_tmp;

    for (int i = 0; i < RES_X * RES_Y; i++)
    {
		cout<<img[i]<<endl;
	   	Color color = Vector3toColor(img[i]);
    	output << color;
    	cout<<i<<endl;
    }

    output.close();
    cout<<"here....";

    //delete [] img;
    
    return 0;
}

