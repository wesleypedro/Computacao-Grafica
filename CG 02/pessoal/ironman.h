#ifndef IRONMAN_H
#define IRONMAN_H

#include <objeto.h>

class ironman : public Objeto
{
public:
    Model3DS* model;
public:
    ironman();
    void desenha();
};

#endif // IRONMAN_H
