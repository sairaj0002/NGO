#include<iostream>
#include"transportation.cpp"
#include"ngo.cpp"
#include"student.cpp"
#include"family.cpp"
#include"familymem.cpp"
#include"slum.cpp"
using namespace std;

int main() {
    int ch;

    while (true) {
        cout << "1.Slum section\n";
        cout << "2.NGO section\n";
        cout << "3.Transportation section\n";
        cout << "4.Family section\n";
        cout << "5.Family Member section\n";
        cout << "6.Student section\n";
        cout << "7.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch(ch) {
            case 1:
                slumsection();
                break;
            case 2:
                alex();
                break;
            case 3:
                tr();
                break;
            case 4:
                family();
                break;
            case 5:
                householdmem();
                break;
            case 6:
                st();
                break;
            case 7:
                cout << "Exiting...\n";
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
