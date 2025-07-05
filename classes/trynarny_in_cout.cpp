#include <iostream>
using namespace std;

int main(){
   cout<<"enter number ";
   int num;
   cin>> num;
   cout<< (num %2 ==0 ? "parne": "not parne")<<endl;
   return 0;
}