#include "RoundRobin.h"
#include <unistd.h> // Para sleep()

// Método polimórfico

void RoundRobin::ejecutar(Proceso* cabeza) {
    // Verificar si hay procesos cargados
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    bool procesosPendientes;

    do {
        procesosPendientes = false; // Reiniciar el estado de procesos pendientes
        Proceso* actual = cabeza;

        while (actual) {
            if (!actual->instrucciones.empty()) {
                procesosPendientes = true; // Hay procesos pendientes
                std::cout << "Ejecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n";
                
                std::string instruccion;
                int tiempoConsumido = 0;

                // Procesar las instrucciones
                while (tiempoConsumido < quantum && !actual->instrucciones.empty()) {
                    // Obtener la siguiente instrucción
                    size_t pos = actual->instrucciones.find('\n');
                    if (pos == std::string::npos) {
                        instruccion = actual->instrucciones; // Última instrucción
                        actual->instrucciones.clear(); // Limpiar instrucciones
                    } else {
                        instruccion = actual->instrucciones.substr(0, pos);
                        actual->instrucciones = actual->instrucciones.substr(pos + 1); // Actualizar a las instrucciones restantes
                    }

                    std::cout << "Ejecutando: " << instruccion << "\n";

                    // Simular ejecución de la instrucción
                    if (instruccion == "e/s") {
                        std::cout << "Simulando operación de entrada/salida (3 ciclos)...\n";
                        sleep(3);
                        tiempoConsumido += 3;
                    } else {
                        std::cout << "Simulando instrucción normal (1 ciclo)...\n";
                        sleep(1);
                        tiempoConsumido++;
                    }
                }

                // Si todas las instrucciones han sido ejecutadas, se dejará vacío
                if (actual->instrucciones.empty()) {
                    std::cout << "Proceso " << actual->nombre << " completado.\n";
                }
            }
            actual = actual->siguiente;
        }

        // Llamar al método para eliminar procesos completados
       
        
    } while (procesosPendientes); // El bucle continuará si hay procesos pendientes

    std::cout << "Todos los procesos han sido ejecutados con Round Robin.\n";
}
