#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#define GREEN "\033[32m"
#define YELLOW "\033[93m"
#define GREY "\033[90m"
#define RESET "\033[0m"

using namespace std;


int timesPlayed;
int averageAttempts;
float winPercentage;
int currentStreak;
int longestStreak;
float wins;
int guessesTotal;


void readStatsFromFile(int& timesPlayed, int& averageAttempts, float& winPercentage, int& currentStreak, int& longestStreak, float& wins, int& guessesTotal) {
    ifstream infile("stats.txt");
    if (infile) {
        infile >> timesPlayed >> averageAttempts >> winPercentage >> currentStreak >> longestStreak >> wins;
        infile.close();
    }
}

void updateStatsFile(int timesPlayed, int averageAttempts, float winPercentage, int currentStreak, int longestStreak, float wins, int guessesTotal){
    ofstream outfile("stats.txt");
    if (outfile) {
        outfile << timesPlayed << endl;
        outfile << averageAttempts << endl;
        outfile << winPercentage << endl;
        outfile << currentStreak << endl;
        outfile << longestStreak << endl;
        outfile << wins << endl;
        outfile.close();
    }
}

void resetStats() {
    system("clear");
    timesPlayed = 0;
    averageAttempts = 0;
    winPercentage = 0.0f;
    currentStreak = 0;
    longestStreak = 0;
    wins = 0.0f;
    guessesTotal = 0;

    std::ofstream statsFile("stats2.csv");
    statsFile.close();
    updateStatsFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal);

}

void writeCSV(string& answer, int guessCount, string& status) {
    
    std::ofstream outfile("stats2.csv", std::ios_base::app);
        string upperAnswer;
    for (int i = 0; i < answer.length(); i++) {
        upperAnswer += toupper(answer[i]);
    }

    outfile << upperAnswer << "," << guessCount+1 << "," << status << "\n";
    
    outfile.close();
}

void readCSV() {
    std::ifstream infile("stats2.csv");
    
    std::vector<std::vector<std::string>> data;

    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string value;
        while (std::getline(ss, value, ',')) {
            row.push_back(value);
        }
        data.push_back(row);
    }

    infile.close();

    for (auto& row : data) {
        std::cout << std::setw(18) << left << row[0];
        std::cout << std::setw(7) << left << row[1];
        std::cout << std::setw(5) << right << row[2] << "\n";
    }
}

void displayMenu() {
    cout << "=========================" << endl;
    cout << "    WELCOME TO WORDLE    " << endl; 
    cout << "=========================" << endl;
    cout << "1. Play Wordle" << endl;
    cout << "2. How to Play" << endl;
    cout << "3. Statistics Summary" << endl;
    cout << "4. Reset Statistics" << endl;
    cout << "5. Exit\n" << endl; 
    cout << "Select an option: "; 
}


void displayHowToPlay() {
    system("clear");
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
    system("clear");
}

