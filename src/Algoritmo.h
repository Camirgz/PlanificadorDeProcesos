#ifndef ALGORITMO_H
#define ALGORITMO_H

#define MAGENTA "\033[35m"
#define ROJO "\033[31m"
#define AMARILLO "\033[33m"
#define VERDE "\033[32m"
#define CYAN "\033[36m"
#define AZUL "\033[34m"
#define RESET "\033[0m"


#include "Proceso.h"

class Algoritmo {

public:
    // Método virtual puro
    virtual void ejecutar(Proceso* cabeza) = 0; // Método polimórfico
    virtual ~Algoritmo() = default;
};

#endif 
