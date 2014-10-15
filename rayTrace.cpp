#include <iostream>
#include "essentials.h"

// IMAGE SETTINGS (resolution)
#define RES_X 320
#define RES_Y 240

int main()
{
    //Vector3<unsigned int> c1(12,13,14);
	Vector3<unsigned int> c1(0);
    Vector3<float> f1(6.1,5.0,3.0);
    Vector3<char> c2('a','b','c');

    cout<<c1;
    cout<<endl<<f1;
    cout<<endl<<c2;
    cout<<endl<<sqrt(4);
    cout<<endl;
    return 0;
}

