#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Define color constants
#define COLOR_GREEN 2
#define COLOR_YELLOW 6
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_WHITE 7

// Randint game functions
int addition(int items);
int subtraction(int items);
int multiplication(int items);
int division(int items);
int menu();
// File handling functions
int login(char currentUsername[]);
void signup();
void loadUsers();
void saveUsers();

//leaderboards functions
void showLeaderboard();
void updateLeaderboard(char username[], int score, int gameType);
void sortLeaderboard();
void sortAdditionLeaderboard();
void AdditionLeaderboard();
void sortSubtractionLeaderboard();
void SubtractionLeaderboard();
void sortMultiplicationLeaderboard();
void MultiplicationLeaderboard();
void sortDivisionLeaderboard();
void DivisionLeaderboard();
void leaderboardMenu();

// For saving user input
typedef struct {
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
} User;

User users[100];
int userCount = 10;

int main() {
    loadUsers();

    int choice;
    char currentUsername[50];  
    const int n = 5;  // Number of questions
    while (1) {
        printf("\n1. Login\n2. Signup\n3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (login(currentUsername)) {
                int cor;
                while (1) {
                    switch (menu()) {
                        case 1:
                            srand(time(NULL));
                            cor = addition(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            updateLeaderboard(currentUsername, cor, 1);
                            break;
                        case 2:
                            srand(time(NULL));
                            cor = subtraction(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            updateLeaderboard(currentUsername, cor, 2);
                            break;
                        case 3:
                            srand(time(NULL));
                            cor = multiplication(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            updateLeaderboard(currentUsername, cor, 3);
                            break;
                        case 4:
                            srand(time(NULL));
                            cor = division(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            updateLeaderboard(currentUsername, cor, 4);
                            break;
                        case 5:
                            leaderboardMenu();  // Call the leaderboard menu
                            break;
                        case 6:
                            exit(0);
                            system("cls");
                            return 0;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
            } else {
                printf("Login failed. Please try again.\n");
            }
        } else if (choice == 2) {
            signup();
        } else if (choice == 3) {
            exit(0);
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int addition(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        a = rand() % 30 + 1;
        b = rand() % 30 + 1;
        printf("%d) What is %d + %d?", i, a, b);
        scanf("%d", &ans);
        if (ans == a + b) {
            printf("Perfect!\n");
            c++;
        } else {
            printf("Incorrect! The correct answer is %d\n", a + b);
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
        printf("%d) What is %d - %d?", i, a, b);
        scanf("%d", &ans);
        if (ans == a - b) {
            printf("Perfect!\n");
            c++;
        } else {
            printf("Incorrect! The correct answer is %d\n", a - b);
        }
    }
    return c;
}

int multiplication(int items) {
    int i, a, b, ans, c = 0;
    for (i = 1; i <= items; i++) {
        a = rand() % 25 + 1;
        b = rand() % 25 + 1;
        printf("%d) What is %d * %d?", i, a, b);
        scanf("%d", &ans);
        if (ans == a * b) {
            printf("Perfect!\n");
            c++;
        } else {
            printf("Incorrect! The correct answer is %d\n", a * b);
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
        printf("%d) What is %d / %d?", i, a, b);
        scanf("%d", &ans);
        if (ans == a / b) {
            printf("Perfect!\n");
            c++;
        } else {
            printf("Incorrect! The correct answer is %d\n", a / b);
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
    printf("\n***********************************\n");
    printf("Welcome to the Arithmetic Game\n");
    setConsoleColor(COLOR_GREEN);
    printf("1. Easy Addition\n");
    setConsoleColor(COLOR_YELLOW);
    printf("2. Standard Subtraction\n");
    setConsoleColor(COLOR_RED);
    printf("3. Crazy Multiplication\n");
    setConsoleColor(COLOR_MAGENTA);
    printf("4. Extreme Division\n");
    setConsoleColor(COLOR_WHITE);
    printf("5. Leaderboards\n");
    printf("6. Exit\n");
    printf("***********************************\n");
    printf("Pick 1 to 6:\n");
    scanf("%d", &op);

    return op;
}

int login(char currentUsername[]) {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    // if username is saved is same as the registered one and if password saved is same as the registered one
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("login successfully");
            strcpy(currentUsername, username);  // Store the current username
            return 1;
            system("cls");
        } else {
            printf("Invalid username or password. Please try again.\n");
            return 0;
            system("cls");
        }
    }
    return 0;
    system("cls");
}

void signup() {
    char username[50];
    char password[50];

    printf("Enter a new username: ");
    scanf("%s", username);
    printf("Enter a your password: ");
    scanf("%s", password);

    // check if account is existing
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already taken, please use a different one\n");
            return;
        }
    }
    // copy the registered username and password
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].score = 0;  // initialize score 0
    users[userCount].gamesPlayed = 0;  // initialize games played 0
    users[userCount].additionGames = 0;  // initialize addition games played 0
    users[userCount].subtractionGames = 0;  // initialize subtraction games played 0
    users[userCount].multiplicationGames = 0;  // initialize multiplication games played 0
    users[userCount].divisionGames = 0;  // initialize division games played 0
    userCount++;

    // Insert and Save users username and password for future purposes
    FILE *ptr = fopen("users.txt", "a");  // Open in append mode
    if (ptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(ptr, "%s %s %d %d %d %d %d %d\n", username, password, 0, 0, 0, 0, 0, 0);  // Save with initial scores and games played
    fclose(ptr);

    printf("Signup successful!\n");
    system("cls");
}

void saveUsers() {
    FILE *ptr = fopen("users.txt", "w");
    if (ptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(ptr, "%s %s %d %d %d %d %d %d %d %d %f\n",
                users[i].username, users[i].password,
                users[i].additionGames, users[i].subtractionGames,
                users[i].multiplicationGames, users[i].divisionGames,
                users[i].additionScore, users[i].subtractionScore,
                users[i].multiplicationScore, users[i].divisionScore,
                users[i].ave);
    }
    fclose(ptr);
    printf("User data saved successfully.\n");
}

void loadUsers() {
    FILE *ptr = fopen("users.txt", "r");
    if (ptr == NULL) {
        printf("No existing user data found. Starting with an empty user list.\n");
        return;
    }
    userCount = 0;
    while (1) {
        int result = fscanf(ptr, "%s %s %d %d %d %d %d %d %d %d %f",
                            users[userCount].username, users[userCount].password,
                            &users[userCount].additionGames, &users[userCount].subtractionGames,
                            &users[userCount].multiplicationGames, &users[userCount].divisionGames,
                            &users[userCount].additionScore, &users[userCount].subtractionScore,
                            &users[userCount].multiplicationScore, &users[userCount].divisionScore,
                            &users[userCount].ave);
        if (result == 11) {  
            userCount++;
            if (userCount >= 100) {  
                printf("Maximum user limit reached. Cannot load more users.\n");
                break;
            }
        } else if (feof(ptr)) {  
            break;
        } else {  
            printf("Error reading user data. Skipping invalid line.\n");
            char buffer[100];
            fgets(buffer, sizeof(buffer), ptr);  
        }
    }
    fclose(ptr);
    printf("User data loaded successfully. Total users: %d\n", userCount);
}

void sortLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].ave > users[i].ave) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void showLeaderboard() {
    sortLeaderboard();  // Sort the users before displaying the leaderboard
    printf("\n--- Leaderboard ---\n");
    for (int i = 0; i < userCount; i++) {
        if (users[i].additionGames > 0 && users[i].subtractionGames > 0 && users[i].multiplicationGames > 0 && users[i].divisionGames > 0) {
            printf("%d. %s: %.2f\n", i + 1, users[i].username, users[i].ave);
            // displays rank, name, and average score in order
        } else {
            printf("%d. %s: (Play 1 game in each to see your average)\n", i + 1, users[i].username);
        }
    }
}

void updateLeaderboard(char username[], int score, int gameType) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            users[i].gamesPlayed++;  // Increment total games played

            if (gameType == 1) {  // Addition
                users[i].additionGames++;
                users[i].additionScore += score;
            } else if (gameType == 2) {  // Subtraction
                users[i].subtractionGames++;
                users[i].subtractionScore += score;
            } else if (gameType == 3) {  // Multiplication
                users[i].multiplicationGames++;
                users[i].multiplicationScore += score;
            } else if (gameType == 4) {  // Division
                users[i].divisionGames++;
                users[i].divisionScore += score;
            }

            // Update average score
            users[i].ave = (float)(users[i].additionScore + users[i].subtractionScore +
                                   users[i].multiplicationScore + users[i].divisionScore) /
                           users[i].gamesPlayed;

            saveUsers();  // Save updated scores to file
            return;
        }
    }
}

void sortAdditionLeaderboard() {
    for (int i = 0; i < userCount-1; i++ ) {
        for (int j = 1; j < userCount; j++ ) {
            if (users[j].additionGames > users[i].additionGames) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}
        
    

void AdditionLeaderboard() {
    sortAdditionLeaderboard();  // Sort the users before displaying the leaderboard
    printf("\n--- Addition Leaderboard ---\n");
    printf("Rank|Username  |Number of games|Total Score\n");
    for (int i = 0; i < userCount; i++) {
        if (users[i].additionGames > 0) {
            printf("%d. %s: \t\t%d \t\t%d\n", i + 1, users[i].username, users[i].additionGames, users[i].additionScore);
        } else {
            printf("%d. %s: (No addition games played)\n", i + 1, users[i].username);
        }
    }
}

void sortSubtractionLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].subtractionGames > users[i].subtractionGames) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void SubtractionLeaderboard() {
    sortSubtractionLeaderboard();  // Sort the users before displaying the leaderboard
    printf("\n--- Subtraction Leaderboard ---\n");
    printf("Rank|Username  |Number of games|Total Score\n");
    for (int i = 0; i < userCount; i++) {
        if (users[i].subtractionGames > 0) {
            printf("%d. %s:\t\t%d \t\t%d\n", i + 1, users[i].username, users[i].subtractionGames, users[i].subtractionScore);
        } else {
            printf("%d. %s: (No subtraction games played)\n", i + 1, users[i].username);
        }
    }
}

void sortMultiplicationLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].multiplicationScore > users[i].multiplicationScore) { // Compare scores instead of games
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void MultiplicationLeaderboard() {
    sortMultiplicationLeaderboard();  // Sort the users before displaying the leaderboard
    printf("\n--- Multiplication Leaderboard ---\n");
    printf("Rank|Username  |Number of games|Total Score\n");
    for (int i = 0; i < userCount; i++) {
        if (users[i].multiplicationGames > 0) {
            printf("%d. %s: \t\t%d \t\t%d\n", i + 1, users[i].username, users[i].multiplicationGames, users[i].multiplicationScore);
        } else {
            printf("%d. %s: (No multiplication games played)\n", i + 1, users[i].username);
        }
    }
}

void sortDivisionLeaderboard() {
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (users[j].divisionGames > users[i].divisionGames) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

void DivisionLeaderboard() {
    sortDivisionLeaderboard();  // Sort the users before displaying the leaderboard
    printf("\n--- Division Leaderboard ---\n");
    printf("Rank|Username  |Number of games|Total Score\n");
    for (int i = 0; i < userCount; i++) {
        if (users[i].divisionGames > 0) {
            printf("%d. %s: \t\t%d \t\t%d\n", i + 1, users[i].username, users[i].divisionGames, users[i].divisionScore);
        } else {
            printf("%d. %s: (No division games played)\n", i + 1, users[i].username);
        }
    }
}

void leaderboardMenu() {
    int choice;
    while (1) {
        printf("\n--- Leaderboards ---\n");
        printf("1. Addition Leaderboard\n");
        printf("2. Subtraction Leaderboard\n");
        printf("3. Multiplication Leaderboard\n");
        printf("4. Division Leaderboard\n");
        printf("5. Overall Leaderboard\n");
        printf("6. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AdditionLeaderboard();
                break;
            case 2:
                SubtractionLeaderboard();
                break;
            case 3:
                MultiplicationLeaderboard();
                break;
            case 4:
                DivisionLeaderboard();
                break;
            case 5:
                showLeaderboard();
                break;
            case 6:
                return;  // Exit the leaderboard menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}