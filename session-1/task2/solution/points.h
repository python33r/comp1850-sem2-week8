#ifndef _POINT_H_
#define _POINT_H_

typedef struct _point {
    float x;
    float y;
} Point;

float distance(Point, Point);
Point reflect(Point);
Point shift(Point, Point);

#endif  // _POINT_H_
