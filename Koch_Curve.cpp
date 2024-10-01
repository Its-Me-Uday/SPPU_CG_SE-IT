#include <GL/glut.h>
#include <cmath>

struct Point {
    float x, y;
};

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void kochCurve(Point p1, Point p2, int depth) {
    if (depth == 0) {
        drawLine(p1, p2);  // Base case, draw the line
    } else {
        Point a, b, c, d;

        // Divide the line segment into 3 parts
        a.x = (2 * p1.x + p2.x) / 3;
        a.y = (2 * p1.y + p2.y) / 3;

        b.x = (p1.x + 2 * p2.x) / 3;
        b.y = (p1.y + 2 * p2.y) / 3;

        // Find the peak point using the 60-degree rotation
        float theta = M_PI / 3;  // 60 degrees
        c.x = a.x + (b.x - a.x) * cos(theta) - (b.y - a.y) * sin(theta);
        c.y = a.y + (b.x - a.x) * sin(theta) + (b.y - a.y) * cos(theta);

        // Recursive calls for the 4 smaller segments
        kochCurve(p1, a, depth - 1);
        kochCurve(a, c, depth - 1);
        kochCurve(c, b, depth - 1);
        kochCurve(b, p2, depth - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Point p1 = { -0.8, 0.0 };  // Starting point of Koch Curve
    Point p2 = { 0.8, 0.0 };   // Ending point of Koch Curve

    int depth = 4;  // Change depth for more iterations of the Koch curve
    kochCurve(p1, p2, depth);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glColor3f(0.0, 0.0, 0.0);          // Set drawing color to black
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
