#include <iostream.h>
#include "essentials.h"

int main()
{
    Color<unsigned int> c1(12,13,14);
    Color<float> f1(6.1,5.0,3.0);
    Color<char> c2('a','b','c');

    cout<<c1;
    cout<<endl<<f1;
    cout<<endl<<c2;
    cout<<"\nhello world.. I am back\n";
    return 0;
}

