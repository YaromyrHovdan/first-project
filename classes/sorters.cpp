#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int nums[] = {85,-9,-23,-7,67,45,-2,12};
    int size = sizeof(nums) / sizeof(nums[0]);
    sort(nums,nums + size);
    cout<<"array sorted: ";
    for(int i = 0; i < size; i++){
        cout<< nums[i] <<" ";
        }
    return 0;
    } 