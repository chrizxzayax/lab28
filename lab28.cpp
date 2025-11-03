#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void mstone5bycolor(const list<Goat> &trip);
void mstone6countolderthan(const list<Goat> &trip);

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    

    string names[SZ_NAMES];
    int nameCount = 0;
    ifstream fin("names.txt");
    if (!fin) {
        cerr << "Error: names.txt not found." << endl;
        return 1;
    }
    while (nameCount < SZ_NAMES && (fin >> names[nameCount])) ++nameCount;
    fin.close();
    if (nameCount == 0) {
        cerr << "No names found in names.txt" << endl;
        return 1;
    }

    string colors[SZ_COLORS];
    int colorCount = 0;
    ifstream fin1("colors.txt");
    if (!fin1) {
        cerr << "Error: colors.txt not found." << endl;
        return 1;
    }
    while (colorCount < SZ_COLORS && (fin1 >> colors[colorCount])) ++colorCount;
    fin1.close();
    if (colorCount == 0) {
        cerr << "No colors found in colors.txt" << endl;
        return 1;
    }

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    for (int i = 0; i < tripSize; ++i) {
        int age = rand() % MAX_AGE;
        string nm = names[rand() % nameCount];
        string cl = colors[rand() % colorCount];
        Goat tmp(nm, age, cl);
        trip.emplace_back(tmp);
    }
    
    bool running = true;
    while (running) {
        int choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                cout << "LIST OF GOATS\n";
                display_trip(trip);
                break;
            case 4:
                mstone5bycolor(trip);
                break;
            case 5:
                mstone6countolderthan(trip);
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}

int main_menu() {
    int choice = 0;
    cout << "\n*** GOAT MANAGER 3001 (Expanded Menu) ***\n";
    cout << "[1]  Add a goat\n";
    cout << "[2]  Delete a goat\n";
    cout << "[3]  List goats\n";
    cout << "---- STL algorithm milestones: ----\n";
    cout << "[4]  Milestone 5: Find first goat by color (find_if)\n";
    cout << "[5]  Milestone 6: Count goats older than X (count_if)\n";
    cin >> choice;
    while (choice < 1 || choice > 5) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}