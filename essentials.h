


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
        Vector3() : x(T(0)), y(T(0)), z(T(0)) {}
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