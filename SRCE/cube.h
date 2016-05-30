/*! \file cube.h
 *  \brief Classa Cube
 *
 *  Metoda ResetCube
 *  U klasi cube se nalaze metode za crtanje rubikove kocke, pomeranje oko osa,
 *  kao i sam prokaz rubikove kocke.
 *
 */

#ifndef CUBE_H
#define CUBE_H


class Cube
 {
 public:
     float coords[8][3]; /*!< Koordinate kocke*/
     float norm[6][3]; /*!<  ??? ??? ???*/
     int colors[6]; /*!< Nasih sest boja kocki*/

     /*! \brief kreiraj rubikovu kocku
      *
      * @param[in] x0,y0,z0 Postavljane koordinata
      * @param[in] b velicina jedne kockice
      * @param[in] r1,r2,r3,r4,r5,r6 sest boja
      */
     Cube(float x0,float y0,float z0,float b,int r1,int r2,int r3,int r4,int r5,int r6);


     /*! \brief Pomeri rubikovu kocku
      *
      * @param[in] dx,dy,dz Zakoliko se pomera nasa rubikova kocka u odnosu na x,z,y osu
      *
      */
     void move(float dx,float dy,float dz);

     /*! \brief Izrtaj Rubikovu kocku
      *
      */
     void drawCube();

     /*! \brief Nacrtaj 3D mrezu Rubikove kocke
      */
     void drawWireCube();

    /*! \brief Rotiraj oko X ose*/
     void rotX(int angle);
   /*! \brief Rotiraj oko Y ose*/
     void rotY(int angle);
   /*! \brief Rotiraj oko Z ose*/
     void rotZ(int angle);

 };
/*! \brief Resetuj Rubikovu kocku*/
void resetCube();

#endif // CUBE_H
