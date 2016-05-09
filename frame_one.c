#include<GLUT/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

float hexagon_r=20;
float hexagon_dx,hexagon_dy,hexagon_gx,hexagon_gy;
void draw_hexagon(float,float);
void drawCircle(float, float , float , int);

void drawCancerCells(float,float,int,int);


void initialize(){
  hexagon_dx=hexagon_r*cos(30.0*M_PI/180.0);
  hexagon_dy=hexagon_r*sin(30.0*M_PI/180.0);
  hexagon_gx=2.0*hexagon_dx;
  hexagon_gy=2.0*hexagon_dx*sin(60.0*M_PI/180.0);
  // printf("%d  %d  %d  %d\n",hexagon_dx,hexagon_dy,hexagon_gx,hexagon_gy );
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
  int i;
  int triangleAmount = 20; //# of triangles used to draw circle

  //GLfloat radius = 0.8f; //radius
  GLfloat twicePi = 2.0f * M_PI;

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y); // center of circle
  for(i = 0; i <= triangleAmount;i++) {
    glVertex2f(
      x + (radius * cos(i *  twicePi / triangleAmount)),
      y + (radius * sin(i * twicePi / triangleAmount))
    );
  }
  glEnd();
}
void draw_hexagon(float x,float y)
{
  glBegin(GL_LINE_LOOP);
  glVertex2f(x-hexagon_dx,y-hexagon_dy);
  glVertex2f(x-hexagon_dx,y+hexagon_dy);
  glVertex2f(x           ,y+hexagon_r );
  glVertex2f(x+hexagon_dx,y+hexagon_dy);
  glVertex2f(x+hexagon_dx,y-hexagon_dy);
  glVertex2f(x           ,y-hexagon_r );
  glEnd();
  //glFlush();
  drawCircle(x,y,4.0,20);
}
void drawCancerCell(float x,float y,float dx,float dy)
{
  int r =( rand() % 20)/10.0f;
  dx*=r;
  dy*=r;
  glColor3f(0.831f,0.608f,0.627f);
  glBegin(GL_POLYGON);
  glVertex2f(x-hexagon_dx-2*dx,y-hexagon_dy+dy);
  glVertex2f(x-hexagon_dx+dx,y+hexagon_dy+dy);
  glVertex2f(x     +dx      ,y+hexagon_r );
  glVertex2f(x+hexagon_dx-dx,y+hexagon_dy-dy);
  glVertex2f(x+hexagon_dx-dx,y-hexagon_dy+dx);
  glVertex2f(x           ,y-hexagon_r );
  glEnd();

  glColor3f(0.612f,0.220f,0.290f);
  glBegin(GL_LINE_LOOP);
  glVertex2f(x-hexagon_dx-2*dx,y-hexagon_dy+dy);
  glVertex2f(x-hexagon_dx+dx,y+hexagon_dy+dy);
  glVertex2f(x     +dx      ,y+hexagon_r );
  glVertex2f(x+hexagon_dx-dx,y+hexagon_dy-dy);
  glVertex2f(x+hexagon_dx-dx,y-hexagon_dy+dx);
  glVertex2f(x           ,y-hexagon_r );
  glEnd();
  glColor3f(0.596f,0.537f,0.494f);
  drawFilledCircle(x,y,4);
  glFlush();
}
/*
void Timer(int iUnused)
{
//glutPostRedisplay();
drawCancerCells(-100,-100,10,10);
glutTimerFunc(90, Timer, 0);

}*/
void draw_hexagon_grid(float x,float y,int ni,int nj)
{
  int i,j; float x0,shiftP=2.0;
  x-=((float)(ni-1))*hexagon_gx*0.5; // just shift x,y to start position (i=0,j=0)
  x-=((float)(nj-1))*hexagon_dx*0.5;
  y-=((float)(nj-1))*hexagon_gy*0.5;
  //x1=x+15*hexagon_gx*0.5,y1=y+9*hexagon_gx*0.5;
  for (x0=x,j=0;j<nj;j++,x0+=hexagon_dx+shiftP,x=x0+shiftP,y+=hexagon_gy+shiftP)
  for (i=0;i<ni;i++,x+=hexagon_gx+shiftP){
    draw_hexagon(x,y);
  }

  /*  x-=((float)(ni-1))*hexagon_gx*0.5; // just shift x,y to start position (i=0,j=0)
  x-=((float)(nj-1))*hexagon_dx*0.5;
  y-=((float)(nj-1))*hexagon_gy*0.5;*/

}


void drawCancerCells(float x,float y,int ni,int nj){
  int i,j; float x0,shiftP=2.0;
  float x1,y1;
  x-=((float)(ni-1))*hexagon_gx*0.5; // just shift x,y to start position (i=0,j=0)
  x-=((float)(nj-1))*hexagon_dx*0.5;
  y-=((float)(nj-1))*hexagon_gy*0.5;
  x1=x+15*hexagon_gx*0.5,y1=y+9*hexagon_gx*0.5;
  glColor3f(1.0,1.0,0.0);

  shiftP+=2;
  /* cancer cells are drawn here
  add amination here*/
  for (x0=x1,j=5; j<nj-2; j++){
    for (i=5; i<ni-2; i++){
      float dx[]= {2,3,1,2,3,4,5,6};
      float  dy[]={7,4,5,3,2,5,7,8,3,2,3};

      drawCancerCell(x1,y1,dx[j-5],dy[j-5]);
      x1+=hexagon_gx+shiftP-.3*i;
    }
    x0+=hexagon_dx+shiftP +.5*i;
    x1=x0+shiftP;
    y1+=hexagon_gy+shiftP;
  }
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.5, 0.0, 0.0);


  draw_hexagon_grid(-100,-100,10,10);
  //  Timer(60);
  //  drawCancerCells(-100,-100,10,10);
  glFlush();
  glutSwapBuffers();
}

void drawCircle(float cx, float cy, float r, int num_segments)
{
  glBegin(GL_LINE_LOOP);
  for(int ii = 0; ii < num_segments; ii++)
  {
    float theta = 2.0f * 3.1415926f * (float)ii / (float)(num_segments);//get the current angle

    float x = r * cosf(theta);//calculate the x component
    float y = r * sinf(theta);//calculate the y component

    glVertex2f(x + cx, y + cy);//output vertex

  }
  glEnd();
}
int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  initialize();


  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowSize(1000,1000);
  //  glutInitWindowPosition(0,0);
  glutCreateWindow("Polygon");
  //glutTimerFunc(10, Timer, 0);
  glutDisplayFunc(display);
  glClearColor(1.0,1.0,1.0,1.0);
  gluOrtho2D(-500,500.0,-500,500.0);
  glutMainLoop();

  return 1;
}
