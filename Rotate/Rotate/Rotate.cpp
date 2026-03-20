#define _USE_MATH_DEFINES
#include <glut.h>  
#include <math.h>  
#include <cmath>
#include <iostream>
int ww = 600, wh = 400;  
  
float xi, yi, xf, yf;  
const int rows = 3;//in 2d transformations always rows 3     [x y 1,x1 y1 ,1] likewise

const int NoOfVertices = 4; 
float coordinates [rows][NoOfVertices];

const double pi = M_PI;

void setCoordinates(float x1, float y1, float x2, float y2)
{
	coordinates[0][0]=x1;   //[x1    x2   x2   x1
	coordinates[1][0]=y1;   //   y1    y1   y2   y2
	coordinates[2][0]=1;    //   1     1    1    1 ]
	coordinates[0][1]=x2;
	coordinates[1][1]=y1;
	coordinates[2][1]=1;
	coordinates[0][2]=x2;
	coordinates[1][2]=y2;
	coordinates[2][2]=1;
	coordinates[0][3]=x1;
	coordinates[1][3]=y2;
	coordinates[2][3]=1;
}
void setRotationMatrx(float teta, float rotationMatrix[rows][rows])
{
	rotationMatrix[0][0]=cos(teta);
	rotationMatrix[0][1]=-1*sin(teta);
	rotationMatrix[0][2]=0;
	rotationMatrix[1][0]=sin(teta);
	rotationMatrix[1][1]=cos(teta);
	rotationMatrix[1][2]=0;
	rotationMatrix[2][0]=0;
	rotationMatrix[2][1]=0;
	rotationMatrix[2][2]=1;
}

void setTranslationMatrix(float dx, float dy, float translationMatrix[rows][rows])
{
	translationMatrix[0][0]=1;
	translationMatrix[0][1]=0;
	translationMatrix[0][2]=dx;
	translationMatrix[1][0]=0;
	translationMatrix[1][1]=1;
	translationMatrix[1][2]=dy;
	translationMatrix[2][0]=0;
	translationMatrix[2][1]=0;
	translationMatrix[2][2]=1;
}
void multiply_arrays(float A[rows][rows], float B[rows][NoOfVertices], float C[rows][NoOfVertices]) 
{
    for (int i = 0; i < rows; i++) 
	{  
        for (int j = 0; j < NoOfVertices; j++) 
		{
            C[i][j] = 0;
            for (int k = 0; k < rows; k++) 
			{
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void putPixel (int x, int y)  
{  
   //glColor3f (0.3, 0.2, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
	   glVertex2i (x, y); // set the point  
	   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 
 
void display()  
{  
   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
}  
void bresenhamLine(int x0, int y0, int x1, int y1)  
{  
  int dx = abs (x1 - x0);  
  int dy = abs (y1 - y0);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (x0 < x1)   
       {  
            x = x0;  
            y = y0;  
        }  
        else  
        {   
            x = x1;  
            y = y1;  
            x1 = x0;  
            y1 = y0;  
        }  
	  putPixel (x, y);  
	  while (x < x1)  
	  {  
		if (d < 0)  
			d += ds;  
			else {  
				 if (y < y1) {  
				   y++;  
				   d += dt;  
					}   
				 else {  
					y--;  
					d += dt;             
				 }  
			}  
			x++;  
			putPixel (x, y);  
		}  
	}  
   else 
   {   
	   int d = 2*dx-dy;  
		 int ds = 2*dx;  
		 int dt = 2*(dx-dy);  
		 if (y0 < y1) 
		 {  
			 x = x0;  
			 y = y0;  
		 }  
		 else 
		 {   
			 x = x1;  
			 y = y1;  
			 y1 = y0;  
			 x1 = x0;  
		 }  
		putPixel (x, y);   
		while (y < y1)  
		{  
			  if (d < 0)  
				 d += ds;  
			 else {  
				   if (x > x1)
				   {  
						x--;  
						d += dt;  
					} else 
					{  
						x++;  
						d += dt;  
					}                
				}  
			y++;  
			 putPixel (x, y);
			 
	   }        
	}  
}  

void drawObject(float points[][NoOfVertices])
{
	for(int i=1;i<NoOfVertices;i++)
	{
		bresenhamLine((int) points[0][i-1],(int) points[1][i-1],(int) points[0][i],(int) points[1][i]);
		
	}
	bresenhamLine((int)points[0][0],(int)points[1][0],(int)points[0][NoOfVertices-1],(int)points[1][NoOfVertices-1]);
	glFlush();
	

}
void printArray(int rows, int cols, float arr[][3]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
void printArray2(int rows, int cols, float arr[][4]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void activity()
{
	float degree = 60; 
	float teta  = degree * M_PI / 180;
	float dx=coordinates[0][0];
	float dy=coordinates[1][0];
	float tmatrix [3] [3]; //step 1 matrix
	
	float rmatrix [3] [3]; // //step 2 matrix
	float tmatrix2 [3] [3]; // //step 3 matrix
	setTranslationMatrix(-dx, -dy, tmatrix);
	setRotationMatrx(teta, rmatrix);
	
	setTranslationMatrix(dx, dy, tmatrix2);
	std::cout << " Coordinate matrix" << std::endl;
	printArray2(3,4,coordinates);
	std::cout << " translation matrix" << std::endl;
	printArray(3,3,tmatrix);
	//Start multiplication 
	float temp [3][NoOfVertices]; // to strore results of tmatrix*coordinates 
	multiply_arrays(tmatrix, coordinates, temp);

	float temp2 [3][NoOfVertices]; // to strore results of rmatrix*temp 
	multiply_arrays(rmatrix, temp, temp2);
	float temp3 [3][NoOfVertices]; // to strore results of  rmatrix *temp2 
	multiply_arrays(tmatrix2, temp2, temp3); 
	glColor3f(1.0, 0.0, 0.9);
	drawObject(temp3);
	std::cout << " Results matrix" << std::endl;
	printArray2(3,4,temp3);
	




}
  

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = (float)x;
			yi = (float)(wh - y);
		}
		else if (state == GLUT_UP) {
			xf = (float)x;
			yf = (float)(wh - y);
			//glutPostRedisplay();
			setCoordinates(xi, yi, xf, yf);
			drawObject(coordinates);
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		activity();
	}
}
void myinit()  
{        
     glViewport(0,0,ww,wh);  
     glMatrixMode(GL_PROJECTION);  
     glLoadIdentity();  
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
     glMatrixMode(GL_MODELVIEW);  
}  
int main(int argc, char** argv)  
{  
     glutInit(&argc,argv);  
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
     glutInitWindowSize(ww,wh);  
     glutCreateWindow("Bresenham Line Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  