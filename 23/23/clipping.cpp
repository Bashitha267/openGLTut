#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf;

// Clipping window
const float xmin = 50, xmax = 250, ymin = 50, ymax = 250;

// -------------------- Pixel --------------------
void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// -------------------- Bresenham --------------------
void bresenhamAlg(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x, y;

    if (dx >= dy)
    {
        int d = 2 * dy - dx;
        int ds = 2 * dy;
        int dt = 2 * (dy - dx);

        if (x0 < x1) {
            x = x0; y = y0;
        } else {
            x = x1; y = y1;
            x1 = x0; y1 = y0;
        }

        putPixel(x, y);

        while (x < x1)
        {
            if (d < 0)
                d += ds;
            else {
                if (y < y1) y++;
                else y--;
                d += dt;
            }
            x++;
            putPixel(x, y);
        }
    }
    else
    {
        int d = 2 * dx - dy;
        int ds = 2 * dx;
        int dt = 2 * (dx - dy);

        if (y0 < y1) {
            x = x0; y = y0;
        } else {
            x = x1; y = y1;
            y1 = y0; x1 = x0;
        }

        putPixel(x, y);

        while (y < y1)
        {
            if (d < 0)
                d += ds;
            else {
                if (x < x1) x++;
                else x--;
                d += dt;
            }
            y++;
            putPixel(x, y);
        }
    }
}

// -------------------- Liang–Barsky --------------------
void liangBarskyMouse(int x0, int y0, int x1, int y1)
{
    float t0 = 0.0f, t1 = 1.0f;
    float dx = x1 - x0, dy = y1 - y0;
    float p, q, r;

    for (int edge = 0; edge < 4; edge++)
    {
        if (edge == 0) { p = -dx; q = x0 - xmin; }
        else if (edge == 1) { p = dx; q = xmax - x0; }
        else if (edge == 2) { p = -dy; q = y0 - ymin; }
        else { p = dy; q = ymax - y0; }

        if (p == 0)
        {
            if (q < 0) return;
        }
        else
        {
            r = q / p;

            if (p < 0)
            {
                if (r > t1) return;
                if (r > t0) t0 = r;
            }
            else
            {
                if (r < t0) return;
                if (r < t1) t1 = r;
            }
        }
    }

    int xc1 = x0 + t0 * dx;
    int yc1 = y0 + t0 * dy;
    int xc2 = x0 + t1 * dx;
    int yc2 = y0 + t1 * dy;

    // Draw clipped line (RED)
    glColor3f(1.0, 0.0, 0.0);
    bresenhamAlg(xc1, yc1, xc2, yc2);

    glFlush();
}

// -------------------- Display --------------------
void display()
{
    glClearColor(0.4, 0.7, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    glFlush();
}

// -------------------- Mouse --------------------
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            xi = x;
            yi = wh - y;
        }
        else if (state == GLUT_UP)
        {
            xf = x;
            yf = wh - y;

            // Draw original line (WHITE)
            glColor3f(1.0, 1.0, 1.0);
            bresenhamAlg(xi, yi, xf, yf);

            // Draw clipped line (RED)
            liangBarskyMouse(xi, yi, xf, yf);
        }
    }

    // Right click to clear
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        display();
    }
}

// -------------------- Init --------------------
void myinit()
{
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, ww, 0.0, wh);
    glMatrixMode(GL_MODELVIEW);
}

// -------------------- Main --------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Liang-Barsky Line Clipping");

    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}