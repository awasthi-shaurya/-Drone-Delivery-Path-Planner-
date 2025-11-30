#include <stdio.h>
#include "planner.h"
#include "distance.h"
#include "utils.h"

int choose_next(Package *p, int n, double cx, double cy, double rem) {
    int best = -1;
    int bestPr = -9999;
    double bestDist = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].delivered || p[i].undeliverable) continue;
        if (p[i].weight > rem) continue;

        double d = distance(cx, cy, p[i].x, p[i].y);

        if (p[i].priority > bestPr ||
            (p[i].priority == bestPr && d < bestDist)) {

            best = i;
            bestPr = p[i].priority;
            bestDist = d;
        }
    }

    return best;
}

void plan_deliveries(Package *p, int n, double capacity,
                     double speed, double baseFuel, double weightFactor) {

    double totalDist = 0, totalFuel = 0, totalTime = 0;
    int trip = 0;

    while (1) {
        int left = count_pending(p, n);
        if (left == 0) break;

        trip++;
        printf("\n========= Trip %d =========\n", trip);

        double cx = 0, cy = 0;
        double rem = capacity;
        double tripDist = 0;
        double payload = 0;

        while (1) {
            int next = choose_next(p, n, cx, cy, rem);
            if (next == -1) break;

            double d = distance(cx, cy, p[next].x, p[next].y);
            tripDist += d;

            printf("Delivering package %d at (%.1f, %.1f)\n",
                p[next].id, p[next].x, p[next].y);

            rem -= p[next].weight;
            payload += p[next].weight;
            p[next].delivered = 1;

            cx = p[next].x;
            cy = p[next].y;
        }

        double back = distance(cx, cy, 0, 0);
        tripDist += back;

        double fuel = compute_fuel(tripDist, payload, baseFuel, weightFactor);
        double time = tripDist / speed;

        printf("Trip distance: %.2f m\n", tripDist);
        printf("Fuel used: %.4f\n", fuel);
        printf("Time: %.2f sec\n", time);

        totalDist += tripDist;
        totalFuel += fuel;
        totalTime += time;
    }

    print_final_report(p, n, totalDist, totalFuel, totalTime);
}
