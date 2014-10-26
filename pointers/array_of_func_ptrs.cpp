#include <iostream>

using namespace std;

int main()
{
    char (*a)(int);
    //char (*b)[10](int);   //error
    //char (*b)(int)[10];   //error
    char (*b[10])(int);
    
    return 0;
}
