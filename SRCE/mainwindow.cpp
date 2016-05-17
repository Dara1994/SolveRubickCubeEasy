#include "mainwindow.h"
#include <GL/gl.h>
#include <GL/glu.h>

float R=0.2,S=0.16;
float dist=7;
#define ORTHOFRUSTRUM glFrustum (-.3, .3, -.3, .3, 4, 10);

//float DT=500.;
//int way=1;

class MoveBuffer {
    char *movBuffer;
    int movBufferLen;
    int movBufferMem;

public:
    MoveBuffer() {movBuffer=0; movBufferLen=0; movBufferMem=0;}
    ~MoveBuffer() {free(movBuffer);}

    void pushBuffer(char mov);
    char popBuffer();
};

MoveBuffer Buffer;

void MoveBuffer::pushBuffer(char mov)
{
    if (movBufferLen>0 &&
        movBuffer[movBufferLen-1]==-mov) {
            movBufferLen--;
            return;
    }
    if (movBufferLen>1 &&
        movBuffer[movBufferLen-1]==mov &&
        movBuffer[movBufferLen-2]==mov) {
            movBuffer[movBufferLen-2]=-mov;
            movBufferLen--;
            return;
    }


    if (movBufferLen==movBufferMem) {
        movBufferMem+=10;
        movBuffer=(char *)realloc(movBuffer,movBufferMem*sizeof(char));
    }
    movBuffer[movBufferLen]=mov;
    movBufferLen++;
}

char MoveBuffer::popBuffer()
{
    if (movBufferLen>0) {
        movBufferLen--;
        return movBuffer[movBufferLen];
    }
    return 0;
}


float col[][3]={{0.1,0.1,0.1},{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1}};

int map[6][3][3]=
{{{1,1,1},{1,1,1},{1,1,1}},
    {{2,2,2},{2,2,2},{2,2,2}},
    {{3,3,3},{3,3,3},{3,3,3}},
    {{4,4,4},{4,4,4},{4,4,4}},
    {{5,5,5},{5,5,5},{5,5,5}},
    {{6,6,6},{6,6,6},{6,6,6}}};



class Cube
 {
 public:
     float coords[8][3];
     float norm[6][3];
     int colors[6];
     Cube(float x0,float y0,float z0,float b,int r1,int r2,int r3,int r4,int r5,int r6);
     void move(float dx,float dy,float dz);
     void drawCube();
     void drawWireCube();
 };

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

    glEnd();
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

Cube *A[27]={0};


void resetCube()
{
    int k;
    for (k=0; k<27; k++) {
         delete A[k];
    }
    int k1,k2,k3;
     k=0;
     int c1,c2,c3,c4,c5,c6;


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




 GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(parent)
{
     resetCube();
}

 GLWidget::~GLWidget()
 {
     int k;
     for (k=0; k<27; k++) {
         delete A[k];
     }
  }

 QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }



 void GLWidget::initializeGL()
 {
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_shininess[] = {30.0};
//izmenjeno {0, 0, 1, 0}
GLfloat light_position[] = { 1, 0, 0, 1 };
    glClearColor(1,1,1,0);
     glShadeModel(GL_FLAT);
     glEnable(GL_DEPTH_TEST);
     glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

     glColorMaterial(GL_FRONT, GL_DIFFUSE);
     glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glTranslated(0.0, 0.0, -dist);
     glEnable(GL_CULL_FACE);
 }

void GLWidget::paintGL()
{

    float ww=3.14159/180.;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    makeObject();
}

 void GLWidget::resizeGL(int width, int height)
 {

     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     ORTHOFRUSTRUM;
     glMatrixMode(GL_MODELVIEW);
     lastPos = QCursor::pos ();
 }

int processHits (GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    float z1,z2;
    int hit;

    float minZ;
    int ret=0;
    GLuint ii, jj, names, *ptr;
    ptr = (GLuint *) buffer;
    for (i = 0; i < hits; i++) { /* za svai hit */
        names = *ptr;
        ptr++;
        z1=(float)*ptr/0x7fffffff;
        ptr++;
        z2=(float)*ptr/0x7fffffff;
        ptr++;
        for (j = 0; j < names; j++) { /* za svaki naziv */
            hit=*ptr;
            if (j == 0) /* postavi red i kolonu */
            ii = *ptr;
            else if (j == 1)
            jj = *ptr;
            ptr++;
        }
        if (i==0) {
            ret=hit;
            minZ=(z1<z2)?z1:z2;
        } else {
            if (z1<minZ || z2<minZ) {
                ret=hit;
                minZ=(z1<z2)?z1:z2;
            }
        }

    }
    return ret;
}

 GLuint GLWidget::makeObject()
 {


    int render_mode;
    glGetIntegerv(GL_RENDER_MODE,&render_mode);

    if (render_mode==GL_SELECT) {
        float a=R+S*.5;

        glLoadName( 1);
        glBegin(GL_QUADS);
        glVertex3f(-a,-a,-a);
        glVertex3f( a,-a,-a);
        glVertex3f( a,-a, a);
        glVertex3f(-a,-a, a);
        glEnd();

        glLoadName( 2);
        glBegin(GL_QUADS);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a,-a, a);
        glVertex3f(-a, a, a);
        glVertex3f(-a, a,-a);
        glEnd();

        glLoadName( 3);
        glBegin(GL_QUADS);
        glVertex3f(-a,-a, a);
        glVertex3f( a,-a, a);
        glVertex3f( a, a, a);
        glVertex3f(-a, a, a);
        glEnd();

        glLoadName( 4);
        glBegin(GL_QUADS);
        glVertex3f(-a,-a,-a);
        glVertex3f(-a, a,-a);
        glVertex3f( a, a,-a);
        glVertex3f( a,-a,-a);
        glEnd();

        glLoadName( 5);
        glBegin(GL_QUADS);
        glVertex3f( a,-a,-a);
        glVertex3f( a, a,-a);
        glVertex3f( a, a, a);
        glVertex3f( a,-a, a);
        glEnd();

        glLoadName( 6);
        glBegin(GL_QUADS);
        glVertex3f(-a, a,-a);
        glVertex3f(-a, a, a);
        glVertex3f( a, a, a);
        glVertex3f( a, a,-a);
        glEnd();

    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);


        int k;

        for (k=0; k<27; k++) {
            if (A[k]) A[k]->drawCube();
        }


        glDisable(GL_LIGHTING);

        glColor3f(0,0,0);
        for (k=0; k<27; k++) {
            if (A[k]) A[k]->drawWireCube();
        }

        glBegin(GL_LINES);
        glLineWidth(6);
        //iscrtavanje linija rotacije: vrtex-odakle polazi linija
        glColor3f(1,.2,.2);
        glVertex3f(0,0,0); glVertex3f(1,0,0);
        glColor3f(.2,1,.2);
        glVertex3f(0,0,0); glVertex3f(0,1,0);
        glColor3f(.2,.2,1);
        glVertex3f(0,0,0); glVertex3f(0,0,1);
        glEnd();
    }
     return 0;
}
