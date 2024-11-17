#include <iostream>
#include "ListaProcesos.h"
#include "Controlador.h"

using namespace std;

void Controlador :: procesarConsulta(){

  // Crear lista de procesos
  ListaProcesos lista;
  string entrada;

  // Leer archivo de procesos
  cout << "===Bienvenido al Planificador de Procesos ===" << endl;
  cout << "Ingrese el nombre de su archivo guardado en Files: ";
  getline(cin, entrada);
  string nombreArchivo = "files/" + entrada+".txt"; 
  lista.leerArchivo(nombreArchivo);

  // ver qué procesos se ejecutarán
  lista.mostrarProcesos();

  // Preguntar al usuario qué método de planificación desea usar
  cout << "Cuál método quiere usar? \n1) Prioridad \n2) Round Robin \n3) Salir del programa \n";
  getline(cin, entrada);
  if (entrada == "1") {
    cout << "Opción 1: Prioridad";
    lista.ejecutarPorPrioridad();
  } else if (entrada == "2") {
    cout << "Opción 2: Round Robin";
    int quantum = 5;
    lista.ejecutarRoundRobin(quantum);
  } else if (entrada == "3") {
    cout << "Opción 3: Salir del programa";
    cout << "\n ===Gracias===" << endl;
  } else {
    cout << "Opción no válida";
    }

  cout << "Procesos cargados desde el archivo:\n" << nombreArchivo << endl;
  

  cout << "\n ===Gracias===" << endl;
};