#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 3;  // Number of students

// Function to save parallel arrays into a file
void saveToFile(string names[], int marks[], int size) {
    ofstream outFile("students.txt");  // Open file in write mode
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        outFile << names[i] << "\n" << marks[i] << endl;  // Store name on a separate line
    }

    outFile.close();  // Close file
    cout << "Data saved successfully!\n";
}

// Function to retrieve data from file into parallel arrays
void loadFromFile(string names[], int marks[], int size) {
    ifstream inFile("students.txt");  // Open file in read mode
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        getline(inFile, names[i]);  // Read full name (including spaces)
        inFile >> marks[i];         // Read marks
        inFile.ignore();            // Ignore newline after marks
    }

    inFile.close();  // Close file
    cout << "Data loaded successfully!\n";
}

int main() {
    string names[SIZE] = {"Mel Chor", "Gas Par", "Bal Tzar"};
    int marks[SIZE] = {85, 90, 78};

    // Save to file
    saveToFile(names, marks, SIZE);

    // Clear arrays before loading data
    string loadedNames[SIZE];
    int loadedMarks[SIZE];

    // Load from file
    loadFromFile(loadedNames, loadedMarks, SIZE);

    // Display retrieved data
    cout << "\nRetrieved Data:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << loadedNames[i] << " - " << loadedMarks[i] << endl;
    }

    return 0;
}
