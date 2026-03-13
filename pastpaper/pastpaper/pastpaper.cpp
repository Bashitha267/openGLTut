#include <glut.h>  
#include <math.h>  
int ww = 600, wh = 400;    
int xi, yi, xf, yf;  

void putPixel (int x, int y)  
{  
   glColor3f (1.0, 0.0, 0.0);  
   glBegin (GL_POINTS);  
   glVertex2i (x, y); 
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void putPixelcircle (int x, int y)  
{  
	if((x>100 && x<300)&&(y<287 && y>113)){
	  glColor3f (0.0, 1.0, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
   glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  }
	}
	else {
	return;
	}
} 

 
void display()  
{  
   glClearColor(1.0,1.0, 1.0, 1.0);  
   glColor3f(1.0, 1.0, 1.0);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
}  

void plotCircle(int h, int k, int x, int y)
{
	putPixelcircle((x+h), (y+k)); //x,y
	putPixelcircle((y+h), (x+k));//y, x
	putPixelcircle((-y+h), (x+k));//-y, x
	putPixelcircle((-x+h), (y+k));//-x, y
	putPixelcircle((-x+h), (-y+k));//-x,-y
	putPixelcircle((-y+h), (-x+k));//-y,-x
	putPixelcircle((y+h), (-x+k));//y,-x
	putPixelcircle((x+h), (-y+k));//x,-y

}

void plotCir(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k)); //x,y
	putPixel((y+h), (x+k));//y, x
	putPixel((-y+h), (x+k));//-y, x
	putPixel((-x+h), (y+k));//-x, y
	putPixel((-x+h), (-y+k));//-x,-y
	putPixel((-y+h), (-x+k));//-y,-x
	putPixel((y+h), (-x+k));//y,-x
	putPixel((x+h), (-y+k));//x,-y

}
void bresenhamCircle(int h, int k, int r)
{
	int x=0, y=r, d= 3-2*r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
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
void bresenhamAlg (int x0, int y0, int x1, int y1)  
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
}  
  
void myloop(){
			
			bresenhamAlg (150,287, 250,287);
			bresenhamAlg (250,287, 300,200);
			bresenhamAlg (300,200, 250,113);
			bresenhamAlg (250,113, 150,113);
			bresenhamAlg (150,113, 100,200);
			bresenhamAlg (100,200, 150,287);



}
void mycir(){
	bresenhamCircle(200,200,100);
}

void mycircle(){
	bresenhamCircle(250,287,100);
	bresenhamCircle(300,200,100);
	bresenhamCircle(250,113,100);
	bresenhamCircle(150,113,100);
	bresenhamCircle(100,200,100);
	bresenhamCircle(150,287,100);


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
			mycir();
			mycircle();

			
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
     glutCreateWindow("Bresenham Line Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  