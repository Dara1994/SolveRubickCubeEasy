/*! \file mainwindow.cpp
 * \brief Implementacija
 * Implementacija metoda, pomocna klasa MoveBuffer.
 */
#include "mainwindow.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTime>

/*! @param R je float sa vrednoscu 0.2
 * koja se koristi za postavljanje koordinatnog pocetke za kockice
 */
float R=0.2;
/*! @param S je float sa vrednoscu 0.16
 * koja se koristi za ??? ??? ??? */
float S=0.16;
/*! @param dist je int sa vrednoscu 7
 *  koja se kosti za ??? ??? ???*/
float dist=7;
/*!  ORTHOFRUSTRUM
 *  koja sluzi za ??? ??? ??? */
#define ORTHOFRUSTRUM glFrustum (-.3, .3, -.3, .3, 4, 10);
/*! float DT je tipa float vrednosti 500
 * koju koristimo u kalsama za iscrtavanje. ??? ??? ???*/
float DT=500.;
/*! way je int
 * koja defenise u kom smeru cemo da pomeramo rotacije. */
int way=1;

/*! @class MoveBuffer
 * \brief Pomocna klasa MoveBuffer
 * Pomocna klasa kojom manipulisemo bufferom poteza.
 */
class MoveBuffer {
     /*! pokazivac na top vrednost */
    char *movBuffer;
     /*! duzina buffera*/
    int movBufferLen;
  /*!< memorija*/
       int movBufferMem;

public:
    /*! \brief Konstruktor za MoveBuffer
     * @param[in] movBuffer pokazivac na vrh buffera
     * @param[in] movBufferLen duzina buffera
     * @param[in] movBufferMem memorija
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

/*! Buffer
 * Napravili smo jedan buffer u kome cemo cuvati nase interakcije sa tastaturom
 */
MoveBuffer Buffer;

/*! Realizacija metode pushBuffer
 *  * Stavljamo mov na vrh buffer posto izvsimo provere.
 * ??? ??? ??? opisati sta svaki if radi sta tacno proveravamo ??? ??? ???
 */
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

/*! Realizacije metode popBuffer
 * @param[out] karakter na vrhu buffera
 * ukoliko duzina buffera nije nula smanjimo tu duzino i vratimo char sa vrha.
 * ukoliko nam je duzina buffera nula, odnosno Buffer je prazan, vracamo nulu.
 */
char MoveBuffer::popBuffer()
{
    if (movBufferLen>0) {
        movBufferLen--;
        return movBuffer[movBufferLen];
    }
    return 0;
}

/*! Inicializacija promenljive vezane za boje rubikove kocke
 * @param col je dvo dimezioni niz koji cuva informacije o nasim bojama RGB
 */
float col[][3]={{0.1,0.1,0.1},{0.8,0,0},{0,0.8,0},{0,0,0.8},{0.8,0.8,0},{0.8,0,0.8},{0,0.8,0.8}};
/*! Mapa
 *  @param map je trodimezioni niz koji mapira sve kvadrata na svim stranama rubikove kocke.*/
int map[6][3][3]=
{{{1,1,1},{1,1,1},{1,1,1}},
    {{2,2,2},{2,2,2},{2,2,2}},
    {{3,3,3},{3,3,3},{3,3,3}},
    {{4,4,4},{4,4,4},{4,4,4}},
    {{5,5,5},{5,5,5},{5,5,5}},
    {{6,6,6},{6,6,6},{6,6,6}}};

/*! \class Klasa Cube
 * \brief Klasa kojom definisemo ponasanje cube
 * Ovde imamo sve metode vezane za manipulaciju nase rubikove kocke.
 * Definisanje kocke, iscrtavanja i rotacija oko xyz osa.
 */
class Cube
 {
 public:
    /*! Koordinate u prostoru
     *Iscrtavamo relevatne tacke za nasu kocku to su uglovi rubikove kocke u prostoru.
     */
     float coords[8][3];
     /*! ??? ??? ??? */
     float norm[6][3];
     /*! Boje*/
     int colors[6];
     /*! Konstruktor
      * @param[in] x0, y0, z0 su koordinate koordinatnog pocetka
      * @param[in] b je ??? ??? ???
      * @param[in] r1, r2 ,r3 ,r4, r5 ,r6 su relevatne boje.
      */
     Cube(float x0,float y0,float z0,float b,int r1,int r2,int r3,int r4,int r5,int r6);
     /*! Pomeri rubikovu kocku
      * @param dx, dy, dz su vrednosti za koje pomeramo u odnosu na xyz ose.
      */
     void move(float dx,float dy,float dz);
     /*! Iscrtavanje kocke*/
     void drawCube();
     /*! Isrtavanje mreze rubikove kocke*/
     void drawWireCube();
     /*! Rotacija oko x ose
      * @param[in] zadati ugao
      */
     void rotX(int angle);
     /*! Rotacija oko y ose
      * @param[in] zadati ugao
      */
     void rotY(int angle);
     /*! Rotacija oko z ose
      * @param[in] zadati ugao
      */
     void rotZ(int angle);
 };
/*! Realizacija
 * postavimo zadate vrednosti boja.
 * Izracunamo koordinate za svaku od 8 relevatnih tacaka
 * I postavimo norm
 */
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
/*! Realizacija
 * Crta rubikovu kocku.
 * ??? ??? ??? Sta se koristi i mozda opis kako koristi odredene ugradene funkcije? ??? ??? ???
 */
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
/*! Realizacija
 * Uvelicamo sve koordinate za odgovarajuce unete parametre.
 */
void Cube::move(float dx,float dy,float dz)
{
    int k;
    for (k=0; k<8; k++) {
        coords[k][0]+=dx;
        coords[k][1]+=dy;
        coords[k][2]+=dz;
    }
}

/*! Realizacija
 * Na svaki pritisnut taster izvsavamo relevatnu rotaciju. Predefinisani okret.
 * Dok vrednost tastera stavljamo u buffer.
 */
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F){
        rotLD();
        Buffer.pushBuffer('F');
    }
    if(event->key() == Qt::Key_D){
        rotLU();
        Buffer.pushBuffer('D');
    }
    if(event->key() == Qt::Key_J){
        rotRD();
        Buffer.pushBuffer('J');
    }
    if(event->key() == Qt::Key_K){
        rotRU();
        Buffer.pushBuffer('K');
    }
    if(event->key() == Qt::Key_H){
        rotFR();
        Buffer.pushBuffer('H');
    }
    if(event->key() == Qt::Key_R){
        rotTL();
        Buffer.pushBuffer('R');
    }
    if(event->key() == Qt::Key_I){
        rotTR();
        Buffer.pushBuffer('I');
    }
    if(event->key() == Qt::Key_G){
        rotFL();
        Buffer.pushBuffer('G');
    }
    if(event->key() == Qt::Key_C){
         rotDL();
         Buffer.pushBuffer('C');
    }
    if(event->key() == Qt::Key_M){
        rotDR();
        Buffer.pushBuffer('M');
    }

}

