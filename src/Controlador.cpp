#include <iostream>
#include "ListaProcesos.h"
#include "Controlador.h"
#include "RoundRobin.h"
#include "Prioridades.h"

using namespace std;

void Controlador::procesarConsulta() {
    ListaProcesos lista;
    string entrada;

    cout << "=== Bienvenido al Planificador de Procesos ===\n";
    cout << "Ingrese el nombre de su archivo guardado en Files: ";
    getline(cin, entrada);
    string nombreArchivo = "files/" + entrada + ".txt";
    lista.leerArchivo(nombreArchivo);

    lista.mostrarProcesos();

    cout << "¿Cuál método quiere usar?\n1) Prioridad\n2) Round Robin\n3) Salir del programa\n";
    getline(cin, entrada);

    Algoritmo* algoritmo = nullptr;
    if (entrada == "1") {
        algoritmo = new Prioridades();
    } else if (entrada == "2") {
        int quantum = 5; // Quantum predeterminado
        algoritmo = new RoundRobin(quantum);
    } else if (entrada == "3") {
        cout << "=== Gracias ===\n";
        return;
    } else {
        cout << "Opción no válida.\n";
        return;
    }

    algoritmo->ejecutar(lista.obtenerCabeza());
    delete algoritmo;

    cout << "=== Gracias ===\n";
}
