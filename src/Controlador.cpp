#include <iostream>
#include "ListaProcesos.h"
#include "Controlador.h"

using namespace std;

void Controlador :: procesarConsulta(){

  ListaProcesos lista;
  string entrada;
  cout << "===Bienvenido al Planificador de Procesos ===" << endl;
  cout << "Ingrese el nombre de su archivo guardado en Files: ";
  getline(cin, entrada);
  string nombreArchivo = "files/" + entrada+".txt"; 
  lista.leerArchivo(nombreArchivo);


  cout << "Cuál método quiere usar? \n1) Prioridad \n2) Round Robin \n3) Salir del programa \n";
  getline(cin, entrada);
  if (entrada == "1") {
    cout << "Opción 1: Prioridad";
    lista.ejecutarPorPrioridad();
  } else if (entrada == "2") {
    cout << "Opción 2: Round Robin";
  } else if (entrada == "3") {
    cout << "Opción 3: Salir del programa";
    cout << "\n ===Gracias===" << endl;
  } else {
    cout << "Opción no válida";
    }

  cout << "Procesos cargados desde el archivo:\n" << entrada << endl;
  

  cout << "\n ===Gracias===" << endl;
};