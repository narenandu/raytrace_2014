#include <fstream>
#include <math.h>
#include "essentials.h"

// IMAGE SETTINGS (resolution)
#define RES_X 160 //image width
#define RES_Y 120 //image height

#define MAX_RAY_BOUNCES 3

/*
    This function will take in the pixel values (x,y) on the 
    image plane and calculates the ray direction required to 
    shoot in to the scene (negative Z)
*/
Vector3<float> calculateRay(int x, int y, float tanFovX, float tanFovY)
{
    float pointX = ((2 * (x + 0.5) - RES_X) / (float)RES_X) * tanFovX;
    float pointY = ((2 * (y + 0.5) - RES_Y) / (float)RES_Y) * tanFovY;

    return Vector3<float> (pointX, pointY, -1.0);
}

int main()
{
    // initialize the image data to be written out
    Vector3<float> *img, *img_tmp;
    img = new Vector3<float>[RES_X * RES_Y];
    img_tmp = img;

    // reference: www.unknownraod.com/rtfm/grahics/rt_eyerays.html
    float aspectRatio = (RES_X/(float)RES_Y);
    float fovX = M_PI/4.0;
    float fovY = fovX * (RES_Y/(float)RES_X);
    float tanFovX = tan(fovX);
    float tanFovY = tan(fovY);

    // Loop through each pixel from 0,0 to RES_X,RES_Y
    for (int j = 0; j < RES_Y; j++)
    {
        for (int i = 0; i < RES_X; i++)
        {

            Vector3<float> eyeRay;
            //TO_DO: Write the actual tracing code which would calculate
            
            // the ray's starting point (from eye to middle of the pixel)
            // reference: www.unknownraod.com/rtfm/grahics/rt_eyerays.html
            // Assumptions: eye/camera -> (0,0,0)
            //              center of view plane -> (0,0,-1) and parallel to XY axis
            eyeRay = calculateRay(i, j, tanFovX, tanFovY);

            // the direction in to the scene. Will be creating only a single sphere

            *img = Vector3<float> (0, 0, 255);
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
        Color color = Vector3toColor(img[i]);
        output << color;
    }

    output.close();

    delete [] img;
    
    return 0;
}

