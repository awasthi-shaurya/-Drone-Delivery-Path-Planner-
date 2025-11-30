#ifndef PLANNER_H
#define PLANNER_H

typedef struct {
    int id;
    double x, y;
    double weight;
    int priority;
    int delivered;
    int undeliverable;
} Package;

void plan_deliveries(Package *packages, int n, double capacity,
                     double speed, double baseFuel, double weightFactor);

int choose_next(Package *packages, int n, double cx, double cy, double remaining);

#endif
