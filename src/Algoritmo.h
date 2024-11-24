#ifndef ALGORITMO_H
#define ALGORITMO_H

#define MAGENTA "\033[35m"
#define ROJO "\033[31m"
#define AMARILLO "\033[33m"
#define VERDE "\033[32m"
#define CYAN "\033[36m"
#define AZUL "\033[34m"
#define RESET "\033[0m"


#include <iostream>
#include "Proceso.h"

class Algoritmo {

public:
    // Método virtual puro
    /**
     * @brief metodo virtual puro que ejecuta el algoritmo
     * 
     * @param cabeza 
     */
    virtual void ejecutar(Proceso* cabeza) = 0; // Método polimórfico

    /**
     * @brief Destroy the Algoritmo object
     * 
     */
    virtual ~Algoritmo() = default;

    /**
     * @brief metodo que imprime los estados de los procesos
     * 
     * @param cabeza 
     */
    void imprimirEstados(Proceso* cabeza) {
    Proceso* actual = cabeza;
    std::cout << "\n=== Estado actual de los procesos: ===\n";
    while (actual) {
        std::cout << "Proceso: " << actual->nombre << " (Prioridad: " << actual->prioridad << ") (Estado: ";
        if (actual->estado == "Listo") {
            std::cout << AZUL << actual->estado << RESET;
        } else if (actual->estado == "Finalizado") {
            std::cout << VERDE << actual->estado << RESET;
        } else if (actual->estado == "Bloqueado por E/S") {
            std::cout << AMARILLO << actual->estado << RESET;
        } else if (actual->estado == "En ejecución: Activo") {
            std::cout << MAGENTA << actual->estado << RESET;
        } else {
            std::cout << actual->estado; // Sin color para otros estados
        }
        std::cout << ")\n";
        actual = actual->siguiente;
    }
}
};

#endif 
