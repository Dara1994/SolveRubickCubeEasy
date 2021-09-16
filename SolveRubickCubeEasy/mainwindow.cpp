#include "mainwindow.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QTime>
#include <cstdlib>
#include <math.h>

/*! @param R je float sa vrednoscu 0.2
 * koja se koristi za postavljanje koordinatnog pocetke za kockice
 */
float R = 0.2;
/*! @param S je float sa vrednoscu 0.16
 * koja se koristi za velicinu stranice kockice sa 0.2 ne bi bilo razmaka*/
float S = 0.16;

/*!  ORTHOFRUSTRUM
 *  koja sluzi za projekciju kocke, tj. pogleda na projekciju kocke . Mnozi
 * matricu i zamenjuje je novom. */
#define ORTHOFRUSTRUM glFrustum(-.3, .3, -.3, .3, 4, 10);
/*! float DT je tipa float vrednosti 500
 * koju koristimo u klasama za iscrtavanje. Definise brzinu rotacija kocke. */
float DT = 500.;
/*! way je int
 * koja defenise u kom smeru cemo da pomeramo rotacije. */
int way = 1;

/*! @class MoveBuffer
 * \brief Pomocna klasa MoveBuffer
 * Pomocna klasa kojom manipulisemo bufferom poteza.
 */
class MoveBuffer
{
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
    MoveBuffer()
    {
        movBuffer = 0;
        movBufferLen = 0;
        movBufferMem = 0;
    }

    /*! Destruktor */
    ~MoveBuffer()
    {
        free(movBuffer);
    }
    /*! \brief Push
     * @param[in] mov Vrednost koju postavljamo na vrh buffer.
     *
     *  Pushujemo na vrh buffera slovo koje odgovara dugmetu koje smo
     * pritisli.
     */
    void pushBuffer(char mov);
    /*! \brief Pop.
     * \return slovo sa vrha buffera.
     */
    auto popBuffer() -> char;
};

/*! Buffer
 * Napravili smo jedan buffer u kome cemo cuvati nase interakcije sa tastaturom
 */
MoveBuffer Buffer;

/*! Realizacija metode pushBuffer
 *  * Stavljamo mov na vrh buffer posto izvsimo provere.
 * Proveravamo da li je memorija puna ili prazna.
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

    if (movBufferLen == movBufferMem) {
        movBufferMem += 10;
        char * tmp =
                (char *)realloc(movBuffer, movBufferMem * sizeof(char));
        if(tmp == NULL){
            return;
        }
        else{
            movBuffer = tmp;
        }
    }
    movBuffer[movBufferLen] = mov;
    movBufferLen++;
}

/*! Realizacije metode popBuffer
 * @param[out] karakter na vrhu buffera
 * ukoliko duzina buffera nije nula smanjimo tu duzino i vratimo char sa vrha.
 * ukoliko nam je duzina buffera nula, odnosno Buffer je prazan, vracamo nulu.
 */
auto MoveBuffer::popBuffer() -> char
{
    if (movBufferLen > 0) {
        movBufferLen--;
        return movBuffer[movBufferLen];
    }
    return 0;
}

/*! Inicializacija promenljive vezane za boje rubikove kocke
 * @param col je dvo dimezioni niz koji cuva informacije o nasim bojama RGB
 */
float col[][3] = { { 0.1, 0.1, 0.1 }, { 0.8, 0, 0 },   { 0, 0.8, 0 },
           { 0, 0, 0.8 },     { 0.8, 0.8, 0 }, { 0.8, 0, 0.8 },
           { 0, 0.8, 0.8 } };
/*! Mapa
 *  @param map je trodimezioni niz koji mapira sve kvadrata na svim stranama
 * rubikove kocke.*/
int map[6][3][3] = { { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } },
             { { 2, 2, 2 }, { 2, 2, 2 }, { 2, 2, 2 } },
             { { 3, 3, 3 }, { 3, 3, 3 }, { 3, 3, 3 } },
             { { 4, 4, 4 }, { 4, 4, 4 }, { 4, 4, 4 } },
             { { 5, 5, 5 }, { 5, 5, 5 }, { 5, 5, 5 } },
             { { 6, 6, 6 }, { 6, 6, 6 }, { 6, 6, 6 } } };

/*! \class Klasa Cube
 * \brief Klasa kojom definisemo ponasanje cube
 * Ovde imamo sve metode vezane za manipulaciju nase rubikove kocke.
 * Definisanje kocke, iscrtavanja i rotacija oko xyz osa.
 */
class Cube
{
      public:
    /*! Koordinate u prostoru
     *Iscrtavamo relevatne tacke za nasu kocku to su uglovi rubikove kocke u
     *prostoru.
     */
    float coords[8][3];
    /*! Kasnije ih inicijalizujemo , to su jedinicni vektori*/
    float norm[6][3];
    /*! Boje*/
    int colors[6];
    /*! Konstruktor
     * @param[in] x0, y0, z0 su koordinate koordinatnog pocetka
     * @param[in] b je velicina stranice a0 u potpisu ili S globalno
     * @param[in] r1, r2 ,r3 ,r4, r5 ,r6 su relevatne boje.
     */
    Cube(float x0, float y0, float z0, float b, int r1, int r2, int r3,
         int r4, int r5, int r6);
    /*! Pomeri rubikovu kocku
     * @param dx, dy, dz su vrednosti za koje pomeramo u odnosu na xyz ose.
     */
    void move(float dx, float dy, float dz);
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
Cube::Cube(float x0, float y0, float z0, float a, int r1, int r2, int r3,
       int r4, int r5, int r6)
{
    colors[0] = r1;
    colors[1] = r2;
    colors[2] = r3;
    colors[3] = r4;
    colors[4] = r5;
    colors[5] = r6;
    coords[0][0] = x0 - a * .5;
    coords[0][1] = y0 - a * .5;
    coords[0][2] = z0 - a * .5;
    coords[1][0] = x0 + a * .5;
    coords[1][1] = y0 - a * .5;
    coords[1][2] = z0 - a * .5;
    coords[2][0] = x0 - a * .5;
    coords[2][1] = y0 + a * .5;
    coords[2][2] = z0 - a * .5;
    coords[3][0] = x0 + a * .5;
    coords[3][1] = y0 + a * .5;
    coords[3][2] = z0 - a * .5;
    coords[4][0] = x0 - a * .5;
    coords[4][1] = y0 - a * .5;
    coords[4][2] = z0 + a * .5;
    coords[5][0] = x0 + a * .5;
    coords[5][1] = y0 - a * .5;
    coords[5][2] = z0 + a * .5;
    coords[6][0] = x0 - a * .5;
    coords[6][1] = y0 + a * .5;
    coords[6][2] = z0 + a * .5;
    coords[7][0] = x0 + a * .5;
    coords[7][1] = y0 + a * .5;
    coords[7][2] = z0 + a * .5;

    norm[0][0] = 0;
    norm[0][1] = -1;
    norm[0][2] = 0;
    norm[1][0] = -1;
    norm[1][1] = 0;
    norm[1][2] = 0;
    norm[2][0] = 0;
    norm[2][1] = 0;
    norm[2][2] = 1;
    norm[3][0] = 0;
    norm[3][1] = 0;
    norm[3][2] = -1;
    norm[4][0] = 1;
    norm[4][1] = 0;
    norm[4][2] = 0;
    norm[5][0] = 0;
    norm[5][1] = 1;
    norm[5][2] = 0;
}
/*! Realizacija
 * Crta rubikovu kocku.
 * Koristimo funkcije iz biblioteke opengl za iscrtavanje kocke. Pomocu
 * jedinicnih vektora.
 */
void Cube::drawCube()
{
    /*! Metod glBegin() sluzi za podelu temena u grupe.
     * U ovom slucaju delice ih u kocke, zbog konstante GL_QUADS
     */
    glBegin(GL_QUADS);
    /*! Za svaku od 6 strana kocke metodom glColor3fv() bira boju,
     * metodom GlVertex3fv() odredjuju se koordinate svakog temena
     */
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
void Cube::move(float dx, float dy, float dz)
{
    int k;
    for (k = 0; k < 8; k++) {
        coords[k][0] += dx;
        coords[k][1] += dy;
        coords[k][2] += dz;
    }
}

/*! Realizacija
 * Na svaki pritisnut taster izvsavamo relevatnu rotaciju. Predefinisani okret.
 * Dok vrednost tastera stavljamo u buffer.
 */
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F) {
        rotLD();
        Buffer.pushBuffer('F');
    }
    if (event->key() == Qt::Key_D) {
        rotLU();
        Buffer.pushBuffer('D');
    }
    if (event->key() == Qt::Key_J) {
        rotRD();
        Buffer.pushBuffer('J');
    }
    if (event->key() == Qt::Key_K) {
        rotRU();
        Buffer.pushBuffer('K');
    }
    if (event->key() == Qt::Key_H) {
        rotFR();
        Buffer.pushBuffer('H');
    }
    if (event->key() == Qt::Key_R) {
        rotTL();
        Buffer.pushBuffer('R');
    }
    if (event->key() == Qt::Key_I) {
        rotTR();
        Buffer.pushBuffer('I');
    }
    if (event->key() == Qt::Key_G) {
        rotFL();
        Buffer.pushBuffer('G');
    }
    if (event->key() == Qt::Key_C) {
        rotDL();
        Buffer.pushBuffer('C');
    }
    if (event->key() == Qt::Key_M) {
        rotDR();
        Buffer.pushBuffer('M');
    }
    if (event->key() == Qt::Key_U) {
        rotBR();
        Buffer.pushBuffer('U');
    }
    if (event->key() == Qt::Key_T) {
        rotBL();
        Buffer.pushBuffer('T');
    }
}

