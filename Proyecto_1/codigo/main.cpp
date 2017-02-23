/** Universidad Simón Bolívar
*   CI5437 - Diseño de Algoritmos I
*   Trimestre Ene-Mar 2017
*
*   Proyecto I
*   Programa Principal.
* 
*   Hecho por: Enrique Iglesias 11-10477
*              Gabriel Iglesias 11-10476
*
*   Última modificación: 20/02/17
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include <unistd.h>
#include <string>

#include "grafo.cpp"

using namespace std;

int main(int argc, char const *argv[]) {

	time_t inicio, fin;
	double seconds;

	std::ifstream arch_entrada;
	ofstream arch_salida;

	char str[] = "Debe especificar un archivo de entrada.";
	char data[10];
    char line;
    int nvertice;

	time(&inicio);      // obtiene el tiempo al iniciar el programa.

	if (argc < 2) {
		cerr << "Error : " << str << endl;
		return -1;
	}

	arch_entrada.open(argv[1], ios::in);
	arch_salida.open("salida.txt", ios::out);

	cout << "Reading from the file" << endl;
	string a, b, c, d;
	arch_entrada >> a >> b >> c >> d >> nvertice;
	
	struct Graph * grafo = createGraph(nvertice);  
	cout << "\n" << nvertice << " " << "vertices" << endl;

	for (int i = 0; i < 5; ++i) {
		arch_entrada >> data;
	} 
	cout << "\n" << data << " " << "aristas" << endl;
	int nodo1, nodo2, costo, beneficio;
	string number;
	while (arch_entrada >> number >> nodo2 >> costo >> beneficio) {
		if (number != "number")
		{
			nodo1 = atoi(number.c_str());
			addEdge(grafo, nodo1, nodo2);
		}
	}

	printGraph(grafo);

	// Se escriben los resultados en el archivo de salida.
	arch_salida << "Ganancia" << " " << "xx" << endl;
	arch_salida << "Camino" << " " << "..." << endl;
	
	// Cierre de archivos.
	arch_entrada.close();
	arch_salida.close();

	time(&fin);         // obtiene el tiempo al finalizar el programa.
	
	seconds = difftime(fin,inicio);

	cout << "\n" << seconds << " segundos" << endl;

	return 0;
}