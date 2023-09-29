#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>
#include <string>
#include <random>

using namespace std;

const string red = "\033[31m";
const string green = "\033[32m";
const string upd = "\033[0m";

const string leaderboardFileName = "leaderboard.txt";

struct LeaderboardEntry {
    string playerName;
    int elapsedTime;
};

void display_interface(vector<vector<bool>>& field, vector<char>& shapes) {
    cout << "  A B C D" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 4; j++) {
            int index = i * 4 + j;
            if (field[i][j]) {
                cout << green << shapes[index] << " ";
            }
            else {
                cout << red << "X ";
            }
        }
        cout << upd << endl;
    }
}

int getRandomValue() {
    
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribution(0, 15);

    int randomValue = distribution(gen);

    return randomValue;
}

pair<int, int> getCoordinatesFromString(const string& input) {
    if (input.length() != 2) {
        return { -1, -1 }; 
    }

    int x = -1;
    int y = -1;

    char col = tolower(input[0]);
    char row = input[1];

    if (col >= 'a' && col <= 'd') {
        x = col - 'a';
    }
    else if (col >= 'A' && col <= 'D') {
        x = col - 'A';
    }

    if (row >= '1' && row <= '4') {
        y = row - '1';
    }

    return { y, x }; 
}

void shuffleBoard(vector<char>& shapes) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(shapes.begin(), shapes.end(), gen);
}

char intToLetter(int num) {
    if (num >= 0 && num < 26) {
        return static_cast<char>('A' + num);
    }
    else {
        return '?';
    }
}