/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u odgovarajuci
 *  coords reda k prve koordinate i norm.
 */
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
/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u odgovarajuci
 *  coords reda k druge koordinate i norm.
 */
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
/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u odgovarajuci
 *  coords reda k trece koordinate i norm.
 */
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
/*! Realizacija
 * @param P je niz koji koristimo za ??? ??? ???
 * @param P1 je niz koji koristimo za ??? ??? ???
 * ??? ??? ??? Kako iscrtava sta koristimo ??? ??? ???
 */
void Cube::drawWireCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,coords);


    static unsigned int P[]={0,1,3,2,0,4,5,7,6,4};

    glDrawElements(GL_LINE_STRIP,10,GL_UNSIGNED_INT,(void *)P);
    static unsigned int P1[]={1,5,2,6,3,7};
    glDrawElements(GL_LINES,6,GL_UNSIGNED_INT,(void *)P1);

}

/*! A
 * Napravili smo niz pokazivaca na nase kockice koje cine rubikovu kocku
 */
Cube *A[27]={0};

/*! Realizacija
 * @param k brojac koji broji kockice.
 *
 * Prvo obrisemo svaki elemenat iz niza A. Potom za svaku od tih 27 kockica koje cine rubikovu kocku
 * koristimo konstruktor Cube sa odgovarajucim elementima. R za koordinatni pocetak za svaku kockicu,
 * S za ??? ??? ???, i odgovarajuce map za strane koje su vidljive a 0 za one koje nevidimo.
 */
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
/*! Definisemo pomeranje jedne strane ??? ??? ???nalevo/nadesno??? ??? ???*/
#define SHIFT_FACE(a_)\
tmp[0]=map[a_][2][2]; tmp[1]=map[a_][1][2];\
tmp[2]=map[a_][0][2]; tmp[3]=map[a_][0][1];\
tmp[4]=map[a_][0][0]; tmp[5]=map[a_][1][0];\
tmp[6]=map[a_][2][0]; tmp[7]=map[a_][2][1];\
map[a_][2][2]=tmp[6]; map[a_][1][2]=tmp[7];\
map[a_][0][2]=tmp[0]; map[a_][0][1]=tmp[1];\
map[a_][0][0]=tmp[2]; map[a_][1][0]=tmp[3];\
map[a_][2][0]=tmp[4]; map[a_][2][1]=tmp[5];

/*! Definisemo pomeranje jedne strane ??? ??? ???nalevo/nadesno??? ??? ???*/
#define DESHIFT_FACE(a_)\
tmp[6]=map[a_][2][2]; tmp[7]=map[a_][1][2];\
tmp[0]=map[a_][0][2]; tmp[1]=map[a_][0][1];\
tmp[2]=map[a_][0][0]; tmp[3]=map[a_][1][0];\
tmp[4]=map[a_][2][0]; tmp[5]=map[a_][2][1];\
map[a_][2][2]=tmp[0]; map[a_][1][2]=tmp[1];\
map[a_][0][2]=tmp[2]; map[a_][0][1]=tmp[3];\
map[a_][0][0]=tmp[4]; map[a_][1][0]=tmp[5];\
map[a_][2][0]=tmp[6]; map[a_][2][1]=tmp[7];

