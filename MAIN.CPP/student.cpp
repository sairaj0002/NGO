#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to store details of a child
struct Child {
    int id;
    string name;
    int age;
    string grade;
    string address;
};

// Function to display the details of all children
void displayChildren(const vector<Child>& children) {
    if (children.empty()) {
        cout << "No children records available.\n";
        return;
    }

    cout << "\nList of Children:\n";
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age"
         << setw(10) << "Grade" << "Address" << endl;
    cout << string(60, '-') << endl;

    for (const auto& child : children) {
        cout << left << setw(5) << child.id << setw(20) << child.name << setw(5)
             << child.age << setw(10) << child.grade << child.address << endl;
    }
}

// Function to add a new child record
void addChild(vector<Child>& children) {
    if (children.size() >= 100) {
        cout << "Maximum limit of 100 children reached.\n";
        return;
    }

    Child newChild;
    newChild.id = children.size() + 1;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newChild.name);

    cout << "Enter age: ";
    cin >> newChild.age;

    cout << "Enter grade (e.g., A, B, or Class 1): ";
    cin >> newChild.grade;

    cout << "Enter address: ";
    cin.ignore();
    getline(cin, newChild.address);

    children.push_back(newChild);
    cout << "Child record added successfully!\n";
}

// Function to search for a child by ID
void searchChild(const vector<Child>& children) {
    if (children.empty()) {
        cout << "No children records available.\n";
        return;
    }

    int searchId;
    cout << "Enter the ID of the child to search: ";
    cin >> searchId;

    for (const auto& child : children) {
        if (child.id == searchId) {
            cout << "\nChild Found:\n";
            cout << "ID: " << child.id << "\nName: " << child.name
                 << "\nAge: " << child.age << "\nGrade: " << child.grade
                 << "\nAddress: " << child.address << endl;
            return;
        }
    }

    cout << "Child with ID " << searchId << " not found.\n";
}

// Function to edit a child's record
void editChild(vector<Child>& children) {
    if (children.empty()) {
        cout << "No children records available.\n";
        return;
    }

    int editId;
    cout << "Enter the ID of the child to edit: ";
    cin >> editId;

    for (auto& child : children) {
        if (child.id == editId) {
            cout << "Editing details for Child ID " << editId << ":\n";

            cout << "Enter new name (current: " << child.name << "): ";
            cin.ignore();
            getline(cin, child.name);

            cout << "Enter new age (current: " << child.age << "): ";
            cin >> child.age;

            cout << "Enter new grade (current: " << child.grade << "): ";
            cin >> child.grade;

            cout << "Enter new address (current: " << child.address << "): ";
            cin.ignore();
            getline(cin, child.address);

            cout << "Child record updated successfully!\n";
            return;
        }
    }

    cout << "Child with ID " << editId << " not found.\n";
}

// Function to delete a child's record
void deleteChild(vector<Child>& children) {
    if (children.empty()) {
        cout << "No children records available.\n";
        return;
    }

    int deleteId;
    cout << "Enter the ID of the child to delete: ";
    cin >> deleteId;

    for (auto it = children.begin(); it != children.end(); ++it) {
        if (it->id == deleteId) {
            children.erase(it);
            cout << "Child record deleted successfully!\n";

            // Update IDs
            for (size_t i = 0; i < children.size(); ++i) {
                children[i].id = i + 1;
            }
            return;
        }
    }

    cout << "Child with ID " << deleteId << " not found.\n";
}

// Function to save records to a file
void saveToFile(const vector<Child>& children) {
    ofstream outFile("children_records.txt");

    if (!outFile) {
        cout << "Error saving to file.\n";
        return;
    }

    for (const auto& child : children) {
        outFile << child.id << "|" << child.name << "|" << child.age << "|"
                << child.grade << "|" << child.address << "\n";
    }

    outFile.close();
    cout << "Records saved successfully to 'children_records.txt'.\n";
}

// Function to load records from a file
void loadFromFile(vector<Child>& children) {
    ifstream inFile("children_records.txt");

    if (!inFile) {
        cout << "No previous records found.\n";
        return;
    }

    children.clear();
    Child child;
    string line;

    while (getline(inFile, line)) {
        size_t pos = 0;
        string token;
        vector<string> tokens;

        while ((pos = line.find('|')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line); // Last token

        child.id = stoi(tokens[0]);
        child.name = tokens[1];
        child.age = stoi(tokens[2]);
        child.grade = tokens[3];
        child.address = tokens[4];

        children.push_back(child);
    }

    inFile.close();
    cout << "Records loaded successfully from 'children_records.txt'.\n";
}

// Main function
int st() {
    vector<Child> children;

    // Load existing records from file
    loadFromFile(children);

    int choice;
    do {
        cout << "\n--- Slum Children Education Program ---\n";
        cout << "1. Add Child Details\n";
        cout << "2. Display All Children\n";
        cout << "3. Search Child by ID\n";
        cout << "4. Edit Child Details\n";
        cout << "5. Delete Child Record\n";
        cout << "6. Save Records to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addChild(children);
                break;
            case 2:
                displayChildren(children);
                break;
            case 3:
                searchChild(children);
                break;
            case 4:
                editChild(children);
                break;
            case 5:
                deleteChild(children);
                break;
            case 6:
                saveToFile(children);
                break;
            case 7:
                cout << "Exiting the program. Thank you!\n";
                saveToFile(children); // Save before exiting
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
//int main()
//{
//    st();
//}
