#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<map>
using namespace std;

struct Person
{
    string name;
    string nationality;
    int age;
    string dob;
    bool hasVoterID;
    string birthPlace;
    string educationQualification;
    string occupation;
    string aadharNumber;
    bool isMigrated;
    string migrationSource;
    string migrationReason;
    string emergency;
};

struct MedicinalNeeds
{
    string hasDisease;
    string medicineRecommendation;
};

struct Shelter
{
    string name;
    string location;
};

struct Donation
{
    string donorName;
    double amount;
    string date;
    string reason;
};

struct Hospital
{
    string name;
    string location;
};

class NGOApp
{
private:
    vector<Person> people;
    vector<MedicinalNeeds> medicinalNeeds;
    vector<Shelter> shelters;
    vector<Donation> donations;
    vector<Hospital> hospitals;

public:
    void readFromFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            Person p;
            MedicinalNeeds m;
            Shelter s;

            getline(ss, p.name, ',');
            getline(ss, p.nationality, ',');
            ss >> p.age;
            ss.ignore();

            getline(ss, p.dob, ',');

            char hasVoterID;
            ss >> hasVoterID;
            ss.ignore();
            p.hasVoterID = (hasVoterID == 'Y' || hasVoterID == 'y');

            getline(ss, p.birthPlace, ',');
            getline(ss, p.educationQualification, ',');
            getline(ss, p.occupation, ',');
            getline(ss, p.aadharNumber, ',');

            char migratedResponse;
            ss >> migratedResponse;
            ss.ignore();
            p.isMigrated = (migratedResponse == 'Y' || migratedResponse == 'y');

            if (p.isMigrated)
            {
                getline(ss, p.migrationSource, ',');
                getline(ss, p.migrationReason, ',');
            }

            getline(ss, p.emergency, ',');

            people.push_back(p);

            getline(ss, m.hasDisease, ',');

            if (m.hasDisease == "Yes")
            {
                m.medicineRecommendation = "Recommended Medicine: Take prescribed medicines.";
            }
            else
            {
                m.medicineRecommendation = "No medicinal needs.";
            }

            medicinalNeeds.push_back(m);

            getline(ss, s.name, ',');
            getline(ss, s.location);

