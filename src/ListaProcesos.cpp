#include "ListaProcesos.h"
#include "Algoritmo.h" //Colores
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
ListaProcesos::ListaProcesos() : cabeza(nullptr) {}

// Agregar un proceso a la lista
void ListaProcesos::agregarProceso(const string& nombre, int prioridad, const string& instrucciones) {

    // Crear un nuevo proceso
    Proceso* nuevo = new Proceso(nombre, prioridad);
    nuevo->instrucciones = instrucciones;

    // Agregar el proceso a la lista
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

// Mostrar los procesos de la lista (imprimir)
void ListaProcesos::mostrarProcesos() const {
    cout << "=== Procesos cargados ===\n";
    Proceso* actual = cabeza;
    while (actual) {
        cout << AZUL << "\nNombre del Proceso: " << RESET << actual->nombre << "\n";
        cout << CYAN << "Prioridad: " << RESET << actual->prioridad << "\n";
        cout << VERDE << "Instrucciones:\n" << RESET << actual->instrucciones << "\n\n";
        actual = actual->siguiente;
    }
}

// Leer un archivo de texto con los procesos
void ListaProcesos::leerArchivo(const string& nombreArchivo) {

    // Abrir el archivo
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo.\n";
        abrirArchivo = false;
        return;
    }

    // Leer el archivo línea por línea
    string linea;
    string nombreProceso;
    int prioridad = 0;
    string instrucciones = "";
    bool leyendoProceso = false;

    // Leer el archivo línea por línea
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
    abrirArchivo = true;
    archivo.close();
}

// Ejecutar los procesos por prioridad
void ListaProcesos::eliminarLista() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Ejecutar los procesos por prioridad
Proceso* ListaProcesos::obtenerCabeza() const {
    return cabeza;
}

// Destructor
ListaProcesos::~ListaProcesos() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

bool ListaProcesos::obtenerAbrirArchivo() const {
    return abrirArchivo;
}