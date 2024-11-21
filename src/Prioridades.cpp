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

    const int quantum = 3; // Definir el quantum (en ciclos)
    Proceso* actual = cabeza;
    // int cont_e_s = 0;
    std::cout << "Ejecutando procesos en orden de prioridad..." << std::endl;
    // Variables para el control
    size_t i = 0;
    bool nombreProceso = true;
    bool instruccionesPendientes = true;

    while (actual != nullptr) {

        std::string instruccion;
        size_t ciclos = 0;
        instruccionesPendientes = true;

        if (nombreProceso) {

            std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n\n" << RESET;
            nombreProceso = false;
        }

        // Ejecutar instrucciones del proceso actual
        while (instruccionesPendientes && actual != nullptr) {
            // Ejecutar hasta que no haya más instrucciones o se agote el quantum
            if (i < actual->instrucciones.size()) {
                // Si encontramos un salto de línea o es la última instrucción
                if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                    if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                        instruccion += actual->instrucciones[i];
                    }
                    
                    if(instruccion.find("fin proceso") != std::string::npos){
                        instruccionesPendientes = false;
                        nombreProceso = true;
                        i++;
                        break;
                    }

                    // Verificar el tipo de instrucción
                    if (instruccion.find("e/s") != std::string::npos) {
                        // cont_e_s++;
                        // std::cout << AZUL << "Simulando operación de entrada/salida (3 ciclos)...\n" << RESET;
                        
                        std::cout << AMARILLO << "Proceso " << actual->nombre << " bloqueado por E/S.\n" << RESET;
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        
                        
                        sleep(3);
                        // saltar al que sigue ya que hay 2 e/s seguidos, solo se ejecuta 1 el otro se supone que desbloquea al proceso
                        i+=2;
                        instruccion.clear();
                        instruccion=" ";
                        break; // Proceso pasa a bloqueado
                    } else {
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n" << RESET;
                        sleep(1);
                    }

                    instruccion.clear();
                    ciclos++;
                     i++; // Avanzar al siguiente carácter/instrucción
                    if (ciclos == quantum) { // Se cumple el quantum
                        if (i >= actual->instrucciones.size()) {
                            nombreProceso = true; // Marcar que el proceso ha terminado
                        } else {
                            std::cout << ROJO << "Quantum agotado. Proceso " << actual->nombre << " cortado.\n" << RESET;
                        }
                        break; // Salimos del bucle para reprogramar
                    }

                    
                   
                } else {
                    instruccion += actual->instrucciones[i];
                    i++; // Continuar procesando la instrucción
                }
            } else {
                // Si ya no hay más instrucciones, pasamos al siguiente proceso
                instruccionesPendientes = false; // Marcar que no hay más instrucciones pendientes
            }
        }

        // Si el proceso ha terminado (todas las instrucciones ejecutadas), pasamos al siguiente
        if (!instruccionesPendientes) {
             cout << VERDE << "\nProceso " << actual->nombre << " finalizado.\n" << RESET;
            actual = actual->siguiente; // Cambiar al siguiente proceso
            i = 0; // Reiniciar el índice para el próximo proceso
            instruccionesPendientes = true; // Marcar que el nuevo proceso tiene instrucciones pendientes
            nombreProceso = true;  // Aquí se debe poner en true al cambiar de proceso
            ciclos = 0; // Reiniciar los ciclos para el nuevo proceso
        }
    }
}