/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko X ose.
 */
void  GLWidget::rotLD()
{
    int tmp[8];
    if (way==1) {
        SHIFT_FACE(1);
        tmp[0]=map[5][2][0]; tmp[1]=map[5][1][0]; tmp[2]=map[5][0][0];
        map[5][2][0]=map[3][2][0]; map[5][1][0]=map[3][1][0]; map[5][0][0]=map[3][0][0];
        map[3][2][0]=map[0][0][0]; map[3][1][0]=map[0][1][0]; map[3][0][0]=map[0][2][0];
        map[0][0][0]=map[2][0][0]; map[0][1][0]=map[2][1][0]; map[0][2][0]=map[2][2][0];
        map[2][0][0]=tmp[0]; map[2][1][0]=tmp[1]; map[2][2][0]=tmp[2];
    } else {
        DESHIFT_FACE(1);
        tmp[0]=map[2][0][0]; tmp[1]=map[2][1][0]; tmp[2]=map[2][2][0];
        map[2][0][0]=map[0][0][0]; map[2][1][0]=map[0][1][0]; map[2][2][0]=map[0][2][0];
        map[0][0][0]=map[3][2][0]; map[0][1][0]=map[3][1][0]; map[0][2][0]=map[3][0][0];
        map[3][2][0]=map[5][2][0]; map[3][1][0]=map[5][1][0]; map[3][0][0]=map[5][0][0];
        map[5][2][0]=tmp[0]; map[5][1][0]=tmp[1]; map[5][0][0]=tmp[2];
    }


    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[0]->rotX(r); A[3]->rotX(r); A[6]->rotX(r);
        A[9]->rotX(r); A[12]->rotX(r); A[15]->rotX(r);
        A[18]->rotX(r); A[21]->rotX(r); A[24]->rotX(r);

    }

    updateGL();
    resetCube();
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko X ose.
 */
