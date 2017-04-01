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

#include "algo_greedy.cpp" 

using namespace std;

/* Prototypes */

// int obtenerMaximoBeneficio(deque<Arista> lados);

// deque<Arista> obtenerSucesores(deque<Arista> lados);

// bool cicloNegativo(struct Arista arista, struct Solucion solucion);

// bool ladoEnSolParcial(struct Arista arista, struct Solucion solucion);

// bool repiteCiclo(struct Arista arista, struct Solucion solucion);

// bool cumpleAcotamiento(struct Arista arista, struct Solucion solucion);

// struct Arista eliminarUltimoLado(struct Solucion solucion);

// void agregarLado(struct Arista arista, struct Solucion solucion);

void busquedaEnProfundidad(); 

void hallarCamino(struct Solucion solInicial);

/* Programa Principal */

int main(int argc, char const *argv[]) {


	/* Declaracion de Variables */
	
	time_t inicio, fin;
	double seconds;

	ifstream arch_entrada;
	ofstream arch_salida;

    char line;
	char data[10];
	char message[] = "Debe especificar un archivo de entrada, un camino solución y la ganancia del camino.";
    
    int nvertices, nlados;

    //int ganancia = 0;
	//string camino = "";

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

	struct Solucion solInicial;

	solInicial.camino = "1 - 2 - 5 - 4 - 3 - 2 - 1";
	solInicial.beneficio = 14;

	/*-----------------------------------------------------*/

	/* Inicialización del Grafo. */
	
	//struct Graph* grafo = createGraph(nvertices);

	graph = createGraph(nvertices);
	struct Graph* grafo_greedy = createGraph(nvertices);

	//deque<Arista> aristas;             // Estructura que almacena las aristas.
	string number;                       // Variable para chequear que tipo de linea se lee.

	int nodo1, nodo2, costo, beneficio;
	
	while (arch_entrada >> number) {
		
		//cout << number << endl;
		if (number != "number") {

			nodo1 = atoi(number.c_str());
			arch_entrada >> nodo2 >> costo >> beneficio;
			addEdge(graph, nodo1, nodo2);
			addEdge(grafo_greedy, nodo1, nodo2);
			aristas.push_front(crear_arista(nodo1, nodo2, costo, beneficio));
		}

		else {
			arch_entrada >> a >> b >> c >> d >> e;
		}
	}

	//printGraph(graph);
	//cout << aristas.size() << endl;

	/*-----------------------------------------------------*/

	int ganancia = 0;
	string camino = "";

	struct Graph* grafo = graph;
	deque<Arista> arcos = aristas;

	printGraph(graph);

	if (grafo->array[1].head->next) {
		cout << graph->array[1].head->next->id << endl;
	}

	else {
		cout << "null" << endl << endl;
	}

	//solInicial = hallarCamino_greedy(grafo_greedy, arcos, camino, ganancia);

	cout << graph->array[1].nodeid->id << endl;
	cout << graph->array[1].nodeid->value << endl;
	cout << graph->array[1].nodeid->parent << endl;

	//cout << "solInicial" << endl;
	//cout << solInicial.camino << endl;
	//cout << solInicial.beneficio << endl;

    //Algoritmo 1

    hallarCamino(solInicial);

    /* Se escriben los resultados en el archivo de salida. */

	//arch_salida << "Ganancia" << " " << ganancia << endl;
	//arch_salida << "Camino:" << " " << camino << endl;

	time(&fin);         // obtiene el tiempo al finalizar el programa.
	seconds = difftime(fin, inicio);

	arch_salida << "Tiempo:" << " " << seconds << endl;

	// Cierre de archivos.
	arch_entrada.close();
	arch_salida.close();

	cout << "\n" << seconds << " segundos" << endl;

	return 0;
}

void hallarCamino(struct Solucion solInicial) {

	solParcial.beneficio = 0;
	solParcial.camino.append("1");

	mejorSol = solInicial;

	beneficioDisponible = obtener_maximo_beneficio(aristas);
	busquedaEnProfundidad();

	cout << "Camino: " << mejorSol.camino << endl;
	cout << "Beneficio: " << mejorSol.beneficio << endl;
}

void busquedaEnProfundidad() {

	char v = solParcial.camino.back();

	priority_queue<struct Arista, vector<Arista>, Mycomparison> ladosAdyacentes = obtener_lista_de_sucesores(v);

	if ((v != '1')) {

		if (solParcial.beneficio > mejorSol.beneficio) {
			mejorSol = solParcial;
		}
	}

	struct Arista arco;


	cout << "Cola Vacia: " << ladosAdyacentes.empty() << endl;
	
	//deque<Arista>::iterator it = ladosAdyacentes.begin();

	while (!ladosAdyacentes.empty()) {

		arco = ladosAdyacentes.top();
		ladosAdyacentes.pop();
		cout << arco.nodo1 << " " << arco.nodo2 << endl;
		cout << ciclo_negativo(v, arco, solParcial) << endl;
		cout << esta_lado_en_solparcial(v, arco, solParcial) << endl;
		cout << repite_ciclo(ladosAdyacentes, arco, solParcial) << endl;
		cout << cumple_acotamiento(arco, solParcial) << endl;
		if (!ciclo_negativo(v, arco, solParcial) && !esta_lado_en_solparcial(v, arco, solParcial)
		     &&  !repite_ciclo(ladosAdyacentes, arco, solParcial) && cumple_acotamiento(arco, solParcial)) {

			agregar_lado(v, arco, solParcial);
			beneficioDisponible = beneficioDisponible - max(0, (arco.beneficio - arco.costo));
			cout << solParcial.camino << endl;
			busquedaEnProfundidad();
		}
	}

	cout << "bla" << endl;

	arco = eliminar_ultimo_lado();
	beneficioDisponible = beneficioDisponible + max(0, (arco.beneficio - arco.costo));
}