#include <glut.h>
#include <cmath>

float angle = 0.0f;  // Angle for camera movement

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Moving camera in a circular path
    float radius = 5.0f;
    float camX = radius * cos(angle);
    float camZ = radius * sin(angle);
    gluLookAt(camX, 2.0, camZ,    // Camera position (X, Y, Z)
              0.0, 0.0, 0.0,      // Look-at point (teapot at origin)
              0.0, 1.0, 0.0);     // Up direction

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 0.0, 1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    GLfloat specular[] = { 0.0, 0.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glutSolidTeapot(1.0);  // Render the teapot

    glFlush();
    glutSwapBuffers();  // Double buffering for smooth animation
}

void timer(int value) {
    angle += 0.01f;
    if (angle > 2 * 3.14159f) angle -= 2 * 3.14159f;
    glutPostRedisplay();          // Redraw the scene
    glutTimerFunc(16, timer, 0);  // Approx 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Animated Teapot with Moving Camera");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);  // Start animation timer

    glutMainLoop();
    return 0;
}