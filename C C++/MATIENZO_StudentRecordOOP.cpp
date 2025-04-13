#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

class Student {
private:
    string name;
    int q1, q2, q3;

public:
    Student(string n = "", int quiz1 = 0, int quiz2 = 0, int quiz3 = 0)
        : name(n), q1(quiz1), q2(quiz2), q3(quiz3) {}

    float computeAverage() const {
        return (q1 + q2 + q3) / 3.0f;
    }

    string getName() const { return name; }
    int getQuiz1() const { return q1; }
    int getQuiz2() const { return q2; }
    int getQuiz3() const { return q3; }

    void display(int index) const {
        float avg = computeAverage();
        cout << left << setw(5) << index + 1 << setw(20) << name
             << setw(10) << q1 << setw(10) << q2 << setw(10) << q3
             << setw(10) << fixed << setprecision(2) << avg
             << setw(10) << (avg >= 75 ? "PASS" : "FAIL") << endl;
    }

    void saveToFile(ofstream &out) const {
        out << name << " " << q1 << " " << q2 << " " << q3 << endl;
    }

    void loadFromFile(ifstream &in) {
        in >> name >> q1 >> q2 >> q3;
    }
};

class StudentRecord {
private:
    vector<Student> students;

    int findStudent(const string &name) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getName() == name) return i;
        }
        return -1;
    }

public:
    void addStudent(const string &name, int q1, int q2, int q3) {
        if (findStudent(name) != -1) {
            cout << "\n[Error] Student \"" << name << "\" already exists.\n";
            return;
        }
        students.emplace_back(name, q1, q2, q3);
        cout << "\n[Success] Student added successfully!\n";
    }

    void deleteStudent(const string &name) {
        int index = findStudent(name);
        if (index == -1) {
            cout << "\n[Error] Student not found.\n";
            return;
        }
        students.erase(students.begin() + index);
        cout << "\n[Success] Student \"" << name << "\" deleted.\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "\n[Info] No student records available.\n";
            return;
        }
        cout << "\nStudent Records:\n";
        cout << left << setw(5) << "No." << setw(20) << "Name"
             << setw(10) << "Quiz 1" << setw(10) << "Quiz 2"
             << setw(10) << "Quiz 3" << setw(10) << "Average"
             << setw(10) << "Remarks" << endl;
        cout << string(70, '-') << endl;
        for (size_t i = 0; i < students.size(); i++) {
            students[i].display(i);
        }
    }

    void saveToFile(const string &filename) const {
        ofstream out(filename);
        if (!out) {
            cout << "\n[Error] Could not save records.\n";
            return;
        }
        for (const auto &student : students) {
            student.saveToFile(out);
        }
        cout << "\n[Success] Records saved successfully!\n";
    }

    void loadFromFile(const string &filename) {
        ifstream in(filename);
        if (!in) {
            cout << "\n[Info] No existing records found. Starting fresh.\n";
            return;
        }
        students.clear();
        Student temp;
        while (in) {
            temp.loadFromFile(in);
            if (in) students.push_back(temp);
        }
        cout << "\n[Success] Records loaded successfully!\n";
    }
};

int main() {
    StudentRecord record;
    string filename = "students.txt";
    record.loadFromFile(filename);
    
    while (true) {
        cout << "\n======= Student Record System =======\n";
        cout << "1. Add a Student\n";
        cout << "2. Delete a Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Save Records\n";
        cout << "5. Exit\n";
        cout << "Select an option (1-5): ";
        
        int op;
        cin >> op;
        cin.ignore(); 
        
        switch (op) {
            case 1: {
                string name;
                int q1, q2, q3;
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Quiz 1 Score: "; cin >> q1;
                cout << "Enter Quiz 2 Score: "; cin >> q2;
                cout << "Enter Quiz 3 Score: "; cin >> q3;
                record.addStudent(name, q1, q2, q3);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Name to Delete: ";
                getline(cin, name);
                record.deleteStudent(name);
                break;
            }
            case 3:
                record.displayAll();
                break;
            case 4:
                record.saveToFile(filename);
                break;
            case 5:
                record.saveToFile(filename);
                cout << "\n[Goodbye] Exiting program.\n";
                return 0;
            default:
                cout << "\n[Error] Invalid choice. Please select a valid option.\n";
        }
    }
}
