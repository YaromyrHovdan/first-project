#include <iostream>
using namespace std;

int main(){
    cout<<"enter ur age ";
    int age;
    cin>> age;
    int year = 2025;
cout <<
        (age < 0 ? "Некоректний вік" :
        age == 0 ? "Ти ще немовля 🙂" :
        age <= 120 ? "Твій приблизний рік народження: " + to_string(year - age) :
        "Мабуть, ти безсмертний 😅");
    return 0;
    } 