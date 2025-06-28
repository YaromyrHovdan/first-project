#include <iostream>
using namespace std;

int main(){
    int numbers[] = {-2,6,76 -13,89,-45,67,-32};
    int counting = 0;
    int size = sizeof(numbers)/sizeof(numbers[0]);
    for (int i = -1; i <= size;i++){
        if (numbers[i] < 0){
            counting += 1;
            }
        }
        cout<< counting;
    return 0;
    }