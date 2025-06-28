#include <iostream>
using namespace std;

int main(){
    int nums[] = {9,8,45,78,54,24,64,99,87,41,32};
    int max = nums[0];
    int size = sizeof(nums) / sizeof(nums[0]);
    for(int i = 0; i < size; i++){
        if (nums[i] > max){
            max = nums[i];
            }
        }
        cout<< max;
    return 0;
    }
    