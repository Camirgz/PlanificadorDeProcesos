#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Algoritmo.h"
#include <iostream>

class RoundRobin : public Algoritmo { // Clase Algoritmo hereda a RoundRobin

// Atributos
private:
    int quantum;

public:
    // Constructor
    RoundRobin(int quantum_) : quantum(quantum_) {}

    // Método polimórfico
    void ejecutar(Proceso* cabeza) override;
    
};

#endif 
