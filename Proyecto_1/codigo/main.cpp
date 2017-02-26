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
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "grafo.cpp"

using namespace std;

// Función template para imprimir una cola.
template <typename T> void print_queue(T q) {
    
    while (!q.empty()) {
        cout << q.top().id << " " << q.top().value << " ";
        q.pop();
    }

    cout << '\n';
}

// Función template para buscar un elemento.
template <typename T> bool find_and_remove(T& q, int nodo) {

	int i = 0;
	T aux1;
	T aux2 = q;

	while (!aux2.empty()) {
		if (nodo == aux2.top().id) {
			++i;
		} else {
			aux1.push(aux2.top());
			//cout << "F&R  ";
			//print_queue(aux1);
			//cout << "\n";
		}
		aux2.pop();
	}

	if (i) {
		q.swap(aux1);
		return true;
	} else {
		return false;
	}
}

// Clase para comparar dos nodos en la cola de prioridades.
class Mycomparison {

	private:
		bool reverse;

	public:
		Mycomparison(const bool& param=false) {
			reverse = param;
		}

		bool operator() (const struct AdjListNode& node1, const struct AdjListNode& node2) const {
			if (reverse)
				return node1.value > node2.value;
			else
				return node1.value < node2.value;
		}
};

void hallarCamino(struct Graph* graph, deque<Arista> aristas, string& camino, int& ganancia) {

	struct AdjListNode *start;
	struct AdjListNode aux, src, dest;

	start = graph->array[1].nodeid; 
	start->value = 0;                       // Inicializamos el valor del nodo 
	                                        // depósito a cero.

	priority_queue<struct AdjListNode, std::vector<AdjListNode>, Mycomparison> pq;  // Cola de prioridades.
	
	// Inicializamos la Cola de prioridades.
	for (int i = 1; i < graph->V; ++i) {
		aux = *(graph->array[i].nodeid);
		//cout << aux.id << " ";
		pq.push(aux);
	}

	//print_queue(pq);

	// cout << find(pq, 4) << endl;
	// cout << find(pq, 8) << endl;

	int beneficio, costo, total;
	struct Arista arco;

	int i = 0;
	ganancia = 0;

	cout << "1";
	camino.append("1");

	while (!pq.empty()) {
		
		++i;
		// cout << "vuelta" << i << endl;
		// print_queue(pq);
		// cout << "\n";

		src = pq.top();
		pq.pop();

		// cout << "se sacó a " << src.id << endl;
		// print_queue(pq);

		// cout << "nodo" << src.id << " " << "padre" << src.parent << endl;
		// cout << endl;
		
		// Imprime el camino recorrido.
		if (src.parent != 0) {
			// cout << "camino" << endl;
			// cout << "d - ";
			ganancia = ganancia + src.value;
			cout << " - " <</*src.parent << " - " <<*/ src.id;
			camino.append(" - ");
			camino.append(to_string(src.id));
		}

		//Calcula el beneficio que se obtiene al ir a cada nodo adyacente 
		//del recien sacado de la cola
		dest = *(graph->array[src.id].head);

		while (dest.id != -1) {

			// cout << "adyacente" << dest.id << endl;

			arco = extraer_arista(aristas, src.id, dest.id);
			costo = arco.costo;
			beneficio = arco.beneficio;
			total = beneficio - costo;
			// cout << "total " << total << endl;
			// cout << "\n";

			if ((total > 0) && (find_and_remove(pq, dest.id)) && (total > dest.value)) {
				
				// cout << "entre al if" <<endl;

				dest.value  = total;
				dest.parent = src.id;
				pq.push(dest);

				// cout << "despues del push" << endl;
				// print_queue(pq);
				// cout << "\n";

			}

			// cout << "saliendo de " << dest.id << endl;
			// print_queue(pq);
			// cout << "\n";
			if (dest.next == NULL) {
				break;
			} else {
				dest = *(dest.next);
			}
		}
	}

	cout << "\n" << endl;
	cout << "Ganancia: " << ganancia << endl;
} 

int main(int argc, char const *argv[]) {

	time_t inicio, fin;
	double seconds;

	std::ifstream arch_entrada;
	ofstream arch_salida;

	char str[] = "Debe especificar un archivo de entrada.";
	char data[10];
    char line;
    int nvertices, nlados;

	time(&inicio);      // obtiene el tiempo al iniciar el programa.

	// Verficación de la ejecución del programa.
	if (argc < 2) {
		cerr << "Error : " << str << endl;
		return -1;
	}

	const char* s = new char [strlen(argv[1])+strlen("_salida.txt")+1];
	strcat(const_cast<char*>(s),argv[1]);
    strcat(const_cast<char*>(s),"_salida.txt");
	
	arch_entrada.open(argv[1], ios::in);
	arch_salida.open(s, ios::out);

	// Lectura del Archivo
	string a, b, c, d, e;
	
	cout << "Reading from the file... " << endl;
	
	arch_entrada >> a >> b >> c >> d >> nvertices;
	cout << "\n" << nvertices << " " << "vertices" << endl; 

	// for (int i = 0; i < 5; ++i) {
	// 	arch_entrada >> data;
	// }

	arch_entrada >> a >> b >> c >> d >> nlados;
	cout << "\n" << nlados << " " << "aristas" << endl;

	cout << "\n";

	// Inicialización del Grafo.
	struct Graph * grafo = createGraph(nvertices); 
	
	int nodo1, nodo2, costo, beneficio;
	deque<Arista> aristas;
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

	//printGraph(grafo);

	cout << "Camino:" << endl;

	int ganancia = 0;
	string camino = "";
	hallarCamino(grafo, aristas, camino, ganancia);
	
	//cout << (extraer_arista(aristas,1,2)).costo << endl;
	
	// Se escriben los resultados en el archivo de salida.
	arch_salida << "Ganancia" << " " << ganancia << endl;
	arch_salida << "Camino:" << " " << camino << endl;

	time(&fin);         // obtiene el tiempo al finalizar el programa.
	
	seconds = difftime(fin,inicio);

	arch_salida << "Tiempo:" << " " << seconds << endl;

	// Cierre de archivos.
	arch_entrada.close();
	arch_salida.close();

	cout << "\n" << seconds << " segundos" << endl;

	return 0;
}