#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// Household Class Definition
class Household {
private:
    int householdID;
    string address;
    string headOfHousehold;
    int numOfMembers;

public:
    Household() : householdID(0), address(""), headOfHousehold(""), numOfMembers(0) {}

    void inputHousehold() {
        cout << "Enter Household ID: ";
        cin >> householdID;
        cin.ignore();

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Head of Household: ";
        getline(cin, headOfHousehold);

        cout << "Enter Number of Members: ";
        cin >> numOfMembers;
        cin.ignore();
    }

    void displayHousehold() const {
        cout << "Household ID: " << householdID << "\n";
        cout << "Address: " << address << "\n";
        cout << "Head of Household: " << headOfHousehold << "\n";
        cout << "Number of Members: " << numOfMembers << "\n";
    }

    int getHouseholdID() const {
        return householdID;
    }

    string getAddress() const {
        return address;
    }
};

// Charity Class Definition (formerly NGO)
class Charity {
private:
    vector<Household> households;  // List of all households
    queue<int> serviceQueue; // Queue for service requests (stores Household IDs)

public:
    void addHousehold() {
        Household household;
        household.inputHousehold();
        households.push_back(household);
        cout << "\nHousehold added successfully! Household ID: " << household.getHouseholdID() << "\n";
    }

    void displayAllHouseholds() const {
        if (households.empty()) {
            cout << "\nNo households available to display.\n";
            return;
        }
        for (const auto &household : households) {
            household.displayHousehold();
            cout << "-----------------------------------\n";
        }
    }

    void searchHouseholdByID(int id) const {
        for (const auto &household : households) {
            if (household.getHouseholdID() == id) {
                household.displayHousehold();
                return;
            }
        }
        cout << "\nNo household found with ID " << id << ".\n";
    }

    void addToServiceQueue(int householdID) {
        // Verify that the household ID exists
        bool found = false;
        for (const auto &household : households) {
            if (household.getHouseholdID() == householdID) {
                found = true;
                break;
            }
        }

        if (found) {
            serviceQueue.push(householdID);
            cout << "\nHousehold ID " << householdID << " added to the service queue.\n";
        } else {
            cout << "\nInvalid Household ID. Cannot add to service queue.\n";
        }
    }

    void processServiceQueue() {
        if (serviceQueue.empty()) {
            cout << "\nThe service queue is empty. No households to process.\n";
            return;
        }

        int householdID = serviceQueue.front();
        serviceQueue.pop();
        cout << "\nProcessing service for Household ID: " << householdID << "\n";

        // Display the household details
        searchHouseholdByID(householdID);
    }

    void displayServiceQueue() const {
        if (serviceQueue.empty()) {
            cout << "\nThe service queue is empty.\n";
            return;
        }

        cout << "\nCurrent Service Queue:\n";
        queue<int> tempQueue = serviceQueue; // Copy the queue for display
        while (!tempQueue.empty()) {
            cout << "Household ID: " << tempQueue.front() << "\n";
            tempQueue.pop();
        }
    }
};

// Function to display the menu (renamed from displayMenu to showMenu)
void showMenu() {
    cout << "\n--- Charity Slum Data Management System ---\n";
    cout << "1. Add Household\n";
    cout << "2. Display All Households\n";
    cout << "3. Search Household by ID\n";
    cout << "4. Add Household to Service Queue\n";
    cout << "5. Process Next Household in Service Queue\n";
    cout << "6. Display Service Queue\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Main function with switch-case
int householdmem() {
    Charity charity;
    int choice;

    do {
        showMenu();  // Updated function name
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                charity.addHousehold();
                break;
            }
            case 2: {
                charity.displayAllHouseholds();
                break;
            }
            case 3: {
                int id;
                cout << "Enter Household ID to search: ";
                cin >> id;
                cin.ignore();
                charity.searchHouseholdByID(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Household ID to add to service queue: ";
                cin >> id;
                cin.ignore();
                charity.addToServiceQueue(id);
                break;
            }
            case 5: {
                charity.processServiceQueue();
                break;
            }
            case 6: {
                charity.displayServiceQueue();
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

//int main() {
//    householdmem();
//}
