#include <iostream>

using namespace std;

#pragma pack(8)

struct _s1{
    char c;
    int i;
    long l;
    double d;
};

struct _s2{
    int i;
    char c;
    long l;
    double d;
};

struct _s3{
    int i;
    long l;
    char c;
    double d;
};

struct _s4{
    int i;
    long l;
    double d;
    char c;
};

int main()
{
   cout << sizeof(long long) << endl;
   cout << sizeof(_s1) << endl; 
   cout << sizeof(_s2) << endl; 
   cout << sizeof(_s3) << endl; 
   cout << sizeof(_s4) << endl; 
   
   return 0;
}
//8
//24
//24
//32
//32

//4
//24*4
