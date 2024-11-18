#include <iostream>
#include "ListaProcesos.h"
#include "Controlador.h"
#include "RoundRobin.h"
#include "Prioridades.h"

using namespace std;

void Controlador::procesarConsulta() {

    // Crear lista de procesos
    ListaProcesos lista;
    string entrada;

    // Leer archivo
    cout << "=== Bienvenido al Planificador de Procesos ===\n";
    cout << "Ingrese el nombre de su archivo guardado en Files: ";
    getline(cin, entrada);
    string nombreArchivo = "files/" + entrada + ".txt";
    lista.leerArchivo(nombreArchivo);

    // Mostrar procesos
    lista.mostrarProcesos();

    // Elegir algoritmo
    cout << "¿Cuál método quiere usar?\n1) Prioridad\n2) Round Robin\n3) Salir del programa\n";
    getline(cin, entrada);

    // Crear puntero a algoritmo
    Algoritmo* algoritmo = nullptr;

    // Elección de algoritmo	
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

    // Ejecutar algoritmo elegido con la lista de procesos a través de un método polimórfico
    algoritmo->ejecutar(lista.obtenerCabeza());

    // Liberar memoria
    delete algoritmo;

    cout << "=== Gracias ===\n";
}
