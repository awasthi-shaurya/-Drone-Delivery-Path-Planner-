#include <stdio.h>
#include "utils.h"
#include "distance.h"

int count_pending(Package *p, int n) {
    int c = 0;
    for (int i = 0; i < n; i++)
        if (!p[i].delivered && !p[i].undeliverable)
            c++;
    return c;
}

double compute_fuel(double dist, double payload, double baseFuel, double weightFactor) {
    double km = dist / 1000.0;
    double avg = payload / 2.0;
    return km * (baseFuel + avg * weightFactor);
}

void print_final_report(Package *p, int n, double dist, double fuel, double time) {
    printf("\n========= FINAL REPORT =========\n");
    printf("Total distance: %.2f m\n", dist);
    printf("Total fuel: %.4f units\n", fuel);
    printf("Total time: %.2f seconds\n", time);

    printf("\nUndeliverable packages:\n");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].undeliverable) {
            printf("Package %d (%.2f kg) — too heavy\n", p[i].id, p[i].weight);
            found = 1;
        }
    }
    if (!found) printf("None\n");
}

