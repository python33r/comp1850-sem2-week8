#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"


int main(void) {
    Point p = { .x = 0.0f, .y = 0.0f };
    Rectangle r = makeRectangle(p, 10.0f, 5.0f);

    printf("Rectangle area = %g\n", area(r));

    printf("Scaling by 0.5...\n");
    scaleRectangle(&r, 0.5);
    printf("New area = %g\n", area(r));

    Point dp = { .x = 1.5f, .y = 3.5f };
    printf("Shifting by (%g, %g)...\n", dp.x, dp.y);
    shiftRectangle(&r, dp);
    printf("New position = (%g, %g)\n", r.p.x, r.p.y);

    Point* c = corners(r);
    printf("Corners:");
    for (int i = 0; i < 4; ++i) {
        printf(" (%g, %g)", c[i].x, c[i].y);
    }
    printf("\n");

    free(c);

    return 0;
}


Rectangle makeRectangle(Point p, float width, float height) {
    assert(width > 0.0 && height > 0.0);

    Rectangle rect = {
        .p = p,
        .width = width,
        .height = height
    };

    return rect;
}


float area(Rectangle rect) {
    return rect.width * rect.height;
}


void shiftRectangle(Rectangle* rect, Point dp) {
    rect->p.x += dp.x;
    rect->p.y += dp.y;
}


void scaleRectangle(Rectangle* rect, float scale) {
    assert(scale > 0.0);
    rect->width *= scale;
    rect->height *= scale;
}


Point* corners(Rectangle rect) {
    Point* cor = (Point*) calloc(4, sizeof(Point));
    assert(cor != NULL);

    cor[0] = rect.p;
    cor[1].x = rect.p.x; cor[1].y = rect.p.y + rect.height;
    cor[2].x = rect.p.x + rect.width; cor[2].y = rect.p.y + rect.height;
    cor[3].x = rect.p.x + rect.width; cor[3].y = rect.p.y;

    return cor;
}
