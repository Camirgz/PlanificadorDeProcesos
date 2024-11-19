#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

// Includes
#include "Proceso.h"
#include <unistd.h> // Para sleep() en sistemas UNIX/Linux
#include <string>

// Clase ListaProcesos
class ListaProcesos {

// Atributos
private:

    // Puntero a la cabeza de la lista
    Proceso* cabeza;
    bool abrirArchivo;
// Métodos
public:
    ListaProcesos();
    bool obtenerAbrirArchivo() const;
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
