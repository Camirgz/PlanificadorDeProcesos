#ifndef PRIORIDADES_H
#define PRIORIDADES_H

#include "Algoritmo.h"
#include <iostream>
#include <unistd.h>

class Prioridades : public Algoritmo { // Clase Algoritmo hereda a Prioridades

public:

    // Método polimórfico
    void ejecutar(Proceso* cabeza) override;
    
};

#endif 