/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u
 * odgovarajuci coords reda k prve koordinate i norm.
 */
void Cube::rotX(int angle)
{
    float f = angle * 3.14159 / 180.;
    float cosf = cos(f), sinf = sin(f);
    float b, c;
    int k;
    for (k = 0; k < 8; k++) {
        b = cosf * coords[k][1] - sinf * coords[k][2];
        c = sinf * coords[k][1] + cosf * coords[k][2];
        coords[k][1] = b;
        coords[k][2] = c;
    }
    for (k = 0; k < 6; k++) {
        b = cosf * norm[k][1] - sinf * norm[k][2];
        c = sinf * norm[k][1] + cosf * norm[k][2];
        norm[k][1] = b;
        norm[k][2] = c;
    }
}
/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u
 * odgovarajuci coords reda k druge koordinate i norm.
 */
void Cube::rotY(int angle)
{
    float f = angle * 3.14159 / 180.;
    float cosf = cos(f), sinf = sin(f);
    float b, c;
    int k;
    for (k = 0; k < 8; k++) {
        b = cosf * coords[k][2] - sinf * coords[k][0];
        c = sinf * coords[k][2] + cosf * coords[k][0];
        coords[k][2] = b;
        coords[k][0] = c;
    }
    for (k = 0; k < 6; k++) {
        b = cosf * norm[k][2] - sinf * norm[k][0];
        c = sinf * norm[k][2] + cosf * norm[k][0];
        norm[k][2] = b;
        norm[k][0] = c;
    }
}
/*! Realizacija
 * @param f je angle puta pi.
 * @param cosf, sinf su vrednosti kosinusa i sinusa respektivno od f
 * @param b,c vrednosti pomeranja
 * @param k broji uglove
 *
 * Za svaki ugao mi racunamo razliku u pomeranu i taj rezultat sacuvamo u
 * odgovarajuci coords reda k trece koordinate i norm.
 */
void Cube::rotZ(int angle)
{
    float f = angle * 3.14159 / 180.;
    float cosf = cos(f), sinf = sin(f);
    float b, c;
    int k;
    for (k = 0; k < 8; k++) {
        b = cosf * coords[k][0] - sinf * coords[k][1];
        c = sinf * coords[k][0] + cosf * coords[k][1];
        coords[k][0] = b;
        coords[k][1] = c;
    }
    for (k = 0; k < 6; k++) {
        b = cosf * norm[k][0] - sinf * norm[k][1];
        c = sinf * norm[k][0] + cosf * norm[k][1];
        norm[k][0] = b;
        norm[k][1] = c;
    }
}
/*! Realizacija
 * @param P je niz koji sadrzi temena, kroz koja prolaze "trake" zice kocke
 * @param P1 je niz koji temena kroz koja prolaze linije
 */
void Cube::drawWireCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, coords);

    static unsigned int P[] = { 0, 1, 3, 2, 0, 4, 5, 7, 6, 4 };

    glDrawElements(GL_LINE_STRIP, 10, GL_UNSIGNED_INT, (void *)P);
    static unsigned int P1[] = { 1, 5, 2, 6, 3, 7 };
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void *)P1);
}

/*! A
 * Napravili smo niz pokazivaca na nase kockice koje cine rubikovu kocku
 */
Cube *A[27] = { 0 };

/*! Realizacija
 * @param k brojac koji broji kockice.
 *
 * Prvo obrisemo svaki elemenat iz niza A. Potom za svaku od tih 27 kockica koje
 * cine rubikovu kocku koristimo konstruktor Cube sa odgovarajucim elementima. R
 * za koordinatni pocetak za svaku kockicu, S je velicina stranice kockice 1.6,
 * i odgovarajuce map za strane koje su vidljive a 0 za one koje nevidimo.
 */
