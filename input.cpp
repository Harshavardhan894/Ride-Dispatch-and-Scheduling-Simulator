#include "input.h"
#include <iostream>

using namespace std;

void readDrivers(vector<driver>& drivers) {
    for (int i = 0; i < drivers.size(); i++) {
        cin >> drivers[i].x >> drivers[i].y;
        drivers[i].id = i;
        drivers[i].freetime = 0;
    }
}

void readRiders(vector<rider>& riders) {
    for (int i = 0; i < riders.size(); i++) {
        cin >> riders[i].x >> riders[i].y 
            >> riders[i].reqtime >> riders[i].ridetime;
        riders[i].id = i;
    }
}
