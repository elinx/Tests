#include <iostream>

using namespace std;

#include <list>
#include <vector>
#include <memory>

using std::list;
using std::vector;
using std::shared_ptr;


template<typename T>
class F{
};


template<typename T>
class E{
  shared_ptr< E<T> > m;  
};

shared_ptr<int> foo(){
    //return new int(3); //error
    return shared_ptr<int>(new int(3)); //ok
}
int main()
{
   cout << "Hello World" << endl; 
   
   E< F<int> > m;
   
   shared_ptr<int> a(new int(5));
   
   int* b = a.get();
   
   return 0;
}
