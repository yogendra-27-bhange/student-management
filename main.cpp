#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student s;

    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Marks: ";
    cin >> s.marks;

    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();

    cout << "Student added successfully!\n";
}

void viewStudents() {
    ifstream inFile("students.dat", ios::binary);
    Student s;

    cout << "\n--- Student Records ---\n";
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        cout << "\nRoll No: " << s.rollNo;
        cout << "\nName: " << s.name;
        cout << "\nMarks: " << s.marks << "\n";
    }

    inFile.close();
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Management System ---";
        cout << "\n1. Add Student";
        cout << "\n2. View Students";
        cout << "\n3. Delete Student";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: deleteStudent(); break;
            case 4: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
