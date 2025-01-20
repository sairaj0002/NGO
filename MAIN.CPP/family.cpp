#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// Family Class Definition
class Family {
private:
    int familyID;
    string address;
    string headOfFamily;
    int numOfMembers;

public:
    Family() : familyID(0), address(""), headOfFamily(""), numOfMembers(0) {}

    void inputFamily() {
        cout << "Enter Family ID: ";
        cin >> familyID;
        cin.ignore();

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Head of Family: ";
        getline(cin, headOfFamily);

        cout << "Enter Number of Members: ";
        cin >> numOfMembers;
        cin.ignore();
    }

    void displayFamily() const {
        cout << "Family ID: " << familyID << "\n";
        cout << "Address: " << address << "\n";
        cout << "Head of Family: " << headOfFamily << "\n";
        cout << "Number of Members: " << numOfMembers << "\n";
    }

    int getFamilyID() const {
        return familyID;
    }

    string getAddress() const {
        return address;
    }
};

// NGO Class Definition
class NGO {
private:
    vector<Family> families;  // List of all families
    queue<int> serviceQueue; // Queue for service requests (stores Family IDs)

public:
    void addFamily() {
        Family family;
        family.inputFamily();
        families.push_back(family);
        cout << "\nFamily added successfully! Family ID: " << family.getFamilyID() << "\n";
    }

    void displayAllFamilies() const {
        if (families.empty()) {
            cout << "\nNo families available to display.\n";
            return;
        }
        for (const auto &family : families) {
            family.displayFamily();
            cout << "-----------------------------------\n";
        }
    }

    void searchFamilyByID(int id) const {
        for (const auto &family : families) {
            if (family.getFamilyID() == id) {
                family.displayFamily();
                return;
            }
        }
        cout << "\nNo family found with ID " << id << ".\n";
    }

    void addToServiceQueue(int familyID) {
        // Verify that the family ID exists
        bool found = false;
        for (const auto &family : families) {
            if (family.getFamilyID() == familyID) {
                found = true;
                break;
            }
        }

        if (found) {
            serviceQueue.push(familyID);
            cout << "\nFamily ID " << familyID << " added to the service queue.\n";
        } else {
            cout << "\nInvalid Family ID. Cannot add to service queue.\n";
        }
    }

    void processServiceQueue() {
        if (serviceQueue.empty()) {
            cout << "\nThe service queue is empty. No families to process.\n";
            return;
        }

        int familyID = serviceQueue.front();
        serviceQueue.pop();
        cout << "\nProcessing service for Family ID: " << familyID << "\n";

        // Display the family details
        searchFamilyByID(familyID);
    }

    void displayServiceQueue() const {
        if (serviceQueue.empty()) {
            cout << "\nThe service queue is empty.\n";
            return;
        }

        cout << "\nCurrent Service Queue:\n";
        queue<int> tempQueue = serviceQueue; // Copy the queue for display
        while (!tempQueue.empty()) {
            cout << "Family ID: " << tempQueue.front() << "\n";
            tempQueue.pop();
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\n--- NGO Slum Data Management System ---\n";
    cout << "1. Add Family\n";
    cout << "2. Display All Families\n";
    cout << "3. Search Family by ID\n";
    cout << "4. Add Family to Service Queue\n";
    cout << "5. Process Next Family in Service Queue\n";
    cout << "6. Display Service Queue\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Main function with switch-case
int family() {
    NGO ngo;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                ngo.addFamily();
                break;
            }
            case 2: {
                ngo.displayAllFamilies();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Family ID to search: ";
                cin >> id;
                cin.ignore();
                ngo.searchFamilyByID(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Family ID to add to service queue: ";
                cin >> id;
                cin.ignore();
                ngo.addToServiceQueue(id);
                break;
            }
            case 5: {
                ngo.processServiceQueue();
                break;
            }
            case 6: {
                ngo.displayServiceQueue();
                break;
            }
            case 7: {
                cout << "\nExiting the system. Goodbye!\n";
                break;
            }
            default: {
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
    } while (choice != 7);

    return 0;
}
//int main()
//{

//family();
//}
