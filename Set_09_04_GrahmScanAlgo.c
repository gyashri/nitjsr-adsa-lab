#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point p0;

// Swap two points
void swap(Point *a, Point *b) {
    Point t = *a;
    *a = *b;
    *b = t;
}

// Return orientation: 0 = collinear, 1 = clockwise, 2 = counterclockwise
int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Distance squared
int distSq(Point a, Point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

// Compare for sorting by polar angle
int compare(const void *p1, const void *p2) {
    Point *a = (Point*)p1;
    Point *b = (Point*)p2;
    int o = orientation(p0, *a, *b);
    if (o == 0)
        return distSq(p0, *b) >= distSq(p0, *a) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

void convexHull(Point points[], int n) {
    // Find bottom-most point
    int min = 0;
    for(int i=1; i<n; i++)
        if(points[i].y < points[min].y || 
           (points[i].y == points[min].y && points[i].x < points[min].x))
            min = i;

    swap(&points[0], &points[min]);
    p0 = points[0];

    // Sort points by angle
    qsort(&points[1], n-1, sizeof(Point), compare);

    Point stack[100];
    int top = 0;

    // Push first 3 points
    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    for(int i=3; i<n; i++) {
        while(orientation(stack[top-2], stack[top-1], points[i]) != 2)
            top--;  // Pop
        stack[top++] = points[i];
    }

    // Print hull
    printf("Convex Hull points:\n");
    for(int i=0; i<top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    Point points[] = {{0,3},{2,2},{1,1},{2,1},{3,0},{0,0},{3,3}};
    int n = sizeof(points)/sizeof(points[0]);

    convexHull(points, n);

    return 0;
}
