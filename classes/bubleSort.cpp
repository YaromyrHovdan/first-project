#include <iostream>
#include <algorithm>
using namespace std;

void bubleSort(int arr[],int n){
    for (int i = 0; i < n - 1; ++i) {              
        for (int j = 0; j < n - i - 1; ++j) {     
            if (arr[j] > arr[j + 1]) {              
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    }

int main(){
    int arr[] = {-6,8,75,-56,24,-83,-8,3};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubleSort(arr, size);
    cout<<"array sorted";
      for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    return 0;
    } 