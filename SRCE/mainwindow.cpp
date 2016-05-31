/*! \file mainwindow.cpp
 * \brief ??? ??? ???
 * ??? ??? ???
 */

#include "mainwindow.h"
#include "pokreti.h"
#include <math.h>
#include "cube.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTime>


extern float R=0.2,S=0.16;
extern Cube *A[27]={0};
extern float col[][3]={{0.1,0.1,0.1},{0.8,0,0},{0,0.8,0},{0,0,0.8},{0.8,0.8,0},{0.8,0,0.8},{0,0.8,0.8}};
float dist=7;
#define ORTHOFRUSTRUM glFrustum (-.3, .3, -.3, .3, 4, 10);

float DT=500.;
int way=1;


extern int map[6][3][3]=
{{{1,1,1},{1,1,1},{1,1,1}},
    {{2,2,2},{2,2,2},{2,2,2}},
    {{3,3,3},{3,3,3},{3,3,3}},
    {{4,4,4},{4,4,4},{4,4,4}},
    {{5,5,5},{5,5,5},{5,5,5}},
    {{6,6,6},{6,6,6},{6,6,6}}};
/*! \brief Pomocna klasa MoveBuffer
 * Klasa kojom manipulisemo bufferom poteza.
 */
class MoveBuffer {
    char *movBuffer; /*!< */
    int movBufferLen; /*!< */
    int movBufferMem; /*!< */

public:
    /*! \brief Konstruktor za MoveBuffer
     * @param[in] movBuffer ??? ??? ???
     * @param[in] movBufferLen ??? ??? ???
     * @param[in] movBufferMem ??? ??? ???
     */
    MoveBuffer() {movBuffer=0; movBufferLen=0; movBufferMem=0;}

    /*! Destruktor */
    ~MoveBuffer() {free(movBuffer);}
    /*! \brief Push
     * @param[in] mov Vrednost koju postavljamo na vrh buffer.
     *
     *  Pushujemo na vrh buffera slovo koje odgovara dugmetu koje smo pritisli.
     */
    void pushBuffer(char mov);
    /*! \brief Pop.
     * \return slovo sa vrha buffera.
     */
    char popBuffer();
};

MoveBuffer Buffer; /*!< Napravili smo jedan buffer */

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

MoveWidget PokreniUSmer;

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F){
        PokreniUSmer.rotLD (way,map,DT,A);
        Buffer.pushBuffer('F');
    }
    if(event->key() == Qt::Key_D){
        PokreniUSmer.rotLU(way,map,DT,A);
        Buffer.pushBuffer('D');
    }
    if(event->key() == Qt::Key_J){
         PokreniUSmer.rotRD(way,map,DT,A);
        Buffer.pushBuffer('J');
    }
    if(event->key() == Qt::Key_K){
         PokreniUSmer.rotRU(way,map,DT,A);
        Buffer.pushBuffer('K');
    }
    if(event->key() == Qt::Key_H){
         PokreniUSmer.rotFR(way,map,DT,A);
        Buffer.pushBuffer('H');
    }
    if(event->key() == Qt::Key_R){
         PokreniUSmer.rotTL(way,map,DT,A);
        Buffer.pushBuffer('R');
    }
    if(event->key() == Qt::Key_I){
         PokreniUSmer.rotTR(way,map,DT,A);
        Buffer.pushBuffer('I');
    }
    if(event->key() == Qt::Key_G){
         PokreniUSmer.rotFL(way,map,DT,A);
        Buffer.pushBuffer('G');
    }
    if(event->key() == Qt::Key_C){
          PokreniUSmer.rotDL(way,map,DT,A);
         Buffer.pushBuffer('C');
    }
    if(event->key() == Qt::Key_M){
         PokreniUSmer.rotDR(way,map,DT,A);
        Buffer.pushBuffer('M');
    }
    if(event->key() == Qt::Key_Q){
        RandomCube();
        Buffer.pushBuffer('Q');
    }


    if(event->key() == Qt::Key_W){
        DT=100;
        int k;
        for (;;) {
             k=Buffer.popBuffer();
             if (k>0) way=0; else way=1;
             if (k<0) k=-k;
             switch (k) {
                case 'R':  PokreniUSmer.rotTL(way,map,DT,A); break;
                case 'D':  PokreniUSmer.rotLU(way,map,DT,A); break;
                case 'C':  PokreniUSmer.rotDL(way,map,DT,A); break;
                case 'F':  PokreniUSmer.rotLD(way,map,DT,A); break;
                case 'G':  PokreniUSmer.rotFL(way,map,DT,A); break;
                case 'H':  PokreniUSmer.rotFR(way,map,DT,A); break;
                case 'I':  PokreniUSmer.rotTR(way,map,DT,A); break;
                case 'J':  PokreniUSmer.rotRD(way,map,DT,A); break;
                case 'K':  PokreniUSmer.rotRU(way,map,DT,A); break;
                case 'M':  PokreniUSmer.rotDR(way,map,DT,A); break;

             }
             if (k==0) break;
        }
        DT=500;
        way=1;
   }
}