string randomWord() {
    vector<string> words;
    string word;
    ifstream file("words.txt");
    if (file.is_open()) {
        while (getline(file, word)) {
            words.push_back(word);
        }
        file.close();
    }
    srand(time(0));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

bool guessCheck(string word) {
    ifstream file1("words.txt");
    if (file1.is_open()) {
        string w;
        while (getline(file1, w)) {
            if (w == word) {
                file1.close();
                return true;
            }
        }
        file1.close();
    }
    ifstream file2("allowed.txt");
    if (file2.is_open()) {
        string w;
        while (getline(file2, w)) {
            if (w == word) {
                file2.close();
                return true;
            }
        }
        file2.close();
    }
    return false;
}

void wordleMain() {
    readStatsFromFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal);
    timesPlayed++;
    system("clear");
    string answer = randomWord();
    cout << answer << endl;
    string guess;
    string status = "No";
    while(guess.length() != 5) {
        cout << "Enter Your Guess: ";
        cin >> guess;
        system("clear");
    }

    vector<char> vGuess;
    vector<char> vAnswer;
    vector<string> colors = {GREY, GREY, GREY, GREY, GREY};

vector<vector<char>> guesses;
    vector<vector<string>> vColors;

    for (int i = 0; i < answer.length(); i++) {
            vAnswer.push_back(answer[i]);
    }

    int guessCount = 0;
    while (guessCount != 5 && guess != answer) {
        system("clear");
        for (int i = 0; i < answer.length(); i++) {
                vGuess.push_back(guess[i]);
        }

        guesses.push_back(vGuess);
        for (int y = 0; y < vAnswer.size(); y++) {
            for (int x = 0; x < vAnswer.size(); x++) {
                if (x != y && vGuess[y]==vAnswer[x]) {
                    colors[y] = YELLOW;
                }
            }
        }
        
        for (int g = 0; g < vAnswer.size(); g++) {
            if (vGuess[g] == vAnswer[g]) {
                colors[g] = GREEN;
            }
        }


        vColors.push_back(colors);
        for (int i = 0; i < guesses.size(); i++) {
            cout << vColors[i][0] << " --- " << vColors[i][1] << " --- " << vColors[i][2] << " --- " << vColors[i][3] << " --- " << vColors[i][4] << " --- " << RESET << endl;
            cout << vColors[i][0] << "| " << static_cast<char>(toupper(guesses[i][0])) << " |" << vColors[i][1] << "| " << static_cast<char>(toupper(guesses[i][1])) << " |" << vColors[i][2] << "| " << static_cast<char>(toupper(guesses[i][2])) << " |" << vColors[i][3] << "| " << static_cast<char>(toupper(guesses[i][3])) << " |" << vColors[i][4] << "| " << static_cast<char>(toupper(guesses[i][4])) << " |" << RESET << endl;
            cout << vColors[i][0] << " --- " << vColors[i][1] << " --- " << vColors[i][2] << " --- " << vColors[i][3] << " --- " << vColors[i][4] << " --- " << RESET << endl;
        }   

        guessCount++;

        guess = "";

    while(guess.length() != 5) {
        cout << "Enter Your Guess: ";
        cin >> guess;
        if (!guessCheck(guess)) {
            guess = "";
        }
    }


        vGuess.clear();

        colors = {GREY, GREY, GREY, GREY, GREY};
    }
    
   for (int i = 0; i < answer.length(); i++) {
            vGuess.push_back(guess[i]);
    }


    for (int y = 0; y < vAnswer.size(); y++) {
        for (int x = 0; x < vAnswer.size(); x++) {
            if (x != y && vGuess[y]==vAnswer[x]) {
                colors[y] = YELLOW;
            }
        }
    }

    for (int g = 0; g < vAnswer.size(); g++) {
        if (vGuess[g] == vAnswer[g]) {
            colors[g] = GREEN;
        }
    }

    guesses.push_back(vGuess);
    vColors.push_back(colors);
    system("clear");
    for (int i = 0; i < guesses.size(); i++) {
        cout << vColors[i][0] << " --- " << vColors[i][1] << " --- " << vColors[i][2] << " --- " << vColors[i][3] << " --- " << vColors[i][4] << " --- " << RESET << endl;
        cout << vColors[i][0] << "| " << static_cast<char>(toupper(guesses[i][0])) << " |" << vColors[i][1] << "| " << static_cast<char>(toupper(guesses[i][1])) << " |" << vColors[i][2] << "| " << static_cast<char>(toupper(guesses[i][2])) << " |" << vColors[i][3] << "| " << static_cast<char>(toupper(guesses[i][3])) << " |" << vColors[i][4] << "| " << static_cast<char>(toupper(guesses[i][4])) << " |" << RESET << endl;
        cout << vColors[i][0] << " --- " << vColors[i][1] << " --- " << vColors[i][2] << " --- " << vColors[i][3] << " --- " << vColors[i][4] << " --- " << RESET << endl;
    }
    
    if (guess == answer) {
        cout << "\nWinner Winner Chicken Dinner!\n\n" << endl;
        wins++;
        currentStreak++;
        if (currentStreak > longestStreak) {
            longestStreak = currentStreak;
        }
        status = "Yes";
    } else {
        string print;
        for (int i = 0; i < answer.length(); i++) {
            print += toupper(answer[i]);
        }
        cout << "\n\nThe word was: " << GREEN << print << RESET << endl;
        cout << "\nYou Did Great, Try again later!!\n\n" << endl;
        currentStreak = 0;
    }

    guessesTotal += (guessCount+1);    
    winPercentage =  (float(wins/timesPlayed));
    averageAttempts = (guessesTotal/timesPlayed);

    cout << "Press [enter] to continue";
    cin.ignore();
    string dummy;
    getline(cin, dummy);
    system("clear");

    writeCSV(answer, guessCount, status);

    updateStatsFile(timesPlayed, averageAttempts, winPercentage, currentStreak, longestStreak, wins, guessesTotal);
}

void statisticsSum() {
    system("clear");
    cout << "==============================" << endl;
    cout << "      STATISTICS SUMMARY      " << endl;
    cout << "==============================" << endl;
    cout << setw(25) << left << "Times Played:" << setw(5) << right << timesPlayed << endl;
    cout << setw(25) << left << "Average Attempts:" << setw(5) << right << averageAttempts << endl;
    cout << setw(25) << left << "Win Percentage:" << setw(5) << right << setprecision(3) << winPercentage * 100 << "%" << endl;
    cout << setw(25) << left << "Current Streak:" << setw(5) << right << currentStreak << endl;
    cout << setw(25) << left << "Longest Streak:" << setw(5) << right << longestStreak << endl;

    cout << "\n------------------------------" << endl;
    cout << "WORD       ATTEMPTS        WIN" << endl;
    cout << "------------------------------" << endl;

    readCSV();

    cout << "\n\nPress [enter] to continue";
    string dummy;
    getline(cin, dummy);
    system("clear");
}


#endif