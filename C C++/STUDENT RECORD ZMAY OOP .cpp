#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

// Encapsulation of student data using a class
class Student {
private:
    string name;
    int q1, q2, q3;

public:
    // Constructor
    Student(string n = "", int quiz1 = 0, int quiz2 = 0, int quiz3 = 0)
        : name(n), q1(quiz1), q2(quiz2), q3(quiz3) {}

    // Compute average
    float computeAverage() const {
        return (q1 + q2 + q3) / 3.0f;
    }

    // Getters
    string getName() const { return name; }
    int getQuiz1() const { return q1; }
    int getQuiz2() const { return q2; }
    int getQuiz3() const { return q3; }

    // Display student details
    void display(int index) const {
        float average = computeAverage();
        cout << index + 1 << ".) " << setw(15) << name << setw(10) << q1 << setw(10) << q2
             << setw(10) << q3 << setw(10) << fixed << setprecision(2) << average
             << setw(10) << (average >= 75 ? "PASS" : "FAIL") << endl;
    }

    // Save student
    void saveToFile(ofstream &out) const {
        out << name << " " << q1 << " " << q2 << " " << q3 << endl;
    }

    // Load student
    void loadFromFile(ifstream &in) {
        in >> name >> q1 >> q2 >> q3;
    }
};

// StudentRecord
class StudentRecord {
private:
    vector<Student> students;

    // Find student by name
    int findStudent(const string &name) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getName() == name) {
                return i;
            }
        }
        return -1;
    }

public:
    // Add a student
    void addStudent(const string &name, int q1, int q2, int q3) {
        if (findStudent(name) != -1) {
            cout << "Error: Student with name \"" << name << "\" already exists.\n";
            return;
        }
        students.emplace_back(name, q1, q2, q3);
        cout << "Student added successfully.\n";
    }

    // Delete a student
    void deleteStudent(const string &name) {
        int index = findStudent(name);
        if (index == -1) {
            cout << "Error: Student not found.\n";
            return;
        }
        students.erase(students.begin() + index);
        cout << "Student \"" << name << "\" deleted successfully.\n";
    }

    // Display all students
    void displayAll() const {
        if (students.empty()) {
            cout << "No records to display.\n";
            return;
        }
        cout << setw(5) << "No." << setw(15) << "Name" << setw(10) << "Quiz 1"
             << setw(10) << "Quiz 2" << setw(10) << "Quiz 3" << setw(10) << "Average"
             << setw(10) << "Remarks" << endl;
        cout << string(65, '-') << endl;
        for (size_t i = 0; i < students.size(); i++) {
            students[i].display(i);
        }
    }

    // Save all students to file
    void saveToFile(const string &filename) const {
        ofstream out(filename);
        if (!out) {
            cout << "Error: Could not open file for writing.\n";
            return;
        }
        for (const auto &student : students) {
            student.saveToFile(out);
        }
        out.close();
        cout << "Records saved successfully.\n";
    }

    // Load all students from file
    void loadFromFile(const string &filename) {
        ifstream in(filename);
        if (!in) {
            cout << "No existing records found. Starting with an empty list.\n";
            return;
        }
        students.clear();
        Student temp;
        while (in) {
            temp.loadFromFile(in);
            if (in) {
                students.push_back(temp);
            }
        }
        in.close();
        cout << "Records loaded successfully.\n";
    }
};

// Main function
int main() {
    StudentRecord record;
    string filename = "students.txt";
    record.loadFromFile(filename);

    int op;

    while (true) {
        cout << "\nMenu\n";
        cout << "1. Add a Record\n";
        cout << "2. Delete a Record\n";
        cout << "3. Display All\n";
        cout << "4. Save Records\n";
        cout << "5. Exit\n";
        cout << "Select (1-5): ";
        cin >> op;

        switch (op) {
            case 1: {
                string name;
                int q1, q2, q3;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Quiz 1 Score: ";
                cin >> q1;
                cout << "Enter Quiz 2 Score: ";
                cin >> q2;
                cout << "Enter Quiz 3 Score: ";
                cin >> q3;
                record.addStudent(name, q1, q2, q3);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Name to Delete: ";
                cin.ignore();
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
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select between 1 and 5.\n";
        }
    }
}
