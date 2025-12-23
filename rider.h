#ifndef RIDER_H
#define RIDER_H

struct rider {
    int id;

    int px, py;   // pickup
    int dx, dy;   // destination
    int reqtime;

    int mappedDriver;
    int expectedPickup;
    int expectedDrop;

    bool assigned;
};

#endif
