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
#include <string>
#include <vector>
#include <deque>
#include <queue>

#include <fstream>           // istream, ostream
#include <iostream>          // cout, cin, endl
#include <algorithm>         // max

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

int beneficioDisponible;

struct Solucion solParcial;
struct Solucion mejorSolucion;

/* Prototypes */

int obtenerMaximoBeneficio(deque<Arista> lados);

deque<Arista> obtenerSucesores(deque<Arista> lados);

bool cicloNegativo(struct Arista arista, struct Solucion solucion);

bool ladoEnSolParcial(struct Arista arista, struct Solucion solucion);

bool repiteCiclo(struct Arista arista, struct Solucion solucion);

bool cumpleAcotamiento(struct Arista arista, struct Solucion solucion);

struct Arista eliminarUltimoLado(struct Solucion solucion);

void agregarLado(struct Arista arista, struct Solucion solucion);

void busquedaEnProfundidad(); 

void hallarCamino(struct Graph* graph, deque<Arista> aristas, struct Solucion solInicial);

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

	int nodo1, nodo2, costo, beneficio;
	
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

void hallarCamino(struct Graph* graph, deque<Arista> aristas, struct Solucion solInicial) {
	
	solParcial.camino.append("1");
	mejorSolucion = solInicial;
	beneficioDisponible = obtenerMaximoBeneficio(aristas);
	busquedaEnProfundidad();
}

void busquedaEnProfundidad() {

	char v = solParcial.camino.back();

	if (v == '1') {

		if (solParcial.beneficio > mejorSolucion.beneficio) {
			mejorSolucion = solParcial;
		}
	}

	struct Arista arco;
	deque<Arista> ladosAdyacentes = obtenerSucesores(aristas);
	deque<Arista>::iterator it = ladosAdyacentes.begin();

	while (it != ladosAdyacentes.end()) {

		arco = *it;
		if (!cicloNegativo(arco, solParcial) && !ladoEnSolParcial(arco, solParcial)
		     &&  !repiteCiclo(arco, solParcial) && cumpleAcotamiento(arco, solParcial)) {

			agregarLado(arco, solParcial);
			beneficioDisponible = beneficioDisponible - max(0, (arco.beneficio - arco.costo));
			busquedaEnProfundidad();
		}
	}

	arco = eliminarUltimoLado(solParcial);
	beneficioDisponible = beneficioDisponible + max(0, (arco.beneficio - arco.costo));
}

bool cumpleAcotamiento(struct Arista lado, struct Solucion solucion) {
	
	int beneficioE = lado.beneficio - lado.costo;
	int beneficioSolParcial = solParcial.beneficio + beneficioE;
	int maxBeneficio = beneficioDisponible -  max(0, beneficioE) + beneficioSolParcial;
	
	if (maxBeneficio <= mejorSolucion.beneficio)	{
		return false;
	}

	return true;
}