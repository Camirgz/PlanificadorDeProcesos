#include "RoundRobin.h"
#include <unistd.h> // Para sleep()

void RoundRobin::ejecutar(Proceso* cabeza) {
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    bool procesosPendientes;
    do {
        procesosPendientes = false;
        Proceso* actual = cabeza;

        while (actual) {
            if (!actual->instrucciones.empty()) {
                procesosPendientes = true;
                std::cout << "Ejecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n";

                std::string instruccion;
                int tiempoConsumido = 0;

                for (size_t i = 0; i < actual->instrucciones.size(); i++) {
                    if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                        if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                            instruccion += actual->instrucciones[i];
                        }

                        std::cout << "Ejecutando: " << instruccion << "\n";

                        if (instruccion == "e/s") {
                            std::cout << "Simulando operación de entrada/salida (3 ciclos)...\n";
                            sleep(3);
                            tiempoConsumido += 3;
                        } else {
                            std::cout << "Simulando instrucción normal (1 ciclo)...\n";
                            sleep(1);
                            tiempoConsumido++;
                        }

                        if (tiempoConsumido >= quantum) {
                            std::cout << "Quantum finalizado. Proceso pausado: " << actual->nombre << "\n";
                            break;
                        }
                        instruccion.clear();
                    } else {
                        instruccion += actual->instrucciones[i];
                    }
                }
                actual->instrucciones = actual->instrucciones.substr(tiempoConsumido);
            }
            actual = actual->siguiente;
        }
    } while (procesosPendientes);

    std::cout << "Todos los procesos han sido ejecutados con Round Robin.\n";
}
