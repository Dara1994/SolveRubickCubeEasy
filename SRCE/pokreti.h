/*! \file pokreti.h
 * \brief Moguci pokreti rubikove kocke
 *
 * Ovde imamo Kontejner klasu MoveWidget koja nasleduje od QGLWidget ??? ??? ???
 * za nase pokrete, koja sadrzi metode za iste.
 * Moguci pokreti su:
 * LU - left side up /levu kolonu nagore
 * LD - left side down /levu kolonu nadole
 * RU - right side up /desnu kolonu nagore
 * RD - right side down /desnu kolonu nadole
 * FR - front face right / nalicje rotiraj nadesno
 * FL - front face left / nalicije rotiraj nalevo
 * TL - top row left /gorni red nalevo
 * TR - top row right /gornji red nadesno
 * DL - down row left /donji red nalevo
 * DR - down row rigth /donji red nadesno
 *
 * Imamo konstruktor i destruktor nasledjeni od roditeljske klase.
 */

#ifndef POKRETI_H
#define POKRETI_H
#include "cube.h"
#include "mainwindow.h"
#include <QGLWidget>
#include <QMouseEvent>

class MoveWidget : public QGLWidget
{
    Q_OBJECT

public:
    MoveWidget(QWidget *parent = 0);
    ~MoveWidget();
/*! \brief  LD - left side down /levu kolonu nadole
 * @param[in] way smer okreta
 * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
 * @param[in] DT ??? ??? ???
 * @param[in] A pripada klasi Cube,nasa rubikova kocka
*/
    void rotLD(int & way,int (&map)[6][3][3], float & DT,  Cube *A[] );


    /*! \brief  LU - left side up /levu kolonu nagore
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotLU(int &way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief   RD - right side down /desnu kolonu nadole
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotRD(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief   RU - right side up /desnu kolonu nagore
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotRU(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief   FR - front face right /nalicije rotiraj nadesno
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void  rotFR(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief   TL - top row left /gornji red nalevo
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void  rotTL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief  TL - top row rigth /gornji red nadesno
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void  rotTR(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief  DL - down row left /donji red nalevo
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotDL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief  DR - down row right /donji red nadesno
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotDR(int & way, int(&map)[6][3][3], float & DT,  Cube *A[]);

    /*! \brief  front face left / nalicije rotiraj nalevo
     * @param[in] way smer okreta
     * @param[in] map mapa trenutnog rasporeda boja nase rubikove kocke
     * @param[in] DT ??? ??? ???
     * @param[in] A pripada klasi Cube,nasa rubikova kocka
    */
    void rotFL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[]);

};

#endif
