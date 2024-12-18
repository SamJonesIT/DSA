/*
Consider a student database of SEIT class (at least 15 records).
Database contains different fields of every student like Roll No,
Name and SGPA. (Array of structures)
1. Arrange list of students alphabetically. (Use Insertion sort) 
2. Search students according to SGPA. If more than one student
having same SGPA, then print list of all students having same SGPA. 
3. Search a particular student according to name using binary search
without recursion. (all the student records having the presence of
search key should be displayed) 
4. Design a roll call list, arrange list of students according to
roll numbers in ascending order (Use Bubble Sort) 
5. Arrange list of students to find out first ten toppers from a
class. (Use Quick sort) 
*/

# include <bits/stdc++.h>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

//function to display student records
void displayStudents(Student student[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Roll No: " << student[i].rollNo
             << ", Name: " << student[i].name
             << ", SGPA: " << student[i].sgpa << endl;
    }
    cout << endl;
}

//insertion sort for alphabetical order
void insertionSort(Student student[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = student[i];
        int j = i - 1;
        //compare
        while (j >= 0 && student[j].name > key.name) {
            student[j + 1] = student[j];
            j--;
        }
        student[j + 1] = key;
    }
}

//search SGPA
void searchSGPA(Student student[], int n, float sgpa) {
    bool found = false;
    cout << "Students with SGPA: " << sgpa << "\n";
    for (int i = 0; i < n; i++) {
        if (student[i].sgpa == sgpa) {
            cout << "Roll no: " << student[i].rollNo 
                 << ", Name: " << student[i].name << endl;
            found = true; 
        }
    }
    if (!found) {
        cout << "No student found with SGPA " << sgpa << endl;
    }
}

//binary search without recursion
void binarySearch(Student student[], int n, string name) {
    int left = 0, right = n - 1;
    bool found = false;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (student[mid].name == name) {
            found = true;
            //display found
            cout << "Student found:\n";
            int temp = mid;
            //traverse left for duplicate
            while (temp >= 0 && student[temp].name == name) {
                cout << "Roll No: " << student[temp].rollNo
                     << ", Name: " << student[temp].name
                     << ", SGPA: " << student[temp].sgpa << endl;
                temp--;
            }
            //traverse right for duplicate
            temp = mid + 1;
            while (temp < n && student[temp].name == name) {
                cout << "Roll No: " << student[temp].rollNo
                     << ", Name: " << student[temp].name
                     << ", SGPA: " << student[temp].sgpa << endl;
                temp++;
            }
            break;
        }
        if (student[mid].name < name)
            left = mid + 1;
        else
            right = mid -1;
    }
    if (!found) {
        cout << "No such student found!\n";
    }
}

//bubble sort for ascending order
void bubbleSort(Student student[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j-n-1; j++) {
            if (student[j].rollNo > student[j+1].rollNo) {
                swap(student[j],student[j+1]);
            }
        }
    }
}

//quicksort 10 toppers
// Partition function for Quick Sort
int partition(Student student[], int low, int high) {
    float pivot = student[high].sgpa; // pivot element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (student[j].sgpa >= pivot) { // Sort in descending order
            i++;
            // Swap students[i] and students[j]
            Student temp = student[i];
            student[i] = student[j];
            student[j] = temp;
        }
    }
    // Swap students[i+1] and students[high] (pivot)
    Student temp = student[i + 1];
    student[i + 1] = student[high];
    student[high] = temp;

    return i + 1;
}

// Quick Sort to arrange students by SGPA in descending order
void quickSortBySGPA(Student student[], int low, int high) {
    if (low < high) {
        int pi = partition(student, low, high);

        quickSortBySGPA(student, low, pi - 1);
        quickSortBySGPA(student, pi + 1, high);
    }
}


//main function
int main() {
    const int numStudents = 18;
    Student student[numStudents] = {
        {1, "Hemant", 10}, 
        {2, "Vedant", 9.5},
        {3, "Omkar", 8}, 
        {4, "Harshad", 8.5},
        {5, "Shreyash", 8.6}, 
        {6, "Tejas", 9},
        {7, "Austin", 9.5}, 
        {8, "Shravan", 7.9},
        {9, "Priyanshu", 8.1}, 
        {10, "Chaitanya", 9.2},
        {11, "Priyanka", 10}, 
        {12, "Anvi", 9.1},
        {13, "Falguni", 9.9}, 
        {14, "Aayush", 8.7},
        {15, "Ayushi", 8.4},
        {16, "Sagar", 9.6}, 
        {17, "Yashraj", 9.5},
        {18, "Sarvesh", 9.4},
    };

    cout << "Original students list:\n";
    displayStudents(student, numStudents);

    insertionSort(student, numStudents);
    cout << "Alphabetically sorted list:\n";
    displayStudents(student, numStudents);

    float sgpa;
    cout << "Enter the SGPA to search for: ";
    cin >> sgpa;
    searchSGPA(student, numStudents, sgpa);

    string searchname;
    cout << "\nEnter the name to search for\n(please keep the first letter capital): ";
    cin >> searchname;
    binarySearch(student, numStudents, searchname);

    bubbleSort(student, numStudents);
    cout << "\nAscending order sorted list:\n";
    displayStudents(student, numStudents);

    quickSortBySGPA(student, 0, numStudents - 1);
    cout << "\nFirst ten toppers are:\n";
    displayStudents(student, 10);

    return 0;
}
