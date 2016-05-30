#include "mainwindow.h"
#include "pokreti.h"
#include "cube.h"

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTime>


void Cube::rotX(int angle)
{
    float f=angle*3.14159/180.;
    float cosf=cos(f),sinf=sin(f);
    float b,c;
    int k;
    for (k=0; k<8; k++) {
        b=cosf*coords[k][1]-sinf*coords[k][2];
        c=sinf*coords[k][1]+cosf*coords[k][2];
        coords[k][1]=b; coords[k][2]=c;
    }
    for (k=0; k<6; k++) {
        b=cosf*norm[k][1]-sinf*norm[k][2];
        c=sinf*norm[k][1]+cosf*norm[k][2];
        norm[k][1]=b; norm[k][2]=c;
    }
}
void Cube::rotY(int angle)
{
    float f=angle*3.14159/180.;
    float cosf=cos(f),sinf=sin(f);
    float b,c;
    int k;
    for (k=0; k<8; k++) {
        b=cosf*coords[k][2]-sinf*coords[k][0];
        c=sinf*coords[k][2]+cosf*coords[k][0];
        coords[k][2]=b; coords[k][0]=c;
    }
    for (k=0; k<6; k++) {
        b=cosf*norm[k][2]-sinf*norm[k][0];
        c=sinf*norm[k][2]+cosf*norm[k][0];
        norm[k][2]=b; norm[k][0]=c;
    }
}
void Cube::rotZ(int angle)
{
    float f=angle*3.14159/180.;
    float cosf=cos(f),sinf=sin(f);
    float b,c;
    int k;
    for (k=0; k<8; k++) {
        b=cosf*coords[k][0]-sinf*coords[k][1];
        c=sinf*coords[k][0]+cosf*coords[k][1];
        coords[k][0]=b; coords[k][1]=c;
    }
    for (k=0; k<6; k++) {
        b=cosf*norm[k][0]-sinf*norm[k][1];
        c=sinf*norm[k][0]+cosf*norm[k][1];
        norm[k][0]=b; norm[k][1]=c;
    }
}
void Cube::drawWireCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,coords);


    static unsigned int P[]={0,1,3,2,0,4,5,7,6,4};

    glDrawElements(GL_LINE_STRIP,10,GL_UNSIGNED_INT,(void *)P);
    static unsigned int P1[]={1,5,2,6,3,7};
    glDrawElements(GL_LINES,6,GL_UNSIGNED_INT,(void *)P1);

}


void resetCube()
{
    int k;
    for (k=0; k<27; k++) {
         delete A[k];
    }
    k=0;
    A[ 0]=new Cube(-R,-R,-R,S,		map[0][0][0],map[1][0][2],           0,		map[3][0][0],           0,           0);
    A[ 1]=new Cube( 0,-R,-R,S,		map[0][0][1],           0,           0,		map[3][0][1],           0,           0);
    A[ 2]=new Cube( R,-R,-R,S,		map[0][0][2],           0,           0,		map[3][0][2],map[4][0][2],           0);
    A[ 3]=new Cube(-R, 0,-R,S,		           0,map[1][0][1],           0,		map[3][1][0],           0,           0);
    A[ 4]=new Cube( 0, 0,-R,S,		           0,           0,           0,		map[3][1][1],           0,           0);
    A[ 5]=new Cube( R, 0,-R,S,		           0,           0,           0,		map[3][1][2],map[4][0][1],           0);
    A[ 6]=new Cube(-R, R,-R,S,		           0,map[1][0][0],           0,		map[3][2][0],           0,map[5][0][0]);
    A[ 7]=new Cube( 0, R,-R,S,		           0,           0,           0,		map[3][2][1],           0,map[5][0][1]);
    A[ 8]=new Cube( R, R,-R,S,		           0,           0,           0,		map[3][2][2],map[4][0][0],map[5][0][2]);

    A[ 9]=new Cube(-R,-R, 0,S,		map[0][1][0],map[1][1][2],           0,		           0,           0,           0);
    A[10]=new Cube( 0,-R, 0,S,		map[0][1][1],           0,           0,		           0,           0,           0);
    A[11]=new Cube( R,-R, 0,S,		map[0][1][2],           0,           0,		           0,map[4][1][2],           0);
    A[12]=new Cube(-R, 0, 0,S,		           0,map[1][1][1],           0,		           0,           0,           0);
    A[13]=new Cube( 0, 0, 0,S,		           0,           0,           0,		           0,           0,           0);
    A[14]=new Cube( R, 0, 0,S,		           0,           0,           0,		           0,map[4][1][1],           0);
    A[15]=new Cube(-R, R, 0,S,		           0,map[1][1][0],           0,		           0,           0,map[5][1][0]);
    A[16]=new Cube( 0, R, 0,S,		           0,           0,           0,		           0,           0,map[5][1][1]);
    A[17]=new Cube( R, R, 0,S,		           0,           0,           0,		           0,map[4][1][0],map[5][1][2]);

    A[18]=new Cube(-R,-R, R,S,		map[0][2][0],map[1][2][2],map[2][0][0],		           0,           0,           0);
    A[19]=new Cube( 0,-R, R,S,		map[0][2][1],           0,map[2][0][1],		           0,           0,           0);
    A[20]=new Cube( R,-R, R,S,		map[0][2][2],           0,map[2][0][2], 	           0,map[4][2][2],           0);
    A[21]=new Cube(-R, 0, R,S,		           0,map[1][2][1],map[2][1][0],		           0,           0,           0);
    A[22]=new Cube( 0, 0, R,S,		           0,           0,map[2][1][1],		           0,           0,           0);
    A[23]=new Cube( R, 0, R,S,		           0,           0,map[2][1][2],		           0,map[4][2][1],           0);
    A[24]=new Cube(-R, R, R,S,		           0,map[1][2][0],map[2][2][0],		           0,           0,map[5][2][0]);
    A[25]=new Cube( 0, R, R,S,		           0,           0,map[2][2][1],		           0,           0,map[5][2][1]);
    A[26]=new Cube( R, R, R,S,		           0,           0,map[2][2][2],		           0,map[4][2][0],map[5][2][2]);

}

