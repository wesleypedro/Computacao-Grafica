#include "caminho.h"

Caminho::Caminho()
{

}

void Caminho::desenha(){
    glColor3f(0,1,1);
    glPushMatrix();
        glTranslatef(0,0,0);
//        GUI::drawBox(-1,-1,-1, 1,1,1);
        GUI::drawBox(-0.1,-0.5,-0.1, 0.1,0.5,0.1);
    glPopMatrix();
}
