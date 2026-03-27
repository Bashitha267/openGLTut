#include <glut.h>  
#include <math.h>  
int ww = 800, wh = 800;    
int xi, yi, xf, yf;  
// Define the region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Define the clipping window
const float xmin = 100, xmax = 500, ymin = 100, ymax = 500;

void putPixel (int x, int y)  
{  
	glPointSize(2.0);
	int dx=x-300;
	int dy=y-300;
	int val=dx*dx+dy*dy;
	if(val<100*100){
		glColor3f (1.0, 0.0, 0.0);
	}
	else{
		glColor3f (0.0, 0.0, 1.0);
	}

  
   glBegin (GL_POINTS);  
   glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 
void putPixelCircle (int x, int y)  
{  	
   glPointSize(2.0);
   glColor3f (0.0, 1.0, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
	glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void plotCircle(int h, int k, int x, int y)
{
	putPixelCircle((x+h), (y+k)); //x,y
	putPixelCircle((y+h), (x+k));//y, x
	putPixelCircle((-y+h), (x+k));//-y, x
	putPixelCircle((-x+h), (y+k));//-x, y
	putPixelCircle((-x+h), (-y+k));//-x,-y
	putPixelCircle((-y+h), (-x+k));//-y,-x
	putPixelCircle((y+h), (-x+k));//y,-x
	putPixelCircle((x+h), (-y+k));//x,-y

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
// Function to compute the region code of a point
int computeOutCode(int x, int y) {
    int code = INSIDE;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}
// Function to clip a line using Cohen-Sutherland algorithm
void cohenSutherland(int x0, int y0, int x1, int y1) {
    int outcode0, outcode1, outcode;
    bool accept = false, done = false;

    outcode0 = computeOutCode(x0, y0);
    outcode1 = computeOutCode(x1, y1);

    do {
        if (!(outcode0 | outcode1)) { // Trivially accepted
            accept = true;
            done = true;
        } else if (outcode0 & outcode1) { // Trivially rejected
            done = true;
        } else {
            float x, y;
            outcode = outcode0 ? outcode0 : outcode1;

            if (outcode & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcode & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcode & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (outcode & LEFT) {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (outcode == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    } while (!done);

    if (accept) {
        glColor3f(1.0, 0.0, 0.0);
		bresenhamAlg ( x0,  y0,  x1,  y1);
    }
}

 
void display()  
{  

   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
}  
void liangBarsky(int x0, int y0, int x1, int y1) {
    float t0 = 0.0f, t1 = 1.0f;
    float dx = x1 - x0;
    float dy = y1 - y0;
    float p, q, r;

    // Loop through left, right, bottom, top edges
    for (int edge = 0; edge < 4; edge++) {
        if (edge == 0)      { p = -dx; q = x0 - xmin; } // Left
        else if (edge == 1) { p = dx;  q = xmax - x0; } // Right
        else if (edge == 2) { p = -dy; q = y0 - ymin; } // Bottom
        else                { p = dy;  q = ymax - y0; } // Top

        if (p == 0 && q < 0) return; // Line parallel and outside

        if (p < 0) {
            r = q / p;
            if (r > t1) return; // Outside
            else if (r > t0) t0 = r;
        } 
        else if (p > 0) {
            r = q / p;
            if (r < t0) return; // Outside
            else if (r < t1) t1 = r;
        }
    }

    // Compute clipped points
    float x_clipped0 = x0 + t0 * dx;
    float y_clipped0 = y0 + t0 * dy;
    float x_clipped1 = x0 + t1 * dx;
    float y_clipped1 = y0 + t1 * dy;

    // Draw the clipped line
    glColor3f(1.0, 0.0, 0.0); // red color
    bresenhamAlg((int)x_clipped0, (int)y_clipped0, (int)x_clipped1, (int)y_clipped1);
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
			glBegin(GL_LINE_LOOP);
			glPointSize(2.0);
			glVertex2f(500, 100);
			glVertex2f(500, 500);
			glVertex2f(100, 500);
			glVertex2f(100, 100);
			glEnd();
			
			liangBarsky( xi, yi, xf, yf);
			// Draw a circle at center (300,300) with radius 100
			bresenhamCircle(300, 300, 100);
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