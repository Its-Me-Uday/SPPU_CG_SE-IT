#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

Point bezier(Point p0, Point p1, Point p2, Point p3, float t) {
    float u = 1 - t;
    Point p;
    p.x = u * u * u * p0.x + 3 * u * u * t * p1.x + 3 * u * t * t * p2.x + t * t * t * p3.x;
    p.y = u * u * u * p0.y + 3 * u * u * t * p1.y + 3 * u * t * t * p2.y + t * t * t * p3.y;
    return p;
}

void drawBezier(Point p0, Point p1, Point p2, Point p3) {
    glBegin(GL_POINTS);
    for (float t = 0; t <= 1; t += 0.001) {
        Point p = bezier(p0, p1, p2, p3, t);
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void fractalBezier(Point p0, Point p1, Point p2, Point p3, int depth) {
    if (depth == 0) {
        drawBezier(p0, p1, p2, p3);
    } else {
        Point q0 = bezier(p0, p1, p2, p3, 0.0);
        Point q1 = bezier(p0, p1, p2, p3, 0.25);
        Point q2 = bezier(p0, p1, p2, p3, 0.5);
        Point q3 = bezier(p0, p1, p2, p3, 0.75);
        Point q4 = bezier(p0, p1, p2, p3, 1.0);

        fractalBezier(q0, q1, q2, q3, depth - 1);
        fractalBezier(q1, q2, q3, q4, depth - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Point p0 = { -0.8, -0.8 };
    Point p1 = { -0.4, 0.8 };
    Point p2 = { 0.4, 0.8 };
    Point p3 = { 0.8, -0.8 };

    int depth = 3;  // Change depth for more complexity
    fractalBezier(p0, p1, p2, p3, depth);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Fractal Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