void resetCube()
{
    int k;
    for (k = 0; k < 27; k++) {
        delete A[k];
    }

    A[0] = new Cube(-R, -R, -R, S, map[0][0][0], map[1][0][2], 0,
            map[3][0][0], 0, 0);
    A[1] = new Cube(0, -R, -R, S, map[0][0][1], 0, 0, map[3][0][1], 0, 0);
    A[2] = new Cube(R, -R, -R, S, map[0][0][2], 0, 0, map[3][0][2],
            map[4][0][2], 0);
    A[3] = new Cube(-R, 0, -R, S, 0, map[1][0][1], 0, map[3][1][0], 0, 0);
    A[4] = new Cube(0, 0, -R, S, 0, 0, 0, map[3][1][1], 0, 0);
    A[5] = new Cube(R, 0, -R, S, 0, 0, 0, map[3][1][2], map[4][0][1], 0);
    A[6] = new Cube(-R, R, -R, S, 0, map[1][0][0], 0, map[3][2][0], 0,
            map[5][0][0]);
    A[7] = new Cube(0, R, -R, S, 0, 0, 0, map[3][2][1], 0, map[5][0][1]);
    A[8] = new Cube(R, R, -R, S, 0, 0, 0, map[3][2][2], map[4][0][0],
            map[5][0][2]);

    A[9] = new Cube(-R, -R, 0, S, map[0][1][0], map[1][1][2], 0, 0, 0, 0);
    A[10] = new Cube(0, -R, 0, S, map[0][1][1], 0, 0, 0, 0, 0);
    A[11] = new Cube(R, -R, 0, S, map[0][1][2], 0, 0, 0, map[4][1][2], 0);
    A[12] = new Cube(-R, 0, 0, S, 0, map[1][1][1], 0, 0, 0, 0);
    A[13] = new Cube(0, 0, 0, S, 0, 0, 0, 0, 0, 0);
    A[14] = new Cube(R, 0, 0, S, 0, 0, 0, 0, map[4][1][1], 0);
    A[15] = new Cube(-R, R, 0, S, 0, map[1][1][0], 0, 0, 0, map[5][1][0]);
    A[16] = new Cube(0, R, 0, S, 0, 0, 0, 0, 0, map[5][1][1]);
    A[17] = new Cube(R, R, 0, S, 0, 0, 0, 0, map[4][1][0], map[5][1][2]);

    A[18] = new Cube(-R, -R, R, S, map[0][2][0], map[1][2][2], map[2][0][0],
             0, 0, 0);
    A[19] = new Cube(0, -R, R, S, map[0][2][1], 0, map[2][0][1], 0, 0, 0);
    A[20] = new Cube(R, -R, R, S, map[0][2][2], 0, map[2][0][2], 0,
             map[4][2][2], 0);
    A[21] = new Cube(-R, 0, R, S, 0, map[1][2][1], map[2][1][0], 0, 0, 0);
    A[22] = new Cube(0, 0, R, S, 0, 0, map[2][1][1], 0, 0, 0);
    A[23] = new Cube(R, 0, R, S, 0, 0, map[2][1][2], 0, map[4][2][1], 0);
    A[24] = new Cube(-R, R, R, S, 0, map[1][2][0], map[2][2][0], 0, 0,
             map[5][2][0]);
    A[25] = new Cube(0, R, R, S, 0, 0, map[2][2][1], 0, 0, map[5][2][1]);
    A[26] = new Cube(R, R, R, S, 0, 0, map[2][2][2], 0, map[4][2][0],
             map[5][2][2]);
}
/*! Definisemo pomeranje jedne strane u smeru kazaljke na satu*/
#define SHIFT_FACE(a_)          \
    tmp[0] = map[a_][2][2]; \
    tmp[1] = map[a_][1][2]; \
    tmp[2] = map[a_][0][2]; \
    tmp[3] = map[a_][0][1]; \
    tmp[4] = map[a_][0][0]; \
    tmp[5] = map[a_][1][0]; \
    tmp[6] = map[a_][2][0]; \
    tmp[7] = map[a_][2][1]; \
    map[a_][2][2] = tmp[6]; \
    map[a_][1][2] = tmp[7]; \
    map[a_][0][2] = tmp[0]; \
    map[a_][0][1] = tmp[1]; \
    map[a_][0][0] = tmp[2]; \
    map[a_][1][0] = tmp[3]; \
    map[a_][2][0] = tmp[4]; \
    map[a_][2][1] = tmp[5];

/*! Definisemo pomeranje jedne strane u suprotnom smeru od smera kazaljke na
 * satu*/
#define DESHIFT_FACE(a_)        \
    tmp[6] = map[a_][2][2]; \
    tmp[7] = map[a_][1][2]; \
    tmp[0] = map[a_][0][2]; \
    tmp[1] = map[a_][0][1]; \
    tmp[2] = map[a_][0][0]; \
    tmp[3] = map[a_][1][0]; \
    tmp[4] = map[a_][2][0]; \
    tmp[5] = map[a_][2][1]; \
    map[a_][2][2] = tmp[0]; \
    map[a_][1][2] = tmp[1]; \
    map[a_][0][2] = tmp[2]; \
    map[a_][0][1] = tmp[3]; \
    map[a_][0][0] = tmp[4]; \
    map[a_][1][0] = tmp[5]; \
    map[a_][2][0] = tmp[6]; \
    map[a_][2][1] = tmp[7];

/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * X ose.
 */