void GLWidget::rotLU()
{
    int tmp[8];
    if (way!=1) {
        SHIFT_FACE(1);
        tmp[0]=map[5][2][0]; tmp[1]=map[5][1][0]; tmp[2]=map[5][0][0];
        map[5][2][0]=map[3][2][0]; map[5][1][0]=map[3][1][0]; map[5][0][0]=map[3][0][0];
        map[3][2][0]=map[0][0][0]; map[3][1][0]=map[0][1][0]; map[3][0][0]=map[0][2][0];
        map[0][0][0]=map[2][0][0]; map[0][1][0]=map[2][1][0]; map[0][2][0]=map[2][2][0];
        map[2][0][0]=tmp[0]; map[2][1][0]=tmp[1]; map[2][2][0]=tmp[2];
    } else {
        DESHIFT_FACE(1);
        tmp[0]=map[2][0][0]; tmp[1]=map[2][1][0]; tmp[2]=map[2][2][0];
        map[2][0][0]=map[0][0][0]; map[2][1][0]=map[0][1][0]; map[2][2][0]=map[0][2][0];
        map[0][0][0]=map[3][2][0]; map[0][1][0]=map[3][1][0]; map[0][2][0]=map[3][0][0];
        map[3][2][0]=map[5][2][0]; map[3][1][0]=map[5][1][0]; map[3][0][0]=map[5][0][0];
        map[5][2][0]=tmp[0]; map[5][1][0]=tmp[1]; map[5][0][0]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[0]->rotX(-r); A[3]->rotX(-r); A[6]->rotX(-r);
        A[9]->rotX(-r); A[12]->rotX(-r); A[15]->rotX(-r);
        A[18]->rotX(-r); A[21]->rotX(-r); A[24]->rotX(-r);

    }

    updateGL();
    resetCube();
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko X ose.
 */
void  GLWidget::rotRD()
{
    int tmp[8];
    if (way==1) {
        SHIFT_FACE(4);
        tmp[0]=map[5][0][2]; tmp[1]=map[5][1][2]; tmp[2]=map[5][2][2];
        map[5][0][2]=map[3][0][2]; map[5][1][2]=map[3][1][2]; map[5][2][2]=map[3][2][2];
        map[3][0][2]=map[0][2][2]; map[3][1][2]=map[0][1][2]; map[3][2][2]=map[0][0][2];
        map[0][2][2]=map[2][2][2]; map[0][1][2]=map[2][1][2]; map[0][0][2]=map[2][0][2];
        map[2][2][2]=tmp[0]; map[2][1][2]=tmp[1]; map[2][0][2]=tmp[2];

    } else {
        DESHIFT_FACE(4);
        tmp[0]=map[2][2][2]; tmp[1]=map[2][1][2]; tmp[2]=map[2][0][2];
        map[2][2][2]=map[0][2][2]; map[2][1][2]=map[0][1][2]; map[2][0][2]=map[0][0][2];
        map[0][2][2]=map[3][0][2]; map[0][1][2]=map[3][1][2]; map[0][0][2]=map[3][2][2];
        map[3][0][2]=map[5][0][2]; map[3][1][2]=map[5][1][2]; map[3][2][2]=map[5][2][2];
        map[5][0][2]=tmp[0]; map[5][1][2]=tmp[1]; map[5][2][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[2]->rotX(r); A[5]->rotX(r); A[8]->rotX(r);
        A[11]->rotX(r); A[14]->rotX(r); A[17]->rotX(r);
        A[20]->rotX(r); A[23]->rotX(r); A[26]->rotX(r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko X ose.
 */
void  GLWidget::rotRU()
{
    int tmp[8];
    if (way!=1) {
        SHIFT_FACE(4);
        tmp[0]=map[5][0][2]; tmp[1]=map[5][1][2]; tmp[2]=map[5][2][2];
        map[5][0][2]=map[3][0][2]; map[5][1][2]=map[3][1][2]; map[5][2][2]=map[3][2][2];
        map[3][0][2]=map[0][2][2]; map[3][1][2]=map[0][1][2]; map[3][2][2]=map[0][0][2];
        map[0][2][2]=map[2][2][2]; map[0][1][2]=map[2][1][2]; map[0][0][2]=map[2][0][2];
        map[2][2][2]=tmp[0]; map[2][1][2]=tmp[1]; map[2][0][2]=tmp[2];

    } else {
        DESHIFT_FACE(4);
        tmp[0]=map[2][2][2]; tmp[1]=map[2][1][2]; tmp[2]=map[2][0][2];
        map[2][2][2]=map[0][2][2]; map[2][1][2]=map[0][1][2]; map[2][0][2]=map[0][0][2];
        map[0][2][2]=map[3][0][2]; map[0][1][2]=map[3][1][2]; map[0][0][2]=map[3][2][2];
        map[3][0][2]=map[5][0][2]; map[3][1][2]=map[5][1][2]; map[3][2][2]=map[5][2][2];
        map[5][0][2]=tmp[0]; map[5][1][2]=tmp[1]; map[5][2][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[2]->rotX(-r); A[5]->rotX(-r); A[8]->rotX(-r);
        A[11]->rotX(-r); A[14]->rotX(-r); A[17]->rotX(-r);
        A[20]->rotX(-r); A[23]->rotX(-r); A[26]->rotX(-r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Z ose.
 */
void  GLWidget::rotFR()
{
    int tmp[8];
    if (way==1) {
        SHIFT_FACE(2);
        tmp[0]=map[1][2][0]; tmp[1]=map[1][2][1]; tmp[2]=map[1][2][2];
        map[1][2][0]=map[0][2][0]; map[1][2][1]=map[0][2][1]; map[1][2][2]=map[0][2][2];
        map[0][2][0]=map[4][2][2]; map[0][2][1]=map[4][2][1]; map[0][2][2]=map[4][2][0];
        map[4][2][2]=map[5][2][2]; map[4][2][1]=map[5][2][1]; map[4][2][0]=map[5][2][0];
        map[5][2][2]=tmp[0]; map[5][2][1]=tmp[1]; map[5][2][0]=tmp[2];
    } else {
        DESHIFT_FACE(2);
        tmp[0]=map[5][2][2]; tmp[1]=map[5][2][1]; tmp[2]=map[5][2][0];
        map[5][2][2]=map[4][2][2]; map[5][2][1]=map[4][2][1]; map[5][2][0]=map[4][2][0];
        map[4][2][2]=map[0][2][0]; map[4][2][1]=map[0][2][1]; map[4][2][0]=map[0][2][2];
        map[0][2][0]=map[1][2][0]; map[0][2][1]=map[1][2][1]; map[0][2][2]=map[1][2][2];
        map[1][2][0]=tmp[0]; map[1][2][1]=tmp[1]; map[1][2][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[18]->rotZ(-r); A[19]->rotZ(-r); A[20]->rotZ(-r);
        A[21]->rotZ(-r); A[22]->rotZ(-r); A[23]->rotZ(-r);
        A[24]->rotZ(-r); A[25]->rotZ(-r); A[26]->rotZ(-r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Z ose.
 */
void  GLWidget::rotFL()
{
    int tmp[8];
    if (way!=1) {
        SHIFT_FACE(2);
        tmp[0]=map[1][2][0]; tmp[1]=map[1][2][1]; tmp[2]=map[1][2][2];
        map[1][2][0]=map[0][2][0]; map[1][2][1]=map[0][2][1]; map[1][2][2]=map[0][2][2];
        map[0][2][0]=map[4][2][2]; map[0][2][1]=map[4][2][1]; map[0][2][2]=map[4][2][0];
        map[4][2][2]=map[5][2][2]; map[4][2][1]=map[5][2][1]; map[4][2][0]=map[5][2][0];
        map[5][2][2]=tmp[0]; map[5][2][1]=tmp[1]; map[5][2][0]=tmp[2];
    } else {
        DESHIFT_FACE(2);
        tmp[0]=map[5][2][2]; tmp[1]=map[5][2][1]; tmp[2]=map[5][2][0];
        map[5][2][2]=map[4][2][2]; map[5][2][1]=map[4][2][1]; map[5][2][0]=map[4][2][0];
        map[4][2][2]=map[0][2][0]; map[4][2][1]=map[0][2][1]; map[4][2][0]=map[0][2][2];
        map[0][2][0]=map[1][2][0]; map[0][2][1]=map[1][2][1]; map[0][2][2]=map[1][2][2];
        map[1][2][0]=tmp[0]; map[1][2][1]=tmp[1]; map[1][2][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[18]->rotZ(r); A[19]->rotZ(r); A[20]->rotZ(r);
        A[21]->rotZ(r); A[22]->rotZ(r); A[23]->rotZ(r);
        A[24]->rotZ(r); A[25]->rotZ(r); A[26]->rotZ(r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Y ose.
 */
void  GLWidget::rotTL()
{
    int tmp[8];
    if (way==1) {
        DESHIFT_FACE(5);
        tmp[0]=map[1][0][0]; tmp[1]=map[1][1][0]; tmp[2]=map[1][2][0];
        map[1][0][0]=map[2][2][0]; map[1][1][0]=map[2][2][1]; map[1][2][0]=map[2][2][2];
        map[2][2][0]=map[4][2][0]; map[2][2][1]=map[4][1][0]; map[2][2][2]=map[4][0][0];
        map[4][2][0]=map[3][2][2]; map[4][1][0]=map[3][2][1]; map[4][0][0]=map[3][2][0];
        map[3][2][2]=tmp[0]; map[3][2][1]=tmp[1]; map[3][2][0]=tmp[2];
    } else {
        SHIFT_FACE(5);
        tmp[0]=map[3][2][2]; tmp[1]=map[3][2][1]; tmp[2]=map[3][2][0];
        map[3][2][2]=map[4][2][0]; map[3][2][1]=map[4][1][0]; map[3][2][0]=map[4][0][0];
        map[4][2][0]=map[2][2][0]; map[4][1][0]=map[2][2][1]; map[4][0][0]=map[2][2][2];
        map[2][2][0]=map[1][0][0]; map[2][2][1]=map[1][1][0]; map[2][2][2]=map[1][2][0];
        map[1][0][0]=tmp[0]; map[1][1][0]=tmp[1]; map[1][2][0]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if(way==0) r=-r;
        A[6]->rotY(-r); A[7]->rotY(-r); A[8]->rotY(-r);
        A[15]->rotY(-r); A[16]->rotY(-r); A[17]->rotY(-r);
        A[24]->rotY(-r); A[25]->rotY(-r); A[26]->rotY(-r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Y ose.
 */
void  GLWidget::rotTR()
{
    int tmp[8];
    if (way!=1) {
        DESHIFT_FACE(5);
        tmp[0]=map[1][0][0]; tmp[1]=map[1][1][0]; tmp[2]=map[1][2][0];
        map[1][0][0]=map[2][2][0]; map[1][1][0]=map[2][2][1]; map[1][2][0]=map[2][2][2];
        map[2][2][0]=map[4][2][0]; map[2][2][1]=map[4][1][0]; map[2][2][2]=map[4][0][0];
        map[4][2][0]=map[3][2][2]; map[4][1][0]=map[3][2][1]; map[4][0][0]=map[3][2][0];
        map[3][2][2]=tmp[0]; map[3][2][1]=tmp[1]; map[3][2][0]=tmp[2];
    } else {
        SHIFT_FACE(5);
        tmp[0]=map[3][2][2]; tmp[1]=map[3][2][1]; tmp[2]=map[3][2][0];
        map[3][2][2]=map[4][2][0]; map[3][2][1]=map[4][1][0]; map[3][2][0]=map[4][0][0];
        map[4][2][0]=map[2][2][0]; map[4][1][0]=map[2][2][1]; map[4][0][0]=map[2][2][2];
        map[2][2][0]=map[1][0][0]; map[2][2][1]=map[1][1][0]; map[2][2][2]=map[1][2][0];
        map[1][0][0]=tmp[0]; map[1][1][0]=tmp[1]; map[1][2][0]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if(way==0) r=-r;
        A[6]->rotY(r); A[7]->rotY(r); A[8]->rotY(r);
        A[15]->rotY(r); A[16]->rotY(r); A[17]->rotY(r);
        A[24]->rotY(r); A[25]->rotY(r); A[26]->rotY(r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Y ose.
 */
void  GLWidget::rotDL()
{
    int tmp[8];

    if (way!=1) {
        SHIFT_FACE(0);
        tmp[0]=map[1][2][2]; tmp[1]=map[1][1][2]; tmp[2]=map[1][0][2];
        map[1][2][2]=map[3][0][0]; map[1][1][2]=map[3][0][1]; map[1][0][2]=map[3][0][2];
        map[3][0][0]=map[4][0][2]; map[3][0][1]=map[4][1][2]; map[3][0][2]=map[4][2][2];
        map[4][0][2]=map[2][0][2]; map[4][1][2]=map[2][0][1]; map[4][2][2]=map[2][0][0];
        map[2][0][2]=tmp[0]; map[2][0][1]=tmp[1]; map[2][0][0]=tmp[2];
    } else {
        DESHIFT_FACE(0);
        tmp[0]=map[2][0][2]; tmp[1]=map[2][0][1]; tmp[2]=map[2][0][0];
        map[2][0][2]=map[4][0][2]; map[2][0][1]=map[4][1][2]; map[2][0][0]=map[4][2][2];
        map[4][0][2]=map[3][0][0]; map[4][1][2]=map[3][0][1]; map[4][2][2]=map[3][0][2];
        map[3][0][0]=map[1][2][2]; map[3][0][1]=map[1][1][2]; map[3][0][2]=map[1][0][2];
        map[1][2][2]=tmp[0]; map[1][1][2]=tmp[1]; map[1][0][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if(way==0) r=-r;
        A[0]->rotY(-r); A[1]->rotY(-r); A[2]->rotY(-r);
        A[9]->rotY(-r); A[10]->rotY(-r); A[11]->rotY(-r);
        A[18]->rotY(-r); A[19]->rotY(-r); A[20]->rotY(-r);
    }

    updateGL();
    resetCube();

}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu. Pomocu SHIFT_FACE / DESHIFT_FACE
 * kada smo rotirali stranu rotiracemo i sve boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao ??? ??? ???
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos vremena nam je ostalo
 * i za to vreme polako pomerati odgovarajuce kockice oko Y ose.
 */
void GLWidget::rotDR()
{
    int tmp[8];

    if (way==1) {
        SHIFT_FACE(0);
        tmp[0]=map[1][2][2]; tmp[1]=map[1][1][2]; tmp[2]=map[1][0][2];
        map[1][2][2]=map[3][0][0]; map[1][1][2]=map[3][0][1]; map[1][0][2]=map[3][0][2];
        map[3][0][0]=map[4][0][2]; map[3][0][1]=map[4][1][2]; map[3][0][2]=map[4][2][2];
        map[4][0][2]=map[2][0][2]; map[4][1][2]=map[2][0][1]; map[4][2][2]=map[2][0][0];
        map[2][0][2]=tmp[0]; map[2][0][1]=tmp[1]; map[2][0][0]=tmp[2];
    } else {
        DESHIFT_FACE(0);
        tmp[0]=map[2][0][2]; tmp[1]=map[2][0][1]; tmp[2]=map[2][0][0];
        map[2][0][2]=map[4][0][2]; map[2][0][1]=map[4][1][2]; map[2][0][0]=map[4][2][2];
        map[4][0][2]=map[3][0][0]; map[4][1][2]=map[3][0][1]; map[4][2][2]=map[3][0][2];
        map[3][0][0]=map[1][2][2]; map[3][0][1]=map[1][1][2]; map[3][0][2]=map[1][0][2];
        map[1][2][2]=tmp[0]; map[1][1][2]=tmp[1]; map[1][0][2]=tmp[2];
    }

    int k;
    int r;
    float fr;
    QTime time;

    k=0;
    fr=0;
    while (k<90) {
        time.start();
        updateGL();
        fr+=(time.elapsed()*90.)/DT;
        r=fr; fr-=r;
        if (k+r>90) r=90-k;
        k=k+r;
        if (way==0) r=-r;
        A[0]->rotY(r); A[1]->rotY(r); A[2]->rotY(r);
        A[9]->rotY(r); A[10]->rotY(r); A[11]->rotY(r);
        A[18]->rotY(r); A[19]->rotY(r); A[20]->rotY(r);

    }

    resetCube();

    updateGL();
    }

/*! Realizacija
 * @param number je broj ukupnih pokreta. Postavljen nadeset
 * @param n je Broj nasumicnih potez, postavljen na 15
 * @param valueR nasumicna vrednost u opsegu [0-9]
 * @param DT postavimo na  100, da ubrzamo pokrete, posle izvrsenja funkcije vracamo na 500.
 *
 * U for petlji biramo nasumicno jedan broj kojim je definisan jedan pokret valueR to pomocu switch
 * odredujemo koji pokret hocemo pa izvrsimo taj pokret i ponovimo petlju.
 */
void GLWidget::RandomCube()
{ DT = 100;
    int number = 10;
    int n=15;
    int valueR;

for(int i=0; i<n;i++){
    valueR= qrand()%number;
    switch(valueR){
    case 0:
        rotLD();
         Buffer.pushBuffer('F');
        break;
    case 1:
        rotLU();
         Buffer.pushBuffer('D');
        break;
    case 2:
        rotRD();
         Buffer.pushBuffer('J');
        break;
    case 3:
        rotRU();
         Buffer.pushBuffer('K');
        break;
    case 4:
        rotFR();
         Buffer.pushBuffer('H');
        break;
    case 5:
        rotFL();
        Buffer.pushBuffer('G');
        break;
    case 6:
        rotTL();
         Buffer.pushBuffer('R');
        break;
    case 7:
        rotTR();
         Buffer.pushBuffer('I');
        break;
    case 9:
        rotDL();
         Buffer.pushBuffer('C');
        break;
    case 8:
        rotDR();
         Buffer.pushBuffer('M');
        break;
    }
}

DT = 500;
}
/*! Realizacija
 * pozovemo metodu RandomCube .Polse stavimo na vrh buffera Q
 */
void GLWidget::make_random_cube(){
    RandomCube();
    Buffer.pushBuffer('Q');

}

/*! Realizacija
 * @param k brojac
 * @param DT koji postavimo na 100 da bi ubrzali posle izvrsenja funkcije vracamo na 500.
 *
 * Da bi vratili kocku u poziciju za novu igru  mi zemo prati poteze na bufferu i vratiti
 * se pokretima unazad sve dok nam buffer nije prazan. Ukoliko imamo vrednost koja nije jedan od pokreta na
 * bufferu nju cemo samo skinuti, i ignorisati.
 * Moramo da obratimo paznju na promenljivu way dok radimo.
 */
void GLWidget::new_game(){
    DT=100;
    int k;
    for (;;) {
         k=Buffer.popBuffer();
         if (k>0) way=0; else way=1;
         if (k<0) k=-k;
         switch (k) {
            case 'R': rotTL(); break;
            case 'D': rotLU(); break;
            case 'C': rotDL(); break;
            case 'F': rotLD(); break;
            case 'G': rotFL(); break;
            case 'H': rotFR(); break;
            case 'I': rotTR(); break;
            case 'J': rotRD(); break;
            case 'K': rotRU(); break;
            case 'M': rotDR(); break;

         }
         if (k==0) break;
    }
    DT=500;
    way=1;

}
/*! Realizacija
 * Pozovemo  SolveSimple i na buffer pushujemo P.
 */
void GLWidget::solve_it(){
        SolveSimple();
        Buffer.pushBuffer('P');

}

/*! Realizacija
 * Pozovemo resetCube
 */
GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(parent)
{
     resetCube();
}
/*! Realizacija
 *@param k je brojac
 *
 * U for ciklusu idemo k ide od 0 do 27 i za svaki elemenat A me ga brisemo.
 */

 GLWidget::~GLWidget()
 {
     int k;
     for (k=0; k<27; k++) {
         delete A[k];
     }
  }

 /*! Realizacija
  * vratimo funkciju Qsize sa vrednostima 50 za duzinu i 50 za sirinu.
  */
 QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 /*! Realizacija
  * vratimo Qsize sa vrednostima 400 za sirinu i duzinu.
  */
 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }

/**************************************/

 /*! mapa resene rubikove kocke*/
 int mapGoal[6][3][3]=
 {{{1,1,1},{1,1,1},{1,1,1}},
     {{2,2,2},{2,2,2},{2,2,2}},
     {{3,3,3},{3,3,3},{3,3,3}},
     {{4,4,4},{4,4,4},{4,4,4}},
     {{5,5,5},{5,5,5},{5,5,5}},
     {{6,6,6},{6,6,6},{6,6,6}}};
 /*! \brief pomocna metoda za proveru stanja nase trenutne rubikove kocke i koliko je daleko od resenja*/
 int vrednost(int tekmap[6][3][3])
 {
     /*! @param br je broj polja koji se nalaze na tacnom mestu minimalno je 6 jer centri su
      * uvek na tacnom mestu a max je 54 odnosno solved cube
      * radi jednostavnosti brojimo od 0 ipak.
      */
      int br=0;
     for (int i =0;i<6;i++)
         for(int j=0; j<3;j++)
             for(int k=0;k<3;k++)
                 if(tekmap[i][j][k]==mapGoal[i][j][k]) br++;
     return br;
 }

 /*! Realizacija
  * @param n = ogranicenje za maksimum ciklusa, da bi sprecili beskonacnu petlju.
  * @param tekbr, novbr tekuca i nova vrednost stanja mape
  * @param[out] resenje je niz poteza do resenja
  * @param brojac za niz resenja
  * @param flag je pomocna promenjljiva koja kada nije moguce vise izvrsavati jednostruke poteze
  * pokusa da izvrsava dvostruke poteze da dodje do resenja.
  *
  * Algoritam se svodi na try and error.
  * Mi posle svakog pokreta racunamo koliko vrednosti nam se poklapaju izmedju trenutne mape, globalne promenljive
  * i ciljne mape. Sto je ta vrednost veca to smo blizi resenju. Ukoliko smo dosli do maximuma od 54, to jest potpunog
  * poklapanja nasih mapa, mi radimo break.
  * Ukoliko nam novo stanje samo vece od starog, mi sacuvamo to stanje i radimo continue.
  *
  */
 void GLWidget::SolveSimple()
 {

     int n=100;
     int tekbr,novbr;
     char resenje [200];
     int i=0;
     int flag = 0;
     tekbr= vrednost(map);
     while( tekbr!=54 || n>0)
     {
     tekbr= vrednost(map);
     n=n-1;

     rotDL();
     novbr= vrednost(map);
     if (novbr > tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'D';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotDR();}

     rotFL();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'F';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotFR();}

     rotLD();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'L';
         i=i+1;
         resenje [i]= 'D';
         i=i+1;
         if(tekbr == 54) break;
         continue;

     }else {rotLU();}

     rotTL();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'T';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotTR();}

     rotRD();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'R';
         i=i+1;
         resenje [i]= 'D';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotRU();}
  /*! Suptrni smer*/
     rotDR();
     novbr= vrednost(map);
     if (novbr > tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'D';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotDL();}

     rotFR();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'F';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotFL();}

     rotLU();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'L';
         i=i+1;
         resenje [i]= 'U';
         i=i+1;
         if(tekbr == 54) break;
         continue;

     }else {rotLD();}

     rotTR();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'T';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotTL();}

     rotRU();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'R';
         i=i+1;
         resenje [i]= 'U';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotRD();}

     /***Dvostruki potezi ako nam jednostruki nedaju da pridjemo blize resenju****/
 if (flag == 2){
     flag=0;

     rotDL();
     rotDL();
     novbr= vrednost(map);
     if (novbr > tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'D';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotDR();rotDR();}
     rotDR();
     rotDR();
     novbr= vrednost(map);
     if (novbr > tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'D';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotDL();rotDL();}
     rotFL();
     rotFL();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'F';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotFR();rotFR();}

     rotFR();
     rotFR();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'F';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotFL();rotFL();}
     rotLD();
     rotLD();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'L';
         i=i+1;
         resenje [i]= 'D';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;

     }else {rotLU();rotLU();}
     rotLU();
     rotLU();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'L';
         i=i+1;
         resenje [i]= 'U';
         i=i+1;
         resenje [i]= '2';
         i=i+1;
         if(tekbr == 54) break;
         continue;

     }else {rotLD();rotLD();}
     rotTL();
     rotTL();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'T';
         i=i+1;
         resenje [i]= 'L';
         i=i+1;
         resenje[i]= '2';
         if(tekbr == 54) break;
         continue;
     }else {rotTR();rotTR();}
     rotTR();
     rotTR();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'T';
         i=i+1;
         resenje [i]= 'R';
         i=i+1;
         resenje[i]= '2';
         if(tekbr == 54) break;
         continue;
     }else {rotTL();rotTL();}
     rotRD();
     rotRD();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'R';
         i=i+1;
         resenje [i]= 'D';
         i=i+1;
         resenje[i]='2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotRU();rotRU();}

     rotRU();
     rotRU();
     novbr= vrednost(map);
     if (novbr >tekbr)
     {
         tekbr= novbr;
         resenje [i] = 'R';
         i=i+1;
         resenje [i]= 'U';
         i=i+1;
         resenje[i]='2';
         i=i+1;
         if(tekbr == 54) break;
         continue;
     }else {rotRD();rotRD();}


 }else {flag= flag + 1 ;}


     }

 }

 /**********************************************************************************/

/*! Realizacija
 *
 * ??? ??? ???
 */
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
/*! Realizacija
 * ??? ??? ???
 * Pozovemo makeObject.
 */
void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeObject();
}

/*! Realizacija
 *
 * Vrsi se promena velicine pomocu glVieport.
 * ??? ??? ???
 */
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

/*! Realizacija
 * @param i,j su brojaci
 * @param z1,z2 su ??? ??? ???
 * @param hit je ??? ??? ???
 * @param minZ je ??? ??? ???
 * @param ret je ??? ??? ???
 * @param ii ??? ??? ???
 * @param jj ??? ??? ???
 * @param names ??? ??? ???
 * @param ptr je pokazivac na ??? ??? ???
 *
 * ??? ??? ???
 */
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
/*! Realizacija
 * @param lastPos je poslednja pozicija misa ??? ??? ???
 *
 * ??? ??? ???
 */
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
/*! Realizacija
 * @param dx,dy za koliko se mis pomerio u odnosu na poslednju poziciju ??? ??? ???
 *
 * ??? ??? ???
 */
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

 /*! Realizacija
  * @param render_mode ??? ??? ???
  *
  * ??? ??? ???
  */

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
