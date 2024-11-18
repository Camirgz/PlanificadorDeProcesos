#include "RoundRobin.h"
#include <unistd.h> // Para sleep()

// Método polimórfico
void RoundRobin::ejecutar(Proceso* cabeza) {

    // Verificar si hay procesos cargados
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    // Ejecutar los procesos en orden de llegada
    bool procesosPendientes;

    // Iterar hasta que no haya procesos pendientes
    do {

        // Inicializar len falso
        procesosPendientes = false;
        Proceso* actual = cabeza;

        // Iterar sobre los procesos
        while (actual) {

            // Verificar que el proceso tenga instrucciones (no está vacío)
            if (!actual->instrucciones.empty()) { //empty es un metodo de string que verifica si esta vacio

                // Indicar que hay procesos pendientes
                procesosPendientes = true;
                std::cout << "Ejecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n";
                
                // Ejecutar las instrucciones del proceso
                std::string instruccion;
                int tiempoConsumido = 0;

                // Iterar sobre las instrucciones del proceso
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
