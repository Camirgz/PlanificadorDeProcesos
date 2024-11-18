#include "ListaProcesos.h"
#include <iostream>
#include <fstream>
using namespace std;

ListaProcesos::ListaProcesos() : cabeza(nullptr) {}

void ListaProcesos::agregarProceso(const string& nombre, int prioridad, const string& instrucciones) {
    Proceso* nuevo = new Proceso(nombre, prioridad);
    nuevo->instrucciones = instrucciones;

    if (!cabeza) {
        cabeza = nuevo;
    } else {
        Proceso* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void ListaProcesos::mostrarProcesos() const {
    Proceso* actual = cabeza;
    while (actual) {
        cout << "\nNombre del Proceso: " << actual->nombre << "\n";
        cout << "Prioridad: " << actual->prioridad << "\n";
        cout << "Instrucciones:\n" << actual->instrucciones << "\n\n";
        actual = actual->siguiente;
    }
}

void ListaProcesos::leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return;
    }

    string linea;
    string nombreProceso;
    int prioridad = 0;
    string instrucciones = "";
    bool leyendoProceso = false;

    while (getline(archivo, linea)) {
        if (linea.find("proceso") == 0) {
            if (leyendoProceso) {
                agregarProceso(nombreProceso, prioridad, instrucciones);
                instrucciones.clear();
            }
            leyendoProceso = true;
            size_t pos1 = linea.find(" ");
            size_t pos2 = linea.rfind(" ");
            nombreProceso = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            prioridad = stoi(linea.substr(pos2 + 1));
        } else if (linea == "fin proceso") {
            agregarProceso(nombreProceso, prioridad, instrucciones);
            instrucciones.clear();
            leyendoProceso = false;
        } else {
            instrucciones += linea + "\n";
        }
    }

    archivo.close();
}

void ListaProcesos::eliminarLista() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

Proceso* ListaProcesos::obtenerCabeza() const {
    return cabeza;
}

ListaProcesos::~ListaProcesos() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
