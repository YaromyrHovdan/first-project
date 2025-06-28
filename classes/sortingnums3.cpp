#include <iostream>
using namespace std;

int main(){
    int numbers[] = {2,23,34,45,56,66,77,88,99};
    int max = numbers[0];
    int min = numbers[0];
    int size = sizeof(numbers)/sizeof(numbers[0]);
    for (int i = 0; i < size; i++){
        if (numbers[i] > max){
            max = numbers[i];
        }
        if (numbers[i] < min){
            min = numbers[i];
            }    
        } 
        cout<< max <<endl;
        cout<< min <<endl;
    return 0;
    }