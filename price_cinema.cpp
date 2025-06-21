#include <iostream>
using namespace std;

int main(){
    cout<<"what is your birth year?";
    int userBirthYear;
    cin>> userBirthYear;
    cout<<"what day is today?";
    string day;
    cin>> day;
    int age;
    age = 2025 - userBirthYear;
    int totprice = 0;
    int price = 0;
    if(age <= 12){
        price = 50;
        cout<<"kid  ";
        }
    else if(age >= 13 && age <= 17){
        price = 70;
        cout<<"teen ";
        }    
    else if(age >= 18 && age <= 59){
        price = 100;
        cout<<"adult";
        }    
    else if(age >= 60){
        price = 60;
        cout<<"old  ";
        } 
    if(day == "tuesday"){
        cout<< day <<"  ";
        totprice = price * 0.9;
        cout<<"yes  ";
        cout<<totprice;
        }    
    else {
         cout<< day;
        totprice = price;
        cout<<"no  ";
        cout<<totprice;
        }    
    return 0;
    }