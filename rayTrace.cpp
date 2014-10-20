#include <fstream>
#include <math.h>
#include <vector>
#include "essentials.h"


// IMAGE SETTINGS (resolution)
#define RES_X 320 //image width
#define RES_Y 240//image height

#define MAX_RAY_BOUNCES 3

/*
    This function would generated the scene with given number of
    spheres
*/
std::vector <Sphere>generateScene()
{
    std::vector <Sphere> sphSet;

    Sphere s1 ( Vector3<float> (1.0, 4.0, -1.0),// center
                3,                              // radius
                0,                              // reflectivity
                0);                             // transparency

    sphSet.push_back(s1);
    return sphSet;
}

/*
    This function traverses the scene for each ray
*/
Vector3<float> rayTrace(Vector3<float> primRay, Sphere s)
{
    // code for checking intersection    
}


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

    // generate the scene
    std::vector <Sphere> scene = generateScene();

    // Loop through each pixel from 0,0 to RES_X,RES_Y
    for (int j = 0; j < RES_Y; j++)
    {
        for (int i = 0; i < RES_X; i++)
        {

            Vector3<float> eyeRay;
            Vector3<float> col;
            
            // the ray's starting point (from eye to middle of the pixel)
            // reference: www.unknownraod.com/rtfm/grahics/rt_eyerays.html
            // Assumptions: eye/camera -> (0,0,0)
            //              center of view plane -> (0,0,-1) and parallel to XY axis
            eyeRay = calculateRay(i, j, tanFovX, tanFovY);

            // Will be tracing only a single sphere
            for (int i = 0; i < scene.size(); ++i)
            {
                col = rayTrace(eyeRay, scene[i]);
            }

            *img = Vector3<float> (0, 122, 240);
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

