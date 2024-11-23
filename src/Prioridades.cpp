#include "Prioridades.h"
#include <unistd.h> // Para sleep()

void Prioridades::ejecutar(Proceso *cabeza)
{
    if (!cabeza)
    {
        std::cout << "No hay procesos cargados.\n";
        return;
    }

    // Ordenar los procesos por prioridad (menor valor = mayor prioridad)
    for (Proceso *actual = cabeza; actual != nullptr; actual = actual->siguiente)
    {
        for (Proceso *siguiente = actual->siguiente; siguiente != nullptr; siguiente = siguiente->siguiente)
        {
            if (actual->prioridad > siguiente->prioridad)
            {
                std::swap(actual->nombre, siguiente->nombre);
                std::swap(actual->prioridad, siguiente->prioridad);
                std::swap(actual->instrucciones, siguiente->instrucciones);
            }
        }
    }

    bool procesosPendientes;

    do
    {
        procesosPendientes = false;
        Proceso *actual = cabeza;

        while (actual)
        {
            if (!actual->instrucciones.empty())
            {
                procesosPendientes = true;

                // Cambiar estado a "En ejecución: Activo"
                actual->estado = "En ejecución: Activo";
                imprimirEstados(cabeza); // Imprimir estados después del cambio

                std::cout << MAGENTA << "\nEjecutando proceso: " << actual->nombre
                          << " (Prioridad: " << actual->prioridad << ")\n"
                          << RESET;

                std::string instruccion;
                bool bloqueadoPorES = false;

                while (!actual->instrucciones.empty())
                {
                    size_t pos = actual->instrucciones.find('\n');
                    if (pos == std::string::npos)
                    {
                        instruccion = actual->instrucciones;
                        actual->instrucciones.clear();
                    }
                    else
                    {
                        instruccion = actual->instrucciones.substr(0, pos);
                        actual->instrucciones = actual->instrucciones.substr(pos + 1);
                    }

                    if (instruccion.find("e/s") != std::string::npos)
                    {
                        if (bloqueadoPorES)
                        {
                            // Si el proceso ya estaba bloqueado, intentamos desbloquearlo verificando la siguiente instrucción
                            size_t nextPos = actual->instrucciones.find('\n');
                            std::string nextInstruccion = (nextPos == std::string::npos)
                                                              ? actual->instrucciones
                                                              : actual->instrucciones.substr(0, nextPos);

                            if (nextInstruccion.find("e/s") != std::string::npos)
                            {
                                std::cout << VERDE << "Se encontró la siguiente operación de E/S. Proceso "
                                          << actual->nombre << " ahora desbloqueado.\n"
                                          << RESET;
                                bloqueadoPorES = false; // Desbloquear
                                actual->instrucciones = (nextPos == std::string::npos)
                                                            ? ""
                                                            : actual->instrucciones.substr(nextPos + 1);
                                continue; // Avanzar a la siguiente instrucción
                            }
                            else
                            {
                                std::cout << ROJO << "No se encontró la siguiente operación de E/S. Proceso "
                                          << actual->nombre << " se mantiene bloqueado.\n"
                                          << RESET;
                                break; // Salir del ciclo
                            }
                        }
                        else
                        {
                            // Primera vez que se encuentra una operación E/S
                            actual->estado = "Bloqueado por E/S";
                            imprimirEstados(cabeza); // Imprimir estados después del cambio

                            std::cout << AMARILLO << "Proceso " << actual->nombre
                                      << " bloqueado por E/S. Se encontró la primera operación de E/S.\n"
                                      << RESET;
                            bloqueadoPorES = true; // Bloqueo inicial
                            sleep(3);              // Simular tiempo de espera por E/S
                        }
                    }
                    else
                    {
                        if (bloqueadoPorES)
                        {
                            std::cout << ROJO << "No se encontró la siguiente operación de E/S. Proceso "
                                      << actual->nombre << " se mantiene bloqueado.\n"
                                      << RESET;
                            break; // Salir del ciclo sin desbloquear
                        }

                        std::cout << "Ejecutando: " << instruccion << "\n";
                        std::cout << CYAN << "Simulando instrucción normal (1 ciclo)...\n"
                                  << RESET;
                        sleep(1);
                    }
                }

                if (actual->instrucciones.empty())
                {
                    if (bloqueadoPorES)
                    {
                        actual->estado = "Bloqueado por E/S";
                        imprimirEstados(cabeza); // Imprimir estados después del cambio

                        std::cout << ROJO << "\nProceso " << actual->nombre
                                  << " finalizó con una operación de E/S pendiente. Se mantiene bloqueado.\n"
                                  << RESET;
                    }
                    else
                    {
                        actual->estado = "Finalizado";
                        imprimirEstados(cabeza); // Imprimir estados después del cambio

                        std::cout << VERDE << "\nProceso " << actual->nombre << " finalizado (Estado: "
                                  << VERDE << actual->estado << RESET << ").\n";
                    }
                }
            }
            actual = actual->siguiente;
        }

    } while (procesosPendientes);

    std::cout << "\nTodos los procesos han sido ejecutados en orden de prioridad.\n";
}
