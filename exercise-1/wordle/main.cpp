#include <iostream>
#include <string>
#include "functions.h"

using namespace std;



int main() {
    readStatsFromFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal); 
    updateStatsFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal);
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
            readStatsFromFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal); 
            statisticsSum();
        } else if (option == "4") {
            resetStats();
            statisticsSum();
        } else {
            cout << "Bye" << endl;
        }
    }
    return 0;
}

