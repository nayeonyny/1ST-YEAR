#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

// Function Declarations
void getRec(char n[][31], int q1[], int q2[], int q3[]);
void displayRec(char n[][31], int q1[], int q2[], int q3[]);
float computeAve(int q1, int q2, int q3);

char name[MAX][31]; 
int quiz1[MAX];
int quiz2[MAX];
int quiz3[MAX]; 

// Main
int main() {
    getRec(name, quiz1, quiz2, quiz3);
    displayRec(name, quiz1, quiz2, quiz3);
    return 0;
}

// User defined functions definitions
void getRec(char n[][31], int q1[], int q2[], int q3[]) {
    for (int i = 0; i < MAX; i++) {
        printf("\nRecord#%d:\n", i + 1);
        printf("Input Name: ");
        fgets(n[i], sizeof(n[i]), stdin);

        size_t len = strlen(n[i]);
        if (len > 0 && n[i][len - 1] == '\n') {
            n[i][len - 1] = '\0';
        }

        printf("Input quiz1: ");
        scanf("%d", &q1[i]);
        printf("Input quiz2: ");
        scanf("%d", &q2[i]);
        printf("Input quiz3: ");
        scanf("%d", &q3[i]);
        getchar();  
    }
}

void displayRec(char n[][31], int q1[], int q2[], int q3[]) {
    printf("\nNo.\tNAME\tQuiz1\tQuiz2\tQuiz3\tAverage\tRemarks\n");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < MAX; i++) {
        float ave = computeAve(q1[i], q2[i], q3[i]);
        printf("%d\t%s\t%d\t%d\t%d\t%.2f\t%s\n", i + 1, n[i], q1[i], q2[i], q3[i], ave, ave >= 75 ? "PASS" : "FAIL");
    }
}

float computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0;
}
