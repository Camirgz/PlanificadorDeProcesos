#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

#include "Proceso.h"
#include <string>

class ListaProcesos {
private:
    Proceso* cabeza;

public:
    ListaProcesos();
    void agregarProceso(const std::string& nombre, int tiempoInicio, const std::string& instrucciones);
    void mostrarProcesos() const;
    void leerArchivo(const std::string& nombreArchivo);
    ~ListaProcesos();
};

#endif // LISTA_PROCESOS_H
