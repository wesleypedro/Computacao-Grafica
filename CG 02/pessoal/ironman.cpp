#include "ironman.h"

ironman::ironman()
{
    model = new Model3DS("../3ds/ironman.3DS");
}

void ironman::desenha(){
    glPushMatrix();
        Objeto::desenha();

        glScalef(0.05,0.05,0.05);
        glRotated(20,1,0,0);

        model->draw();
    glPopMatrix();
}
