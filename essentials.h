#include <limits.h>
#include <stdlib.h>
#include <math.h>

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
        Vector3(T x=0, T y=0,T z=0) : x(x), y(y), z(z) {}
        template <typename K>
        friend ostream& operator<< (ostream &out, const Vector3<K> &c);
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

    public:
        Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
        Color* Vector3toColor(Vector3<unsigned char> inVector);
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
    return out << c.r << c.g << c.b ;
}

Color Vector3toColor(Vector3<float> inVector)
{
    Color outColor(0,0,0);
    // limiting value between 0 - 1 and then scaling it in 255 (UCHAR_MAX) colors 
    outColor.r = std::min(1.0f, std::max(0.0f, inVector.x)) * UCHAR_MAX;
    outColor.g = std::min(1.0f, std::max(0.0f, inVector.y)) * UCHAR_MAX;
    outColor.b = std::min(1.0f, std::max(0.0f, inVector.z)) * UCHAR_MAX;

    return outColor;
}

