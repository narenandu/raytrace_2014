#include <iostream>
#include <algorithm>
#include <limits.h>


/* 
 This would be my basic Vector Class for storing color values
 or vectors. For Vectors there will be operations like dot product,
 magnitude calculation etc..
*/
template <typename T>
class Vector3
{
    private:
        T x;
        T y;
        T z;
      
    public:
        Vector3(T val) : x(val), y(val), z(val) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vector3() : x(0), y(0), z(0) {}

        template <typename K>
        friend ostream& operator<< (ostream &out, const Vector3<K> &c);
        
        inline T getX(){return x;}
        inline T getY(){return y;}
        inline T getZ(){return z;}

        void operator=(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        T magnitude() 
        {
            return sqrt(x * x + y * y + z * z);
        }

        T dot(Vector3<T> v) 
        {
            return (x * v.x + y * v.y + z * v.z);
        }

        Vector3<T> normalize()
        {
            float val = magnitude();

            if (val > 0)
            {
                x = x / val;
                y = y / val;
                z = z / val;
                return Vector3<T> (x, y, z);
            }
            else
            { 
                return Vector3<T> (0, 0, 0);
            }
        }

        const Vector3<T>& operator+(const Vector3<T> &v)
        {
            x += v.x, y += v.y, z +=v.z;
            return *this;
        }

        const Vector3<T>& operator-(const Vector3<T> &v)
        {
            x -= v.x, y -= v.y, z -=v.z;
            return *this;
        }

        const Vector3<T>& operator*(const T &v)
        {
            x *= v, y *= v, z *= v;
            return *this;
        }
};


template <typename T>
ostream& operator<< (ostream &out, const Vector3<T> &vec)
{
    return out << '('<< vec.x << ','
                     << vec.y << ','
                     << vec.z << ')';
}


/* 
 Color Class which would be mainly used for 
*/
class Color
{
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        
        Color(unsigned col) : r(col), g(col), b(col) {}
        Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
        Color* Vec3toColor(Vector3<unsigned char> inVector);
        void operator=(const Color &c)
        {
            r = c.r;
            g = c.g;
            b = c.b;
        }
        friend ostream& operator<< (ostream &out, const Color &c);
};

ostream& operator<< (ostream &out, const Color &c)
{
    return out << c.r << c.g << c.b;
}

Color Vec3toColor(Vector3<float> inVector)
{
    Color outColor(0,0,0);
    // limiting value between 0 - 1 and then scaling it in 255 (UCHAR_MAX) colors 
    outColor.r = (unsigned char)std::min(1.0f, std::max(0.0f, inVector.getX())) * UCHAR_MAX;
    outColor.g = (unsigned char)std::min(1.0f, std::max(0.0f, inVector.getY())) * UCHAR_MAX;
    outColor.b = (unsigned char)std::min(1.0f, std::max(0.0f, inVector.getZ())) * UCHAR_MAX;

    return outColor;
}

class Sphere
{
    public: 
        Vector3<float> center;
        Vector3<float> color;
        int radius;
        float reflectivity;
        float transparency;

        Sphere(Vector3<float>, Vector3<float>, int, float, float);
        Vector3<float> intersection(Vector3<float>);
};

Sphere::Sphere( Vector3<float> cntr,
                Vector3<float> col, 
                int rad = 1,
                float refl = 0.0,
                float trns = 0.0)
{
    center = cntr;
    color = col;
    radius = rad;
    reflectivity = refl;
    transparency = trns;
}

Vector3<float> Sphere::intersection(Vector3<float> ray)
{
    // reference: https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
    Vector3<float> Eye(0,0,0);

    float v = Eye.dot(ray);
    float disc = (radius * radius) - (Eye.dot(Eye) - v * v);

    if (disc < 0)
    {
        return Vector3<float> (disc);
    }
    else
    {
        float d = sqrt(disc);
        // Eye position + normalized ray * distance
        return Vector3<float> ( Eye +  ray * (v - d) );
    }
}


class Light
{
    public: 
        Vector3<float> position;
        Vector3<float> color;

        Light(Vector3<float>, Vector3<float>);
};

Light::Light( Vector3<float> pos, 
              Vector3<float> col )
{
    position = pos;
    color = col;
}