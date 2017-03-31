/** Universidad Simón Bolívar
*   CI5437 - Diseño de Algoritmos I
*   Trimestre Ene-Mar 2017
*
*   Proyecto II
*  
* 
*   Hecho por: Enrique Iglesias 11-10477
*              Gabriel Iglesias 11-10476
*
*   Última modificación: 
*/


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

/* Definición de Estructuras */

struct Solucion
{
	int beneficio;
	string camino;
};

/* Variables Globales */

int beneficioDisponible;

struct Solucion solParcial;
struct Solucion mejorSol;

deque<Arista> aristas;
struct Graph* graph;

// Función template para imprimir una cola.
template <typename T> void print_queue(T q) {
    
    while (!q.empty()) {
        cout << q.top().nodo1 << " - " << q.top().nodo2 << " b "; 
        cout << q.top().beneficio << " c " << q.top().costo << endl;
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

// Clase para comparar dos aristas en la cola de prioridades segun el beeficio.
class Mycomparison {

	private:
		bool reverse;

	public:
		Mycomparison(const bool& param=false) {
			reverse = param;
		}

		bool operator() (const struct Arista& arco1, const struct Arista& arco2) const {
			if (reverse)
				return (arco1.beneficio - arco1.costo) > (arco2.beneficio - arco2.costo);
			else
				return (arco1.beneficio - arco1.costo) < (arco2.beneficio - arco2.costo);
		}
};

/* Funciones */

priority_queue<struct Arista, vector<Arista>, Mycomparison> obtener_lista_de_sucesores(char nodo){

	struct AdjListNode* v;

	// Encontramos la lista de adyacencia del nodo de entrada.
	// for (int i = 1; i < graph->V; ++i) {

	// 	if (graph->array[i].nodeid->id == (nodo - '0')) {
	// 		v = graph->array[i].nodeid;
	// 		break;
	// 	}
	// }

	int index = nodo - '0';
	v = graph->array[index].head;

	cout << v->id << endl;
	cout << v->value << endl;
	cout << v->parent << endl;
	//cout << v->id << endl;

	//deque<Arista> sucesores;
	
	struct AdjListNode* next = v->next;

	// if (next == NULL) {
	// 	cout << "bla" << endl;
	// }

	priority_queue<struct Arista, vector<Arista>, Mycomparison> pq;
	
	while (next) {
	
		struct Arista lado = extraer_arista(aristas, v->id, next->id);
		
		pq.push(lado);
		pq.push(crear_arista(v->id, next->id, lado.costo, 0));
		
		//sucesores.push_front(lado);
		//sucesores.push_front(crear_arista(v->id, next->id, lado.costo, 0));
		
		next = next->next;
	}

	//print_queue(pq);

	return pq;
}

bool hay_ciclo(struct Arista lado, struct Solucion solucion){
	
	for (int i = 0; i < solucion.camino.length(); ++i) {

		if (lado.nodo2 == atoi(solucion.camino.substr(i,1).c_str())) {
			return true;
		}
	}

	return false;
}

bool beneficio_negativo(struct Arista lado, struct Solucion solucion) {
	
	int count = lado.costo - lado.beneficio;
	for (int i = solucion.camino.length()-1; 0 < i; --i) {

		struct Arista a = extraer_arista(aristas, atoi(solucion.camino.substr(i-1,1).c_str()), atoi(solucion.camino.substr(i,1).c_str()));
		count = count + (a.costo - a.beneficio);
		
		if (atoi(solucion.camino.substr(i-1,1).c_str()) == lado.nodo2) {
			break;
		}
	}

	return count < 0;
}

bool ciclo_negativo(struct Arista lado, struct Solucion solucion){
	
	if ((hay_ciclo(lado, solucion)) && (beneficio_negativo(lado, solucion))) {
		return true;
	}

	return false;
}

int arista_pertenece(struct Arista lado, struct Solucion solucion){

	int count = 0;

	for (int i = 0; i < solucion.camino.length(); ++i)
	{
		if (((lado.nodo1 == atoi(solucion.camino.substr(i,1).c_str()))) and ((lado.nodo2 == atoi(solucion.camino.substr(i+1,1).c_str()))))
		{
			count++;
		}
	}

	return count;
}

bool esta_lado_en_solparcial(struct Arista lado, struct Solucion solucion){

	if (arista_pertenece(lado, solucion) == 0) {
		return false;
	}

	else if (arista_pertenece(lado, solucion) == 1){
		
		if (lado.beneficio == 0) {
			return false;
		}

		else {
			return true;
		}
	}

	else {		
		return true;
	}
}

bool cumple_acotamiento(struct Arista lado, struct Solucion solucion) {
	
	int beneficioE = lado.beneficio - lado.costo;
	int beneficioSolParcial = solucion.beneficio + beneficioE;
	int maxBeneficio = beneficioDisponible -  max(0, beneficioE) + beneficioSolParcial;
	
	if (maxBeneficio <= mejorSol.beneficio)	{
		return false;
	}

	return true;
}

bool repite_ciclo(priority_queue<struct Arista, std::vector<Arista>, Mycomparison> adyacentes, struct Arista arista, struct Solucion solucion) {

	return false;
}

void agregar_lado(struct Arista arista, struct Solucion& solucion) {

	string str = " - ";
	str.append(to_string(arista.nodo2));
	solucion.camino.append(str);
}

struct Arista eliminar_ultimo_lado() {

	int nodo1, nodo2;
	struct Arista arista;

	cout << solParcial.camino.length() << endl;

	//c = solParcial.camino.back();

	if (solParcial.camino.length() >= 5) {

		nodo2 = solParcial.camino.at(solParcial.camino.length()-1);

		cout << "nodo2 " << nodo2 << endl;

		nodo1 = solParcial.camino.at(solParcial.camino.length()-5);
		solParcial.camino.erase(solParcial.camino.length()-6, 5);
		arista = extraer_arista(aristas, nodo1, nodo2);
	}

	return arista;
}

int obtener_maximo_beneficio(deque<Arista> lados) {

	int beneficio = 0;
	deque<Arista>::iterator it = lados.begin();

	while (it != lados.end()) {

		struct Arista arco = *it;

		if (arco.beneficio > arco.costo) {
			beneficio = beneficio + arco.beneficio - arco.costo;
		}

		++it;
	}

	return beneficio;
}