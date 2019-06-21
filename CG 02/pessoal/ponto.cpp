#include "pessoal/ponto.h"

Ponto::Ponto(){

}

void Ponto::desenha(){
    glPushMatrix();
        glTranslated(tx,ty,tz);
        glRotated(0,0,0,1);
        glRotated(0,0,1,0);
        glRotated(0,1,0,0);
        glScaled(1, 1, 1);

        glTranslated(0.5,0.5,0.5);
        //Desenha::drawBox(-0.2,-0.2,-0.2,0.2,0.2,0.2);
        glutSolidSphere(0.5,100,100);
    glPopMatrix();
}

Vetor3D Ponto::getCoordenadas(){
    return Vetor3D(tx, ty, tz);
}
