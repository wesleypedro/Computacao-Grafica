#ifndef PONTO_H
#define PONTO_H
#include <pessoal/objeto.h>
#include <bib/Vetor3D.h>
#include <GL/glut.h>

class Ponto
{
public:
    float tx = 0.0;
    float ty = 0.0; // coordenadas Translação
    float tz = 0.0;

    Ponto();

    void desenha();
    Vetor3D getCoordenadas();
};

#endif // PONTO_H
