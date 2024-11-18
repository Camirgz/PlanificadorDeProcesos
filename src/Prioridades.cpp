#include "Prioridades.h"

void Prioridades::ejecutar(Proceso* cabeza) {

    // Verificar si hay procesos cargados
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    // Ordenar los procesos por prioridad
    for (Proceso* actual = cabeza; actual != nullptr; actual = actual->siguiente) {
        for (Proceso* siguiente = actual->siguiente; siguiente != nullptr; siguiente = siguiente->siguiente) {
            if (actual->prioridad > siguiente->prioridad) {
                std::swap(actual->nombre, siguiente->nombre);
                std::swap(actual->prioridad, siguiente->prioridad);
                std::swap(actual->instrucciones, siguiente->instrucciones);
            }
        }
    }

    // Ejecutar los procesos en orden
    Proceso* actual = cabeza;
    std::cout << "Ejecutando procesos en orden de prioridad...\n";
    while (actual) {
        std::cout << "Ejecutando proceso: " << actual->nombre << " (Prioridad: " << actual->prioridad << ")\n";

        std::string instruccion;

        // Ejecutar las instrucciones del proceso
        for (size_t i = 0; i < actual->instrucciones.size(); i++) {
            if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                    instruccion += actual->instrucciones[i];
                }
                std::cout << "Ejecutando: " << instruccion << "\n";

                if (instruccion == "e/s") {
                    std::cout << "Simulando operación de entrada/salida (3 ciclos)...\n";
                    sleep(3);
                } else {
                    std::cout << "Simulando instrucción normal (1 ciclo)...\n";
                    sleep(1);
                }
                instruccion.clear();
            } else {
                instruccion += actual->instrucciones[i];
            }
        }
        actual = actual->siguiente;
    }

    std::cout << "Todos los procesos han sido ejecutados en orden de prioridad.\n";
}