#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <limits>
#include <iomanip> // For formatting output

using namespace std;

// Color codes for terminal (Linux/Unix)
const string RESET = "\033[0m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string MAGENTA = "\033[35m";



void displayMainMenu();
void monitorAirQuality();
void optimizeTraffic();
void enforcePollutionControl();
void generateReports();
void handleInvalidInput();
double calculateShortestPath(int start, int end, const vector<vector<pair<int, double>>>& graph);
void inputVehicleDetails();
void inputSlumAreaDetails();
void suggestRestrictedVehicles(int start, int end);



class Vehicle

 {
public:
    string licensePlate;
    string type;
    double emissionLevel;
    bool isElectric;
    string ownerName;

    Vehicle(string plate, string type, double emission, bool electric, string owner)
        : licensePlate(plate), type(type), emissionLevel(emission), isElectric(electric), ownerName(owner) {}
};

class AirQualityMonitor

{
private:
    map<string, double> pollutants;

public:
    void addPollutant(const string& name, double level)

    {
        pollutants[name] = level;
    }

    void displayAirQuality() const

    {
        cout << YELLOW << "Current Air Quality Levels:" << RESET << endl;
        cout << left << setw(15) << "Pollutant" << setw(10) << "Level (µg/m³)" << endl;
        cout << string(25, '-') << endl;
        for (const auto& pollutant : pollutants)

            {
            cout << left << setw(15) << pollutant.first << setw(10) << pollutant.second << endl;
        }
    }

    double calculateAQI() const

    {
        double aqi = 0;
        for (const auto& pollutant : pollutants)

            {
            aqi += pollutant.second;
        }
        return aqi / pollutants.size();
    }

    void reducePollutants()
     {
        for (auto& pollutant : pollutants)

            {
            pollutant.second = max(0.0, pollutant.second - 5.0);
        }
    }
};

class TrafficManager

 {
private:
    vector<vector<pair<int, double>>> roadGraph;

public:
    TrafficManager(int n)

    {
        roadGraph.resize(n);
    }

    void addRoad(int u, int v, double weight)

    {
        roadGraph[u].push_back({v, weight});
        roadGraph[v].push_back({u, weight});
    }

    double findShortestPath(int start, int end)

    {
        return calculateShortestPath(start, end, roadGraph);
    }
};

class SlumArea

{
public:
    string areaName;
    double pollutantLimit;

    SlumArea(string name, double limit) : areaName(name), pollutantLimit(limit) {}
};



void displayMainMenu()
 {
     cout << "\033[31m\n----------------------------------------ADVERTISEMENT----------------------------------------\033[0m\n";


cout << "\033[32mTogether, we can create a cleaner, healthier planet for everyone\n"
     << "\t Stay green and travel smart!\033[0m\n";




     cout << "\033[31m\n----------------------------------------ADVERTISEMENT----------------------------------------\033[0m\n";


       cout << "\033[31m\n-------------------------------------------MENU-------------------------------------------\033[0m\n";



    cout << BLUE << "\n--- Vehicle Pollution Control System ---\n" << RESET;

    cout << "1. Monitor Air Quality - View and manage current air quality levels.\n";

    cout << "2. Optimize Traffic - Find the shortest route to reduce traffic congestion.\n";

    cout << "3. Enforce Pollution Control - Check and enforce vehicle pollution limits.\n";

    cout << "4. Generate Reports - Generate detailed reports for analysis.\n";

    cout << "5. Enter Vehicle Details - Add a new vehicle to the system.\n";

    cout << "6. Enter Slum Area Details - Add details of an area with specific pollutant limits.\n";

    cout << "7. Suggest Restricted Vehicles and Routes - Get vehicle restrictions based on air quality.\n";

    cout << "8. Exit - Exit the system.\n";

    cout << "Enter your choice: ";

 }



void monitorAirQuality()

{
    AirQualityMonitor monitor;
    monitor.addPollutant("PM2.5", 45.0);
    monitor.addPollutant("CO", 30.0);
    monitor.addPollutant("NO2", 20.0);
    monitor.addPollutant("SO2", 15.0);  // Added another pollutant for more detail
    monitor.addPollutant("O3", 40.0);   // Added Ozone level

    monitor.displayAirQuality();
    cout << GREEN << "Calculated AQI: " << monitor.calculateAQI() << RESET << endl;

    cout << YELLOW << "Air Quality Index (AQI) Guide:" << RESET << endl;

    cout << "0-50: Good\n51-100: Moderate\n101-150: Unhealthy for Sensitive Groups\n151-200: Unhealthy\n201-300: Very Unhealthy\n300-500: Hazardous" << endl;

    cout << "\nImproving air quality...\n";

    monitor.reducePollutants();

    cout << GREEN << "Air quality improved!" << RESET << endl;

    monitor.displayAirQuality();
}

void optimizeTraffic()

{
    TrafficManager manager(9);  // Create traffic manager with 5 points/locations



    int numRoads;
    cout << "Enter the number of roads: ";
    cin >> numRoads;

    for (int i = 0; i < numRoads; i++)

        {
        int u, v;
        double weight;
        cout << "Enter road " << i + 1 << " details (Start Point, End Point, Distance in km): ";
        cin >> u >> v >> weight;
        if (u < 0 || v < 0 || u >= 5 || v >= 5)

         {
            cout << RED << "Invalid points. Please try again." << RESET << endl;
            i--;  // Retry
            continue;
        }
        manager.addRoad(u, v, weight);
    }

    int start, end;
    cout << "Enter starting point (0-4): ";
    cin >> start;
    cout << "Enter destination point (0-4): ";
    cin >> end;

    if (start < 0 || start > 4 || end < 0 || end > 4)

        {
        cout << RED << "Invalid points. Please try again." << RESET << endl;
        return;
    }

    double shortestPath = manager.findShortestPath(start, end);
    cout << GREEN << "Shortest path from " << start << " to " << end << " is: "
         << shortestPath << " km" << RESET << endl;

    cout << YELLOW << "Traffic optimization complete! The route is now optimized for lower emissions." << RESET << endl;
}

void enforcePollutionControl()

{
    vector<Vehicle> vehicles =

    {
        {"MH12AB1234", "Diesel Car", 120.5, false, "Ravi Kumar"},
        {"DL2CA4567", "Electric Car", 0.0, true, "Neha Sharma"},
        {"KA03DE7890", "Petrol Bike", 80.0, false, "Vikram Singh"},
        {"TN10Z1234", "Electric Scooter", 0.0, true, "Priya Deshmukh"},
        {"UP32A9876", "Diesel Truck", 150.0, false, "Ajay Gupta"}
    };

    double emissionLimit = 100.0;  // Pollution threshold

    cout << YELLOW << "\nEnforcing pollution control...\n" << RESET << endl;
    cout << left << setw(15) << "License Plate" << setw(20) << "Type" << setw(15) << "Emission Level" << setw(15) << "Owner" << setw(10) << "Status" << endl;
    cout << string(75, '-') << endl;

    for (const auto& vehicle : vehicles)

        {
        string status = (vehicle.emissionLevel > emissionLimit && !vehicle.isElectric) ? RED + string("Banned") + RESET : GREEN + string("Allowed") + RESET;
        cout << left << setw(15) << vehicle.licensePlate << setw(20) << vehicle.type << setw(15) << vehicle.emissionLevel
             << setw(15) << vehicle.ownerName << setw(10) << status << endl;
    }

    cout << YELLOW << "Pollution control enforcement completed!" << RESET << endl;
}

void generateReports()

{
    cout << YELLOW << "\nGenerating detailed reports...\n" << RESET;
    cout << GREEN << "--- Vehicle Report ---\n" << RESET;


    cout << "License Plate: MH12AB1234\n";
    cout << "Vehicle Type: Diesel Car\n";
    cout << "Emission Level: 120.5 µg/m³\n";

    cout << GREEN << "--- Slum Area Report ---\n" << RESET;


    cout << "Slum Area: Dharavi\n";
    cout << "Pollutant Limit: 100 µg/m³\n";

    cout << GREEN << "--- Air Quality Report ---\n" << RESET;
    // Display air quality data
    cout << "PM2.5: 45.0 µg/m³\n";
    cout << "CO: 30.0 µg/m³\n";

    cout << GREEN << "Reports successfully generated!" << RESET << endl;
}

void inputVehicleDetails()

{
    string plate, type, owner;
    double emission;
    bool electric;

    cout << MAGENTA << "\nEnter Vehicle Details:" << RESET << endl;
    cout << "License Plate: ";
    cin >> plate;



    cout << "Vehicle Type (e.g., Diesel Car, Electric Car): ";
    cin >> type;



    cout << "Emission Level (in µg/m³): ";
    cin >> emission;
    while (emission < 0)

        {
        cout << RED << "Emission level cannot be negative. Please try again." << RESET << endl;
        cin >> emission;
    }


    cout << "Is it an Electric Vehicle? (1 for Yes, 0 for No): ";
    cin >> electric;

    cout << "Owner Name: ";
    cin.ignore(); // To clear the input buffer before reading the owner's name
    getline(cin, owner);

    Vehicle newVehicle(plate, type, emission, electric, owner);
    cout << GREEN << "Vehicle added successfully!" << RESET << endl;
}

void inputSlumAreaDetails()

{
    string areaName;
    double limit;

    cout << MAGENTA << "\nEnter Slum Area Details:" << RESET << endl;
    cout << "Area Name: ";
    cin >> areaName;


    cout << "Pollutant Limit (µg/m³): ";
    cin >> limit;
    while (limit < 0)

        {
        cout << RED << "Pollutant limit cannot be negative. Please try again." << RESET << endl;
        cin >> limit;
    }

    SlumArea newSlumArea(areaName, limit);
    cout << GREEN << "Slum area added successfully!" << RESET << endl;
}

void suggestRestrictedVehicles(int start, int end)

{


    cout << YELLOW << "\nSuggested Restricted Vehicles and Routes:" << RESET << endl;
    // In a real application, we could match the vehicle details with slum areas and their pollutant levels
    cout << GREEN << "Restricted Vehicle: Diesel Car\n";
    cout << GREEN << "Suggested Route: Avoid Slum Area Dharavi" << RESET << endl;
}

double calculateShortestPath(int start, int end, const vector<vector<pair<int, double>>>& graph)

 {
    vector<double> dist(graph.size(), numeric_limits<double>::infinity());
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())

        {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& neighbor : graph[u])

            {
            int v = neighbor.first;
            double weight = neighbor.second;
            if (dist[u] + weight < dist[v])

            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[end];
}

void handleInvalidInput()

 {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << RED << "Invalid input. Please try again." << RESET << endl;
}




int module1()

{
    int choice;
    do

        {
        displayMainMenu();
        cin >> choice;

        if (cin.fail())

            {
            handleInvalidInput();
            continue;
        }

        switch (choice)
        {
            case 1:
                monitorAirQuality();
                break;
            case 2:
                optimizeTraffic();
                break;
            case 3:
                enforcePollutionControl();
                break;
            case 4:
                generateReports();
                break;
            case 5:
                inputVehicleDetails();
                break;
            case 6:
                inputSlumAreaDetails();
                break;
            case 7:
                suggestRestrictedVehicles(0, 4);
                break;
            case 8:
                cout << GREEN << "Exiting the system. Goodbye!" << RESET << endl;
                break;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
    } while (choice != 8);

    return 0;
}

#include<bits/stdc++.h>
#include <fstream>
#include <chrono> //for delay
#include <stdlib.h>
#include<ctime>


// ***** Smart Traffic Management Solution *****

//keep the record of vehicles                      == recOfVeh()
//keep the record of challan done                  == recOfChall()
//Search the record of vehicles                    == vehSearch()
//Display information of traffic in control booths == trafContBooth()
//Helpline Information and nearby hospitals        == helpInfo()
//control the traffic                              == trafCont()


using namespace std;


class SmartTrafficManagementSystem{


public:

    int welcome()
    {
        system("clear");

        time_t tt;
        struct tm * ti;
        time (&tt);
        ti = localtime(&tt);

        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                                                     " <<asctime(ti);
        delay1();

        system("clear");


        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                          WELCOME TO                                                             '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                SMART TRAFFIC MANAGEMENT SYSTEM                                                  '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                   Press Your Option :-                                                                                          '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                    1.Record of Vehicles                                                                         '**"<<endl;

        cout<<"**'                                    2.Record of Challan                                                                          '**"<<endl;

        cout<<"**'                                    3.Search the Record of Vehicles                                                              '**"<<endl;

        cout<<"**'                                    4.Traffic Control Booths                                                                     '**"<<endl;

        cout<<"**'                                    5.Control the Traffic                                                                        '**"<<endl;

        cout<<"**'                                    6.Help !                                                                                     '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                   Enter your choice __                                                                                          '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;


        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<"**'                                                                                                                                 '**"<<endl;

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;


        int choice{0};
        cin>>choice;

        if(choice > 0 && choice < 7)
        {
            switch (choice)
            {
                case 1:
                    system("clear");
                    recOfVeh();
                    break;

                case 2:
                    system("clear");
                    recOfChall();
                    break;

                case 3:
                    system("clear");
                    vehSearch();
                    break;

                case 4:
                    system("clear");
                    trafContBooth();
                    break;

                case 5:
                    system("clear");
                    trafContBooth();
                    break;

                case 6:
                    system("clear");
                    helpInfo();
                    break;
            }
        } else

        {
            cout<<"Enter Valid option !!"<<endl;
            delay();

            system("clear");
            welcome();
        }
        return 0;
    }

    int delay()
    {
        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono; // nanoseconds, system_clock, seconds

        sleep_for(nanoseconds(1000000));
        sleep_until(system_clock::now() + seconds(1));
    }
    int delay1()
    {
        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono; // nanoseconds, system_clock, seconds

        sleep_for(nanoseconds(1000000000));
        sleep_until(system_clock::now() + seconds(1));
    }
    int delay2()
    {
        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono; // nanoseconds, system_clock, seconds

        sleep_for(nanoseconds(100000000));
        sleep_until(system_clock::now() + seconds(1));
    }
    int recOfVeh()
    {
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;


        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                            WELCOME TO                                                               *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                  SMART TRAFFIC MANAGEMENT SYSTEM                                                    *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                      * Record of Vehicles *                                                         *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                     Press Your Option :-                                                                                            *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                      1. Add a New Vehicle                                                                           *"<<endl;

        cout<<"*                                      2. Search a Vehicle Using registration number                                                  *"<<endl;

        cout<<"*                                      3. Search a Vehicle Using Name of the owner                                                    *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                     Enter 0 For Home                                                                                                *"<<endl;

        cout<<"*                     Enter your choice __                                                                                            *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<"*                                                                                                                                     *"<<endl;

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        int ROVChoice{0};
        cin>>ROVChoice;
        switch (ROVChoice)
        {
            case 0:
                system("clear");
                welcome();
                break;

            case 1:
                recOfVeh_1();
                break;

            case 2:
                recOfVeh_2();
                break;

            case 3:
                recOfVeh_3();
                break;

        }
        return 0;
    }
    int recOfVeh_1()
    {
        system("clear");
        fstream fio;
        string line;
        cout << "                    Welcome to Registration of Vehicles\n"<<endl;
        cout<<"Enter Registration number of the Vehicle in the first line "<<endl;
        cout<<"Enter Name of the owner in the second line "<<endl;
        cout<<endl<<"Enter './' to Exit ";
        fio.open("/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfVehicles.txt", ios::app | ios::out | ios::in);

        // Execute a loop If file successfully Opened
        while (fio) {

            // Read a Line from standard input
            getline(cin, line);

            // Press -1 to exit
            if (line == "./")
                break;

            // Write line in file
            fio << line << endl;
        }
        cout<<"Data Entered successfully !!"<<endl;
        delay();

        system("clear");
        recOfVeh();

    }

    int recOfVeh_2()
    {
        system("clear");
        string path = "/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfVehicles.txt";
        ifstream file( path.c_str() );

        if( file.is_open() )
        {
            cout << "                    Welcome to Registration of Vehicles\n" ;

            cout <<endl<< "Write the Registration number of the vehicle you want to searching for\n" ;
            string word ;
            cin >> word ;

            int countwords = 0 ;
            string candidate ;
            while( file >> candidate ) // for each candidate word read from the file
            {
                if( word == candidate ) ++countwords ;
            }
            if (countwords > 0)

                {
                cout << "The registration number " << word << "' has been found in our records."<<endl ;

                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number ";
                cin>>choice;
                (choice ==1) ? welcome(): recOfVeh_2();



            }
            else

                {
                cout<<"Registration number does not foud !!";
                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number ";
                cin>>choice;
                 (choice ==1) ? welcome(): recOfVeh_2();
            }
        }

        else
        {
            cerr << "Error! 401!\n" ;
            delay();
            welcome();

        }


    }

    int recOfVeh_3()
    {
        system("clear");

        string path = "/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfVehicles.txt";
        ifstream file( path.c_str() );

        if( file.is_open() )
        {
            cout << "                    Welcome to Registration of Vehicles\n" ;

            cout <<endl<< "Write the Name of the Owner of the vehicle you want to searching for\n" ;
            string word ;
            cin >> word ;

            int countwords = 0 ;
            string candidate ;
            while( file >> candidate ) // for each candidate word read from the file
            {
                if( word == candidate ) ++countwords ;
            }
            if (countwords > 0)

                {
                cout << "The Name of the Owner " << word << "' has been found in our records."<<endl ;

                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the Name of the Owner";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfVeh_2();

            }
            else
                {
                cout<<"Name of the Owner does not foud !!";
                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the Name of the Owner ";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfVeh_2();
            }
        }

        else
        {
            cerr << "Error! 401!\n" ;
            delay();
            welcome();

        }

    }

    int recOfChall()
    {
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                            WELCOME TO                                                               *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                  SMART TRAFFIC MANAGEMENT SYSTEM                                                    *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                      * Record of Challan *                                                          *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Press Your Option :-                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                      1. Add a New Challan                                                                           *"<<endl;
        cout<<"*                                      2. Search a Challan Using registration number                                                  *"<<endl;
        cout<<"*                                      3. Search a Challan Using Name of the owner                                                    *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Enter 0 For Home                                                                                                *"<<endl;
        cout<<"*                     Enter your choice __                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        int ROCChoice{0};
        cin>>ROCChoice;
        switch (ROCChoice)
        {
            case 0:
                system("clear");
                welcome();
                break;

            case 1:
                recOfChall_1();

                break;

            case 2:
                recOfChall_2();
                break;

            case 3:
                recOfChall_3();
                break;
            default:
                cout << "please enter a valid case" << endl;

        }
        return  0;
    }

    int recOfChall_1()
    {

        system("clear");
        fstream fio;
        string line;

        cout << "               Welcome to Challan Management System\n"<<endl;

        cout<<"Enter Registration number of the Vehicle in the first line "<<endl;
        cout<<"Enter Name of the owner in the second line "<<endl;
        cout<<endl<<"Enter './' to Exit ";
        fio.open("/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfChallan.txt", ios::app | ios::out | ios::in);

        // Execute a loop If file successfully Opened
        while (fio)
            {

            // Read a Line from standard input
            getline(cin, line);

            // Press -1 to exit
            if (line == "./")
                break;

            // Write line in file
            fio << line << endl;
        }
        cout<<"Data Entered successfully !!"<<endl;
        delay();

        system("clear");
        recOfChall();


    }

    int recOfChall_2()
    {

        system("clear");
        string path = "/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfChallan.txt";
        ifstream file( path.c_str() );

        if( file.is_open() )
        {
            cout << "               Welcome to Challan Management System\n"<<endl;

            cout <<endl<< "Write the registration number of the vehicle you want to searching for\n" ;
            string word ;
            cin >> word ;

            int countwords = 0 ;
            string candidate ;
            while( file >> candidate ) // for each candidate word read from the file
            {
                if( word == candidate ) ++countwords ;
            }
            if (countwords > 0)

                {
                cout << "The Registration number '" << word << "' has been found in our records."<<endl ;

                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number.";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfChall_2();

            }
            else

                {
                cout<<"Registration number does not foud !!";
                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number.";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfChall_2();
            }
        }

        else
        {
            cerr << "Error! 402!\n" ;
            delay();
            welcome();

        }
    }

    int recOfChall_3()
    {
        system("clear");
        string path = "/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfChallan.txt";
        ifstream file( path.c_str() );

        if( file.is_open() )
        {
            cout << "               Welcome to Challan Management System\n"<<endl;

            cout <<endl<< "Write the Name of the Owner of the vehicle you want to searching for\n" ;
            string word ;
            cin >> word ;

            int countwords = 0 ;
            string candidate ;
            while( file >> candidate ) // for each candidate word read from the file
            {
                if( word == candidate ) ++countwords ;
            }
            if (countwords > 0)

                {
                cout << "The Name of the Owner " << word << "' has been found in our records."<<endl ;

                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the Name of the Owner";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfChall_3();

            }
            else

                {
                cout<<"Name of the Owner does not foud !!";
                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the Name of the Owner ";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    recOfChall_3();
            }
        }

        else
        {
            cerr << "Error! 402!\n" ;
            delay();
            welcome();

        }
    }

    int vehSearch()
    {

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                            WELCOME TO                                                               *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                  SMART TRAFFIC MANAGEMENT SYSTEM                                                    *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                 * Search the Record of Vehicles *                                                   *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                               Enter The Vehicles Registration Number                                                *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Enter 0 For Home                                                                                                *"<<endl;
        cout<<"*                     Enter your choice __                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;


        string path = "/home/lamecodes/CLionProjects/untitled/cmake-build-debug/RecordOfVehicles.txt";
        ifstream file( path.c_str() );
        system("clear");

        if( file.is_open() )
        {

            string word ;
            cin >> word ;

            int countwords = 0 ;
            string candidate ;
            while( file >> candidate ) // for each candidate word read from the file
            {
                if( word == candidate ) ++countwords ;
            }
            if (countwords > 0)

                {
                cout << "The registration number " << word << "' has been found in our records."<<endl ;

                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number ";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    vehSearch();
            }
            else

                {
                cout<<"Registration number does not foud !!";
                int choice;
                cout<<endl<<"Enter 1 to go to home screen and enter 2 for again entering the registration number ";
                cin>>choice;
                if (choice ==1)
                    welcome();
                else
                    vehSearch();
            }
        }
        else
        {
            cerr << "Error! 401!\n" ;
            delay();
            welcome();

        }




    }

    int trafContBooth()
    {

        // Traffic Control Booths

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                            WELCOME TO                                                               *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                  SMART TRAFFIC MANAGEMENT SYSTEM                                                    *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                     * Traffic Control Booths *                                                      *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Press Your Option :-                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                      1. Jalandhar Traffic Control Booth                                                             *"<<endl;
        cout<<"*                                      2. Amritsar Traffic Control Booth                                                              *"<<endl;
        cout<<"*                                      3. Chandigarh Traffic Control Booth                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Enter 0 For Home                                                                                                *"<<endl;
        cout<<"*                     Enter your choice __                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        int TCBChoice{0};
        cin>>TCBChoice;
        switch (TCBChoice)
        {
            case 0:
                system("clear");
                welcome();
                break;

            case 1:
                trafContBooth_1();
                break;

            case 2:
                trafContBooth_2();
                break;

            case 3:
                trafContBooth_3();
                break;

        }


        return 0;
    }
    int trafContBooth_1()
    {
        system("clear");

        for (int i = 0; i < 100; ++i)

            {

            cout<<"                     Jalandhar City Traffic Control Booth                 "<<endl;
            cout<<"Vehicles Going out of the City                   Vehicles coming into the City"<<endl;
            cout<<endl<<"      "<<i+1<<"                                             "<<i+5<<endl;
            delay();

            system("clear");

        }

    }

    int trafContBooth_2()
    {
        system("clear");

        for (int i = 0; i < 100; ++i)

            {

            cout<<"                      Amritsar City Traffic Control Booth                 "<<endl;
            cout<<"Vehicles Going out of the City                   Vehicles coming into the City"<<endl;
            cout<<endl<<"      "<<i+5<<"                                             "<<i*7<<endl;
            delay();

            system("clear");

        }


    }

    int trafContBooth_3()
    {

        system("clear");

        for (int i = 0; i < 100; ++i)

            {

            cout<<"                      Chandigarh City Traffic Control Booth                 "<<endl;
            cout<<"Vehicles Going out of the City                   Vehicles coming into the City"<<endl;
            cout<<endl<<"      "<<i*16<<"                                             "<<i*22<<endl;
            delay();

            system("clear");

        }

    }

    int helpInfo()
    {
        //Helpline Information and nearby hospitals

        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                            WELCOME TO                                                               *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                  SMART TRAFFIC MANAGEMENT SYSTEM                                                    *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                             * Helpline Information And Nearby Hospitals *                                           *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Press Your Option :-                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                      1. Helpline Number                                                                             *"<<endl;
        cout<<"*                                      2. Hospitals in Amritsar                                                                       *"<<endl;
        cout<<"*                                      3. Hospitals in Chandigarh                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                     Enter 0 For Home                                                                                                *"<<endl;
        cout<<"*                     Enter your choice __                                                                                            *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<"*                                                                                                                                     *"<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;

        int CTTChoice{0};
        cin>>CTTChoice;
        switch (CTTChoice)

         {
            case 0:
                system("clear");
                welcome();
                break;

            case 1:
                 {
                system("clear");
                string line;
                ifstream myfile("/home/lamecodes/CLionProjects/untitled/cmake-build-debug/HelpNumbers.txt");
                if (myfile.is_open())

                    {
                    while (getline(myfile, line))

                        {
                        cout << line << '\n';
                    }
                    myfile.close();
                } else cout << "Error! 403!";

                int choice;
                cout << endl << "Enter 1 to go Home Page" << endl;
                cin >> choice;
                if (choice == 1)

                    {
                    system("clear");
                    welcome();
                } else {
                    cout << endl << "Enter Valid option !!";
                    cout << endl << endl << "Enter 1 to go Home Page" << endl;
                    cin >> choice;
                    if (choice == 1)

                     {
                        system("clear");
                        welcome();
                    }
                }
                break;
            }
            case 2:

                {

                system("clear");
                string line;
                ifstream myfile("/home/lamecodes/CLionProjects/untitled/cmake-build-debug/HAmritsar.txt");
                if (myfile.is_open())

                    {
                    while (getline(myfile, line))

                     {
                        cout << line << '\n';
                    }
                    myfile.close();
                } else cout << "Error! 403!";

                int choice;
                cout << endl << "Enter 1 to go Home Page" << endl;
                cin >> choice;
                if (choice == 1)

                    {
                    system("clear");
                    welcome();
                } else {
                    cout << endl << "Enter Valid option !!";
                    cout << endl << endl << "Enter 1 to go Home Page" << endl;
                    cin >> choice;
                    if (choice == 1)

                    {
                        system("clear");
                        welcome();
                    }
                }
            }
                break;

            case 3:

                 {

                system("clear");
                string line;
                ifstream myfile("/home/lamecodes/CLionProjects/untitled/cmake-build-debug/HChandigarh.txt");
                if (myfile.is_open())

                    {
                    while (getline(myfile, line))

                        {
                        cout << line << '\n';
                    }
                    myfile.close();
                } else cout << "Error! 403!";

                int choice;
                cout << endl << "Enter 1 to go Home Page" << endl;
                cin >> choice;
                if (choice == 1)

                    {
                    system("clear");
                    welcome();
                } else {
                    cout << endl << "Enter Valid option !!";
                    cout << endl << endl << "Enter 1 to go Home Page" << endl;
                    cin >> choice;
                    if (choice == 1)

                     {
                        system("clear");
                        welcome();
                    }
                }


                break;

            }
        }

        return 0;
    }




};
int module2()
{
    SmartTrafficManagementSystem ob1;
    ob1.welcome();

    //all rights reserved  ©rudrakaniya || CSEBaba
}
int tr()
{
    int choice=0;
    do
    {
    std::cout << "1.module1" << std::endl;

    std::cout << "2.module2" << std::endl;

        std::cout << "3. EXIT " << std::endl;


        std::cout<<"THANK YOU"<<endl;

     std:: cout<<"****************************************************************************************************************"<<endl;


     cout<<"\nEnter your choice:\t";

     cin>>choice;

     switch(choice)
     {
         case 1:module1();

                break;

         case 2:module2();

                break;

                default:cout<<"ENTER VALID CHOICE";

                break;


     }

    }

    while(choice!=4);

    return 0;
}
//int main()
//{
 //   tr();
//}




