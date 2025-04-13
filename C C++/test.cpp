#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

// Define color constants
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_WHITE 7

const int MAX_USERS = 100;

class User {
public:
    string username;
    string password;
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

    User()
        : username(""), password(""), ave(0), score(0), gamesPlayed(0),
          additionGames(0), subtractionGames(0), multiplicationGames(0),
          divisionGames(0), additionScore(0), subtractionScore(0),
          multiplicationScore(0), divisionScore(0) {}
};

class Leaderboard {
public:
    User users[MAX_USERS];
    int userCount;

    Leaderboard() : userCount(0) { loadUsers(); }
};

// Game functions
int addition(int items);
int subtraction(int items);
int multiplication(int items);
int division(int items);
int menu();

// Leaderboard functions
void loadUsers(Leaderboard& leaderboard);
void saveUsers(const Leaderboard& leaderboard);
void showLeaderboard(Leaderboard& leaderboard);
void updateLeaderboard(Leaderboard& leaderboard, const string& username, int score, int gameType);
void sortLeaderboard(Leaderboard& leaderboard);
void sortAdditionLeaderboard(Leaderboard& leaderboard);
void AdditionLeaderboard(Leaderboard& leaderboard);
void sortSubtractionLeaderboard(Leaderboard& leaderboard);
void SubtractionLeaderboard(Leaderboard& leaderboard);
void sortMultiplicationLeaderboard(Leaderboard& leaderboard);
void MultiplicationLeaderboard(Leaderboard& leaderboard);
void sortDivisionLeaderboard(Leaderboard& leaderboard);
void DivisionLeaderboard(Leaderboard& leaderboard);
void leaderboardMenu(Leaderboard& leaderboard);
bool login(Leaderboard& leaderboard, string& currentUsername);
void signup(Leaderboard& leaderboard);

int addition(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        a = rand() % 30 + 1;
        b = rand() % 30 + 1;
        cout << i << ") What is " << a << " + " << b << "? ";
        cin >> ans;
        if (ans == a + b) {
            cout << "Perfect!\n";
            c++;
        } else {
            cout << "Incorrect! The correct answer is " << a + b << "\n";
        }
    }
    return c;
}

int subtraction(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        do {
            a = rand() % 30 + 1;
            b = rand() % 30 + 1;
        } while (a < b);
        cout << i << ") What is " << a << " - " << b << "? ";
        cin >> ans;
        if (ans == a - b) {
            cout << "Perfect!\n";
            c++;
        } else {
            cout << "Incorrect! The correct answer is " << a - b << "\n";
        }
    }
    return c;
}

int multiplication(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        a = rand() % 25 + 1;
        b = rand() % 25 + 1;
        cout << i << ") What is " << a << " * " << b << "? ";
        cin >> ans;
        if (ans == a * b) {
            cout << "Perfect!\n";
            c++;
        } else {
            cout << "Incorrect! The correct answer is " << a * b << "\n";
        }
    }
    return c;
}

int division(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        do {
            a = rand() % 100 + 1;
            b = rand() % 50 + 1;
        } while (a % b != 0);
        cout << i << ") What is " << a << " / " << b << "? ";
        cin >> ans;
        if (ans == a / b) {
            cout << "Perfect!\n";
            c++;
        } else {
            cout << "Incorrect! The correct answer is " << a / b << "\n";
        }
    }
    return c;
}

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int menu() {
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
    cout << "Pick 1 to 6:\n";
    cin >> op;
    return op;
}

void loadUsers(Leaderboard& leaderboard) {
    ifstream file("users.txt");
    if (!file) {
        cout << "No existing user data found. Starting with an empty user list.\n";
        return;
    }
    leaderboard.userCount = 0;
    while (leaderboard.userCount < MAX_USERS &&
           file >> leaderboard.users[leaderboard.userCount].username >>
           leaderboard.users[leaderboard.userCount].password >>
           leaderboard.users[leaderboard.userCount].additionGames >>
           leaderboard.users[leaderboard.userCount].subtractionGames >>
           leaderboard.users[leaderboard.userCount].multiplicationGames >>
           leaderboard.users[leaderboard.userCount].divisionGames >>
           leaderboard.users[leaderboard.userCount].additionScore >>
           leaderboard.users[leaderboard.userCount].subtractionScore >>
           leaderboard.users[leaderboard.userCount].multiplicationScore >>
           leaderboard.users[leaderboard.userCount].divisionScore >>
           leaderboard.users[leaderboard.userCount].ave) {
        leaderboard.userCount++;
    }
    file.close();
    cout << "User data loaded successfully. Total users: " << leaderboard.userCount << "\n";
}

