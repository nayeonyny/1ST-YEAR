#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Randint game functions
int addition(int items);
int subtraction(int items);
int multiplication(int items);
int division(int items);
int menu();
// File handling functions
int login();
void signup();
void loadUsers();
void saveUsers();
void showLeaderboard();
void updateLeaderboard(char username[], int score);

// For saving user input/login
typedef struct {
    char username[50];
    char password[50];
    int score;  // Add score field
} User;

User users[100];
int userCount = 10;

int main() {
    loadUsers();

    int choice;
    while (1) {
        printf("\n1. Login\n2. Signup\n3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (login()) {
                int n = 10;
                int cor = 0;
                while (1) {
                    switch (menu()) {
                        case 1:
                            srand(time(NULL));
                            cor = addition(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            break;
                        case 2:
                            srand(time(NULL));
                            cor = subtraction(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            break;
                        case 3:
                            srand(time(NULL));
                            cor = multiplication(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            break;
                        case 4:
                            srand(time(NULL));
                            cor = division(n);
                            printf("You got %d correct answers out of %d\n", cor, n);
                            break;
                        case 5:
                            exit(0);
                            system("cls");
                            return 0;
                        case 6:
                            showLeaderboard();
                            break;
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
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
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
            a = rand() % 10 + 1;
            b = rand() % 10 + 1;
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
        a = rand() % 10 + 1;
        b = rand() % 10 + 1;
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
            a = rand() % 10 + 1;
            b = rand() % 10 + 1;
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

int menu() {
    int op;
    printf("\n***********************************\n");
    printf("Welcome to the Arithmetic Game");
    return c;
}

int menu (){
    int op;
    printf("\n***********************************\n");
    printf("Welcome to the Arithmetic Game");
    printf ("\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Show Leaderboards\n6.Exit\n");
    printf ("Pick 1 to 6:\n");
    scanf("%d", &op);
    return op;
}

int login (char currentUsername[]) {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username); 
    printf("Enter your password: ");
    scanf("%s", password); 

    //if username is saved is same as the registered one and if password saved is same as the registered one
    for (int i = 0; i < userCount;i++) { 
        if(strcmp(users[i].username,username) == 0 && strcmp (users[i].password,password) == 0){ 
            printf("login successfully");
            strcpy(currentUsername, username);  // Store the current username
            return 1;
        }
    }
    return 0;
}

void signup () {
    char username[50];
    char password[50];

    printf("Enter a new username: ");
    scanf("%s", username); 
    printf("Enter a your password: ");
    scanf("%s", password); 

    // check if account is existing
    for (int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username,username)==0) {
            printf("Username already taken, please use a different one\n");
            return ;
        }
    }
    //copy the registered username and password
    strcpy(users[userCount].username,username);
    strcpy(users[userCount].password,password);
    users[userCount].score = 0;  //initialize score 0
    users[userCount].gamesPlayed = 0;  //initialize games played 0
    userCount++;

    //Insert and Save users username and password for future purposes
    FILE *ptr = fopen("users.txt", "a");  // Open in append mode
    if (ptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(ptr, "%s %s %d\n", username, password, 0);   // Save with initial score 0
    fclose(ptr);

    printf("Signup successful!\n");
}

void saveUsers() {
    FILE *ptr = fopen("users.txt", "w");
    if (ptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    //Save username, password and score
    for (int i = 0; i < userCount; i++) {
        fprintf(ptr, "%s %s %d %d\n", users[i].username, users[i].password,users[i].score,users[i].gamesPlayed);
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
    // Load user username, password, score, and gamesPlayed
    userCount = 0;
    while (fscanf(ptr, "%s %s %d %d", users[userCount].username, users[userCount].password, &users[userCount].score, &users[userCount].gamesPlayed) == 4) {
        userCount++;
        if (userCount >= 100) {  // Prevent buffer overflow
            printf("Maximum limit reached, don't add more\n");
            break;
        }
    }

    fclose(ptr);
    printf("User data loaded successfully.\n");
}

void showLeaderboard() {
    printf("\n--- Leaderboard ---\n");
    for (int i = 0; i < userCount; i++) {
        printf("%d. %s: %f\n", i + 1, users[i].username, users[i].ave); 
        //displays rank, name, score in order
    }
}

void updateLeaderboard(char username[], int score) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            users[i].score += score;  // Add new score instead of replacing
            users[i].gamesPlayed++;  // Increment games played
            users[i].ave = (float)users[i].score / users[i].gamesPlayed;  // Compute average
            saveUsers();  // Save updated scores
            return;
        }
    }
}

