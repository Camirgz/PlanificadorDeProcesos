#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "Proceso.h"

class Algoritmo {

public:
    // Método virtual puro
    virtual void ejecutar(Proceso* cabeza) = 0; // Método polimórfico
    virtual ~Algoritmo() = default;
};

#endif 