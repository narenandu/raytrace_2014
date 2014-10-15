template <typename T>
class Color
{
    private:
        T r;
        T g;
        T b;
      
    public:
        Color(T red=255, T green=255,T blue=255)
        {
            r = red;
            g = green;
            b = blue;
        }

        template <typename K>
        friend ostream& operator<< (ostream &out, const Color<K> &c);

};

template <typename T>
ostream& operator<< (ostream &out, const Color<T> &c)
{
    return out << '('<< c.r << ','
                     << c.g << ','
                     << c.b << ')';
}