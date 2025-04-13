#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <iomanip>

using namespace std;

// Define color constants
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_WHITE 7

// Abstract Base Class: Game
class Game {
public:
    virtual void run() = 0; // Pure virtual function for running the game
    virtual int menu() = 0; // Pure virtual function for displaying the menu
    virtual ~Game() {}      // Virtual destructor for proper cleanup
};

// User class to encapsulate user data
class User {
public:
    string username;
    string password;
    float ave = 0.0;
    int score = 0;
    int gamesPlayed = 0;
    int additionGames = 0;
    int subtractionGames = 0;
    int multiplicationGames = 0;
    int divisionGames = 0;
    int additionScore = 0;
    int subtractionScore = 0;
    int multiplicationScore = 0;
    int divisionScore = 0;
};

// Derived Class: ArithmeticGame
class ArithmeticGame : public Game {
private:
    User users[100];
    int userCount = 0;

    // Helper functions
    void setConsoleColor(int color);
    int addition(int items);
    int subtraction(int items);
    int multiplication(int items);
    int division(int items);
    bool login(string &currentUsername);
    void signup();
    void saveUsers();
    void loadUsers();
    void leaderboardMenu();

    // Leaderboard functions
    void sortLeaderboard();
    void sortAdditionLeaderboard();
    void sortSubtractionLeaderboard();
    void sortMultiplicationLeaderboard();
    void sortDivisionLeaderboard();
    void showOverallLeaderboard();
    void showAdditionLeaderboard();
    void showSubtractionLeaderboard();
    void showMultiplicationLeaderboard();
    void showDivisionLeaderboard();

public:
    // Override base class methods
    void run() override;
    int menu() override;
};

// Set console text color
void ArithmeticGame::setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Menu function (overrides base class method)
int ArithmeticGame::menu() {
    int op;
    cout << "\n***********************************\n";
    cout << "Welcome to the Arithmetic Game\n";
    setConsoleColor(COLOR_GREEN);
    cout << "1. Easy Addition\n";
    setConsoleColor(COLOR_YELLOW);
    cout << "2. Standard Subtraction\n";
    setConsoleColor(COLOR_RED);
    cout << "3. Crazy Multiplication\n";
    setConsoleColor(COLOR_MAGENTA);
    cout << "4. Extreme Division\n";
    setConsoleColor(COLOR_WHITE);
    cout << "5. Leaderboards\n";
    cout << "6. Exit\n";
    cout << "***********************************\n";
    cout << "Pick 1 to 6: ";
    cin >> op;

    return op;
}

// Addition game
int ArithmeticGame::addition(int items) {
    int correct = 0;
    for (int i = 1; i <= items; i++) {
        int a = rand() % 30 + 1;
        int b = rand() % 30 + 1;
        int ans;
        cout << i << ") What is " << a << " + " << b << "? ";
        cin >> ans;
        if (ans == a + b) {
            cout << "Perfect!\n";
            correct++;
        } else {
            cout << "Incorrect! The correct answer is " << a + b << "\n";
        }
    }
    return correct;
}

// Subtraction game
int ArithmeticGame::subtraction(int items) {
    int correct = 0;
    for (int i = 1; i <= items; i++) {
        int a, b;
        do {
            a = rand() % 30 + 1;
            b = rand() % 30 + 1;
        } while (a < b);
        int ans;
        cout << i << ") What is " << a << " - " << b << "? ";
        cin >> ans;
        if (ans == a - b) {
            cout << "Perfect!\n";
            correct++;
        } else {
            cout << "Incorrect! The correct answer is " << a - b << "\n";
        }
    }
    return correct;
}

// Multiplication game
int ArithmeticGame::multiplication(int items) {
    int correct = 0;
    for (int i = 1; i <= items; i++) {
        int a = rand() % 25 + 1;
        int b = rand() % 25 + 1;
        int ans;
        cout << i << ") What is " << a << " * " << b << "? ";
        cin >> ans;
        if (ans == a * b) {
            cout << "Perfect!\n";
            correct++;
        } else {
            cout << "Incorrect! The correct answer is " << a * b << "\n";
        }
    }
    return correct;
}

