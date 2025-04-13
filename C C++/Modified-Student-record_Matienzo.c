#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX 7

// Global variables & Parallel Arrays
char name[MAX][MAX];
int q1[MAX], q2[MAX], q3[MAX];
int last;

// UDFs
void init();
int isfull();
int isempty();
int locate(char n[]);
void del(char n[]);
void add(char n[], int q1, int q2, int q3);
void displayAll();
int menu();
void save();
void retrieve();
float computeAve(int q1, int q2, int q3);
int isduplicate(char n[]);

// New UDFS
void displayOne();
void sort();
void update(char n[], int Q1, int Q2, int Q3);

int main() {
    char n[MAX];
    int Q1, Q2, Q3;
    init(); // initialize the array
    retrieve(); // get the data from code to txt file

    while (1) {
        switch (menu()) {
            case 1:
                system("cls");
                printf("Input Name: ");  scanf(" %[^\n]", n);
                printf("Input Q1: "); scanf("%d", &Q1);
                printf("Input Q2: "); scanf("%d", &Q2);
                printf("Input Q3: "); scanf("%d", &Q3);
                add(n, Q1, Q2, Q3);
                break;
            case 2:
                system("cls");
                update(n, Q1, Q2, Q3);
                break;
            case 3:
                system("cls");
                printf("Input Name: ");
                scanf(" %[^\n]", n);
                del(n);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                system("cls");
                printf("Input name to display:\n");
                scanf(" %[^\n]", n);
                displayOne(n);
                break;
            case 6:
                save();
                exit(0); // save and exit files
            default:
                printf("1 to 6 only.\n");
                system("pause");
        }
    }

    return 0;
}

// UDFs
void init() {
    last = -1;
}

int isfull() {
    return (last == MAX - 1);
}

int isempty() {
    return (last == -1);
}

int locate(char n[]) {
    int i;
    for (i = 0; i <= last; i++) {
        if (strcmp(n, name[i]) == 0)
            return i;
    }
    return -1;
}

void del(char n[]) {
    int p, i;
    if (isempty()) {
        printf("Array is empty.\n");
        system("pause");
    } else {
        p = locate(n);
        if (p < 0) {
            printf("Not found.\n");
            system("pause");
        } else {
            for (i = p; i < last; i++) {
                strcpy(name[i], name[i + 1]);
                q1[i] = q1[i + 1];
                q2[i] = q2[i + 1];
                q3[i] = q3[i + 1];
            }
            last--;
            printf("Record of %s is successfully deleted.\n", n);
            system("pause");
        }
    }
}

void add(char n[], int Q1, int Q2, int Q3) {
    if (isfull()) {
        printf("Array is full.\n");
        system("pause");
        return;
    }
    
    if (isduplicate(n)) { 
        printf("Error: Student name '%s' already exists.\n", n);
        system("pause");
        return;
    }
    
    last++;
    strcpy(name[last], n);
    q1[last] = Q1;
    q2[last] = Q2;
    q3[last] = Q3;
    sort();
    
}

int isduplicate(char n[]) {
    for (int i = 0; i <= last; i++) {
        if (strcmp(n, name[i]) == 0) {
            return 1; // May dups
        }
    }
    return 0; // Walang dups
}

int menu() {
    int op;
    system("cls");
    printf("Menu\n");
    printf("1. Add a Record\n");
    printf("2. Update a Record\n");
    printf("3. Delete a Record\n");
    printf("4. Display All\n");
    printf("5. Display One record\n");
    printf("6. Exit\n");
    printf("\nSelect(1-6): ");
    scanf("%d", &op);
    return op;
}

void displayAll() {
    int i;
    system("cls");
    printf("  NAME\tQ1\tQ2\tQ3\tAVERAGE\tREMARKS\n");
    for (i = 0; i <= last; i++) {
        float ave = computeAve(q1[i], q2[i], q3[i]);
        printf("%d.) %s\t%d\t%d\t%d\t%.2f\t%s\n", i + 1, name[i], q1[i], q2[i], q3[i], ave, ave >= 75 ? "PASS" : "FAIL");
    }
    system("pause");
}

