#include "ListaProcesos.h"
#include <iostream>
using namespace std;

int main() {
    ListaProcesos lista;

    
    // Cambia esto por la ruta al archivo proporcionado.
    string nombreArchivo = "files/PruebaEnunciado.txt";

    lista.leerArchivo(nombreArchivo);

    cout << "Procesos cargados desde el archivo:\n";
    lista.mostrarProcesos();

    return 0;
}
