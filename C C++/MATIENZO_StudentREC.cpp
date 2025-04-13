#include <iostream>
#include <string>
#include <iomanip>
#define MAX 4
using namespace std;

// Global variables
// Parallel Arrays
string name[MAX];
int q1[MAX], q2[MAX], q3[MAX];
int last;

// UDFs
void init();
int isfull();
int isempty();
int locate(const string& n);
void del(const string& n);
void add(const string& n, int q1, int q2, int q3);
void display();
void update(const string& n);
int menu();
float computeAve(int q1, int q2, int q3);
int isduplicate(const string& n);   

int main() {
    string n;
    int Q1, Q2, Q3;
    init(); // Initialize the array

    while (true) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "Input Name: ";
                cin.ignore();
                getline(cin, n);
                cout << "Input Q1: ";
                cin >> Q1;
                cout << "Input Q2: ";
                cin >> Q2;
                cout << "Input Q3: ";
                cin >> Q3;
                add(n, Q1, Q2, Q3);
                break;
            case 2:
                system("cls");
                cout << "Input Name: ";
                cin.ignore();
                getline(cin, n);
                del(n);
                break;
            case 3:
                display();
                break;
            case 4: // New case for updating a record
                system("cls");
                cout << "Input Name: ";
                cin.ignore();
                getline(cin, n);
                update(n);
                break;
            case 5:
                exit(0);
            default:
                cout << "1 to 5 only.\n";
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

int locate(const string& n) {
    for (int i = 0; i <= last; i++) {
        if (n == name[i])
            return i;
    }
    return -1;
}

void del(const string& n) {
    if (isempty()) {
        cout << "Array is empty." << endl;
        system("pause");
    } else {
        int p = locate(n);
        if (p < 0) {
            cout << "Not found." << endl;
            system("pause");
        } else {
            for (int i = p; i < last; i++) {
                name[i] = name[i + 1];
                q1[i] = q1[i + 1];
                q2[i] = q2[i + 1];
                q3[i] = q3[i + 1];
            }
            last--;
            cout << "Record of " << n << " is successfully deleted." << endl;
            system("pause");
        }
    }
}

void add(const string& n, int Q1, int Q2, int Q3) {
    if (isfull()) {
        cout <<"Array is full.\n";
        system("pause");
        return;
    }
    
    if (isduplicate(n)) { 
        cout<<"Error: Student name << n << already exists.\n" <<endl;
        system("pause");
        return;
    }
    
    last++;
    name[last] = n;
    q1[last] = Q1;
    q2[last] = Q2;
    q3[last] = Q3;
    cout << "Added Successfully.\n"<<endl;
    system("pause");
}

int isduplicate(const string& n) {
    for (int i = 0; i <= last; i++) {
        if (n == name[i]) {
            return 1; // May dups
        }
    }
    return 0; // Walang dups
}

int menu() {
    int op;
    system("cls");
    cout << "Menu\n";
    cout << "1. Add a Record\n";
    cout << "2. Delete a Record\n";
    cout << "3. Display All\n";
    cout << "4. Update a Record\n"; 
    cout << "5. Exit\n";
    cout << "\nSelect(1-5): ";
    cin >> op;
    return op;
}

void display() {
    int i;
    system("cls");
    cout <<"  NAME\tQ1\tQ2\tQ3\tAVERAGE\tREMARKS\n";
    for (i = 0; i <= last; i++) {
        float ave = computeAve(q1[i], q2[i], q3[i]);
        cout << (i + 1) << ".) " << name[i] << "\t" << q1[i] << "\t" << q2[i] << "\t" << q3[i]
        << "\t" << fixed << setprecision(2) << ave 
        << "\t" << (ave >= 75 ? "PASS" : "FAIL") << "\n";
    }
    system("pause");
}

void update(const string& n) {
    if (isempty()) {
        cout << "\nError: No records available to update.\n";
        system("pause");
        return;
    }

    int p = locate(n); 
    if (p < 0) {
        cout << "\nError: Record not found.\n";
        system("pause");
        return;
    }

    cout << "\nCurrent Record:\n";
    cout << "Name: " << name[p] << "\n";
    cout << "Quiz 1: " << q1[p] << "\n";
    cout << "Quiz 2: " << q2[p] << "\n";
    cout << "Quiz 3: " << q3[p] << "\n";

    int quizChoice, newScore;
    cout << "\n--- Select Quiz to Update ---\n";
    cout << "1. Quiz 1\n";
    cout << "2. Quiz 2\n";
    cout << "3. Quiz 3\n";
    cout << "Enter your choice (1-3): ";
    cin >> quizChoice;

    if (quizChoice < 1 || quizChoice > 3) {
        cout << "\nError: Invalid choice. Please select a number between 1 and 3.\n";
        system("pause");
        return;
    }

    cout << "\nEnter the new score for Quiz " << quizChoice << ": ";
    cin >> newScore;

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

    cout << "\nSuccess: Record updated successfully.\n";
    system("pause");
}

float computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0f;
}
