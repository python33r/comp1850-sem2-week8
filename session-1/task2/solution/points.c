#include <math.h>
#include <stdio.h>
#include "points.h"

int main(void) {
    Point p1 = { .x=1, .y=2 };
    Point p2 = { .x=-2, .y=4 };
    
    printf("Distance between (%.1f, %.1f) and (%.1f, %.1f) is %f\n", 
        p1.x, p1.y, p2.x, p2.y, distance(p1, p2));

    Point rp1 = reflect(p1);
    printf("x-axis reflection of (%.1f, %.1f) is (%.1f, %.1f)\n",
        p1.x, p1.y, rp1.x, rp1.y
    );

    Point delta = { .x=-0.5, .y=0.5 };
    Point sp1 = shift(p1, delta);
    printf("(%.1f, %.1f) shifted by (%.1f, %.1f) is (%.1f, %.1f)\n",
        p1.x, p1.y, delta.x, delta.y, sp1.x, sp1.y
    );

    return 0;
}

/**
 * Computes the Euclidean distance between two points.
 *
 * @param p First point
 * @param q Second point
 * @return Distance between p and q
 */
float distance(Point p, Point q) {
    return sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}

/**
 * Reflects a point in the x axis.
 *
 * @param p Point to be reflected
 * @return Reflection of p in x axis
 */
Point reflect(Point p) {
    Point reflected = { .x = -p.x, .y = p.y };
    return reflected;
}

/**
 * Shifts a point by the specified displacement.
 *
 * @param p Point to be shifted
 * @param dp Displacement, as a Point object
 * @return Displaced point
 */
 Point shift(Point p, Point dp) {
    Point shifted = { .x = p.x + dp.x, .y = p.y + dp.y };
    return shifted;
 }