void GLWidget::rotLD(int flag)
{
    int tmp[8];
    if (way == 1) {
        SHIFT_FACE(1);
        tmp[0] = map[5][2][0];
        tmp[1] = map[5][1][0];
        tmp[2] = map[5][0][0];
        map[5][2][0] = map[3][2][0];
        map[5][1][0] = map[3][1][0];
        map[5][0][0] = map[3][0][0];
        map[3][2][0] = map[0][0][0];
        map[3][1][0] = map[0][1][0];
        map[3][0][0] = map[0][2][0];
        map[0][0][0] = map[2][0][0];
        map[0][1][0] = map[2][1][0];
        map[0][2][0] = map[2][2][0];
        map[2][0][0] = tmp[0];
        map[2][1][0] = tmp[1];
        map[2][2][0] = tmp[2];
    } else {
        DESHIFT_FACE(1);
        tmp[0] = map[2][0][0];
        tmp[1] = map[2][1][0];
        tmp[2] = map[2][2][0];
        map[2][0][0] = map[0][0][0];
        map[2][1][0] = map[0][1][0];
        map[2][2][0] = map[0][2][0];
        map[0][0][0] = map[3][2][0];
        map[0][1][0] = map[3][1][0];
        map[0][2][0] = map[3][0][0];
        map[3][2][0] = map[5][2][0];
        map[3][1][0] = map[5][1][0];
        map[3][0][0] = map[5][0][0];
        map[5][2][0] = tmp[0];
        map[5][1][0] = tmp[1];
        map[5][0][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;
        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotX(r);
            A[3]->rotX(r);
            A[6]->rotX(r);
            A[9]->rotX(r);
            A[12]->rotX(r);
            A[15]->rotX(r);
            A[18]->rotX(r);
            A[21]->rotX(r);
            A[24]->rotX(r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti paintGl da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * X ose.
 */
void GLWidget::rotLU(int flag)
{
    int tmp[8];
    if (way != 1) {
        SHIFT_FACE(1);
        tmp[0] = map[5][2][0];
        tmp[1] = map[5][1][0];
        tmp[2] = map[5][0][0];
        map[5][2][0] = map[3][2][0];
        map[5][1][0] = map[3][1][0];
        map[5][0][0] = map[3][0][0];
        map[3][2][0] = map[0][0][0];
        map[3][1][0] = map[0][1][0];
        map[3][0][0] = map[0][2][0];
        map[0][0][0] = map[2][0][0];
        map[0][1][0] = map[2][1][0];
        map[0][2][0] = map[2][2][0];
        map[2][0][0] = tmp[0];
        map[2][1][0] = tmp[1];
        map[2][2][0] = tmp[2];
    } else {
        DESHIFT_FACE(1);
        tmp[0] = map[2][0][0];
        tmp[1] = map[2][1][0];
        tmp[2] = map[2][2][0];
        map[2][0][0] = map[0][0][0];
        map[2][1][0] = map[0][1][0];
        map[2][2][0] = map[0][2][0];
        map[0][0][0] = map[3][2][0];
        map[0][1][0] = map[3][1][0];
        map[0][2][0] = map[3][0][0];
        map[3][2][0] = map[5][2][0];
        map[3][1][0] = map[5][1][0];
        map[3][0][0] = map[5][0][0];
        map[5][2][0] = tmp[0];
        map[5][1][0] = tmp[1];
        map[5][0][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotX(-r);
            A[3]->rotX(-r);
            A[6]->rotX(-r);
            A[9]->rotX(-r);
            A[12]->rotX(-r);
            A[15]->rotX(-r);
            A[18]->rotX(-r);
            A[21]->rotX(-r);
            A[24]->rotX(-r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * X ose.
 */
void GLWidget::rotRD(int flag)
{
    int tmp[8];
    if (way == 1) {
        SHIFT_FACE(4);
        tmp[0] = map[5][0][2];
        tmp[1] = map[5][1][2];
        tmp[2] = map[5][2][2];
        map[5][0][2] = map[3][0][2];
        map[5][1][2] = map[3][1][2];
        map[5][2][2] = map[3][2][2];
        map[3][0][2] = map[0][2][2];
        map[3][1][2] = map[0][1][2];
        map[3][2][2] = map[0][0][2];
        map[0][2][2] = map[2][2][2];
        map[0][1][2] = map[2][1][2];
        map[0][0][2] = map[2][0][2];
        map[2][2][2] = tmp[0];
        map[2][1][2] = tmp[1];
        map[2][0][2] = tmp[2];

    } else {
        DESHIFT_FACE(4);
        tmp[0] = map[2][2][2];
        tmp[1] = map[2][1][2];
        tmp[2] = map[2][0][2];
        map[2][2][2] = map[0][2][2];
        map[2][1][2] = map[0][1][2];
        map[2][0][2] = map[0][0][2];
        map[0][2][2] = map[3][0][2];
        map[0][1][2] = map[3][1][2];
        map[0][0][2] = map[3][2][2];
        map[3][0][2] = map[5][0][2];
        map[3][1][2] = map[5][1][2];
        map[3][2][2] = map[5][2][2];
        map[5][0][2] = tmp[0];
        map[5][1][2] = tmp[1];
        map[5][2][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[2]->rotX(r);
            A[5]->rotX(r);
            A[8]->rotX(r);
            A[11]->rotX(r);
            A[14]->rotX(r);
            A[17]->rotX(r);
            A[20]->rotX(r);
            A[23]->rotX(r);
            A[26]->rotX(r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * X ose.
 */
void GLWidget::rotRU(int flag)
{
    int tmp[8];
    if (way != 1) {
        SHIFT_FACE(4);
        tmp[0] = map[5][0][2];
        tmp[1] = map[5][1][2];
        tmp[2] = map[5][2][2];
        map[5][0][2] = map[3][0][2];
        map[5][1][2] = map[3][1][2];
        map[5][2][2] = map[3][2][2];
        map[3][0][2] = map[0][2][2];
        map[3][1][2] = map[0][1][2];
        map[3][2][2] = map[0][0][2];
        map[0][2][2] = map[2][2][2];
        map[0][1][2] = map[2][1][2];
        map[0][0][2] = map[2][0][2];
        map[2][2][2] = tmp[0];
        map[2][1][2] = tmp[1];
        map[2][0][2] = tmp[2];

    } else {
        DESHIFT_FACE(4);
        tmp[0] = map[2][2][2];
        tmp[1] = map[2][1][2];
        tmp[2] = map[2][0][2];
        map[2][2][2] = map[0][2][2];
        map[2][1][2] = map[0][1][2];
        map[2][0][2] = map[0][0][2];
        map[0][2][2] = map[3][0][2];
        map[0][1][2] = map[3][1][2];
        map[0][0][2] = map[3][2][2];
        map[3][0][2] = map[5][0][2];
        map[3][1][2] = map[5][1][2];
        map[3][2][2] = map[5][2][2];
        map[5][0][2] = tmp[0];
        map[5][1][2] = tmp[1];
        map[5][2][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[2]->rotX(-r);
            A[5]->rotX(-r);
            A[8]->rotX(-r);
            A[11]->rotX(-r);
            A[14]->rotX(-r);
            A[17]->rotX(-r);
            A[20]->rotX(-r);
            A[23]->rotX(-r);
            A[26]->rotX(-r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Z ose.
 */
void GLWidget::rotFR(int flag)
{
    int tmp[8];
    if (way == 1) {
        SHIFT_FACE(2);
        tmp[0] = map[1][2][0];
        tmp[1] = map[1][2][1];
        tmp[2] = map[1][2][2];
        map[1][2][0] = map[0][2][0];
        map[1][2][1] = map[0][2][1];
        map[1][2][2] = map[0][2][2];
        map[0][2][0] = map[4][2][2];
        map[0][2][1] = map[4][2][1];
        map[0][2][2] = map[4][2][0];
        map[4][2][2] = map[5][2][2];
        map[4][2][1] = map[5][2][1];
        map[4][2][0] = map[5][2][0];
        map[5][2][2] = tmp[0];
        map[5][2][1] = tmp[1];
        map[5][2][0] = tmp[2];
    } else {
        DESHIFT_FACE(2);
        tmp[0] = map[5][2][2];
        tmp[1] = map[5][2][1];
        tmp[2] = map[5][2][0];
        map[5][2][2] = map[4][2][2];
        map[5][2][1] = map[4][2][1];
        map[5][2][0] = map[4][2][0];
        map[4][2][2] = map[0][2][0];
        map[4][2][1] = map[0][2][1];
        map[4][2][0] = map[0][2][2];
        map[0][2][0] = map[1][2][0];
        map[0][2][1] = map[1][2][1];
        map[0][2][2] = map[1][2][2];
        map[1][2][0] = tmp[0];
        map[1][2][1] = tmp[1];
        map[1][2][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[18]->rotZ(-r);
            A[19]->rotZ(-r);
            A[20]->rotZ(-r);
            A[21]->rotZ(-r);
            A[22]->rotZ(-r);
            A[23]->rotZ(-r);
            A[24]->rotZ(-r);
            A[25]->rotZ(-r);
            A[26]->rotZ(-r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Z ose.
 */
void GLWidget::rotFL(int flag)
{
    int tmp[8];
    if (way != 1) {
        SHIFT_FACE(2);
        tmp[0] = map[1][2][0];
        tmp[1] = map[1][2][1];
        tmp[2] = map[1][2][2];
        map[1][2][0] = map[0][2][0];
        map[1][2][1] = map[0][2][1];
        map[1][2][2] = map[0][2][2];
        map[0][2][0] = map[4][2][2];
        map[0][2][1] = map[4][2][1];
        map[0][2][2] = map[4][2][0];
        map[4][2][2] = map[5][2][2];
        map[4][2][1] = map[5][2][1];
        map[4][2][0] = map[5][2][0];
        map[5][2][2] = tmp[0];
        map[5][2][1] = tmp[1];
        map[5][2][0] = tmp[2];
    } else {
        DESHIFT_FACE(2);
        tmp[0] = map[5][2][2];
        tmp[1] = map[5][2][1];
        tmp[2] = map[5][2][0];
        map[5][2][2] = map[4][2][2];
        map[5][2][1] = map[4][2][1];
        map[5][2][0] = map[4][2][0];
        map[4][2][2] = map[0][2][0];
        map[4][2][1] = map[0][2][1];
        map[4][2][0] = map[0][2][2];
        map[0][2][0] = map[1][2][0];
        map[0][2][1] = map[1][2][1];
        map[0][2][2] = map[1][2][2];
        map[1][2][0] = tmp[0];
        map[1][2][1] = tmp[1];
        map[1][2][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[18]->rotZ(r);
            A[19]->rotZ(r);
            A[20]->rotZ(r);
            A[21]->rotZ(r);
            A[22]->rotZ(r);
            A[23]->rotZ(r);
            A[24]->rotZ(r);
            A[25]->rotZ(r);
            A[26]->rotZ(r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Y ose.
 */
void GLWidget::rotTL(int flag)
{
    int tmp[8];
    if (way == 1) {
        DESHIFT_FACE(5);
        tmp[0] = map[1][0][0];
        tmp[1] = map[1][1][0];
        tmp[2] = map[1][2][0];
        map[1][0][0] = map[2][2][0];
        map[1][1][0] = map[2][2][1];
        map[1][2][0] = map[2][2][2];
        map[2][2][0] = map[4][2][0];
        map[2][2][1] = map[4][1][0];
        map[2][2][2] = map[4][0][0];
        map[4][2][0] = map[3][2][2];
        map[4][1][0] = map[3][2][1];
        map[4][0][0] = map[3][2][0];
        map[3][2][2] = tmp[0];
        map[3][2][1] = tmp[1];
        map[3][2][0] = tmp[2];
    } else {
        SHIFT_FACE(5);
        tmp[0] = map[3][2][2];
        tmp[1] = map[3][2][1];
        tmp[2] = map[3][2][0];
        map[3][2][2] = map[4][2][0];
        map[3][2][1] = map[4][1][0];
        map[3][2][0] = map[4][0][0];
        map[4][2][0] = map[2][2][0];
        map[4][1][0] = map[2][2][1];
        map[4][0][0] = map[2][2][2];
        map[2][2][0] = map[1][0][0];
        map[2][2][1] = map[1][1][0];
        map[2][2][2] = map[1][2][0];
        map[1][0][0] = tmp[0];
        map[1][1][0] = tmp[1];
        map[1][2][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[6]->rotY(-r);
            A[7]->rotY(-r);
            A[8]->rotY(-r);
            A[15]->rotY(-r);
            A[16]->rotY(-r);
            A[17]->rotY(-r);
            A[24]->rotY(-r);
            A[25]->rotY(-r);
            A[26]->rotY(-r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Y ose.
 */
void GLWidget::rotTR(int flag)
{
    int tmp[8];
    if (way != 1) {
        DESHIFT_FACE(5);
        tmp[0] = map[1][0][0];
        tmp[1] = map[1][1][0];
        tmp[2] = map[1][2][0];
        map[1][0][0] = map[2][2][0];
        map[1][1][0] = map[2][2][1];
        map[1][2][0] = map[2][2][2];
        map[2][2][0] = map[4][2][0];
        map[2][2][1] = map[4][1][0];
        map[2][2][2] = map[4][0][0];
        map[4][2][0] = map[3][2][2];
        map[4][1][0] = map[3][2][1];
        map[4][0][0] = map[3][2][0];
        map[3][2][2] = tmp[0];
        map[3][2][1] = tmp[1];
        map[3][2][0] = tmp[2];
    } else {
        SHIFT_FACE(5);
        tmp[0] = map[3][2][2];
        tmp[1] = map[3][2][1];
        tmp[2] = map[3][2][0];
        map[3][2][2] = map[4][2][0];
        map[3][2][1] = map[4][1][0];
        map[3][2][0] = map[4][0][0];
        map[4][2][0] = map[2][2][0];
        map[4][1][0] = map[2][2][1];
        map[4][0][0] = map[2][2][2];
        map[2][2][0] = map[1][0][0];
        map[2][2][1] = map[1][1][0];
        map[2][2][2] = map[1][2][0];
        map[1][0][0] = tmp[0];
        map[1][1][0] = tmp[1];
        map[1][2][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[6]->rotY(r);
            A[7]->rotY(r);
            A[8]->rotY(r);
            A[15]->rotY(r);
            A[16]->rotY(r);
            A[17]->rotY(r);
            A[24]->rotY(r);
            A[25]->rotY(r);
            A[26]->rotY(r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Y ose.
 */
void GLWidget::rotDL(int flag)
{
    int tmp[8];

    if (way != 1) {
        SHIFT_FACE(0);
        tmp[0] = map[1][2][2];
        tmp[1] = map[1][1][2];
        tmp[2] = map[1][0][2];
        map[1][2][2] = map[3][0][0];
        map[1][1][2] = map[3][0][1];
        map[1][0][2] = map[3][0][2];
        map[3][0][0] = map[4][0][2];
        map[3][0][1] = map[4][1][2];
        map[3][0][2] = map[4][2][2];
        map[4][0][2] = map[2][0][2];
        map[4][1][2] = map[2][0][1];
        map[4][2][2] = map[2][0][0];
        map[2][0][2] = tmp[0];
        map[2][0][1] = tmp[1];
        map[2][0][0] = tmp[2];
    } else {
        DESHIFT_FACE(0);
        tmp[0] = map[2][0][2];
        tmp[1] = map[2][0][1];
        tmp[2] = map[2][0][0];
        map[2][0][2] = map[4][0][2];
        map[2][0][1] = map[4][1][2];
        map[2][0][0] = map[4][2][2];
        map[4][0][2] = map[3][0][0];
        map[4][1][2] = map[3][0][1];
        map[4][2][2] = map[3][0][2];
        map[3][0][0] = map[1][2][2];
        map[3][0][1] = map[1][1][2];
        map[3][0][2] = map[1][0][2];
        map[1][2][2] = tmp[0];
        map[1][1][2] = tmp[1];
        map[1][0][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotY(-r);
            A[1]->rotY(-r);
            A[2]->rotY(-r);
            A[9]->rotY(-r);
            A[10]->rotY(-r);
            A[11]->rotY(-r);
            A[18]->rotY(-r);
            A[19]->rotY(-r);
            A[20]->rotY(-r);
        }

        paintGL();
        resetCube();
    }
}
/*! Realizacija
 * @param tmp je pomocni niz.
 *
 * Zavisnosti od promenljive way mi cemo rotirati na jednu ili drugu stranu.
 * Pomocu SHIFT_FACE / DESHIFT_FACE kada smo rotirali stranu rotiracemo i sve
 * boje na ivici pokreta.
 *
 * @param k je vreme u milisekundama.
 * @param r je ugao za koji se pomera
 * @param fr je frame odnosno koliko ce se pomeriti za delic vremena.
 *
 * U while petlji mi cemo vrsiti updateGL da osvezimo sliku, obnovimo koliko jos
 * vremena nam je ostalo i za to vreme polako pomerati odgovarajuce kockice oko
 * Y ose.
 */
void GLWidget::rotDR(int flag)
{
    int tmp[8];

    if (way == 1) {
        SHIFT_FACE(0);
        tmp[0] = map[1][2][2];
        tmp[1] = map[1][1][2];
        tmp[2] = map[1][0][2];
        map[1][2][2] = map[3][0][0];
        map[1][1][2] = map[3][0][1];
        map[1][0][2] = map[3][0][2];
        map[3][0][0] = map[4][0][2];
        map[3][0][1] = map[4][1][2];
        map[3][0][2] = map[4][2][2];
        map[4][0][2] = map[2][0][2];
        map[4][1][2] = map[2][0][1];
        map[4][2][2] = map[2][0][0];
        map[2][0][2] = tmp[0];
        map[2][0][1] = tmp[1];
        map[2][0][0] = tmp[2];
    } else {
        DESHIFT_FACE(0);
        tmp[0] = map[2][0][2];
        tmp[1] = map[2][0][1];
        tmp[2] = map[2][0][0];
        map[2][0][2] = map[4][0][2];
        map[2][0][1] = map[4][1][2];
        map[2][0][0] = map[4][2][2];
        map[4][0][2] = map[3][0][0];
        map[4][1][2] = map[3][0][1];
        map[4][2][2] = map[3][0][2];
        map[3][0][0] = map[1][2][2];
        map[3][0][1] = map[1][1][2];
        map[3][0][2] = map[1][0][2];
        map[1][2][2] = tmp[0];
        map[1][1][2] = tmp[1];
        map[1][0][2] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotY(r);
            A[1]->rotY(r);
            A[2]->rotY(r);
            A[9]->rotY(r);
            A[10]->rotY(r);
            A[11]->rotY(r);
            A[18]->rotY(r);
            A[19]->rotY(r);
            A[20]->rotY(r);
        }

        resetCube();

        paintGL();
    }
}

void GLWidget::rotBL(int flag)
{
    int tmp[8];
    if (way == 1) {
        DESHIFT_FACE(3);
        tmp[0] = map[1][0][2];
        tmp[1] = map[1][0][1];
        tmp[2] = map[1][0][0];
        map[1][0][2] = map[5][0][0];
        map[1][0][1] = map[5][0][1];
        map[1][0][0] = map[5][0][2];
        map[5][0][0] = map[4][0][0];
        map[5][0][1] = map[4][0][1];
        map[5][0][2] = map[4][0][2];
        map[4][0][0] = map[0][0][2];
        map[4][0][1] = map[0][0][1];
        map[4][0][2] = map[0][0][0];
        map[0][0][2] = tmp[0];
        map[0][0][1] = tmp[1];
        map[0][0][0] = tmp[2];
    } else {
        SHIFT_FACE(3);
        tmp[0] = map[0][0][2];
        tmp[1] = map[0][0][1];
        tmp[2] = map[0][0][0];
        map[0][0][2] = map[4][0][0];
        map[0][0][1] = map[4][0][1];
        map[0][0][0] = map[4][0][2];
        map[4][0][0] = map[5][0][0];
        map[4][0][1] = map[5][0][1];
        map[4][0][2] = map[5][0][2];
        map[5][0][0] = map[1][0][2];
        map[5][0][1] = map[1][0][1];
        map[5][0][2] = map[1][0][0];
        map[1][0][2] = tmp[0];
        map[1][0][1] = tmp[1];
        map[1][0][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotZ(r);
            A[1]->rotZ(r);
            A[2]->rotZ(r);
            A[3]->rotZ(r);
            A[4]->rotZ(r);
            A[5]->rotZ(r);
            A[6]->rotZ(r);
            A[7]->rotZ(r);
            A[8]->rotZ(r);
        }

        paintGL();
        resetCube();
    }
}
void GLWidget::rotBR(int flag)
{
    int tmp[8];
    if (way != 1) {
        DESHIFT_FACE(3);
        tmp[0] = map[1][0][2];
        tmp[1] = map[1][0][1];
        tmp[2] = map[1][0][0];
        map[1][0][2] = map[5][0][0];
        map[1][0][1] = map[5][0][1];
        map[1][0][0] = map[5][0][2];
        map[5][0][0] = map[4][0][0];
        map[5][0][1] = map[4][0][1];
        map[5][0][2] = map[4][0][2];
        map[4][0][0] = map[0][0][2];
        map[4][0][1] = map[0][0][1];
        map[4][0][2] = map[0][0][0];
        map[0][0][2] = tmp[0];
        map[0][0][1] = tmp[1];
        map[0][0][0] = tmp[2];
    } else {
        SHIFT_FACE(3);
        tmp[0] = map[0][0][2];
        tmp[1] = map[0][0][1];
        tmp[2] = map[0][0][0];
        map[0][0][2] = map[4][0][0];
        map[0][0][1] = map[4][0][1];
        map[0][0][0] = map[4][0][2];
        map[4][0][0] = map[5][0][0];
        map[4][0][1] = map[5][0][1];
        map[4][0][2] = map[5][0][2];
        map[5][0][0] = map[1][0][2];
        map[5][0][1] = map[1][0][1];
        map[5][0][2] = map[1][0][0];
        map[1][0][2] = tmp[0];
        map[1][0][1] = tmp[1];
        map[1][0][0] = tmp[2];
    }
    if (flag == 0) {
        int k;
        float fr;
        QElapsedTimer time;

        k = 0;
        fr = 0;
        while (k < 90) {
            int r;
            time.start();
            paintGL();
            fr += (time.elapsed() * 90.) / DT;
            r = fr;
            fr -= r;
            if (k + r > 90)
                r = 90 - k;
            k = k + r;
            if (way == 0)
                r = -r;
            A[0]->rotZ(-r);
            A[1]->rotZ(-r);
            A[2]->rotZ(-r);
            A[3]->rotZ(-r);
            A[4]->rotZ(-r);
            A[5]->rotZ(-r);
            A[6]->rotZ(-r);
            A[7]->rotZ(-r);
            A[8]->rotZ(-r);
        }
        paintGL();
        resetCube();
    }
}

/*! Realizacija
 * @param number je broj ukupnih pokreta. Postavljen nadeset
 * @param n je Broj nasumicnih potez, postavljen na 15
 * @param valueR nasumicna vrednost u opsegu [0-9]
 * @param DT postavimo na  100, da ubrzamo pokrete, posle izvrsenja funkcije
 * vracamo na 500.
 *
 * U for petlji biramo nasumicno jedan broj kojim je definisan jedan pokret
 * valueR to pomocu switch odredujemo koji pokret hocemo pa izvrsimo taj pokret
 * i ponovimo petlju.
 */
void GLWidget::RandomCube()
{
    DT = 100;
    int number = 10;
    int n = 15;

    for (int i = 0; i < n; i++) {
        int valueR = rand() % number;

        switch (valueR) {
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
void GLWidget::make_random_cube()
{
    RandomCube();
    Buffer.pushBuffer('Q');
}

/*! Realizacija
 * @param k brojac
 * @param DT koji postavimo na 100 da bi ubrzali posle izvrsenja funkcije
 * vracamo na 500.
 *
 * Da bi vratili kocku u poziciju za novu igru  mi zemo prati poteze na bufferu
 * i vratiti se pokretima unazad sve dok nam buffer nije prazan. Ukoliko imamo
 * vrednost koja nije jedan od pokreta na bufferu nju cemo samo skinuti, i
 * ignorisati. Moramo da obratimo paznju na promenljivu way dok radimo.
 */
void GLWidget::new_game()
{
    DT = 100;
    for (;;) {
        int k = Buffer.popBuffer();
        if (k > 0)
            way = 0;
        else
            way = 1;
        if (k < 0)
            k = -k;
        switch (k) {
        case 'R':
            rotTL();
            break;
        case 'D':
            rotLU();
            break;
        case 'C':
            rotDL();
            break;
        case 'F':
            rotLD();
            break;
        case 'G':
            rotFL();
            break;
        case 'H':
            rotFR();
            break;
        case 'I':
            rotTR();
            break;
        case 'J':
            rotRD();
            break;
        case 'K':
            rotRU();
            break;
        case 'M':
            rotDR();
            break;
        case 'T':
            rotBL();
            break;
        case 'U':
            rotBR();
            break;
        }
        if (k == 0)
            break;
    }
    DT = 500;
    way = 1;
}

int duzinaResenja = 0;

void GLWidget::Solver()
{
    char resenje[300];
    DT = 300;

    int i = 0;

    for (;;) {
        int k = Buffer.popBuffer();
        if (k > 0)
            way = 0;
        else
            way = 1;
        if (k < 0)
            k = -k;
        switch (k) {
        case 'R':
            rotTL();
            resenje[i] = 'T';
            resenje[i + 1] = 'L';
            resenje[i + 2] = ' ';
            break;
        case 'D':
            rotLU();
            resenje[i] = 'L';
            resenje[i + 1] = 'U';
            resenje[i + 2] = ' ';
            break;
        case 'C':
            rotDL();
            resenje[i] = 'D';
            resenje[i + 1] = 'L';
            resenje[i + 2] = ' ';
            break;
        case 'F':
            rotLD();
            resenje[i] = 'L';
            resenje[i + 1] = 'D';
            resenje[i + 2] = ' ';
            break;
        case 'G':
            rotFL();
            resenje[i] = 'F';
            resenje[i + 1] = 'L';
            resenje[i + 2] = ' ';
            break;
        case 'H':
            rotFR();
            resenje[i] = 'F';
            resenje[i + 1] = 'R';
            resenje[i + 2] = ' ';
            break;
        case 'I':
            rotTR();
            resenje[i] = 'T';
            resenje[i + 1] = 'R';
            resenje[i + 2] = ' ';
            break;
        case 'J':
            rotRD();
            resenje[i] = 'R';
            resenje[i + 1] = 'D';
            resenje[i + 2] = ' ';
            break;
        case 'K':
            rotRU();
            resenje[i] = 'R';
            resenje[i + 1] = 'U';
            resenje[i + 2] = ' ';
            break;
        case 'M':
            rotDR();
            resenje[i] = 'D';
            resenje[i + 1] = 'R';
            resenje[i + 2] = ' ';
            break;
        case 'T':
            rotBL();
            resenje[i] = 'B';
            resenje[i + 1] = 'L';
            resenje[i + 2] = ' ';
            break;
        case 'U':
            rotBR();
            resenje[i] = 'B';
            resenje[i + 1] = 'R';
            resenje[i + 2] = ' ';
            break;
        }
        if (k == 0)
            break;
        i = i + 3;
    }
    duzinaResenja = i;
    DT = 500;
    way = 1;

    qInfo("%s", resenje);
}

/*! Realizacija
 * Pozovemo  SolveSimple i na buffer pushujemo P.
 */
void GLWidget::solve_it()
{
    Solver();
    Buffer.pushBuffer('P');
}

/*! Realizacija
 * Pozovemo resetCube
 */
GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
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
    for (k = 0; k < 27; k++) {
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

/*! Realizacija
 * Redefinicija ugradjene funkcije , nasledjene iz klase QGLWidget
 * Sluze za spremanje prostora za widget, iscrtavanje kocke.
 * Nijanse boja, osvetljenje, materijal kocke itd.
 */
void GLWidget::initializeGL()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
    GLfloat mat_shininess[] = { 30.0 };
    // izmenjeno {0, 0, 1, 0}
    GLfloat light_position[] = { 1, 0, 0, 1 };
    glClearColor(1, 1, 1, 0);
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

    glTranslated(0.0, 0.0, -7);
    glEnable(GL_CULL_FACE);
}
/*! Realizacija
 * Poziva svaki put kad treba opet biti iscrtana.
 * i kreira se objekat pozivom makeObject().
 */
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeObject();
}

/*! Realizacija
 *
 * Vrsi se promena velicine pomocu glVieport.
 * isto je virtualna funkcija iz klase QGLWidget.
 */
void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ORTHOFRUSTRUM;
    glMatrixMode(GL_MODELVIEW);
    lastPos = QCursor::pos();
}

/*! Realizacija
 * @param lastPos je poslednja pozicija misa prilikom nekog dogadjaja.
 * Stavlja fokus, izcitava poziciju misa.
 */
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if (event->buttons() & Qt::RightButton) {
        GLint viewport[4];
        int x = lastPos.x();
        int y = lastPos.y();

        glGetIntegerv(GL_VIEWPORT, viewport);
        unsigned int buffer[1000];

        glSelectBuffer(1000, buffer);
        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(100);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        glLoadIdentity();

        gluPickMatrix(x, viewport[3] + 2 * viewport[1] - y, 3, 3,
                  viewport);
        ORTHOFRUSTRUM;

        paintGL();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
}
/*! Realizacija
 * @param dx,dy za koliko se mis pomerio u odnosu na poslednju poziciju.
 * I vrsi pomeranje kocke u odnosu na vektor pomeraj misa.
 */
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->position().x() - lastPos.x();
    int dy = event->position().y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        GLfloat pmat[16];

        glMatrixMode(GL_MODELVIEW);
        glGetFloatv(GL_MODELVIEW_MATRIX, pmat);
        glLoadIdentity();

        glRotatef(dy, 1, 0, 0);
        glRotatef(dx, 0, 1, 0);
        glMultMatrixf(pmat);
        glGetFloatv(GL_MODELVIEW_MATRIX, pmat);
        pmat[12] = 0;
        pmat[13] = 0;
        pmat[14] = -7;
        glLoadMatrixf(pmat);

        paintGL();
    }
    lastPos = event->pos();
}

/*! Realizacija
 * @param render_mode provera da li je kocka vec prikazana i ako nije iscrta je.
 */

auto GLWidget::makeObject() -> GLuint
{
    int render_mode;
    glGetIntegerv(GL_RENDER_MODE, &render_mode);

    if (render_mode == GL_SELECT) {
        float a = R + S * .5;

        glLoadName(1);
        glBegin(GL_QUADS);
        glVertex3f(-a, -a, -a);
        glVertex3f(a, -a, -a);
        glVertex3f(a, -a, a);
        glVertex3f(-a, -a, a);
        glEnd();

        glLoadName(2);
        glBegin(GL_QUADS);
        glVertex3f(-a, -a, -a);
        glVertex3f(-a, -a, a);
        glVertex3f(-a, a, a);
        glVertex3f(-a, a, -a);
        glEnd();

        glLoadName(3);
        glBegin(GL_QUADS);
        glVertex3f(-a, -a, a);
        glVertex3f(a, -a, a);
        glVertex3f(a, a, a);
        glVertex3f(-a, a, a);
        glEnd();

        glLoadName(4);
        glBegin(GL_QUADS);
        glVertex3f(-a, -a, -a);
        glVertex3f(-a, a, -a);
        glVertex3f(a, a, -a);
        glVertex3f(a, -a, -a);
        glEnd();

        glLoadName(5);
        glBegin(GL_QUADS);
        glVertex3f(a, -a, -a);
        glVertex3f(a, a, -a);
        glVertex3f(a, a, a);
        glVertex3f(a, -a, a);
        glEnd();

        glLoadName(6);
        glBegin(GL_QUADS);
        glVertex3f(-a, a, -a);
        glVertex3f(-a, a, a);
        glVertex3f(a, a, a);
        glVertex3f(a, a, -a);
        glEnd();

    } else {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        int k;

        for (k = 0; k < 27; k++) {
            if (A[k])
                A[k]->drawCube();
        }

        glDisable(GL_LIGHTING);

        glColor3f(0, 0, 0);
        for (k = 0; k < 27; k++) {
            if (A[k])
                A[k]->drawWireCube();
        }

        glBegin(GL_LINES);
        glLineWidth(20);

        // iscrtavanje linija rotacije: vrtex-odakle polazi linija
        glColor3f(1, .5, .5);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glColor3f(.5, 1, .5);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        glColor3f(.5, .5, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
        glEnd();
    }
    return 0;
}
/*! Implementacija algoritma za six spots*/
void GLWidget::spots_ptn()
{
    rotTL();
    Buffer.pushBuffer('R');
    rotDL();
    Buffer.pushBuffer('C');
    rotRU();
    Buffer.pushBuffer('K');
    rotLU();
    Buffer.pushBuffer('D');
    rotFR();
    Buffer.pushBuffer('H');
    rotBR();
    Buffer.pushBuffer('U');
    rotTL();
    Buffer.pushBuffer('R');
    rotDL();
    Buffer.pushBuffer('C');
}
/*! Implementacija algoritma za Cross*/
void GLWidget::cross_ptn()
{
    rotTL();
    Buffer.pushBuffer('R');
    rotFR();
    Buffer.pushBuffer('H');
    rotBR();
    Buffer.pushBuffer('U');
    rotLD();
    Buffer.pushBuffer('F');
    rotLD();
    Buffer.pushBuffer('F');
    rotTL();
    Buffer.pushBuffer('R');
    rotTL();
    Buffer.pushBuffer('R');
    rotLD();
    Buffer.pushBuffer('F');
    rotLD();
    Buffer.pushBuffer('F');
    rotFL();
    Buffer.pushBuffer('G');
    rotBL();
    Buffer.pushBuffer('T');
    rotTL();
    Buffer.pushBuffer('R');
    rotTL();
    Buffer.pushBuffer('R');
    rotLD();
    Buffer.pushBuffer('F');
    rotLD();
    Buffer.pushBuffer('F');
    rotTL();
    Buffer.pushBuffer('R');
}
/*! Implementacija algoritma God's number*/
void GLWidget::god_ptn()
{
    rotRU();
    Buffer.pushBuffer('K');
    rotLD();
    Buffer.pushBuffer('F');
    rotTL();
    Buffer.pushBuffer('R');
    rotTL();
    Buffer.pushBuffer('R');
    rotFR();
    Buffer.pushBuffer('H');
    rotTR();
    Buffer.pushBuffer('I');
    rotDR();
    Buffer.pushBuffer('M');
    rotFR();
    Buffer.pushBuffer('H');
    rotFR();
    Buffer.pushBuffer('H');
    rotRU();
    Buffer.pushBuffer('K');
    rotRU();
    Buffer.pushBuffer('K');
    rotBL();
    Buffer.pushBuffer('T');
    rotBL();
    Buffer.pushBuffer('T');
    rotLD();
    Buffer.pushBuffer('F');
    rotTL();
    Buffer.pushBuffer('R');
    rotTL();
    Buffer.pushBuffer('R');
    rotFL();
    Buffer.pushBuffer('G');
    rotBR();
    Buffer.pushBuffer('U');
    rotTL();
    Buffer.pushBuffer('R');
    rotRU();
    Buffer.pushBuffer('K');
    rotRU();
    Buffer.pushBuffer('K');
    rotDR();
    Buffer.pushBuffer('M');
    rotFR();
    Buffer.pushBuffer('H');
    rotFR();
    Buffer.pushBuffer('H');
    rotTL();
    Buffer.pushBuffer('R');
    rotRU();
    Buffer.pushBuffer('K');
    rotRU();
    Buffer.pushBuffer('K');
    rotTL();
    Buffer.pushBuffer('R');
}
/*! Implementacija algoritma checkerboard*/
void GLWidget::checker_ptn()
{
    rotFR();
    Buffer.pushBuffer('H');
    rotBL();
    Buffer.pushBuffer('T');
    rotBL();
    Buffer.pushBuffer('T');
    rotRD();
    Buffer.pushBuffer('J');
    rotDR();
    Buffer.pushBuffer('M');
    rotDR();
    Buffer.pushBuffer('M');
    rotBL();
    Buffer.pushBuffer('T');
    rotRU();
    Buffer.pushBuffer('K');
    rotTL();
    Buffer.pushBuffer('R');
    rotDL();
    Buffer.pushBuffer('C');
    rotRU();
    Buffer.pushBuffer('K');
    rotLU();
    Buffer.pushBuffer('D');
    rotDL();
    Buffer.pushBuffer('C');
    rotFL();
    Buffer.pushBuffer('G');
    rotRU();
    Buffer.pushBuffer('K');
    rotRU();
    Buffer.pushBuffer('K');
    rotDR();
    Buffer.pushBuffer('M');
    rotFR();
    Buffer.pushBuffer('H');
    rotFR();
    Buffer.pushBuffer('H');
    rotBR();
    Buffer.pushBuffer('U');
}
/*! Implementacija algoritma cube in cube in cube*/
void GLWidget::cube_in_cube_ptn()
{
    rotTR();
    Buffer.pushBuffer('I');
    rotLU();
    Buffer.pushBuffer('D');
    rotTR();
    Buffer.pushBuffer('I');
    rotFL();
    Buffer.pushBuffer('G');
    rotRU();
    Buffer.pushBuffer('K');
    rotRU();
    Buffer.pushBuffer('K');
    rotBR();
    Buffer.pushBuffer('U');
    rotRU();
    Buffer.pushBuffer('K');
    rotFR();
    Buffer.pushBuffer('H');
    rotTL();
    Buffer.pushBuffer('R');
    rotBL();
    Buffer.pushBuffer('T');
    rotBL();
    Buffer.pushBuffer('T');
    rotTL();
    Buffer.pushBuffer('R');
    rotBR();
    Buffer.pushBuffer('U');
    rotLD();
    Buffer.pushBuffer('F');
    rotTR();
    Buffer.pushBuffer('I');
    rotFR();
    Buffer.pushBuffer('H');
    rotTL();
    Buffer.pushBuffer('R');
    rotRU();
    Buffer.pushBuffer('K');
    rotFL();
    Buffer.pushBuffer('G');
}
