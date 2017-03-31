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
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "func_bb.cpp"

using namespace std;

// Función template para imprimir una cola.
template <typename T> void print_queue_greedy(T q) {
    
    while (!q.empty()) {
        cout << q.top().id << " " << q.top().value << " ";
        q.pop();
    }

    cout << '\n';
}

// Función template para buscar un elemento.
template <typename T> bool find_and_remove_greedy(T& q, int nodo) {

	int i = 0;
	T aux1;
	T aux2 = q;

	while (!aux2.empty()) {
		if (nodo == aux2.top().id) {
			++i;
		} else {
			aux1.push(aux2.top());
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
class Mycomparison_greedy {

	private:
		bool reverse;

	public:
		Mycomparison_greedy(const bool& param=false) {
			reverse = param;
		}

		bool operator() (const struct AdjListNode& node1, const struct AdjListNode& node2) const {
			if (reverse)
				return node1.value > node2.value;
			else
				return node1.value < node2.value;
		}
};


struct Solucion hallarCamino_greedy(struct Graph* graph, deque<Arista> aristas, string& camino, int& ganancia) {

	int last;
	struct AdjListNode *start;
	struct AdjListNode aux, src, dest2;
	start = graph->array[1].nodeid; 
	start->value = 0;                       // Inicializamos el valor del nodo 
	                                        // depósito a cero.

	priority_queue<struct AdjListNode, std::vector<AdjListNode>, Mycomparison_greedy> pq;  // Cola de prioridades.
	

	// Inicializamos la Cola de prioridades.
	for (int i = 1; i < graph->V; ++i) {
		aux = *(graph->array[i].nodeid);
		pq.push(aux);
	}

	int beneficio, costo, total;
	struct Arista arco;

	int i = 0;
	ganancia = 0;

	//cout << "1";
	camino.append("1");

	while (!pq.empty()) {
		
		++i;
		src = pq.top();
		pq.pop();
		
		// Imprime el camino recorrido.
		if (src.parent != 0) {
			last = src.id;
			ganancia = ganancia + src.value;
			//cout << " - " <</*src.parent << " - " <<*/ src.id;
			camino.append(" - ");
			camino.append(to_string(src.id));
		}

		// Calcula el beneficio que se obtiene al ir a cada nodo adyacente 
		// del recien sacado de la cola
		dest2 = *(graph->array[src.id].head);
		struct AdjListNode& dest = *(graph->array[dest2.id].nodeid);

		// Itera sobre los adyacentes del nodo sacado de la cola
		while (true) {

			arco = extraer_arista(aristas, src.id, graph->array[dest2.id].nodeid->id);
			costo = arco.costo;
			beneficio = arco.beneficio;
			total = beneficio - costo;

			aristas.push_front(crear_arista(arco.nodo2, arco.nodo1, costo, beneficio));

			if ((total > graph->array[dest2.id].nodeid->value) && (find_and_remove_greedy(pq, graph->array[dest2.id].nodeid->id))) {

				graph->array[dest2.id].nodeid->value  = total;
				graph->array[dest2.id].nodeid->parent = src.id;
				pq.push(*graph->array[dest2.id].nodeid);

				modificar_arista(aristas, src.id, graph->array[dest2.id].nodeid->id);
			}
			
			if (dest2.next == NULL) {
				break;
			} else {
				dest2 = *(dest2.next);
			}
		}
	}
	// Reinicializa todos los nodos del grafo
	for (int i = 1; i < graph->V; ++i) {
		//cout << "Nodo " << graph->array[i].nodeid->id << endl;
		graph->array[i].nodeid->value  = -999999;
		graph->array[i].nodeid->parent = 0;
	}

	int nodo1, nodo2;
	struct AdjListNode ult;
	deque<Arista>::iterator it = aristas.begin();

	graph->array[last].nodeid->value = 0;
	ult = *(graph->array[last].nodeid);

	// Relajación progresiva de todos los arcos.
	for (int i = 2; i < graph->V ; ++i) {

    	while (it != aristas.end()) {

    		arco = *it++;
    		total = arco.beneficio - arco.costo;

			if (graph->array[arco.nodo2].nodeid->value < (graph->array[arco.nodo1].nodeid->value + total)) {

    			graph->array[arco.nodo2].nodeid->value  = graph->array[arco.nodo1].nodeid->value + total;
    			graph->array[arco.nodo2].nodeid->parent = arco.nodo1;
    		}
    	}
    }

    // Se halla el camino de vuelta.
    deque<int> vuelta;     // variable que guarda el camino de vuelta 
                           // al nodo deposito
    
    aux = *(graph->array[1].nodeid);
    ganancia = ganancia + aux.value;

    // Agrega a la estructura vuelta los nodos pertenecientes al camino de vuelta.
    while (aux.id != ult.id) {
    	vuelta.push_front(aux.id);
    	aux = *(graph->array[graph->array[aux.id].nodeid->parent].nodeid);
    }

    while (!vuelta.empty()) {
    	camino.append(" - ");
		camino.append(to_string(vuelta.front()));
    	//cout << " - " << vuelta.front();
    	vuelta.pop_front();
    }

	//cout << "\n" << endl;
	//cout << "Ganancia: " << ganancia << endl;

	struct Solucion solucion;
	solucion.beneficio = ganancia;
	solucion.camino = camino;

	return solucion;
} 