#include <iostream>
using namespace std;

int main(){
    char markt;
    cout << "enter ur mark ";
    cin>> markt;
    switch(markt){
        case 'A':
        cout<<"Perfect";
        break;
        case 'B':
        cout<<"Good";
        break;
        case 'C':
        cout<<"Satisfactorily";
        break;
        case 'D':
        cout<<"Bad";
        break;
        case 'F':
        cout<<"Very bad";
        break;
        }
        
    return 0; 
    }