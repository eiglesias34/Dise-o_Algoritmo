/** Universidad Simón Bolívar
*   CI5437 - Diseño de Algoritmos I
*   Trimestre Ene-Mar 2017
*
*   Proyecto II
*   Programa Principal.
* 
*   Hecho por: Enrique Iglesias 11-10477
*              Gabriel Iglesias 11-10476
*
*   Última modificación: 26/02/17
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>

#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "grafo.cpp" 

using namespace std;

struct Solucion
{
	int beneficio;
	string camino;
};

/* Variables Globales */

int beneficioActual;
struct Solucion solParcial;
struct Solucion mejorSolucion;

/* Prototypes */

void busquedaEnProfundidad(); 
void hallarCamino(struct Graph* graph, deque<Arista> aristas, string solInicial);

/* Programa Principal */

int main(int argc, char const *argv[]) {


	/* Declaracion de Variables */
	
	time_t inicio, fin;
	double seconds;

	ifstream arch_entrada;
	ofstream arch_salida;

    char line;
	char data[10];
	char message[] = "Debe especificar un archivo de entrada.";
    
    int nvertices, nlados;

    int ganancia = 0;
	string camino = "";

    /*-----------------------------------------------------*/

    /* Verficación de la ejecución del programa. */
	
	if (argc < 2) {
		cerr << "Error : " << message << endl;
		return -1;
	}

	/*-----------------------------------------------------*/

	/* Creción del nombre del Archivo de Salida. */
    
    const char* output_file = new char [strlen(argv[1])+strlen("_salida.txt")+1];
	
	strcat(const_cast<char*>(output_file),argv[1]);
    strcat(const_cast<char*>(output_file),"_salida.txt");
	
    /*-----------------------------------------------------*/

    time(&inicio);      // obtiene el tiempo al iniciar el programa.

	arch_entrada.open(argv[1], ios::in);
	arch_salida.open(output_file, ios::out);

	/* Se leen las dos primeras líneas del Archivo de entrada. */
	
	string a, b, c, d, e;
	
	cout << "Reading from the file... " << endl;
	
	arch_entrada >> a >> b >> c >> d >> nvertices;
	cout << "\n" << nvertices << " " << "vertices" << endl; 

	arch_entrada >> a >> b >> c >> d >> nlados;
	cout << "\n" << nlados << " " << "aristas" << endl;

	cout << "\n";

	/*-----------------------------------------------------*/

	/* Inicialización del Grafo. */
	
	struct Graph* grafo = createGraph(nvertices);

	deque<Arista> aristas;             // Estructura que almacena las aristas.
	string number;                     // Variable para chequear que tipo de linea se lee.
	
	while (arch_entrada >> number) {
		
		//cout << number << endl;
		if (number != "number") {

			nodo1 = atoi(number.c_str());
			arch_entrada >> nodo2 >> costo >> beneficio;
			
			addEdge(grafo, nodo1, nodo2);
			aristas.push_front(crear_arista(nodo1, nodo2, costo, beneficio));
		}

		else {
			arch_entrada >> a >> b >> c >> d >> e;
		}
	}

	/*-----------------------------------------------------*/

    //Algoritmo 1

    /* Se escriben los resultados en el archivo de salida. */

	arch_salida << "Ganancia" << " " << ganancia << endl;
	arch_salida << "Camino:" << " " << camino << endl;

	time(&fin);         // obtiene el tiempo al finalizar el programa.
	seconds = difftime(fin, inicio);

	arch_salida << "Tiempo:" << " " << seconds << endl;

	// Cierre de archivos.
	arch_entrada.close();
	arch_salida.close();

	cout << "\n" << seconds << " segundos" << endl;

	return 0;
}

void hallarCamino(struct Graph* graph, deque<Arista> aristas, string solInicial) {
	
	solParcial.append("1");
	mejorSolucion = solInicial;
	beneficioActual = ;
	busquedaEnProfundidad();
}

void busquedaEnProfundidad() {

	char v = solParcial.camino.back();

}