#include <iostream>
#include <fstream>
#include <iomanip>
#define MAX 10
using namespace std;

struct Record {
    string name;
    int q1, q2, q3;
};

class Person {
private:
    Record students[MAX];
    int last;
    bool isfull();
    bool isempty();
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

int menu();

int main() {
    Record data;
    Person cs;
    cs.init();

    while (true) {
        switch (int menu()) {
        case 1:
            system("cls");
            cout << "Input Name: "; cin.ignore(); getline(cin, data.name);
            cout << "Quiz 1: "; cin >> data.q1;
            cout << "Quiz 2: "; cin >> data.q2;
            cout << "Quiz 3: "; cin >> data.q3;
            cs.add(data);
            break;
        case 2:
            system("cls");
            cout << "Enter Name to delete: "; cin.ignore(); getline(cin, data.name);
            cs.del(data.name);
            break;
        case 3:
            cs.displayall();
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid input.\n";
            system("pause");
        }
    }
}

void Person::init() {
    last = -1;
    retrieve();
}

bool Person::isfull() {
    return (last == MAX - 1);
}

bool Person::isempty() {
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
    if (isfull()) {
        cout << "Array is full.\n";
        system("pause");
    } else {
        last++;
        students[last] = rec;
        save();
    }
}

void Person::del(string n) {
    int p = locate(n);
    if (p < 0) {
        cout << "Record not found.\n";
    } else {
        for (int i = p; i < last; i++) {
            students[i] = students[i + 1];
        }
        last--;
        cout << "Record deleted successfully.\n";
        save();
    }
    system("pause");
}

void Person::displayall() {
    system("cls");
    cout << left << setw(20) << "Name" << setw(6) << "Q1" << setw(6) << "Q2" << setw(6) << "Q3" << setw(8) << "Average" << "Remarks" << endl;
    for (int i = 0; i <= last; i++) {
        float avg = computeAve(students[i].q1, students[i].q2, students[i].q3);
        cout << i + 1 << ".)" << setw(17) << students[i].name << setw(6) << students[i].q1 << setw(6) << students[i].q2 << setw(6) << students[i].q3
             << setw(8) << fixed << setprecision(2) << avg << " " << (avg >= 75 ? "Passed" : "Failed") << endl;
    }
    system("pause");
}

float Person::computeAve(int q1, int q2, int q3) {
    return (q1 + q2 + q3) / 3.0;
}

void Person::save() {
    ofstream file("student_records.txt");
    for (int i = 0; i <= last; i++) {
        file << students[i].name << "\n" << students[i].q1 << " " << students[i].q2 << " " << students[i].q3 << "\n";
    }
    file.close();
}

void Person::retrieve() {
    ifstream file("student_records.txt");
    string n;
    int q1, q2, q3;
    while (getline(file, n) && file >> q1 >> q2 >> q3 && file.ignore()) {
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
    cout << "MENU\n";
    cout << "1. Add a Record\n";
    cout << "2. Delete a record\n";
    cout << "3. Display all\n";
    cout << "4. Exit\n";
    cout << "Select (1-4): ";
    cin >> op;
    return op;
}
