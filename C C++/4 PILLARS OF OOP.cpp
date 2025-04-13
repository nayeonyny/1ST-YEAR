#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <time.h>
using namespace std;

// Define color constants
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_WHITE 7

// Class: Game
class Game {
public:
    virtual void run() = 0; // Virtual function for running the game
    virtual int menu() = 0; // Virtual function for displaying the menu
    virtual ~Game() {}      // Virtual destructor 
};

// CLASS USER TO SHOW ENCAPSULATION
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
//ABSTRACTION
// Abstract Base Class: sortLeaderboard
class sortLeaderboard {
public:
    virtual void sort(User users[], int userCount) = 0; // Virtual function for sorting
    virtual int getGamesPlayed(const User &user) const = 0; // Virtual function for games played
    virtual ~sortLeaderboard() {} // Virtual destructor
};
// INHERITANCE
// Derived Class sortOverallLeaderboard
class sortOverallLeaderboard : public sortLeaderboard {
public:
    void sort(User users[], int userCount) override {
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

    int getGamesPlayed(const User &user) const override {
        return user.gamesPlayed; 
    }
};
// INHERITANCE
// Derived Class sortAdditionLeaderboard
class sortAdditionLeaderboard : public sortLeaderboard {
public:
    void sort(User users[], int userCount) override {
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

    int getGamesPlayed(const User &user) const override {
        return user.additionGames; 
    }
};
// INHERITANCE
// Derived Class sortSubtractionLeaderboard
class sortSubtractionLeaderboard : public sortLeaderboard {
public:
    void sort(User users[], int userCount) override {
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

    int getGamesPlayed(const User &user) const override {
        return user.subtractionGames;
    }
};
// INHERITANCE
// Derived Class sortMultiplicationLeaderboard
class sortMultiplicationLeaderboard : public sortLeaderboard {
public:
    void sort(User users[], int userCount) override {
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

    int getGamesPlayed(const User &user) const override {
        return user.multiplicationGames; // Multiplication games played
    }
};
// INHERITANCE
// Derived Class sortDivisionLeaderboard
class sortDivisionLeaderboard : public sortLeaderboard {
public:
    void sort(User users[], int userCount) override {
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

    int getGamesPlayed(const User &user) const override {
        return user.divisionGames;
    }
};
// INHERITANCE
// Derived Class: ArithmeticGame
class ArithmeticGame : public Game {
private:
    User users[100];
    int userCount = 0;

    // Helper functions
    void setConsoleColor(int color);
    int addition(int items, string &currentUsername);
    int subtraction(int items, string &currentUsername);
    int multiplication(int items, string &currentUsername);
    int division(int items, string &currentUsername);
    bool login(string &currentUsername);
    void signup();
    void saveUsers();
    void loadUsers();
    void leaderboardMenu();

    // Leaderboard functions
    void showLeaderboard(sortLeaderboard* sort, const string& title, int scoreType);

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
int ArithmeticGame::addition(int items, string &currentUsername) {
    int cor = 0;
    for (int i = 1; i <= items; i++) {
        int a = rand() % 30 + 1;
        int b = rand() % 30 + 1;
        int ans;
        cout << i << ") What is " << a << " + " << b << "? ";
        cin >> ans;
        if (ans == a + b) {
            cout << "Perfect!\n";
            cor++;
        } else {
            cout << "Incorrect! The correct answer is " << a + b << "\n";
        }
    }

    // Update user scores
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == currentUsername) {
            users[i].score += cor;
            users[i].gamesPlayed++;
            users[i].additionGames++;
            users[i].additionScore += cor;
            users[i].ave = static_cast<float>(users[i].score) / users[i].additionGames;
            break;
        }
    }

    return cor;
}

// Subtraction game
int ArithmeticGame::subtraction(int items, string &currentUsername) {
    int cor = 0;
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
            cor++;
        } else {
            cout << "Incorrect! The correct answer is " << a - b << "\n";
        }
    }

    // Update user scores
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == currentUsername) {
            users[i].score += cor;
            users[i].gamesPlayed++;
            users[i].subtractionGames++;
            users[i].subtractionScore += cor;
            users[i].ave = static_cast<float>(users[i].score) / users[i].subtractionGames;
            break;
        }
    }