            shelters.push_back(s);
        }

        inputFile.close();
        cout << "Data read from file successfully!" << endl;
    }

    void readDonationsFromFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cerr << "Error opening donations file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            Donation d;

            getline(ss, d.donorName, ',');
            ss >> d.amount;
            ss.ignore();
            getline(ss, d.date, ',');
            getline(ss, d.reason, ',');

            donations.push_back(d);
        }

        inputFile.close();
        cout << "Donations data read from file successfully!" << endl;
    }

    void readSheltersFromFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cerr << "Error opening shelter file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            Shelter s;
            getline(ss, s.name, ',');
            getline(ss, s.location);
            shelters.push_back(s);
        }

        inputFile.close();
        cout << "Shelters data read from file successfully!" << endl;
    }

    void readHospitalsFromFile(const string& filename)
    {
        ifstream inputFile(filename);
        if (!inputFile)
        {
            cerr << "Error opening hospitals file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            Hospital h;
            getline(ss, h.name, ',');
            getline(ss, h.location);
            hospitals.push_back(h);
        }

        inputFile.close();
        cout << "Hospitals data read from file successfully!" << endl;
    }

    void displayShelters()
    {
        cout << "\n--- Shelter Names and Locations ---\n";
        for (size_t i = 0; i < shelters.size(); i++)
        {
            cout << "Shelter Name: " << shelters[i].name << endl;
            cout << "Location: " << shelters[i].location << endl;
            cout << "---------------------------------\n";
        }
    }

    void displayHospitals()
    {
        cout << "\n--- Hospital Names and Locations ---\n";
        for (size_t i = 0; i < hospitals.size(); i++)
        {
            cout << "Hospital Name: " << hospitals[i].name << endl;
            cout << "Location: " << hospitals[i].location << endl;
            cout << "---------------------------------\n";
        }
    }

    void handleMedicalEmergency(int index)
    {
        if (people[index].emergency == "Yes")
        {
            cout << "Medical emergency detected! Moving " << people[index].name << " to the nearest hospital...\n";
            cout << "Assigned to the nearest hospital.\n";
        }
        else
        {
            cout << people[index].name << " does not have a medical emergency." << endl;
        }
    }

    void provideMedicinalNeeds(int index)
    {
        if (medicinalNeeds[index].hasDisease == "Yes")
        {
            cout << medicinalNeeds[index].medicineRecommendation << endl;
            cout << "Assigned to the nearest hospital.\n";
        }
        else
        {
            cout << "No medicinal needs at this time." << endl;
        }
    }

    void handleShelterNeed(int index)
    {
        if (shelters.size() > index && shelters[index].name != "")
        {
            cout << "Shelter needed for " << people[index].name << ". Assigning to the nearest shelter...\n";
            cout << "Assigned to the nearest shelter.\n";
        }
        else
        {
            cout << "No shelter needed for " << people[index].name << "." << endl;
        }
    }

    void handleShelterNeedOption()
    {
        cout << "Enter the person number to check shelter need: ";
        int personNumber;
        cin >> personNumber;
        if (personNumber < 1 || personNumber > people.size())
        {
            cout << "Invalid person number.\n";
            return;
        }
        handleShelterNeed(personNumber - 1);
    }

    void handleMedicinalEmergency()
    {
        cout << "Enter the person number to handle medicinal emergency: ";
        int personNumber;
        cin >> personNumber;

        if (personNumber < 1 || personNumber > people.size()) {
            cout << "Invalid person number.\n";
            return;
        }

        int index = personNumber - 1;
        if (people[index].emergency == "Yes")
        {
            cout << "Medical emergency detected for " << people[index].name << "!\n";
            cout << "Moving " << people[index].name << " to the nearest hospital...\n";
            cout << "Assigned to the nearest hospital.\n";
        }
        else
        {
            cout << people[index].name << " does not have a medical emergency.\n";
        }
    }

    void shareMedicalEmergencyDetails()
{
    cout << "Enter the person number to update medical emergency details: ";
    int personNumber;
    cin >> personNumber;

    if (personNumber < 1 || personNumber > people.size()) {
        cout << "Invalid person number.\n";
        return;
    }

    int index = personNumber - 1;
    string emergencyDetails;

    cout << "Enter details of the medical emergency for " << people[index].name << ": ";
    cin.ignore();
    getline(cin, emergencyDetails);

    people[index].emergency = emergencyDetails;


    ofstream outputFile("input.txt", ios::app);
    if (!outputFile) {
        cerr << "Error opening file to write medical emergency details." << endl;
        return;
    }


    outputFile << people[index].name << ","
               << people[index].nationality << ","
               << people[index].age << ","
               << people[index].dob << ","
               << (people[index].hasVoterID ? "Y" : "N") << ","
               << people[index].birthPlace << ","
               << people[index].educationQualification << ","
               << people[index].occupation << ","
               << people[index].aadharNumber << ","
               << (people[index].isMigrated ? "Y" : "N") << ",";
    if (people[index].isMigrated) {
        outputFile << people[index].migrationSource << ","
                   << people[index].migrationReason << ",";
    }
    outputFile << people[index].emergency << endl;

    outputFile.close();
    cout << "Medical emergency Assisted for " << people[index].name << "!" << endl;
}

    void handleJobNotification(int index)
    {
        if (people[index].occupation.empty())
        {
            cout << "Job notification is sent to " << people[index].name << " as no occupation is available.\n";
        }
        else
        {
            cout << people[index].name << " already has an occupation: " << people[index].occupation << endl;
        }
    }

    void displayDonationsDetails()
    {
        if (donations.empty())
        {
            cout << "No donations available.\n";
            return;
        }

        cout << "\n------------------ Donation Details ----------------\n";
        for (size_t i = 0; i < donations.size(); i++)
        {
            cout << "Donor: " << donations[i].donorName << endl;
            cout << "Amount: " << donations[i].amount << endl;
            cout << "Date: " << donations[i].date << endl;
            cout << "Reason: " << donations[i].reason << endl;
            cout << "---------------------------------------------------\n";
        }
    }

    void searchDonorDetails()
{
    cout << "Enter the donor name to search: ";
    string donorName;
    cin.ignore();
    getline(cin, donorName);

    bool found = false;
    for (const auto& donation : donations)
    {
        if (donation.donorName == donorName)
        {
            cout << "\n--- Donor Details ---\n";
            cout << "Donor Name: " << donation.donorName << endl;
            cout << "Amount: " << donation.amount << endl;
            cout << "Date: " << donation.date << endl;
            cout << "Reason: " << donation.reason << endl;
            cout << "---------------------\n";
            found = true;
            break;
        }
    }


    if (!found)
    {
        cout << "No donor found with the name " << donorName << endl;
    }
}
void addDonorDetails()
{
    Donation newDonor;
    cout << "Enter donor name: ";
    cin.ignore();
    getline(cin, newDonor.donorName);
    cout << "Enter donation amount: ";
    cin >> newDonor.amount;
    cin.ignore();
    cout << "Enter donation date: ";
    getline(cin, newDonor.date);
    cout << "Enter donation reason: ";
    getline(cin, newDonor.reason);

    donations.push_back(newDonor);

    ofstream outputFile("donations.txt", ios::app);
    if (!outputFile)
    {
        cerr << "Error opening donations file to write." << endl;
        return;
    }

    outputFile << newDonor.donorName << ","
               << newDonor.amount << ","
               << newDonor.date << ","
               << newDonor.reason << endl;

    outputFile.close();
    cout << "New donor added successfully and saved to file!" << endl;
}



    void displayPeopleDetails()
    {
        for (size_t i = 0; i < people.size(); i++)
        {
            cout << "\nPerson " << i + 1 << " Details:\n";
            cout << "Name: " << people[i].name << endl;
            cout << "Nationality: " << people[i].nationality << endl;
            cout << "Age: " << people[i].age << endl;
            cout << "Date of Birth: " << people[i].dob << endl;
            cout << "Has Voter ID: " << (people[i].hasVoterID ? "Yes" : "No") << endl;
            cout << "Birth Place: " << people[i].birthPlace << endl;
            cout << "Educational Qualification: " << people[i].educationQualification << endl;
            cout << "Occupation: " << people[i].occupation << endl;
            cout << "Aadhar Number: " << people[i].aadharNumber << endl;

            cout << "Has Migrated: " << (people[i].isMigrated ? "Yes" : "No") << endl;
            if (people[i].isMigrated)
            {
                cout << "Migrated From: " << people[i].migrationSource << endl;
                cout << "Reason for Migration: " << people[i].migrationReason << endl;
            }

            cout << "Medical Emergency: " << people[i].emergency << endl;
            handleMedicalEmergency(i);

            cout << "Has Disease: " << medicinalNeeds[i].hasDisease << endl;
            provideMedicinalNeeds(i);

            cout << "Needs Shelter: " << shelters[i].name << endl;
            if (!shelters[i].name.empty())
            {
                cout << "Shelter Name: " << shelters[i].name << endl;
                cout << "Location: " << shelters[i].location << endl;
            }

            handleJobNotification(i);
        }
    }

    void addPersonDetails()
    {
        Person newPerson;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, newPerson.name);
        cout << "Enter nationality: ";
        getline(cin, newPerson.nationality);
        cout << "Enter age: ";
        cin >> newPerson.age;
        cin.ignore();
        cout << "Enter date of birth: ";
        getline(cin, newPerson.dob);
        cout << "Has Voter ID (Y/N): ";
        char hasVoterID;
        cin >> hasVoterID;
        newPerson.hasVoterID = (hasVoterID == 'Y' || hasVoterID == 'y');
        cin.ignore();
        cout << "Enter birth place: ";
        getline(cin, newPerson.birthPlace);
        cout << "Enter educational qualification: ";
        getline(cin, newPerson.educationQualification);
        cout << "Enter occupation: ";
        getline(cin, newPerson.occupation);
        cout << "Enter Aadhar Number: ";
        getline(cin, newPerson.aadharNumber);
        cout << "Has Migrated (Y/N): ";
        char isMigrated;
        cin >> isMigrated;
        newPerson.isMigrated = (isMigrated == 'Y' || isMigrated == 'y');
        if (newPerson.isMigrated)
        {
            cin.ignore();
            cout << "Enter migration source: ";
            getline(cin, newPerson.migrationSource);
            cout << "Enter migration reason: ";
            getline(cin, newPerson.migrationReason);
        }
        cout << "Is there a medical emergency (Yes/No): ";
        cin.ignore();
        getline(cin, newPerson.emergency);


        people.push_back(newPerson);


        MedicinalNeeds newMedicinalNeed = { "No", "No medicinal needs." };
        medicinalNeeds.push_back(newMedicinalNeed);

        Shelter newShelter = { "", "" };
        shelters.push_back(newShelter);


        ofstream outputFile("input.txt", ios::app);
        if (!outputFile)
        {
            cerr << "Error opening file to write." << endl;
            return;
        }

        outputFile << newPerson.name << ","
                   << newPerson.nationality << ","
                   << newPerson.age << ","
                   << newPerson.dob << ","
                   << (newPerson.hasVoterID ? "Y" : "N") << ","
                   << newPerson.birthPlace << ","
                   << newPerson.educationQualification << ","
                   << newPerson.occupation << ","
                   << newPerson.aadharNumber << ","
                   << (newPerson.isMigrated ? "Y" : "N") << ",";
        if (newPerson.isMigrated)
        {
            outputFile << newPerson.migrationSource << ","
                       << newPerson.migrationReason << ",";
        }
        outputFile << newPerson.emergency << endl;

        outputFile.close();
        cout << "New person added successfully and saved to file!" << endl;
    }

    void deletePersonDetails()
    {
        cout << "Enter the person number to delete: ";
        int personNumber;
        cin >> personNumber;

        if (personNumber < 1 || personNumber > people.size())
        {
            cout << "Invalid person number.\n";
            return;
        }

        int index = personNumber - 1;
        people.erase(people.begin() + index);
        medicinalNeeds.erase(medicinalNeeds.begin() + index);
        shelters.erase(shelters.begin() + index);
        cout << "Person and associated data deleted successfully!\n";
    }

    void updatePersonDetails()
{
    cout << "Enter the person number to update: ";
    int personNumber;
    cin >> personNumber;

    if (personNumber < 1 || personNumber > people.size())
    {
        cout << "Invalid person number.\n";
        return;
    }

    int index = personNumber - 1;

    Person& p = people[index];

    cout << "Updating details for " << p.name << "\n";

    cout << "Enter new name (current: " << p.name << "): ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter new nationality (current: " << p.nationality << "): ";
    getline(cin, p.nationality);

    cout << "Enter new age (current: " << p.age << "): ";
    cin >> p.age;
    cin.ignore();

    cout << "Enter new date of birth (current: " << p.dob << "): ";
    getline(cin, p.dob);

    cout << "Has Voter ID (current: " << (p.hasVoterID ? "Yes" : "No") << ") (Y/N): ";
    char hasVoterID;
    cin >> hasVoterID;
    p.hasVoterID = (hasVoterID == 'Y' || hasVoterID == 'y');
    cin.ignore();

    cout << "Enter new birth place (current: " << p.birthPlace << "): ";
    getline(cin, p.birthPlace);

    cout << "Enter new educational qualification (current: " << p.educationQualification << "): ";
    getline(cin, p.educationQualification);

    cout << "Enter new occupation (current: " << p.occupation << "): ";
    getline(cin, p.occupation);

    cout << "Enter new Aadhar Number (current: " << p.aadharNumber << "): ";
    getline(cin, p.aadharNumber);

    cout << "Has Migrated (current: " << (p.isMigrated ? "Yes" : "No") << ") (Y/N): ";
    char isMigrated;
    cin >> isMigrated;
    p.isMigrated = (isMigrated == 'Y' || isMigrated == 'y');
    cin.ignore();

    if (p.isMigrated)
    {
        cout << "Enter new migration source (current: " << p.migrationSource << "): ";
        getline(cin, p.migrationSource);

        cout << "Enter new migration reason (current: " << p.migrationReason << "): ";
        getline(cin, p.migrationReason);
    }

    cout << "Enter new medical emergency status (current: " << p.emergency << ") (Yes/No): ";
    getline(cin, p.emergency);


    MedicinalNeeds& m = medicinalNeeds[index];
    cout << "Enter new disease status for medicinal needs (current: " << m.hasDisease << ") (Yes/No): ";
    getline(cin, m.hasDisease);
    if (m.hasDisease == "Yes")
    {
        m.medicineRecommendation = "Recommended Medicine: Take prescribed medicines.";
    }
    else
    {
        m.medicineRecommendation = "No medicinal needs.";
    }

    Shelter& s = shelters[index];
    cout << "Enter new shelter name (current: " << s.name << "): ";
    getline(cin, s.name);
    cout << "Enter new shelter location (current: " << s.location << "): ";
    getline(cin, s.location);


    ofstream outputFile("input.txt", ios::trunc);
    if (!outputFile)
    {
        cerr << "Error opening file to write updated details." << endl;
        return;
    }

    for (const auto& person : people)
    {
        outputFile << person.name << ","
                   << person.nationality << ","
                   << person.age << ","
                   << person.dob << ","
                   << (person.hasVoterID ? "Y" : "N") << ","
                   << person.birthPlace << ","
                   << person.educationQualification << ","
                   << person.occupation << ","
                   << person.aadharNumber << ","
                   << (person.isMigrated ? "Y" : "N") << ",";
        if (person.isMigrated)
        {
            outputFile << person.migrationSource << ","
                       << person.migrationReason << ",";
        }
        outputFile << person.emergency << endl;
    }

    outputFile.close();
    cout << "Person details updated successfully!\n";
}

};
//              Google Map
void showngoLocation(const std::string& dealerName)
{

    std::map<std::string, std::string> dealerLocations = {
        {"Adesh", "https://www.google.com/maps?q=15.864476,74.480626"},
        {"Abhishek", "https://www.google.com/maps?q=15.838434,74.504389"},
        {"Shek", "https://www.google.com/maps?q=15.881335,74.524701"} // Coordinates for Shek
    };



    auto it = dealerLocations.find(dealerName);

    if (it != dealerLocations.end())
        {

        std::string url = "start chrome \"" + it->second + "\""; // For Windows; adjust for other OS
        system(url.c_str());
    }
    else
    {

        std::cout << "Location for dealer \"" << dealerName << "\" not found.\n";

    }
}