void saveUsers(const Leaderboard& leaderboard) {
    ofstream file("users.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (int i = 0; i < leaderboard.userCount; i++) {
        file << leaderboard.users[i].username << " " << leaderboard.users[i].password << " "
             << leaderboard.users[i].additionGames << " " << leaderboard.users[i].subtractionGames << " "
             << leaderboard.users[i].multiplicationGames << " " << leaderboard.users[i].divisionGames << " "
             << leaderboard.users[i].additionScore << " " << leaderboard.users[i].subtractionScore << " "
             << leaderboard.users[i].multiplicationScore << " " << leaderboard.users[i].divisionScore << " "
             << leaderboard.users[i].ave << "\n";
    }
    file.close();
    cout << "User data saved successfully.\n";
}

bool login(Leaderboard& leaderboard, string& currentUsername) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].username == username && leaderboard.users[i].password == password) {
            cout << "Login successful\n";
            currentUsername = username;
            return true;
        }
    }
    cout << "Invalid username or password. Please try again.\n";
    return false;
}

void signup(Leaderboard& leaderboard) {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].username == username) {
            cout << "Username already taken, please use a different one\n";
            return;
        }
    }

    leaderboard.users[leaderboard.userCount].username = username;
    leaderboard.users[leaderboard.userCount].password = password;
    leaderboard.userCount++;
    saveUsers(leaderboard);
    cout << "Signup successful!\n";
}

void sortLeaderboard(Leaderboard& leaderboard) {
    for (int i = 0; i < leaderboard.userCount - 1; i++) {
        for (int j = i + 1; j < leaderboard.userCount; j++) {
            if (leaderboard.users[j].ave > leaderboard.users[i].ave) {
                User temp = leaderboard.users[i];
                leaderboard.users[i] = leaderboard.users[j];
                leaderboard.users[j] = temp;
            }
        }
    }
}

void showLeaderboard(Leaderboard& leaderboard) {
    sortLeaderboard(leaderboard);
    cout << "\n--- Leaderboard ---\n";
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].additionGames > 0 && leaderboard.users[i].subtractionGames > 0 &&
            leaderboard.users[i].multiplicationGames > 0 && leaderboard.users[i].divisionGames > 0) {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": " << leaderboard.users[i].ave << "\n";
        } else {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": (Play 1 game in each to see your average)\n";
        }
    }
}

void updateLeaderboard(Leaderboard& leaderboard, const string& username, int score, int gameType) {
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].username == username) {
            leaderboard.users[i].gamesPlayed++;
            if (gameType == 1) {
                leaderboard.users[i].additionGames++;
                leaderboard.users[i].additionScore += score;
            } else if (gameType == 2) {
                leaderboard.users[i].subtractionGames++;
                leaderboard.users[i].subtractionScore += score;
            } else if (gameType == 3) {
                leaderboard.users[i].multiplicationGames++;
                leaderboard.users[i].multiplicationScore += score;
            } else if (gameType == 4) {
                leaderboard.users[i].divisionGames++;
                leaderboard.users[i].divisionScore += score;
            }
            leaderboard.users[i].ave = (float)(leaderboard.users[i].additionScore + leaderboard.users[i].subtractionScore +
                                               leaderboard.users[i].multiplicationScore + leaderboard.users[i].divisionScore) /
                                       leaderboard.users[i].gamesPlayed;
            saveUsers(leaderboard);
            return;
        }
    }
}

void sortAdditionLeaderboard(Leaderboard& leaderboard) {
    for (int i = 0; i < leaderboard.userCount - 1; i++) {
        for (int j = i + 1; j < leaderboard.userCount; j++) {
            if (leaderboard.users[j].additionGames > leaderboard.users[i].additionGames) {
                User temp = leaderboard.users[i];
                leaderboard.users[i] = leaderboard.users[j];
                leaderboard.users[j] = temp;
            }
        }
    }
}

void AdditionLeaderboard(Leaderboard& leaderboard) {
    sortAdditionLeaderboard(leaderboard);
    cout << "\n--- Addition Leaderboard ---\n";
    cout << "Rank|Username  |Number of games|Total Score\n";
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].additionGames > 0) {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": \t\t" << leaderboard.users[i].additionGames << "\t\t" << leaderboard.users[i].additionScore << "\n";
        } else {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": (No addition games played)\n";
        }
    }
}

void sortSubtractionLeaderboard(Leaderboard& leaderboard) {
    for (int i = 0; i < leaderboard.userCount - 1; i++) {
        for (int j = i + 1; j < leaderboard.userCount; j++) {
            if (leaderboard.users[j].subtractionGames > leaderboard.users[i].subtractionGames) {
                User temp = leaderboard.users[i];
                leaderboard.users[i] = leaderboard.users[j];
                leaderboard.users[j] = temp;
            }
        }
    }
}

