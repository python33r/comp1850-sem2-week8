#ifndef _SHAPES_H_
#define _SHAPES_H_

// Structure definitions

typedef struct _point {
    float x;
    float y;
} Point;

typedef struct _rectangle {
    Point p;
    float width;
    float height;
} Rectangle;

// Function prototypes

Rectangle makeRectangle(Point, float, float);
float area(Rectangle);
void shiftRectangle(Rectangle*, Point);
void scaleRectangle(Rectangle*, float);
Point* corners(Rectangle);
//Rectangle rotate90(Rectangle);

#endif  // _SHAPES_H_
