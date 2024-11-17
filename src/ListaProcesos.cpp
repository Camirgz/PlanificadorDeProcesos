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

void ListaProcesos::ejecutarPorPrioridad() {
    if (!cabeza) {
        cout << "No hay procesos cargados.\n";
        return;
    }

    // Ordenar los procesos por prioridad (sin usar estructuras auxiliares)
    Proceso* actual = nullptr;
    Proceso* siguiente = nullptr;
    for (actual = cabeza; actual != nullptr; actual = actual->siguiente) {
        for (siguiente = actual->siguiente; siguiente != nullptr; siguiente = siguiente->siguiente) {
            if (actual->prioridad > siguiente->prioridad) {
                // Intercambiar los datos de los procesos
                string tempNombre = actual->nombre;
                int tempPrioridad = actual->prioridad;
                string tempInstrucciones = actual->instrucciones;

                actual->nombre = siguiente->nombre;
                actual->prioridad = siguiente->prioridad;
                actual->instrucciones = siguiente->instrucciones;

                siguiente->nombre = tempNombre;
                siguiente->prioridad = tempPrioridad;
                siguiente->instrucciones = tempInstrucciones;
            }
        }
    }

    // Ejecutar los procesos en orden
    actual = cabeza;

    // mostrar los procesos a ejecurtar en orden
    cout << "Procesos a ejecutar en orden de prioridad:\n";
    while (actual) {
        cout << "Nombre del Proceso: " << actual->nombre << " ";
        cout << "Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }

    // reestablecer el puntero al inicio
    actual = cabeza;
    cout << "\nEjecutando procesos en orden de prioridad...\n\n";
    while (actual) {
        cout << "Ejecutando proceso: " << actual->nombre << " (Prioridad: " << actual->prioridad << ")\n";
        string instruccion;
        for (size_t i = 0; i < actual->instrucciones.size(); i++) {
            if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                    instruccion += actual->instrucciones[i];
                }

                cout << "Ejecutando: " << instruccion << "\n";
                
                // Simular ejecución con sleep
                if (instruccion == "e/s") {
                    cout << "Simulando operación de entrada/salida (3 ciclos)...\n";
                    sleep(3); // 3 segundos para pares de entrada/salida
                } else {
                    cout << "Simulando instrucción normal (1 ciclo)...\n";
                    sleep(1); // 1 segundo para instrucciones normales
                }

                instruccion.clear();
            } else {
                instruccion += actual->instrucciones[i];
            }
        }
        cout << "Proceso finalizado: " << actual->nombre << "\n\n";
        actual = actual->siguiente;
    }

    cout << "Todos los procesos han sido ejecutados.\n";
    eliminarLista();

}

void ListaProcesos::ejecutarRoundRobin(int quantum) {
    if (!cabeza) {
        cout << "No hay procesos cargados.\n";
        return;
    }

    // Crear una cola circular simple con los procesos
    Proceso* temp = cabeza;
    int procesos = 0;
    // int contador = 0;
    while (temp) {
        procesos++;
        temp = temp->siguiente;
        if (temp == cabeza) break; // Detener si volvemos al inicio
    }
    temp = cabeza;


   while (true) {
    bool procesosPendientes = false;

    // Recorrer los procesos y asignar tiempo de CPU
    Proceso* actual = cabeza; // Reiniciar a la cabeza al inicio de cada ciclo
    while (actual) {
        if (!actual->instrucciones.empty()) {
            procesosPendientes = true; // Hay al menos un proceso pendiente

            cout << "Ejecutando proceso: " << actual->nombre << " (Quantum: " << quantum << " segundos)\n";

            string instruccion;
            int tiempoConsumido = 0;

            // Ejecutar instrucciones dentro del quantum asignado
            for (size_t i = 0; i < actual->instrucciones.size(); i++) {
                if (actual->instrucciones[i] == '\n' || i == actual->instrucciones.size() - 1) {
                    if (i == actual->instrucciones.size() - 1 && actual->instrucciones[i] != '\n') {
                        instruccion += actual->instrucciones[i];
                    }

                    cout << "Ejecutando: " << instruccion << "\n";

                    // Simular tiempo de ejecución
                    if (instruccion == "e/s") {
                        cout << "Simulando operación de entrada/salida (3 ciclos)...\n";
                        sleep(3);
                        tiempoConsumido += 3;
                    } else {
                        cout << "Simulando instrucción normal (1 ciclo)...\n";
                        sleep(1);
                        tiempoConsumido++;
                    }

                    // Detener si se excede el quantum
                    if (tiempoConsumido >= quantum) {
                        cout << "Quantum finalizado. Proceso pausado: " << actual->nombre << "\n";
                        break;
                    }

                    instruccion.clear();
                } else {
                    instruccion += actual->instrucciones[i];
                }
            }

            // Eliminar las instrucciones ejecutadas del proceso
            if (tiempoConsumido > 0) {
                actual->instrucciones = actual->instrucciones.substr(tiempoConsumido); // Elimina las instrucciones consumidas
            }
        }

        // Avanzar al siguiente proceso
        actual = actual->siguiente;
    }

    // Detener el ciclo si todos los procesos han terminado
    if (!procesosPendientes) {
        cout << "Todos los procesos han finalizado.\n";
        break;
    }
    }

    cout << "Todos los procesos han sido ejecutados con Round Robin.\n";
    eliminarLista();

}

void ListaProcesos::eliminarLista() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

ListaProcesos::~ListaProcesos() {
    while (cabeza) {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