void GLWidget::RandomCube()
{
int number = 10; /*!< Broj ukupnih pokreta.*/
int n=15; /*!< Broj nasumicnih poteza*/
int valueR; /*!< nasumicna vrednost u opsegu [0-9] */
for(int i=0; i<n;i++){
    valueR= qrand()%number;
    switch(valueR){
    case 0:
         PokreniUSmer.rotLD (way,map,DT,A);
         Buffer.pushBuffer('F');
        break;
    case 1:
         PokreniUSmer.rotLU (way,map,DT,A);
         Buffer.pushBuffer('D');
        break;
    case 2:
        PokreniUSmer. rotRD(way,map,DT,A);
         Buffer.pushBuffer('J');
        break;
    case 3:
        PokreniUSmer.rotRU(way,map,DT,A);
         Buffer.pushBuffer('K');
        break;
    case 4:
         PokreniUSmer.rotFR(way,map,DT,A);
         Buffer.pushBuffer('H');
        break;
    case 5:
         PokreniUSmer.rotFL(way,map,DT,A);
        Buffer.pushBuffer('G');
        break;
    case 6:
        PokreniUSmer.rotTL(way,map,DT,A);
         Buffer.pushBuffer('R');
        break;
    case 7:
         PokreniUSmer.rotTR(way,map,DT,A);
         Buffer.pushBuffer('I');
        break;
    case 9:
         PokreniUSmer.rotDL(way,map,DT,A);
         Buffer.pushBuffer('C');
        break;
    case 8:
        PokreniUSmer.rotDR(way,map,DT,A);
         Buffer.pushBuffer('M');
        break;
    }
}
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
    int i, j;
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
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if (event->buttons() & Qt::RightButton) {

        GLint viewport[4];
        int x=lastPos.x();
        int y=lastPos.y();

        glGetIntegerv(GL_VIEWPORT,viewport);
        unsigned int buffer[1000];



        glSelectBuffer(1000,buffer);
        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(100);

        glMatrixMode (GL_PROJECTION);
        glPushMatrix();

        glLoadIdentity();

        gluPickMatrix(x,viewport[3]+2*viewport[1]-y,3,3,viewport);
        ORTHOFRUSTRUM;

        updateGL();

        glMatrixMode (GL_PROJECTION);
        glPopMatrix();

    }
}

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {


         GLfloat pmat[16];

         glMatrixMode (GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX,pmat);
    glLoadIdentity();

    glRotatef(dy,1, 0,0);
    glRotatef(dx, 0,1,0);
    glMultMatrixf(pmat);
    glGetFloatv(GL_MODELVIEW_MATRIX,pmat);
    pmat[12]=0; pmat[13]=0; pmat[14]=-dist;
    glLoadMatrixf(pmat);


         updateGL();

     }
     lastPos = event->pos();
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
        glLineWidth(20);

        //iscrtavanje linija rotacije: vrtex-odakle polazi linija
        glColor3f(1,.5,.5);
        glVertex3f(0,0,0); glVertex3f(1,0,0);
        glColor3f(.5,1,.5);
        glVertex3f(0,0,0); glVertex3f(0,1,0);
        glColor3f(.5,.5,1);
        glVertex3f(0,0,0); glVertex3f(0,0,1);
        glEnd();
    }
     return 0;
}
