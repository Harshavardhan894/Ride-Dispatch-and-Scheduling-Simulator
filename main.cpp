#include <bits/stdc++.h>
#include "driver.h"
#include "rider.h"
#include "scheduler.h"

using namespace std;

int main(){

    vector<driver> drivers;
    queue<rider> waiting;

    int driverId = 0;
    int riderId = 0;
    int currentTime = 0;

    cout << "System started\n";

    while(true){
        string cmd;
        cin >> cmd;

        if(cmd == "end"){
            finalize(drivers, waiting);
            cout << "System shutting down\n";
            break;
        }

        if(cmd == "driver_in"){
            int x,y,t;
            cin >> x >> y >> t;
            currentTime = max(currentTime, t);

            drivers.push_back({driverId++, x, y, t, t, true});
            cout << "Driver logged in\n";
        }
        else if(cmd == "driver_out"){
            int id, t;
            cin >> id;



            if(id >= 0 && id < drivers.size()){
                drivers[id].active = false;
                cout << "Driver " << id << " logged out at " << "\n";
            }

            // Replan without this driver
            schedule(drivers, waiting, currentTime);
        }
        else if(cmd == "rider"){
            rider r;
            cin >> r.px >> r.py >> r.dx >> r.dy >> r.reqtime;
            currentTime = max(currentTime, r.reqtime);

            r.id = riderId++;
            r.mappedDriver = -1;
            r.assigned = false;

            waiting.push(r);
            cout << "Rider " << r.id << " entered\n";
        }

        schedule(drivers, waiting, currentTime);
    }

    return 0;
}
