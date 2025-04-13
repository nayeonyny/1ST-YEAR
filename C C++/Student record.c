#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy(), strcmp()

#define MAX 7

// Global variables
// Parallel Arrays
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
void display();
int menu();
void save();
void retrieve();
float computeAve(int q1, int q2, int q3);
int isduplicate();

int main() {
    char n[MAX];
    int Q1, Q2, Q3;
    init(); // initialize the array
    retrieve(); // populate the parallel arrays with data from file

    while (1) {
        switch (menu()) {
            case 1:
                system("cls");
                printf("Input Name: ");
                scanf(" %[^\n]", n);
                printf("Input Q1: ");
                scanf("%d", &Q1);
                printf("Input Q2: ");
                scanf("%d", &Q2);
                printf("Input Q3: ");
                scanf("%d", &Q3);
                add(n, Q1, Q2, Q3);
                break;
            case 2:
                system("cls");
                printf("Input Name: ");
                scanf(" %[^\n]", n);
                del(n);
                break;
            case 3:
                display();
                break;
            case 4:
                save();
                exit(0); // save contents of arrays into a file and exit.
            default:
                printf("1 to 4 only.\n");
                system("pause");
        }
    }

    return 0;
}

// Define UDFs
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
        return;
    
    if (isduplicate(n)) { 
            printf("Error: Student name '%s' already exists.\n", n);
            system("pause");
            return;
        }
    }
    last++;
    strcpy(name[last], n);
    q1[last] = Q1;
    q2[last] = Q2;
    q3[last] = Q3;
    printf("Added Sucessfully");
}

int isduplicate (char n[]){
    for (int  i= 0; i<= last; i++){
        if(strcmp(n,name[i]) == 0) {
            return 1; // may dups
        }
    }
    return 0; // no dups
}

int menu() {
    int op;
    system("cls");
    printf("Menu\n");
    printf("1. Add a Record\n");
    printf("2. Delete a Record\n");
    printf("3. Display All\n");
    printf("4. Exit\n");
    printf("\nSelect(1-4): ");
    scanf("%d", &op);
    return op;
}

void display() {
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
    fp = fopen("Record.txt", "w");
    if (fp == NULL) {
        printf("File Error.\n");
        system("pause");
    } else {
        for (i = 0; i <= last; i++)
            fprintf(fp, "%s\n%d\n%d\n%d\n", name[i], q1[i], q2[i], q3[i]);
        fclose(fp);
    }
}

void retrieve() {
    FILE *fp;
    int Q1, Q2, Q3;
    char n[MAX];
    fp = fopen("Record.txt", "r");
    if (fp == NULL) {
        printf("File Error.\n");
        system("pause");
    } else {
        while (fscanf(fp, " %[^\n]\n%d\n%d\n%d\n", n, &Q1, &Q2, &Q3) == 4) {
            add(n, Q1, Q2, Q3);
        }
        fclose(fp);
    }
}

float computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0;
}

