#include <iostream>
using namespace std;

int main(){
    int arr[5] = {3,89,-9,34,56};
    int* res = arr;
    int i = 0;
    while (i < 5){
        cout<<"Element "<< i << ": " << *res <<endl;
        res++;
        i++;
        }
    return 0;
    }