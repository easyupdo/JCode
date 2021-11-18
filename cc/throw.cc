#include <iostream>
using namespace std;
 
double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}
 
int main ()
{
   int x = 50;
   int y = 0;
   double z = 0;
 
   try {
     z = division(x, y);
     cout << z << endl;
   }catch (const char* msg) {
     cerr << msg << endl;
   }


    try
    {
        int i = 0;
        throw "FK";
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
    }
    catch(...){
        
    }
 
   return 0;
}