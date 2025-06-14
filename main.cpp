#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "(database) status: working;\n\n";

    string userNameInput, mumNameInput, dadNameInput, petNameInput;
    int userAgeInput, mumAgeInput, dadAgeInput, petAgeInput;

    cout << "What is your name? ";
    getline(cin, userNameInput);

    cout << "How old are you? ";
    cin >> userAgeInput;
    cin.ignore(); // clear newline

    cout << "What is your mum’s name? ";
    getline(cin, mumNameInput);

    cout << "How old is your mum? ";
    cin >> mumAgeInput;
    cin.ignore();

    cout << "What is your dad’s name? ";
    getline(cin, dadNameInput);

    cout << "How old is your dad? ";
    cin >> dadAgeInput;
    cin.ignore();

    cout << "What is your pet’s name? ";
    getline(cin, petNameInput);

    cout << "How old is your pet? ";
    cin >> petAgeInput;

    // Output
    cout << "\n--- Summary ---\n";
    cout << "User: " << userNameInput << " | Age: " << userAgeInput << endl;
    cout << "Mum: " << mumNameInput << " | Age: " << mumAgeInput << endl;
    cout << "Dad: " << dadNameInput << " | Age: " << dadAgeInput << endl;
    cout << "Pet: " << petNameInput << " | Age: " << petAgeInput << endl;

    return 0;
}
