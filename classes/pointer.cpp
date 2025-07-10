#include <iostream>
using namespace std;

int main(){
    int x = 5;
    int* res = &x;
    cout<<"Value of x: "<< x<<endl;
    cout<<"Address of x: "<< &x <<endl;
    cout<<"Address via pointer: "<< res <<endl;
    cout<<"Value via pointer: "<< *res <<endl;
    *res = 20;
    cout<<"New value of x: " << x <<endl;
    return 0;
    }