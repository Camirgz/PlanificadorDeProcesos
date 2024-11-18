#ifndef PRIORIDADES_H
#define PRIORIDADES_H

#include "Algoritmo.h"
#include <iostream>
#include <unistd.h>

class Prioridades : public Algoritmo {
public:
    void ejecutar(Proceso* cabeza) override;
};

#endif // PRIORIDADES_H
