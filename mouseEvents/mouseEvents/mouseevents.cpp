#include <glut.h>
#include <stdio.h>    //printing input and outputs.standard input and output

int ww = 600, wh = 400;
int xi, yi, xf, yf;

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
	glPointSize(2.0);

	glBegin(GL_POINTS);

	glVertex2i(x1, y1);	//plotting the first point

	GLint y;
	float m = (y2 - y1) / (float)(x2 - x1);
	float c = y1 - x1 * m;
	printf("m = %f   ,    c = %f \n", m, c);
	if(x1<x2){
	for (GLint x = x1 + 1; x <= x2; x++) {
		y = m * x + c;
		glVertex2i(x, y);	//plotting points
	}

	glEnd();
	
	}
	else {
	for (GLint x = x2 + 1; x <= x1; x++) {
		y = m * x + c;
		glVertex2i(x, y);	//plotting points
	}
	glEnd();
	}


	
}

void display()
{
	drawLine(xi, yi, xf, yf);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)//this is the user click point
		{
			xi = x;
			yi = (wh - y);
			//yi = (y)
		}
		else if (state == GLUT_UP) { //this is releasing the mouse point
			xf = x;
			yf = (wh - y);
			//yf = (y);

			glutPostRedisplay();
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void myinit()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Lines");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	myinit();
	glutMainLoop();

	return 0;
}