void startGame() {
    char s;
    int rq = 8;
    int hints = 3;

    vector<char> shapes = { 'o', 'o', '+', '+', '=', '=', '*', '*', 'v', 'v', '$', '$', '#', '#', '@', '@' };

    vector<vector<bool>> field(4, vector<bool>(4, false));

    cout << "\tFind all pairs\n"
        << "The goal of the game is to find all pairs inside a 4x4 field.\n"
        << "You have " << hints << " hints (type 'H' to use one)\n";

    this_thread::sleep_for(chrono::seconds(2)); 

    int openPairs = 0;
    auto startTime = chrono::steady_clock::now();
    shuffleBoard(shapes);

    while (openPairs < rq) {
        system("cls");
        display_interface(field, shapes);

        string input;
        cout << "Enter the coordinates of the first cell (e.g., 'A1') or 'H' for a hint:\n";
        cin >> input;

        if (input == "H" || input == "h") {
            int h1, h2;
            if (hints > 0) {
                vector<bool> flattenedField;
                for (const vector<bool>& row : field) {
                    flattenedField.insert(flattenedField.end(), row.begin(), row.end());
                }
                do { h1 = getRandomValue(); } while (flattenedField[h1]);
                do { h2 = getRandomValue(); } while (flattenedField[h2] || h1 == h2);

                int row1 = h1 / 4, col1 = h1 % 4;
                int row2 = h2 / 4, col2 = h2 % 4;

                flattenedField[h1] = true;
                flattenedField[h2] = true;

                cout << "Hint: " << intToLetter(col1) << row1 + 1 << " = '" << shapes[h1] << "'\n";
                cout << "      " << intToLetter(col2) << row2 + 1 << " = '" << shapes[h2] << "'\n";

                hints--;
            }
            string input;
            cout << "Enter the coordinates of the first cell (e.g., 'A1') or 'H' for a hint:\n";
            cin >> input;

            pair<int, int> coordinates1 = getCoordinatesFromString(input);

            if (coordinates1.first == -1 || coordinates1.second == -1) {
                cout << "Invalid input. Please enter coordinates in the format 'A1' to 'D4'." << endl;
                continue;
            }

            int x1 = coordinates1.first;
            int y1 = coordinates1.second;

            string input2;
            cout << "Enter the coordinates of the second cell (e.g., 'A1' to 'D4'):\n";
            cin >> input2;

            pair<int, int> coordinates2 = getCoordinatesFromString(input2);

            if (coordinates2.first == -1 || coordinates2.second == -1) {
                cout << "Invalid input. Please enter coordinates in the format 'A1' to 'D4'." << endl;
                continue;
            }

            int x2 = coordinates2.first;
            int y2 = coordinates2.second;

            if (x1 == x2 && y1 == y2) {
                cout << "You cannot choose the same coordinates for both selections. Try again." << endl;
                continue;
            }

            if (field[x1][y1] || field[x2][y2]) {
                cout << "One or both of these cells are already open or have a matching pair. Try again." << endl;
                continue;
            }

            int index1 = x1 * 4 + y1;
            int index2 = x2 * 4 + y2;
            field[x1][y1] = true;
            field[x2][y2] = true;
            system("cls");
            display_interface(field, shapes);

            if (shapes[index1] == shapes[index2]) {
                openPairs++;
            }
            else {
                this_thread::sleep_for(chrono::seconds(1));
                field[x1][y1] = false;
                field[x2][y2] = false;
                system("cls");
                display_interface(field, shapes);
            }
        }
        else {
            pair<int, int> coordinates1 = getCoordinatesFromString(input);

            if (coordinates1.first == -1 || coordinates1.second == -1) {
                cout << "Invalid input. Please enter coordinates in the format 'A1' to 'D4'." << endl;
                continue;
            }

            int x1 = coordinates1.first;
            int y1 = coordinates1.second;

            string input2;
            cout << "Enter the coordinates of the second cell (e.g., 'A1' to 'D4'):\n";
            cin >> input2;

            pair<int, int> coordinates2 = getCoordinatesFromString(input2);

            if (coordinates2.first == -1 || coordinates2.second == -1) {
                cout << "Invalid input. Please enter coordinates in the format 'A1' to 'D4'." << endl;
                continue;
            }

            int x2 = coordinates2.first;
            int y2 = coordinates2.second;

            if (x1 == x2 && y1 == y2) {
                cout << "You cannot choose the same coordinates for both selections. Try again." << endl;
                continue;
            }

            if (field[x1][y1] || field[x2][y2]) {
                cout << "One or both of these cells are already open or have a matching pair. Try again." << endl;
                continue;
            }

            int index1 = x1 * 4 + y1;
            int index2 = x2 * 4 + y2;
            field[x1][y1] = true;
            field[x2][y2] = true;
            system("cls");
            display_interface(field, shapes);

            if (shapes[index1] == shapes[index2]) {
                openPairs++;
            }
            else {
                this_thread::sleep_for(chrono::seconds(1));
                field[x1][y1] = false;
                field[x2][y2] = false;
                system("cls");
                display_interface(field, shapes);
            }
        }
    }

    auto endTime = chrono::steady_clock::now();
    int elapsedTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

    cout << "Congratulations! You have found all the pairs." << endl;
    cout << "Time taken: " << elapsedTime << " seconds" << endl;

    ofstream leaderboardFile(leaderboardFileName, ios::app);
    if (leaderboardFile.is_open()) {
        string playerName;
        cout << "Enter your name for the leaderboard: ";
        cin.ignore(); 
        getline(cin, playerName);
        LeaderboardEntry entry;
        entry.playerName = playerName;
        entry.elapsedTime = elapsedTime;
        leaderboardFile << entry.playerName << " - Time: " << entry.elapsedTime << " seconds, Hints used: " << 3 - hints << "\n";
        leaderboardFile.close();
    }
}

void showLeaderboard() {
    ifstream leaderboardFile(leaderboardFileName);
    if (leaderboardFile.is_open()) {
        cout << "Leaderboard:\n";
        string line;
        while (getline(leaderboardFile, line)) {
            cout << line << endl;
        }
        leaderboardFile.close();
    }
    else {
        cout << "Leaderboard is empty." << endl;
    }
}

int main() {
    char choice;
    do {
        cout << "Menu:\n";
        cout << "1. Start the game\n";
        cout << "2. Show leaderboard\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1/2/3): ";
        cin >> choice;

        switch (choice) {
        case '1':
            startGame();
            break;
        case '2':
            showLeaderboard();
            break;
        case '3':
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != '3');

    return 0;
}
