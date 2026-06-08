# Ride Dispatch & Scheduling Simulator

A C++ based ride dispatch simulator that models real-time driver assignment and scheduling for ride-sharing systems.

## Features

* Real-time rider and driver simulation
* ETA-based driver matching
* Dynamic driver login/logout
* Global replanning for pending riders
* Stable scheduling with monotonic ETA guarantees
* Queue-based dispatch system

---

## Tech Stack

* C++
* Scheduling Algorithms
* Greedy Optimization
* Queue Simulation

---

## Project Structure

```bash
.
├── main.cpp
├── scheduler.cpp
├── scheduler.h
├── driver.h
├── rider.h
├── distance.h
├── input.h
├── Makefile
└── README.md
```

---

## Build and Run

### Compile

```bash
make
```

### Run

```bash
./simulator.out
```

---

## Supported Commands

### Driver Login

```bash
driver_in <x> <y> <time>
```

Example:

```bash
driver_in 0 0 1
```

---

### Driver Logout

```bash
driver_out <driver_id>
```

Example:

```bash
driver_out 0
```

---

### Rider Request

```bash
rider <pickup_x> <pickup_y> <dest_x> <dest_y> <request_time>
```

Example:

```bash
rider 1 1 7 7 3
```

---

### End Simulation

```bash
end
```

---

## Example Input

```text
driver_in 0 0 1
driver_in 5 5 2

rider 1 1 7 7 3
rider 2 2 8 8 4

driver_out 0

end
```
