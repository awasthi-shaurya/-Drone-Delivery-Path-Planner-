#ifndef UTILS_H
#define UTILS_H

#include "planner.h"

int count_pending(Package *p, int n);
double compute_fuel(double dist, double payload, double baseFuel, double weightFactor);
void print_final_report(Package *p, int n, double dist, double fuel, double time);

#endif

