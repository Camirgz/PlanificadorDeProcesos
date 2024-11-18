#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

#include "Proceso.h"
#include <unistd.h> // Para sleep() en sistemas UNIX/Linux
#include <string>

class ListaProcesos {
private:
    Proceso* cabeza;
   

public:
    ListaProcesos();
    void agregarProceso(const std::string& nombre, int prioridad, const std::string& instrucciones);
    void mostrarProcesos() const;
    void leerArchivo(const std::string& nombreArchivo);
    void ejecutarPorPrioridad();
    void ejecutarRoundRobin(int quantum);
    void eliminarLista();
    ~ListaProcesos();
    Proceso* obtenerCabeza() const;
};

#endif // LISTA_PROCESOS_H
