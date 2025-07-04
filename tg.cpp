#include <iostream>
using namespace std;

int main(){
    int numbers[] = {3,-9,23,45,2,-12,-99,7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    cout<< " enter number " <<endl;
    int num;
    cin>> num;

    // If the number is found, return the index of the number
    // If the number is found multiple times, return the index of the first occurrence
    int index = -1;
    for (int i = 0;i < size; i++){
        if (numbers[i] == num){
            index = i;
            break;
            }
        }
    if (index != -1) {
        cout << "Number found at index: " << index << endl;
    } else {
        cout << "Number not found" << endl;
    return 0;
    }