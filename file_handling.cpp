#include <bits/stdc++.h>
using namespace std;

struct Student {
    string rollNumber;
    string name;
    string division;
    string address;
};

void addStudent() {
    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing!\n";
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile << student.rollNumber << "|" << student.name << "|" << student.division << "|" << student.address << "\n";
    outFile.close();
    cout << "Student added successfully!\n";
}

void displayStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!\n";
        return;
    }

    string rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find('|');
        string storedRollNumber = line.substr(0, pos);

        if (storedRollNumber == rollNumber) {
            found = true;
            size_t nextPos;
            cout << "Roll Number: " << storedRollNumber << "\n";

            nextPos = line.find('|', pos + 1);
            cout << "Name: " << line.substr(pos + 1, nextPos - pos - 1) << "\n";

            pos = nextPos;
            nextPos = line.find('|', pos + 1);
            cout << "Division: " << line.substr(pos + 1, nextPos - pos - 1) << "\n";

            cout << "Address: " << line.substr(nextPos + 1) << "\n";
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }
    inFile.close();
}

void deleteStudent() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!\n";
        return;
    }

    string rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error creating temporary file!\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos = line.find('|');
        string storedRollNumber = line.substr(0, pos);

        if (storedRollNumber == rollNumber) {
            found = true;
            continue;
        }
        tempFile << line << "\n";
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student with Roll Number " << rollNumber << " deleted successfully.\n";
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
        remove("temp.txt");
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Database Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
