#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

// Includes
#include <unistd.h> // Para sleep() en sistemas UNIX/Linux
#include <string>
#include "Proceso.h"

// Clase ListaProcesos - Template
template <typename T>
class ListaProcesos {

    // Atributos
private:
    // Puntero a la cabeza de la lista
    T* cabeza;
    bool abrirArchivo;

    // Métodos
public:
    ListaProcesos();
    bool obtenerAbrirArchivo() const;
    void agregarElemento(const std::string& nombre, int prioridad, const std::string& instrucciones);
    void mostrarElementos() const;
    void mostrarProcesos() const; // Cambiado de mostrarElementos a mostrarProcesos
    void leerArchivo(const std::string& nombreArchivo);
    void eliminarLista();
    ~ListaProcesos();
    T* obtenerCabeza() const;
};

#endif // LISTA_PROCESOS_H
