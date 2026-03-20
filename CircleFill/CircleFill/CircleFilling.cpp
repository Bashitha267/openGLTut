#include <glut.h>
#include <math.h> 
//when we got the 8 pixels from 1 pixel draw 4 lines per each pixel 
int ww = 800, wh = 600;
int xi, yi, xf, yf; 

void putPixel (int x, int y)  
{  
   glColor3f (0.3, 0.2, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
	glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void plotCircle(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k));
	putPixel((y+h), (x+k));
	putPixel((-y+h), (x+k));
	putPixel((-x+h), (y+k));
	putPixel((-x+h), (-y+k));
	putPixel((-y+h), (-x+k));
	putPixel((y+h), (-x+k));
	putPixel((x+h), (-y+k));

}




void display()  
{  
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   glColor3f(1.0, 0.0, 0.0);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
} 

void drawHorizontalLine(int x0,int y0,int x1,int y1)
{	
	glPointSize(2.0);
	

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
       else {   
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
                   if (x < x1)
				   {  
						x++;  
						d += dt;  
					} else 
					{  
						x--;  
						d += dt;  
					}                
				}  
			y++;  
             putPixel (x, y);
			 
       }        
	}  
 
		
	glEnd();
	glFlush();
}

void horizontalLine(int h, int k, int x, int y)
{
	//drawHorizontalLine(-x+h,y+k,x+h,y+k);
	//drawHorizontalLine(-y+h,x+k,y+h,x+k);
	//drawHorizontalLine(-y+h,-x+k,y+h,-x+k);
	//drawHorizontalLine(-x+h,-y+k,x+h,-y+k);
	drawHorizontalLine(-x+h,y+k,x+h,-y+k);
	drawHorizontalLine(-y+h,x+k,y+h,-x+k);
	drawHorizontalLine(-y+h,-x+k,y+h,x+k);
	drawHorizontalLine(-x+h,-y+k,x+h,y+k);
}

void bresenhamCircle(int h, int k, int r)
{
	int x=0, y=r, d= 3-2*r;
	while(x <= y)
	{
		 plotCircle(h, k, x, y);
		horizontalLine(h, k, x, y);
		if(d<0)
		{
			d = d + 4*x + 6; 
		}
		else
		{
			d = d + 4*(x-y) + 10;
			y--;
		}
		x++;
	}
}

void mouse(int btn, int state, int x, int y)
{
	
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
			glutPostRedisplay();
			int r = (int) sqrt((double)(xi-xf)*(xi-xf)+(yi-yf)*(yi-yf));
			bresenhamCircle (xi, yi, r);
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
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
     glutCreateWindow("Bresenham Circle Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}