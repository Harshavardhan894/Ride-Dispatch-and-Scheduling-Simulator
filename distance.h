#ifndef DISTANCE_H
#define DISTANCE_H

#include <cstdlib>

inline int distval(int x1,int y1,int x2,int y2){
    return abs(x1-x2) + abs(y1-y2);
}

#endif
