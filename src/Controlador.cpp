#include <iostream>
#include "ListaProcesos.h"

using namespace std;

void procesarConsulta(){
    
  ListaProcesos lista;
  string entrada;
  cout << "===Bienvenido al Planificador de Procesos ===" << endl;
  cout << "Ingrese el nombre de su archivo guardado en Files: ";
  getline(cin, entrada);
  string nombreArchivo = "files/" + entrada+".txt"; 
  lista.leerArchivo(nombreArchivo);


  cout << "Cuál método quiere usar? \n1) Prioridad \n2) Round Robin \n3) Salir del programa";
  getline(cin, entrada);
  if (entrada == "1") {
    cout << "Opción 1: Prioridad";
  } else if (entrada == "2") {
    cout << "Opción 2: Round Robin";
  } else if (entrada == "3") {
    cout << "Opción 3: Salir del programa";
    cout << "\n ===Gracias===" << endl;
  } else {
    cout << "Opción no válida";
    }

  cout << "Procesos cargados desde el archivo:\n";
  lista.mostrarProcesos();

  cout << "\n ===Gracias===" << endl;
};