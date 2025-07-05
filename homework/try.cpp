#include <iostream>
using namespace std;

int main(){
    cout<<"enter ur age ";
    int num;
    cin>> num;
    int result = 2025 - num;
    cout<< (num < 0  ? "incorect": "u are dead" )<<endl;
    return 0;
    } 