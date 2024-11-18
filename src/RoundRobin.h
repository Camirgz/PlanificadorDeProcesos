#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Algoritmo.h"
#include <iostream>

class RoundRobin : public Algoritmo {
private:
    int quantum;

public:
    RoundRobin(int quantum_) : quantum(quantum_) {}
    void ejecutar(Proceso* cabeza) override;
};

#endif // ROUND_ROBIN_H
