#include "RoundRobin.h"
#include <unistd.h> // Para sleep()

// Función auxiliar para imprimir los estados de los procesos
void RoundRobin::imprimirEstados(Proceso* cabeza) {
    Proceso* actual = cabeza;
    std::cout << "\nEstado actual de los procesos:\n";
    while (actual) {
        std::cout << "Proceso: " << actual->nombre << " (Estado: ";
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

void RoundRobin::ejecutar(Proceso* cabeza) {
    if (!cabeza) {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    // Imprimir estados iniciales
    imprimirEstados(cabeza);

    bool procesosPendientes;

    do {
        procesosPendientes = false;
        Proceso* actual = cabeza;

        while (actual) {
            if (!actual->instrucciones.empty()) {
                procesosPendientes = true;

                // Cambiar estado a "En ejecución: Activo"
                actual->estado = "En ejecución: Activo";
                imprimirEstados(cabeza); // Imprimir estados después del cambio

                std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre
                          << " (Estado: " << actual->estado << ", Quantum: " << quantum << " segundos)\n" << RESET;

                std::string instruccion;
                int tiempoConsumido = 0;
                int contadorES = 0; // Contador de operaciones de E/S

                while (tiempoConsumido < quantum && !actual->instrucciones.empty()) {
                    size_t pos = actual->instrucciones.find('\n');
                    if (pos == std::string::npos) {
                        instruccion = actual->instrucciones;
                        actual->instrucciones.clear();
                    } else {
                        instruccion = actual->instrucciones.substr(0, pos);
                        actual->instrucciones = actual->instrucciones.substr(pos + 1);
                    }

                    if (instruccion.find("e/s") != std::string::npos) {
                        contadorES++;
                        if (contadorES % 2 != 0) {
                            actual->estado = "Bloqueado por E/S";
                            imprimirEstados(cabeza); // Imprimir estados después del cambio

                            std::cout << AMARILLO << "Proceso " << actual->nombre
                                      << " bloqueado por E/S. Se encontró la primera operación de E/S, esperando encontrar la siguiente.\n"
                                      << RESET;
                        } else {
                            std::cout << VERDE << "Se encontró la siguiente operación de E/S. Proceso "
                                      << actual->nombre << " ahora en ejecución: desbloqueado.\n" << RESET;
                        }
                        sleep(3); // Simular tiempo de espera por E/S
                        tiempoConsumido += 3; // Incrementar tiempo por operación E/S
                        continue; // Seguir a la siguiente instrucción
                    } else {
                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n" << RESET;
                        sleep(1);
                        tiempoConsumido++;
                    }
                }

                if (actual->instrucciones.empty()) {
                    if (contadorES % 2 != 0) {
                        actual->estado = "Bloqueado por E/S";
                        imprimirEstados(cabeza); // Imprimir estados después del cambio

                        std::cout << ROJO << "\nProceso " << actual->nombre
                                  << " finalizó con un número impar de operaciones E/S. No puede desbloquearse.\n" << RESET;
                    } else {
                        actual->estado = "Finalizado";
                        imprimirEstados(cabeza); // Imprimir estados después del cambio

                        std::cout << VERDE << "\nProceso " << actual->nombre << " finalizado (Estado: "
                                  << VERDE << actual->estado << RESET << ").\n";
                    }
                } else if (tiempoConsumido >= quantum) {
                    actual->estado = "Listo";
                    imprimirEstados(cabeza); // Imprimir estados después del cambio

                    std::cout << ROJO << "Quantum agotado. Proceso " << actual->nombre
                              << " cortado y regresado a la cola (Estado: "
                              << AZUL << actual->estado << RESET << ").\n";
                }
            }
            actual = actual->siguiente;
        }

    } while (procesosPendientes);

    std::cout << "\nTodos los procesos han sido ejecutados con Round Robin.\n";
}
