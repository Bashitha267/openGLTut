#include <glut.h>
#include <cmath>

float ballPositionX = 0.0f;
float ballPositionY = 0.0f;
float ballRadius = 0.8f;
float deltaX = 0.01f;
float deltaY = 0.015f;
int windowWidth = 800;
int windowHeight = 600;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the ball
    glColor3f(0.0f, 0.0f, 1.0f); // Red color
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1415926f / 180.0f;
        glVertex2f(ballPositionX + ballRadius * cos(theta), ballPositionY + ballRadius * sin(theta));
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // Update the position of the ball
    ballPositionX += deltaX;
    ballPositionY += deltaY;

    // Check for collision with the window edges
    if (ballPositionX + ballRadius > 1.0f || ballPositionX - ballRadius < -1.0f) {
        deltaX = -deltaX; // Reverse direction if hitting the side edges
    }
    if (ballPositionY + ballRadius > 1.0f || ballPositionY - ballRadius < -1.0f) {
        deltaY = -deltaY; // Reverse direction if hitting the top or bottom edges
    }

    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(1, update, 0); // Call the update function again after 16 milliseconds
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the 2D orthogonal projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Ball Animation in OpenGL");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Call the update function immediately
    glutMainLoop();
    return 0;
}