#include <iostream>
#include <string>
#include "functions.h"

using namespace std;



int main() {
    system("clear");
    string option;
    while (option != "5") {
        displayMenu();
        getline(cin, option);
        if (option == "1") {
            wordleMain();
        } else if (option == "2") {
            displayHowToPlay();
        } else if (option == "3") {
            cout << "Statistics summary not implemented yet.\n" << endl;
        } else if (option == "4") {
            cout << "Reset statistics not implemented yet.\n" << endl;
        } else {
            cout << "Bye" << endl;
        }
    }
    return 0;
}

