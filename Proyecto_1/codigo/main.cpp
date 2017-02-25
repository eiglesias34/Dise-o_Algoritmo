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
*   Última modificación: 23/02/17
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include <unistd.h>
#include <string>
#include <deque>
#include <queue>

#include "grafo.cpp"

using namespace std;

// Clase para comparar dos nodos en la cola de prioridades.
class Mycomparison 
{

private:
	bool reverse;

public:
	Mycomparison(bool param=true) {
		reverse = param;
	}

	bool operator() (struct AdjListNode node1, struct AdjListNode node2) const {
		if (reverse)
			return node1.value > node2.value;
		else
			return node1.value < node2.value;
	}
};

/*void hallarCamino(struct Graph* graph, deque<Arista> aristas) {

	struct AdjListNode *start, *aux, *dest;
	const struct AdjListNode *src;
	start = graph->array[1].head; 
	start->value = 0;                       // Inicializamos el valor del nodo 
	                                        // depósito a cero.

	priority_queue<struct AdjListNode, std::vector<AdjListNode>, Mycomparison> pq;  // Cola de prioridades.
	
	// Inicializamos la Cola de prioridades.
	for (int i = 1; i < graph->V; ++i) {
		aux = graph->array[i].head;
		pq.push(aux);
	}

	int beneficio, costo, total;
	struct Arista arco;

	while (!pq.empty()) {
		
		src = &pq.top();
		pq.pop();
		dest = src->next;
		
		while (dest) {

			arco = extraer_arista(aristas, src->id, dest->id);
			costo = arco.costo;
			beneficio = arco.beneficio;
			total = beneficio - costo;

			if ((aux in pq) && (total > 0) && (total > dest->value)) {
				dest->value  = total;
				dest->parent = src->id;
			}
		}
	}
}*/ 

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

	// Verficación de la ejecución del programa.
	if (argc < 2) {
		cerr << "Error : " << str << endl;
		return -1;
	}

	arch_entrada.open(argv[1], ios::in);
	const char* s = new char [strlen(argv[1])+strlen("_salida.txt")+1];
	strcat(const_cast<char*>(s),argv[1]);
    strcat(const_cast<char*>(s),"_salida.txt");
	arch_salida.open(s, ios::out);

	// Lectura del Archivo
	cout << "Reading from the file" << endl;
	string a, b, c, d, e;
	arch_entrada >> a >> b >> c >> d >> nvertice;
	cout << "\n" << nvertice << " " << "vertices" << endl;
	
	// Inicialización del Grafo.
	struct Graph * grafo = createGraph(nvertice);  

	for (int i = 0; i < 5; ++i) {
		arch_entrada >> data;
	} 
	cout << "\n" << data << " " << "aristas" << endl;
	deque<Arista> aristas;
	int nodo1, nodo2, costo, beneficio;
	string number;
	while (arch_entrada >> number) {
		//cout << number << endl;
		if (number != "number")
		{
			arch_entrada >> nodo2 >> costo >> beneficio;
			nodo1 = atoi(number.c_str());
			addEdge(grafo, nodo1, nodo2);
			aristas.push_front(crear_arista(nodo1, nodo2, costo, beneficio));
		}else{
			arch_entrada >> a >> b >> c >> d >> e;
		}
	}

	printGraph(grafo);
	cout << (extraer_arista(aristas,1,2)).costo << endl;
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