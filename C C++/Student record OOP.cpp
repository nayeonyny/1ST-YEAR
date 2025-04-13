#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#define MAX 8
using namespace std;

int menu();

struct Record {
    string name;
    int q1, q2, q3;
};

class Person {
private:
    Record students[MAX];
    int last;
    bool isFull();
    bool isEmpty();
    int locate(string n);
    void save();
    void retrieve();

public:
    void init();
    void add(Record rec);
    void del(string n);
    void displayall();
    float computeAve(int q1, int q2, int q3);
};

int main() {
    Record Data;
    Person cs;
    cs.init();

    while (1) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "Input Name: ";
                cin.ignore();
                getline(cin, Data.name);
                cout << "Input Quiz 1: ";
                cin >> Data.q1;
                cout << "Input Quiz 2: ";
                cin >> Data.q2;
                cout << "Input Quiz 3: ";
                cin >> Data.q3;
                cs.add(Data);
                break;
            case 2:
                system("cls");
                cout << "Enter Name to delete: ";
                cin.ignore();
                getline(cin, Data.name);
                cs.del(Data.name);
                break;
            case 3:
                cs.displayall();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid.\n";
                system("pause");
        }
    }
}

void Person::init() {
    last = -1;
    retrieve();
}

bool Person::isFull() {
    return (last == MAX - 1);
}

bool Person::isEmpty() {
    return (last == -1);
}

int Person::locate(string n) {
    for (int i = 0; i <= last; i++) {
        if (students[i].name == n)
            return i;
    }
    return -1;
}

void Person::add(Record rec) {
    if (isFull()) {
        cout << "Array is full.\n";
        system("pause");
    } else {
        last++;
        students[last] = rec;
        save();
        cout << "Record added successfully.\n";
        system("pause");
    }
}

void Person::del(string n) {
    int p = locate(n);
    if (p < 0) {
        cout << "Record not available.\n";
    } else {
        for (int i = p; i < last; i++) {
            students[i] = students[i + 1];
        }
        last--;
        cout << "Record Deleted.\n";
        save();
    }
    system("pause");
}

float Person::computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0f;
}

void Person::displayall() {
    if (isEmpty()) {
        cout << "No records to display.\n";
        system("pause");
        return;
    }

    system("cls");
    cout << left << setw(18) << "Name" << setw(5) << "Q1" << setw(5) << "Q2" << setw(5) << "Q3" << setw(10) << "Average" << "Remarks" << endl;
    for (int i = 0; i <= last; i++) {
        float avg = computeAve(students[i].q1, students[i].q2, students[i].q3);
        cout << i + 1 << ". " << setw(15) << students[i].name << setw(5) << students[i].q1 << setw(5) << students[i].q2 << setw(5) << students[i].q3
             << setw(10) << fixed << setprecision(2) << avg << " " << (avg >= 75 ? "Passed" : "Failed") << endl;
    }
    system("pause");
}

void Person::save() {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error: Unable to open file for saving.\n";
        return;
    }
    for (int i = 0; i <= last; i++) {
        file << students[i].name << "\n" << students[i].q1 << " " << students[i].q2 << " " << students[i].q3 << "\n";
    }
    file.close();
}

void Person::retrieve() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No existing records found. Starting with an empty list.\n";
        return;
    }
    string n;
    int q1, q2, q3;
    while (getline(file, n) && file >> q1 >> q2 >> q3 && file.ignore()) {
        if (isFull()) {
            cout << "Warning: Maximum capacity reached. Some records may not be loaded.\n";
            break;
        }
        last++;
        students[last].name = n;
        students[last].q1 = q1;
        students[last].q2 = q2;
        students[last].q3 = q3;
    }
    file.close();
}

int menu() {
    int op;
    system("cls");
    cout << "STUDENT RECORD MENU.\n";
    cout << "1. Add a Record\n";
    cout << "2. Delete a Record\n";
    cout << "3. Display All\n";
    cout << "4. Exit\n";
    cout << "Select (1-4) only: ";
    cin >> op;
    return op;
}