int alex()
{
    NGOApp app;
    int choice;

    while (true)
    {
        cout << "------------------------------ Fundraising Advertisement --------------------------------\n";
        cout << "\t Support Our Cause!\n";
        cout << "\t We are raising funds for medical aid, education programs, and disaster relief.\n";
        cout << "\t Donate today and be a part of our mission to help those in need!\n";
        cout << "-------------------------------------------------------------------------------------------\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";

        cout << "-------------------- DATABASE OF PERSON ------------------\n";
        {
            cout << "1. Read Person Details from File\n";
            cout << "2. Display All Person Details\n";
            cout << "3. Add New Person Details\n";
            cout << "4. Delete Person Details\n";
            cout << "5. Update Person Details\n";
        }
        cout << "----------------------------------------------------------\n";
        cout << "\n";

        cout << "-------------------- DONATIONS ------------------\n";
        {
            cout << "6. Display Donations Details\n";
            cout << "7. Display Donor Details (Fundraising Campaign)\n";
            cout << "8. Search Donor Details by Name\n";
            cout << "9. Add Donor Details \n";
        }
        cout << "-------------------------------------------------\n";
        cout << "\n";

        cout << "-------- SHELTER AND MEDICAL EMERGENCY --------\n";
        {
            cout << "10. Check Medicinal Emergency\n";
            cout << "11. Check Shelter Need\n";
            cout << "12. Share Medical Emergency Details\n";
        }
        cout << "---------------------------------------------\n";
        cout << "\n";

        cout << "----- SHELTER AND HOSPITALS LOCATIONS -----\n";
        {
            cout << "13. Shelter Names and Locations\n";
            cout << "14. Hospital Names and Locations\n";
            cout << "15. Show NGO near me\n";
        }
        cout << "--------------------------------------------\n";
        cout << "\n";

        cout << "----- EXIT -----\n";
        {
            cout << "16. Exit\n";
        }
        cout << "-----------------\n";
        cout << "\n";

         cout << "-------------------------------------- WE CARE  ---------------------------------------------\n";
        cout << "\t  JOIN  HANDS WITH US TO MAKE THIS WORLD A BETTER PLACE FOR THE UNSEEN PEOPLE\n";
        cout << "\t  Your small change in mode of transport leads to big impact in controlling pollution \n";
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";

        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                app.readFromFile("input.txt");
                break;
            case 2:
                app.displayPeopleDetails();
                break;
            case 3:
                app.addPersonDetails();
                break;
            case 4:
                app.deletePersonDetails();
                break;
            case 5:
                app.updatePersonDetails();
                break;
            case 6:
                app.readDonationsFromFile("donations.txt");
                app.displayDonationsDetails();
                break;
            case 7:
                app.displayDonationsDetails();
                break;
            case 8:
                app.searchDonorDetails();
                break;
            case 9:
                app.addDonorDetails();
                break;
            case 10:
                app.handleMedicinalEmergency();
                break;
            case 11:
                app.handleShelterNeedOption();
                break;
            case 12:
                app.shareMedicalEmergencyDetails();
                break;
            case 13:
                app.readSheltersFromFile("shelter.txt");
                app.displayShelters();
                break;
            case 14:
                app.readHospitalsFromFile("hospital.txt");
                app.displayHospitals();
                break;
            case 15:
                showngoLocation("Adesh");
                app.displayHospitals();
                break;
            case 16:
                cout << "Exiting..\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
//int main()
//{
 //   alex();
//}
