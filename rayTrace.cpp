#include <fstream>
#include <math.h>
#include <vector>
#include "essentials.h"


// IMAGE SETTINGS (resolution)
#define RES_X 640 //image width
#define RES_Y 480//image height

#define MAX_RAY_BOUNCES 3

/*
    This function would generated the scene with given number of
    spheres
*/
std::vector <Sphere>generateScene()
{
    std::vector <Sphere> sphSet;

    Sphere s1 ( Vector3<float> (1, 4, -5),// center
                Vector3<float> (0, 1, 1),// color
                2,                        // radius
                0,                        // reflectivity
                0);                       // transparency

    sphSet.push_back(s1);
    return sphSet;
}

/*
    This function traverses the scene for each ray
*/
Vector3<float> rayTrace(Vector3<float> primRay, Sphere s)
{
    // code for checking intersection    
    Vector3<float> iPoint = s.intersection(primRay);
    Vector3<float> color(0);
    if (iPoint.getX() < 0 && iPoint.getY() < 0 && iPoint.getZ() < 0)
    {
        return color;
    }
    else
    {
        Light L( Vector3<float> (0, 6, -5), // light position
                 Vector3<float> (1, 0, 0)); // light color: red light

        // light ray from intersection point to the Light
        Vector3<float> lightRay = L.position - iPoint;
        lightRay.normalize();

        // normal at the intersection point 
        Vector3<float> normal = iPoint - s.center;
        normal.normalize();
        
        float shade = lightRay.dot(normal);

        if(shade < 0 )
        {
            shade = 0;
        }

        float ambCoef = 0.2f;  // ambient coefficient = 20%
        float difCoef = 0.8f;  // diffuse coefficient = 1 - ambient coeffient

        color = s.color * (ambCoef + difCoef * shade);
    }

    return color;
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
            for (int obj = 0; obj < scene.size(); ++obj)
            {
                col = rayTrace(eyeRay.normalize(), scene[obj]);
            }

            //*img = Vector3<float> (1, 1, 0);
            *img = col;
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
        Color color = Vec3toColor(img[i]);
        output << color;
    }

    output.close();

    delete [] img;
    
    return 0;
}

