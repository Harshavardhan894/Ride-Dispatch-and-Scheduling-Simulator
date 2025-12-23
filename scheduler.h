#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <queue>
#include "driver.h"
#include "rider.h"

void schedule(
    std::vector<driver>& drivers,
    std::queue<rider>& waiting,
    int currentTime
);

void finalize(
    std::vector<driver>& drivers,
    std::queue<rider>& waiting
);

#endif
