#include <iostream>
using namespace std;

int main(){
    int numbers[] = {1,7,98,65,43,56,32,34,66};
    int totalsum = 0;
    int size = sizeof (numbers) / sizeof (numbers[0]);
    for (int i = 0; i < size; i++){
        if (numbers[i] %2 == 0){
            totalsum += numbers[i];
            }
        }
        cout << totalsum;
    return 0;
    }