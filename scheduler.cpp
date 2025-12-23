#include "scheduler.h"
#include "distance.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/* GLOBAL PLANNER: recompute mappings for ALL pending riders */
static void replanAll(
    vector<driver>& drivers,
    queue<rider>& waiting,
    int currentTime
){
    vector<rider> pending;

    while(!waiting.empty()){
        if(!waiting.front().assigned)
            pending.push_back(waiting.front());
        waiting.pop();
    }

    if(pending.empty()) return;

    cout << "Re-optimizing mappings\n";

    vector<int> vFree(drivers.size());
    vector<pair<int,int>> vPos(drivers.size());

    for(auto &d : drivers){
        vFree[d.id] = d.freetime;
        vPos[d.id] = {d.x, d.y};
    }

    for(auto &r : pending){

        /* 🔴 FIX: invalidate mapping if driver is out */
        if(r.mappedDriver != -1){
            if(!drivers[r.mappedDriver].active){
                r.mappedDriver = -1;
            }
        }

        int bestDriver = -1;
        int bestPickup = INT_MAX;
        int bestDrop = INT_MAX;

        for(auto &d : drivers){
            if(!d.active) continue;

            int start = max(currentTime, vFree[d.id]);
            int toPickup = distval(
                vPos[d.id].first, vPos[d.id].second,
                r.px, r.py
            );
            int ride = distval(r.px, r.py, r.dx, r.dy);

            int pickup = start + toPickup;
            int drop = pickup + ride;

            if(pickup < bestPickup){
                bestPickup = pickup;
                bestDrop = drop;
                bestDriver = d.id;
            }
        }

        /* 🔒 MONOTONICITY GUARD */
        if(r.mappedDriver != -1 &&
           bestPickup >= r.expectedPickup){

            int dId = r.mappedDriver;
            vFree[dId] = r.expectedDrop;
            vPos[dId] = {r.dx, r.dy};

            waiting.push(r);
            continue;
        }

        r.mappedDriver = bestDriver;
        r.expectedPickup = bestPickup;
        r.expectedDrop = bestDrop;

        vFree[bestDriver] = bestDrop;
        vPos[bestDriver] = {r.dx, r.dy};

        cout << "Rider " << r.id
             << " mapped to Driver " << bestDriver
             << " expected pickup " << bestPickup
             << " expected drop " << bestDrop
             << "\n";

        waiting.push(r);
    }
}


/* DISPATCHER: assign using MINIMUM PICKUP TIME (FIXED) */
void schedule(
    vector<driver>& drivers,
    queue<rider>& waiting,
    int currentTime
){
    int sz = waiting.size();

    while(sz--){
        rider r = waiting.front();
        waiting.pop();

        if(r.assigned){
            continue;
        }

        int bestDriver = -1;
        int bestPickup = INT_MAX;

        for(auto &d : drivers){
            if(!d.active) continue;
            if(d.freetime > currentTime) continue;
            if(r.reqtime > currentTime) continue;

            int pickup = currentTime +
                         distval(d.x, d.y, r.px, r.py);

            if(pickup < bestPickup){
                bestPickup = pickup;
                bestDriver = d.id;
            }
        }

        /* ===== THIS IS THE IMPORTANT GUARD ===== */
        if(bestDriver != -1){

            if(r.mappedDriver != -1 &&
               r.expectedPickup <= bestPickup){
                waiting.push(r);
                continue;
            }

            driver &d = drivers[bestDriver];

            int ride = distval(r.px, r.py, r.dx, r.dy);
            int drop = bestPickup + ride;

            cout << "Rider " << r.id
                 << " assigned to Driver " << d.id
                 << " picked " << bestPickup
                 << " dropped " << drop
                 << " wait " << bestPickup - r.reqtime
                 << "\n";

            d.x = r.dx;
            d.y = r.dy;
            d.freetime = drop;

            r.assigned = true;
        }
        else{
            waiting.push(r);
        }
    }

    replanAll(drivers, waiting, currentTime);
}

void finalize(
    vector<driver>& drivers,
    queue<rider>& waiting
){
    cout << "Finalizing pending riders\n";

    while(!waiting.empty()){
        rider r = waiting.front();
        waiting.pop();

        if(r.assigned) continue;
        if(r.mappedDriver == -1) continue;

        driver &d = drivers[r.mappedDriver];

        int start = max(d.freetime, r.reqtime);
        int toPickup = distval(d.x, d.y, r.px, r.py);
        int ride = distval(r.px, r.py, r.dx, r.dy);

        int pickup = start + toPickup;
        int drop = pickup + ride;

        cout << "Final assignment Rider " << r.id
             << " to Driver " << d.id
             << " picked " << pickup
             << " dropped " << drop
             << "\n";

        d.x = r.dx;
        d.y = r.dy;
        d.freetime = drop;
    }
}
