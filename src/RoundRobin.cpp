#include "RoundRobin.h"
#include <unistd.h> // Para sleep()

void RoundRobin::ejecutar(Proceso* cabeza) {
    // Verificar si hay procesos cargados
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    bool procesosPendientes; // Indica si quedan procesos sin completar

    do {
        procesosPendientes = false; // Reiniciar el estado de procesos pendientes
        Proceso* actual = cabeza; // Iterar desde el primer proceso

        while (actual) {
            if (!actual->instrucciones.empty()) {
                procesosPendientes = true; // Hay procesos pendientes
                std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n" << RESET;

                std::string instruccion;
                int tiempoConsumido = 0; // Control del tiempo consumido en el quantum

                // Procesar las instrucciones
                while (tiempoConsumido < quantum && !actual->instrucciones.empty()) {
                    // Extraer la siguiente instrucción
                    size_t pos = actual->instrucciones.find('\n');
                    if (pos == std::string::npos) {
                        instruccion = actual->instrucciones; // Última instrucción
                        actual->instrucciones.clear();      // Limpiar instrucciones
                    } else {
                        instruccion = actual->instrucciones.substr(0, pos);
                        actual->instrucciones = actual->instrucciones.substr(pos + 1); // Actualizar el resto
                    }

                    // Simular la ejecución de la instrucción
                    if (instruccion.find("e/s") != std::string::npos) {
                        std::cout << AMARILLO << "Proceso " << actual->nombre << " bloqueado por E/S.\n" << RESET;
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        sleep(3); // Simular E/S (3 ciclos)
                        tiempoConsumido += 3;
                        break; // Finaliza el quantum por bloqueo
                    } else {
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n" << RESET;
                        sleep(1);
                        tiempoConsumido++;
                    }
                }

                // Evaluar el estado tras consumir el quantum
                if (actual->instrucciones.empty()) {
                    std::cout << VERDE << "\nProceso " << actual->nombre << " finalizado.\n" << RESET;
                } else if (tiempoConsumido >= quantum) {
                    std::cout << ROJO<< "Quantum agotado. Proceso " << actual->nombre << " cortado y regresado a la cola.\n" << RESET;
                }
            }
            actual = actual->siguiente; // Pasar al siguiente proceso
        }

    } while (procesosPendientes); // Continuar mientras haya procesos pendientes

    std::cout << "\nTodos los procesos han sido ejecutados con Round Robin.\n";
}
