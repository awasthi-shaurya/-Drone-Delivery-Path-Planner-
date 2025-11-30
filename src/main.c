#include <stdio.h>
#include <stdlib.h>
#include "planner.h"

int main() {
    int n;
    printf("Enter number of packages: ");
    scanf("%d", &n);

    Package *p = malloc(sizeof(Package) * n);

    printf("Enter (id x y weight priority):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %lf %lf %lf %d",
              &p[i].id, &p[i].x, &p[i].y,
              &p[i].weight, &p[i].priority);
        p[i].delivered = 0;
        p[i].undeliverable = 0;
    }

    double capacity, speed, baseFuel, weightFactor;

    printf("Enter drone max capacity: ");
    scanf("%lf", &capacity);

    printf("Enter speed (m/s): ");
    scanf("%lf", &speed);

    printf("Enter base fuel/km: ");
    scanf("%lf", &baseFuel);

    printf("Enter weight factor: ");
    scanf("%lf", &weightFactor);

    for (int i = 0; i < n; i++)
        if (p[i].weight > capacity)
            p[i].undeliverable = 1;

    plan_deliveries(p, n, capacity, speed, baseFuel, weightFactor);

    free(p);
    return 0;
}