void save() {
    FILE *fp;
    int i;
    fp = fopen("Record.txt", "w+");
    if (fp == NULL) {
        printf("File Error.\n");
        system("pause");
        return;
    }
    
    for (i = 0; i <= last; i++) {
        fprintf(fp, "%s\n%d\n%d\n%d\n", name[i], q1[i], q2[i], q3[i]);
    }
    
    fclose(fp);
    printf("Record saved");
    system("pause");
} 

void retrieve() {
    FILE *fp;
    int Q1, Q2, Q3;
    char n[MAX];
    fp = fopen("Record.txt", "r+");
    if (fp == NULL) {
        printf("File does not exist. Starting with an empty record.\n");
        system("pause");
        return;
    }
    
    while (fscanf(fp, " %[^\n]\n%d\n%d\n%d\n", n, &Q1, &Q2, &Q3) == 4) {
        add(n, Q1, Q2, Q3);
    }
    
    fclose(fp);
}

float computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0;
}

void displayOne(char n[]) {
    system("cls");
    int p = locate(n);
    if (p<0) {
        printf("Record not found"); 
    }else {
    printf("  NAME\tQ1\tQ2\tQ3\tAVERAGE\tREMARKS\n");
        float ave = computeAve(q1[p], q2[p], q3[p]);
        printf("%d.) %s\t%d\t%d\t%d\t%.2f\t%s\n", p + 1, name[p], q1[p], q2[p], q3[p], ave, ave >= 75 ? "PASS":"FAIL");
    
}
    system("pause");
}

void update(char n[], int Q1, int Q2, int Q3) {
    if (isempty()) {
        printf("\nError: No records available to update.\n");
        system("pause");
        return;
    }

    char tempName[MAX]; // Temporary variable to safely input the name
    int quizChoice, newScore;

    printf("\n--- Update Record ---\n");
    printf("Enter the name of the student to update: ");
    scanf(" %[^\n]", tempName);

    int p = locate(tempName); // Use the temporary variable
    if (p < 0) {
        printf("\nError: Record not found.\n");
        system("pause");
        return;
    }

    printf("\nCurrent Record:\n");
    displayOne(tempName); // Use the temporary variable

    printf("\n--- Select Quiz to Update ---\n");
    printf("1. Quiz 1\n");
    printf("2. Quiz 2\n");
    printf("3. Quiz 3\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &quizChoice);

    if (quizChoice < 1 || quizChoice > 3) {
        printf("\nError: Invalid choice. Please select a number between 1 and 3.\n");
        system("pause");
        return;
    }

    printf("\nEnter the new score for Quiz %d: ", quizChoice);
    scanf("%d", &newScore);

    switch (quizChoice) {
        case 1:
            q1[p] = newScore;
            break;
        case 2:
            q2[p] = newScore;
            break;
        case 3:
            q3[p] = newScore;
            break;
    }

    printf("\nSuccess: Record updated successfully.\n");
    system("pause");
}


void sort() {
    int i, j, sortQ1, sortQ2, sortQ3;
    char sortName[MAX];


    for (i = 0; i < last; i++) {
        for (j = 0; j < last - i; j++) { 
            if (strcasecmp(name[j], name[j + 1]) > 0) { 
                
                strcpy(sortName, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], sortName);

                sortQ1 = q1[j];
                q1[j] = q1[j + 1];
                q1[j + 1] = sortQ1;

                sortQ2 = q2[j];
                q2[j] = q2[j + 1];
                q2[j + 1] = sortQ2;

                sortQ3 = q3[j];
                q3[j] = q3[j + 1];
                q3[j + 1] = sortQ3;
            }
        }
    }
}
