#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <windows.h>

using namespace std;

#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_WHITE 7

// Struct for storing user info
struct User {
    char username[50];
    char password[50];
    float ave;
    int score;
    int gamesPlayed;
    int additionGames;
    int subtractionGames;
    int multiplicationGames;
    int divisionGames;
    int additionScore;
    int subtractionScore;
    int multiplicationScore;
    int divisionScore;
};

class GameApp {
private:
    User users[100];
    int userCount = 10;

public:
    void run();
    void signup();
    int login(char currentUsername[]);
    void saveUsers();
    void loadUsers();
    void setConsoleColor(int color);
    int menu();
    int addition(int items);
    int subtraction(int items);
    int multiplication(int items);
    int division(int items);
    void updateLeaderboard(char username[], int score, int gameType);
    void leaderboardMenu();
    void showLeaderboard();
    void AdditionLeaderboard();
    void SubtractionLeaderboard();
    void MultiplicationLeaderboard();
    void DivisionLeaderboard();
    void sortLeaderboard();
    void sortAdditionLeaderboard();
    void sortSubtractionLeaderboard();
    void sortMultiplicationLeaderboard();
    void sortDivisionLeaderboard();
};

void GameApp::setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void GameApp::saveUsers() {
    ofstream outFile("user_data.dat");
    for (int i = 0; i < userCount; ++i) {
        outFile << users[i].username << '\n'
                << users[i].password << '\n'
                << users[i].ave << ' '
                << users[i].score << ' '
                << users[i].gamesPlayed << ' '
                << users[i].additionGames << ' '
                << users[i].subtractionGames << ' '
                << users[i].multiplicationGames << ' '
                << users[i].divisionGames << ' '
                << users[i].additionScore << ' '
                << users[i].subtractionScore << ' '
                << users[i].multiplicationScore << ' '
                << users[i].divisionScore << '\n';
    }
    outFile.close();
}

void GameApp::loadUsers() {
    ifstream inFile("user_data.dat");
    userCount = 0;
    while (inFile.getline(users[userCount].username, 50)) {
        inFile.getline(users[userCount].password, 50);
        inFile >> users[userCount].ave
               >> users[userCount].score
               >> users[userCount].gamesPlayed
               >> users[userCount].additionGames
               >> users[userCount].subtractionGames
               >> users[userCount].multiplicationGames
               >> users[userCount].divisionGames
               >> users[userCount].additionScore
               >> users[userCount].subtractionScore
               >> users[userCount].multiplicationScore
               >> users[userCount].divisionScore;
        inFile.ignore(); // Skip newline after numbers
        userCount++;
    }
    inFile.close();
}

void GameApp::sortLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].score > users[i].score) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void GameApp::sortAdditionLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].additionScore > users[i].additionScore) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void GameApp::sortSubtractionLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].subtractionScore > users[i].subtractionScore) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void GameApp::sortMultiplicationLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].multiplicationScore > users[i].multiplicationScore) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void GameApp::sortDivisionLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].divisionScore > users[i].divisionScore) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void GameApp::AdditionLeaderboard() {
    setConsoleColor(COLOR_YELLOW);
    cout << "\nADDITION LEADERBOARD\n";
    sortAdditionLeaderboard();
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].additionScore << endl;
    }
}

void GameApp::SubtractionLeaderboard() {
    setConsoleColor(COLOR_YELLOW);
    cout << "\nSUBTRACTION LEADERBOARD\n";
    sortSubtractionLeaderboard();
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].subtractionScore << endl;
    }
}

void GameApp::MultiplicationLeaderboard() {
    setConsoleColor(COLOR_YELLOW);
    cout << "\nMULTIPLICATION LEADERBOARD\n";
    sortMultiplicationLeaderboard();
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].multiplicationScore << endl;
    }
}

void GameApp::DivisionLeaderboard() {
    setConsoleColor(COLOR_YELLOW);
    cout << "\nDIVISION LEADERBOARD\n";
    sortDivisionLeaderboard();
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].divisionScore << endl;
    }
}

void GameApp::showLeaderboard() {
    setConsoleColor(COLOR_MAGENTA);
    cout << "\nOVERALL LEADERBOARD\n";
    sortLeaderboard();
    for (int i = 0; i < userCount; i++) {
        cout << i + 1 << ". " << users[i].username << " - " << users[i].score << endl;
    }
    setConsoleColor(COLOR_WHITE);
}

void GameApp::leaderboardMenu() {
    int choice;
    do {
        setConsoleColor(COLOR_WHITE);
        cout << "\n\nChoose leaderboard to view:";
        cout << "\n1. Overall";
        cout << "\n2. Addition";
        cout << "\n3. Subtraction";
        cout << "\n4. Multiplication";
        cout << "\n5. Division";
        cout << "\n6. Back to menu";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showLeaderboard(); break;
            case 2: AdditionLeaderboard(); break;
            case 3: SubtractionLeaderboard(); break;
            case 4: MultiplicationLeaderboard(); break;
            case 5: DivisionLeaderboard(); break;
            case 6: break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 6);
}

int main() {
    GameApp app;
    app.run();
    return 0;
}
