/*! \file pokreti.cpp
 *  \brief Implementacija pokreti.h
 *  ??? ??? ???
 */
#include "mainwindow.h"
#include "pokreti.h"
#include "rubik.h"
#include "cube.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QTime>


int tmp[8]; /*!< Pomocni niz*/

/*!
 *  Definise pomeranje nalicija ??? nalevo ???
 */
#define SHIFT_FACE(a_)\
tmp[0]=map[a_][2][2]; tmp[1]=map[a_][1][2];\
tmp[2]=map[a_][0][2]; tmp[3]=map[a_][0][1];\
tmp[4]=map[a_][0][0]; tmp[5]=map[a_][1][0];\
tmp[6]=map[a_][2][0]; tmp[7]=map[a_][2][1];\
map[a_][2][2]=tmp[6]; map[a_][1][2]=tmp[7];\
map[a_][0][2]=tmp[0]; map[a_][0][1]=tmp[1];\
map[a_][0][0]=tmp[2]; map[a_][1][0]=tmp[3];\
map[a_][2][0]=tmp[4]; map[a_][2][1]=tmp[5];

/*!
 * Definise pomeranje nalicija ??? nadesno ???
 */
#define DESHIFT_FACE(a_)\
tmp[6]=map[a_][2][2]; tmp[7]=map[a_][1][2];\
tmp[0]=map[a_][0][2]; tmp[1]=map[a_][0][1];\
tmp[2]=map[a_][0][0]; tmp[3]=map[a_][1][0];\
tmp[4]=map[a_][2][0]; tmp[5]=map[a_][2][1];\
map[a_][2][2]=tmp[0]; map[a_][1][2]=tmp[1];\
map[a_][0][2]=tmp[2]; map[a_][0][1]=tmp[3];\
map[a_][0][0]=tmp[4]; map[a_][1][0]=tmp[5];\
map[a_][2][0]=tmp[6]; map[a_][2][1]=tmp[7];

void  MoveWidget::rotLD(int & way,int(&map)[6][3][3], float & DT ,  Cube *A[] )
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
void MoveWidget::rotLU(int & way,int(&map)[6][3][3], float & DT,  Cube *A[] )
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
void  MoveWidget::rotRD(int & way, int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotRU(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotFR(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotFL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotTL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotTR(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void  MoveWidget::rotDL(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
void MoveWidget::rotDR(int & way,int(&map)[6][3][3], float & DT,  Cube *A[])
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