void SubtractionLeaderboard(Leaderboard& leaderboard) {
    sortSubtractionLeaderboard(leaderboard);
    cout << "\n--- Subtraction Leaderboard ---\n";
    cout << "Rank|Username  |Number of games|Total Score\n";
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].subtractionGames > 0) {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": \t\t" << leaderboard.users[i].subtractionGames << "\t\t" << leaderboard.users[i].subtractionScore << "\n";
        } else {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": (No subtraction games played)\n";
        }
    }
}

void sortMultiplicationLeaderboard(Leaderboard& leaderboard) {
    for (int i = 0; i < leaderboard.userCount - 1; i++) {
        for (int j = i + 1; j < leaderboard.userCount; j++) {
            if (leaderboard.users[j].multiplicationScore > leaderboard.users[i].multiplicationScore) {
                User temp = leaderboard.users[i];
                leaderboard.users[i] = leaderboard.users[j];
                leaderboard.users[j] = temp;
            }
        }
    }
}

void MultiplicationLeaderboard(Leaderboard& leaderboard) {
    sortMultiplicationLeaderboard(leaderboard);
    cout << "\n--- Multiplication Leaderboard ---\n";
    cout << "Rank|Username  |Number of games|Total Score\n";
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].multiplicationGames > 0) {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": \t\t" << leaderboard.users[i].multiplicationGames << "\t\t" << leaderboard.users[i].multiplicationScore << "\n";
        } else {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": (No multiplication games played)\n";
        }
    }
}

void sortDivisionLeaderboard(Leaderboard& leaderboard) {
    for (int i = 0; i < leaderboard.userCount - 1; i++) {
        for (int j = i + 1; j < leaderboard.userCount; j++) {
            if (leaderboard.users[j].divisionGames > leaderboard.users[i].divisionGames) {
                User temp = leaderboard.users[i];
                leaderboard.users[i] = leaderboard.users[j];
                leaderboard.users[j] = temp;
            }
        }
    }
}

void DivisionLeaderboard(Leaderboard& leaderboard) {
    sortDivisionLeaderboard(leaderboard);
    cout << "\n--- Division Leaderboard ---\n";
    cout << "Rank|Username  |Number of games|Total Score\n";
    for (int i = 0; i < leaderboard.userCount; i++) {
        if (leaderboard.users[i].divisionGames > 0) {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": \t\t" << leaderboard.users[i].divisionGames << "\t\t" << leaderboard.users[i].divisionScore << "\n";
        } else {
            cout << i + 1 << ". " << leaderboard.users[i].username << ": (No division games played)\n";
        }
    }
}

void leaderboardMenu(Leaderboard& leaderboard) {
    int choice;
    while (true) {
        cout << "\n--- Leaderboards ---\n";
        cout << "1. Addition Leaderboard\n";
        cout << "2. Subtraction Leaderboard\n";
        cout << "3. Multiplication Leaderboard\n";
        cout << "4. Division Leaderboard\n";
        cout << "5. Overall Leaderboard\n";
        cout << "6. Back to Main Menu\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AdditionLeaderboard(leaderboard);
                break;
            case 2:
                SubtractionLeaderboard(leaderboard);
                break;
            case 3:
                MultiplicationLeaderboard(leaderboard);
                break;
            case 4:
                DivisionLeaderboard(leaderboard);
                break;
            case 5:
                showLeaderboard(leaderboard);
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    Leaderboard leaderboard;
    string currentUsername;
    const int n = 5;
    int choice, cor;

    while (true) {
        cout << "\n1. Login\n2. Signup\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            if (login(leaderboard, currentUsername)) {
                while (true) {
                    switch (menu()) {
                        case 1:
                            srand(time(nullptr));
                            cor = addition(n);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            updateLeaderboard(leaderboard, currentUsername, cor, 1);
                            break;
                        case 2:
                            srand(time(nullptr));
                            cor = subtraction(n);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            updateLeaderboard(leaderboard, currentUsername, cor, 2);
                            break;
                        case 3:
                            srand(time(nullptr));
                            cor = multiplication(n);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            updateLeaderboard(leaderboard, currentUsername, cor, 3);
                            break;
                        case 4:
                            srand(time(nullptr));
                            cor = division(n);
                            cout << "You got " << cor << " correct answers out of " << n << "\n";
                            updateLeaderboard(leaderboard, currentUsername, cor, 4);
                            break;
                        case 5:
                            leaderboardMenu(leaderboard);
                            break;
                        case 6:
                            exit(0);
                            system("cls");
                            return 0;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                }
            } else {
                cout << "Login failed. Please try again.\n";
            }
        } else if (choice == 2) {
            signup(leaderboard);
        } else if (choice == 3) {
            exit(0);
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