Cube::Cube(float x0,float y0,float z0,float a,int r1,int r2,int r3,int r4,int r5,int r6)
{
    colors[0]=r1; colors[1]=r2; colors[2]=r3;
    colors[3]=r4; colors[4]=r5; colors[5]=r6;
    coords[0][0]=x0-a*.5; coords[0][1]=y0-a*.5; coords[0][2]=z0-a*.5;
    coords[1][0]=x0+a*.5; coords[1][1]=y0-a*.5; coords[1][2]=z0-a*.5;
    coords[2][0]=x0-a*.5; coords[2][1]=y0+a*.5; coords[2][2]=z0-a*.5;
    coords[3][0]=x0+a*.5; coords[3][1]=y0+a*.5; coords[3][2]=z0-a*.5;
    coords[4][0]=x0-a*.5; coords[4][1]=y0-a*.5; coords[4][2]=z0+a*.5;
    coords[5][0]=x0+a*.5; coords[5][1]=y0-a*.5; coords[5][2]=z0+a*.5;
    coords[6][0]=x0-a*.5; coords[6][1]=y0+a*.5; coords[6][2]=z0+a*.5;
    coords[7][0]=x0+a*.5; coords[7][1]=y0+a*.5; coords[7][2]=z0+a*.5;

    norm[0][0]= 0; norm[0][1]=-1; norm[0][2]= 0;
    norm[1][0]=-1; norm[1][1]= 0; norm[1][2]= 0;
    norm[2][0]= 0; norm[2][1]= 0; norm[2][2]= 1;
    norm[3][0]= 0; norm[3][1]= 0; norm[3][2]=-1;
    norm[4][0]= 1; norm[4][1]= 0; norm[4][2]= 0;
    norm[5][0]= 0; norm[5][1]= 1; norm[5][2]= 0;
}

void Cube::drawCube()
{
    glBegin(GL_QUADS);
       glColor3fv(col[colors[0]]);
       glNormal3fv(norm[0]);
       glVertex3fv(coords[0]);
       glVertex3fv(coords[1]);
       glVertex3fv(coords[5]);
       glVertex3fv(coords[4]);

       glColor3fv(col[colors[1]]);
       glNormal3fv(norm[1]);
       glVertex3fv(coords[0]);
       glVertex3fv(coords[4]);
       glVertex3fv(coords[6]);
       glVertex3fv(coords[2]);

       glColor3fv(col[colors[2]]);
       glNormal3fv(norm[2]);
       glVertex3fv(coords[4]);
       glVertex3fv(coords[5]);
       glVertex3fv(coords[7]);
       glVertex3fv(coords[6]);

       glColor3fv(col[colors[3]]);
       glNormal3fv(norm[3]);
       glVertex3fv(coords[0]);
       glVertex3fv(coords[2]);
       glVertex3fv(coords[3]);
       glVertex3fv(coords[1]);

       glColor3fv(col[colors[4]]);
       glNormal3fv(norm[4]);
       glVertex3fv(coords[1]);
       glVertex3fv(coords[3]);
       glVertex3fv(coords[7]);
       glVertex3fv(coords[5]);

       glColor3fv(col[colors[5]]);
       glNormal3fv(norm[5]);
       glVertex3fv(coords[2]);
       glVertex3fv(coords[6]);
       glVertex3fv(coords[7]);
       glVertex3fv(coords[3]);
    glEnd();
}

void Cube::move(float dx,float dy,float dz)
{
    int k;
    for (k=0; k<8; k++) {
        coords[k][0]+=dx;
        coords[k][1]+=dy;
        coords[k][2]+=dz;
    }
}
