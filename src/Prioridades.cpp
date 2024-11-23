#include "Prioridades.h"


void Prioridades::ejecutar(Proceso* cabeza) {
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

    const int quantum = 3; // Definir el quantum
    Proceso* actual = cabeza;

    std::cout << "Ejecutando procesos en orden de prioridad...\n";
    imprimirEstados(cabeza); // Estados iniciales

    size_t i = 0;
    bool nombreProceso = true;
    bool instruccionesPendientes = true;

    while (actual != nullptr) {
        std::string instruccion;
        size_t ciclos = 0;
        instruccionesPendientes = true;

        if (nombreProceso) {
            actual->estado = "En ejecución: Activo";
            imprimirEstados(cabeza); // Estado antes de ejecutar
            std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n\n" << RESET;
            nombreProceso = false;
        }

        while (instruccionesPendientes && actual != nullptr) {
            if (i < actual->instrucciones.size()) {
                if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                    if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                        instruccion += actual->instrucciones[i];
                    }

                    if (instruccion.find("fin proceso") != std::string::npos) {
                        instruccionesPendientes = false;
                        nombreProceso = true;
                        i++;
                        break;
                    }

                    if (instruccion.find("e/s") != std::string::npos) {
                        actual->estado = "Bloqueado por E/S";
                        imprimirEstados(cabeza); // Estado bloqueado
                        std::cout << AMARILLO << "Proceso " << actual->nombre << " bloqueado por E/S.\n" << RESET;
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        sleep(3);
                        i += 2;
                        instruccion.clear();
                        instruccion = " ";
                        break;
                    } else {
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n" << RESET;
                        sleep(1);
                    }

                    instruccion.clear();
                    ciclos++;
                    i++;
                    if (ciclos == quantum) {
                        actual->estado = "Listo";
                        imprimirEstados(cabeza); // Quantum agotado
                        std::cout << ROJO << "Quantum agotado. Proceso " << actual->nombre << " cortado.\n" << RESET;
                        break;
                    }
                } else {
                    instruccion += actual->instrucciones[i];
                    i++;
                }
            } else {
                instruccionesPendientes = false;
            }
        }

        if (!instruccionesPendientes) {
            actual->estado = "Finalizado";
            imprimirEstados(cabeza); // Proceso finalizado
            std::cout << VERDE << "\nProceso " << actual->nombre << " finalizado.\n" << RESET;
            actual = actual->siguiente;
            i = 0;
            instruccionesPendientes = true;
            nombreProceso = true;
            ciclos = 0;
        }
    }

    std::cout << "\nTodos los procesos han sido ejecutados en orden de prioridad.\n";
}
