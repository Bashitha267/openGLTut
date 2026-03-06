#include <glut.h>

float red = 1.0, green = 0.0, blue = 0.0; // Initial color

void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    glColor3f(red, green, blue); 
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f(-0.5,  0.5);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') { red = 1.0; green = 0.0; blue = 0.0; }  // Red
    if (key == 'g') { red = 0.0; green = 1.0; blue = 0.0; }  // Green
    if (key == 'b') { red = 0.0; green = 0.0; blue = 1.0; }  // Blue

    glutPostRedisplay(); // Request to redraw the window
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT PostRedisplay Example");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard callback

    glutMainLoop();
    return 0;
}