// Taqiuddin
// none
// 024
// 12/6/2023

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// 35b24e49-2842-4603-8ba7-0f656200c2d1
//------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector> 
#include <climits>
#include <cmath>
using namespace std;

struct Planet {   //build struct for the data of planet 
    int row;
    int column;
    int id;
    string symbol;
    string name;
    bool isVisited;
};

int rowB; // B = boundaries
int columnB;
int rowS; // s = start
int columnS;
int rowE; // e = end
int columnE;
bool isAllVisited;  // already visited

vector<Planet> planetInRoute;
vector<int> planetIds; // information from the names.txt file
vector<string> planetNames; // information from the names.txt file
vector< vector <string> > route; // the route the driver is going to take

string correction(string p_name) {
    // replace and erase the double "xx"
    // replace _ with space
    
    if (p_name.find("XX") == -1 && p_name.find("_") == -1) {
        return p_name;
    }
     
    while (p_name.find("XX") != -1) {
        p_name = p_name.substr(0, p_name.find("XX")) + p_name.substr(p_name.find("XX") + 2);
    }
    while (p_name.find("_") != -1) {
        p_name.at(p_name.find("_")) = ' ';
    }
    return p_name;
}

string findPlanetName(int id_temp) {
    int index;
    // loops through the planetID vector to get the index in order to find the planetName
    // since the planetName and planetId vector are in the same order
    for (int i = 0; i < planetIds.size(); i++) {
        if (planetIds[i] == id_temp) {
            index = i;
            break;
        }
    }
    // returns the planetName at the index
    return planetNames[index];
}

void outRange(int rowtemp, int columntemp, int id_temp, string symbol_temp) {
    // row and column <= 0, means there shall be no coordinate in negative 
    // r and c > B (boundaries)

    if (rowtemp <= 0 || columntemp <= 0 || 
        rowtemp > rowB || columntemp > columnB) {
        cout << id_temp << " out of range - ignoring\n";
    }
    //if inside the map, store it in the vector 
    else {
        Planet planet;
        planet.row = rowtemp;
        planet.column = columntemp;
        planet.id = id_temp;
        planet.symbol = symbol_temp;
        planet.name = findPlanetName(id_temp);
        planet.isVisited = false;
        planetInRoute.push_back(planet);
    }
}

string fillMap(int r, int c) {   // build map where r=row and c=column based on the size 
    for (int i = 0; i < planetInRoute.size(); i++) {
        if (r == (planetInRoute[i].row - 1) && c == (planetInRoute[i].column - 1)) {
            return planetInRoute[i].symbol;
        }
    }
    return ".";
}

int distance(int x_current, int y_current) {
    // distance = sqrt(pow(x_current - x_potential, 2) + pow(y_current - y_potential, 2))
    double minDistance = INT_MAX;
    int index = 0;
    for (int i = 0; i < planetInRoute.size(); i++) {
        double tempDistance = 0;  // 0 the start values
        double x_potential = 0;
        double y_potential = 0;
        if (planetInRoute[i].isVisited == false) {
            x_potential = planetInRoute[i].row;
            y_potential = planetInRoute[i].column;
            tempDistance = sqrt(pow(x_current - x_potential, 2) + pow(y_current - y_potential, 2));
            if (minDistance > tempDistance) {
                minDistance = tempDistance;   // assign minimum distance as the current temporary distance
                index = i;
            }
        }
    }
    planetInRoute[index].isVisited = true;
    return index;
}

bool is_All_Visited() {  // visited planet bool
    for ( int i = 0; i < planetInRoute.size(); i++) {
        if (planetInRoute[i].isVisited == false) {
            return false;
        }
    }
    return true;
}

int main () {   //main starts here

    //ask people to put in the filename for the location  and name
    string locationFilename;
    string namesFilename;
    
    cout << "Enter Locations Filename: ";
    cin >> locationFilename;

    cout << "Enter Names Filename: ";
    cin >> namesFilename;
    
    ifstream location;  // try to open the file
    ifstream names;  

    location.open(locationFilename.c_str());
    names.open(namesFilename.c_str());
        
    if (!location.is_open() || !names.is_open()) {
        cout << "Input file could not be opened\n";   // if fail, cout statement that its a fail input
        return 1;
    }    
    
    int id;
    string name;

    // reads in the names file and gets the planet id and the planet name
    while (names >> id >> name) {   // orders matters, based on the txt file, it starts with id and then the name of the planet
        planetIds.push_back(id);
        planetNames.push_back(correction(name));   // putback the corrected name (no xx or _) 
    }
    
    // file >> variable;
    location >> rowB >> columnB >> rowS >> columnS >> rowE >> columnE;  // order matters
    
    int rowP; // p = planet
    int columnP;
    int idP;
    // p_name = planet name
    string symbolP;

    while (location >> rowP >> columnP >> symbolP >> idP) {
        outRange(rowP, columnP, idP, symbolP);
    }

    // create location grid
    ofstream journey;
    journey.open("journey.txt");

    vector< vector<string> > map;

    for (int r = 0; r < rowB ; r++) {
        vector <string> row;
        for (int c = 0; c < columnB; c++) {   
            if (r == (rowS - 1) && c == (columnS - 1)) {
                row.push_back("S");   // starting point
            }
            else if (r == (rowE - 1) && c == (columnE - 1)) {
                row.push_back("E");  // end point
            }
            else {
                row.push_back(fillMap(r, c));
            }
        }
        map.push_back(row);
    }

    for (int r = 0 ; r < rowB ; r++) {
        for ( int c = 0 ; c < columnB ; c++) { 
            journey << map[r][c];  
        }
        journey << endl;
    }

    journey << "Start at " << rowS << " " << columnS << endl;   // which row and column it starts/current position
    int x_current = rowS;
    int y_current = columnS;
    
    while (is_All_Visited() == false) {
        int i = distance(x_current, y_current);
        x_current = planetInRoute[i].row;
        y_current = planetInRoute[i].column;
        journey << "Go to " << planetInRoute[i].name << " at " << x_current << " " << y_current << endl;
    }
    journey << "End at " << rowE << " " << columnE << endl;
}