// Division game
int ArithmeticGame::division(int items) {
    int correct = 0;
    for (int i = 1; i <= items; i++) {
        int a, b;
        do {
            a = rand() % 100 + 1;
            b = rand() % 50 + 1;
        } while (a % b != 0);
        int ans;
        cout << i << ") What is " << a << " / " << b << "? ";
        cin >> ans;
        if (ans == a / b) {
            cout << "Perfect!\n";
            correct++;
        } else {
            cout << "Incorrect! The correct answer is " << a / b << "\n";
        }
    }
    return correct;
}

// Login function
bool ArithmeticGame::login(string &currentUsername) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful!\n";
            currentUsername = username;
            return true;
        }
    }
    cout << "Invalid username or password. Please try again.\n";
    return false;
}

// Signup function
void ArithmeticGame::signup() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "Username already taken, please use a different one.\n";
            return;
        }
    }

    users[userCount].username = username;
    users[userCount].password = password;
    userCount++;

    cout << "Signup successful!\n";
}

// Save users to file
void ArithmeticGame::saveUsers() {
    ofstream outFile("users.txt");
    for (int i = 0; i < userCount; i++) {
        outFile << users[i].username << " " << users[i].password << " "
                << users[i].ave << " " << users[i].score << " "
                << users[i].gamesPlayed << " " << users[i].additionGames << " "
                << users[i].subtractionGames << " " << users[i].multiplicationGames << " "
                << users[i].divisionGames << " " << users[i].additionScore << " "
                << users[i].subtractionScore << " " << users[i].multiplicationScore << " "
                << users[i].divisionScore << "\n";
    }
    outFile.close();
    cout << "User data saved successfully.\n";
}

// Load users from file
void ArithmeticGame::loadUsers() {
    ifstream inFile("users.txt");
    if (!inFile) {
        cout << "No existing user data found. Starting with an empty user list.\n";
        return;
    }
    userCount = 0;
    while (inFile >> users[userCount].username >> users[userCount].password
                  >> users[userCount].ave >> users[userCount].score
                  >> users[userCount].gamesPlayed >> users[userCount].additionGames
                  >> users[userCount].subtractionGames >> users[userCount].multiplicationGames
                  >> users[userCount].divisionGames >> users[userCount].additionScore
                  >> users[userCount].subtractionScore >> users[userCount].multiplicationScore
                  >> users[userCount].divisionScore) {
        userCount++;
    }
    inFile.close();
    cout << "User data loaded successfully. Total users: " << userCount << "\n";
}

// Leaderboard sorting and display functions
void ArithmeticGame::sortLeaderboard() {
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

void ArithmeticGame::showOverallLeaderboard() {
    sortLeaderboard();
    cout << "\n--- Overall Leaderboard ---\n";
    cout << left << setw(15) << "Username" << setw(10) << "Score" << setw(10) << "Games Played" << endl;
    for (int i = 0; i < userCount; i++) {
        cout << left << setw(15) << users[i].username << setw(10) << users[i].score << setw(10) << users[i].gamesPlayed << endl;
    }
}

// Leaderboard menu
void ArithmeticGame::leaderboardMenu() {
    int choice;
    do {
        cout << "\n--- Leaderboard Menu ---\n";
        cout << "1. Overall Leaderboard\n";
        cout << "2. Back to Main Menu\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showOverallLeaderboard();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);
}

// Run the game (overrides base class method)
void ArithmeticGame::run() {
    loadUsers();

    int choice;
    string currentUsername;
    const int n = 5; // Number of questions

    while (true) {
        cout << "\n1. Login\n2. Signup\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            if (login(currentUsername)) {
                int correct;
                while (true) {
                    switch (menu()) {
                        case 1:
                            correct = addition(n);
                            cout << "You got " << correct << " correct answers out of " << n << "\n";
                            break;
                        case 2:
                            correct = subtraction(n);
                            cout << "You got " << correct << " correct answers out of " << n << "\n";
                            break;
                        case 3:
                            correct = multiplication(n);
                            cout << "You got " << correct << " correct answers out of " << n << "\n";
                            break;
                        case 4:
                            correct = division(n);
                            cout << "You got " << correct << " correct answers out of " << n << "\n";
                            break;
                        case 5:
                            leaderboardMenu();
                            break;
                        case 6:
                            saveUsers();
                            cout << "Exiting the game. Goodbye!\n";
                            return;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
        } else if (choice == 2) {
            signup();
        } else if (choice == 3) {
            saveUsers();
            cout << "Exiting the game. Goodbye!\n";
            return;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Main function
int main() {
    ArithmeticGame game;
    game.run();
    return 0;
}
