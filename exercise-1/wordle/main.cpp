#include <iostream>
#include <string>

#define GREEN "\033[32m"
#define YELLOW "\033[93m"
#define GREY "\033[90m"
#define RESET "\033[0m"

using namespace std;

void displayMenu() {
    cout << "=========================" << endl;
    cout << "WELCOME TO WORDLE" << endl; 
    cout << "=========================" << endl;
    cout << "1. Play Wordle" << endl;
    cout << "2. How to Play" << endl;
    cout << "3. Statistics Summary" << endl;
    cout << "4. Reset Statistics" << endl;
    cout << "5. Exit\n" << endl; 
    cout << "Select an option: "; 
}

void displayHowToPlay() {
    cout << "=============================================" << endl;
    cout << "                 HOW TO PLAY                 " << endl;
    cout << "=============================================" << endl;            
    cout << "Guess the Wordle in 6 tries.\n\n" << endl;
    cout << "HOW TO PLAY:" << endl;
    cout << "- Each guess must be a valid 5 letter word." << endl;
    cout << "- The color of the tiles will change to show\n  you how close your guess was to the word.\n" << endl;
    cout << GREEN << " --- " << RESET << " ---  ---  ---  --- " << endl;
    cout << GREEN <<"| W |"<< RESET << "| E || A || R || Y |" << endl;
    cout << GREEN << " --- " << RESET << " ---  ---  ---  --- " << endl;
    cout << "W is in the word and in the correct spot.\n" << endl;
    cout << " --- " << YELLOW << " --- " << RESET << " ---  ---  --- " << endl;
    cout << "| P |" << YELLOW << "| I |" << RESET << "| L || L || S |" << endl;
    cout << " --- " << YELLOW << " --- " << RESET << " ---  ---  --- " << endl;
    cout << "I is in the word but in the wrong spot.\n" << endl;
    cout << " ---  ---  --- " << GREY << " --- " << RESET << " --- " << endl;
    cout << "| V || A || G |" << GREY << "| U |" << RESET << "| E |" << endl;
    cout << " ---  ---  --- " << GREY << " --- " << RESET << " --- " << endl;
    cout << "U is not in the word in any spot.\n\n" << endl;
    cout << "Press [enter] to continue";
    cin.ignore();
}

int main() {

    string option;
    while (option != "5") {
        displayMenu();
        getline(cin, option);
        if (option == "1") {
            cout << "Wordle game not implemented yet.\n" << endl;
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