    return cor;
}

// Multiplication game
int ArithmeticGame::multiplication(int items, string &currentUsername) {
    int cor = 0;
    for (int i = 1; i <= items; i++) {
        int a = rand() % 25 + 1;
        int b = rand() % 25 + 1;
        int ans;
        cout << i << ") What is " << a << " * " << b << "? ";
        cin >> ans;
        if (ans == a * b) {
            cout << "Perfect!\n";
            cor++;
        } else {
            cout << "Incorrect! The correct answer is " << a * b << "\n";
        }
    }

    // Update user scores
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == currentUsername) {
            users[i].score += cor;
            users[i].gamesPlayed++;
            users[i].multiplicationGames++;
            users[i].multiplicationScore += cor;
            users[i].ave = static_cast<float>(users[i].score) / users[i].multiplicationGames;
            break;
        }
    }

    return cor;
}

// Division game
int ArithmeticGame::division(int items, string &currentUsername) {
    int cor = 0;
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
            cor++;
        } else {
            cout << "Incorrect! The correct answer is " << a / b << "\n";
        }
    }

    // Update user scores
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == currentUsername) {
            users[i].score += cor;
            users[i].gamesPlayed++;
            users[i].divisionGames++;
            users[i].divisionScore += cor;
            users[i].ave = static_cast<float>(users[i].score) / users[i].gamesPlayed;
            break;
        }
    }

    return cor;
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
    ofstream outFile("player.txt");
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
    ifstream inFile("player.txt");
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
// POLYMORPHISM
// Show leaderboard function
void ArithmeticGame::showLeaderboard(sortLeaderboard* sort, const string& title, int scoreType) {
    sort->sort(users, userCount);
    cout << "\n--- " << title << " ---\n";
    cout << left << setw(15) << "Username" << setw(10) << "Score" << setw(15) << "Games Played" << endl;
    for (int i = 0; i < userCount; i++) {
        cout << left << setw(15) << users[i].username
             << setw(10) << scoreType
             << setw(15) << sort->getGamesPlayed(users[i]) << endl;
    }
}

// Leaderboard menu
void ArithmeticGame::leaderboardMenu() {
    int choice;
    do {
        cout << "\n--- Leaderboard Menu ---\n";
        cout << "1. Overall Leaderboard\n";
        cout << "2. Addition Leaderboard\n";
        cout << "3. Subtraction Leaderboard\n";
        cout << "4. Multiplication Leaderboard\n";
        cout << "5. Division Leaderboard\n";
        cout << "6. Back to Main Menu\n";
        cout << "Choose an option: ";
        cin >> choice;
        //POLYMORPHISM
        switch (choice) {
            case 1: {
                sortOverallLeaderboard overallSort;
                showLeaderboard(&overallSort, "Overall Leaderboard", users[0].score);
                break;
            }
            case 2: {
                sortAdditionLeaderboard additionSort;
                showLeaderboard(&additionSort, "Addition Leaderboard", users[0].additionScore);
                break;
            }
            case 3: {
                sortSubtractionLeaderboard subtractionSort;
                showLeaderboard(&subtractionSort, "Subtraction Leaderboard", users[0].subtractionScore);
                break;
            }
            case 4: {
                sortMultiplicationLeaderboard multiplicationSort;
                showLeaderboard(&multiplicationSort, "Multiplication Leaderboard", users[0].multiplicationScore);
                break;
            }
            case 5: {
                sortDivisionLeaderboard divisionSort;
                showLeaderboard(&divisionSort, "Division Leaderboard", users[0].divisionScore);
                break;
            }
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
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
                int cor;
                while (true) {
                    switch (menu()) {
                        case 1:
                            srand(time(NULL));
                            cor = addition(n, currentUsername);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            break;
                        case 2:
                            srand(time(NULL));
                            cor = subtraction(n, currentUsername);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            break;
                        case 3:
                            srand(time(NULL));
                            cor = multiplication(n, currentUsername);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            break;
                        case 4:
                            srand(time(NULL));
                            cor = division(n, currentUsername);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
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
