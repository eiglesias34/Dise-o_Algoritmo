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

deque<Arista> aristas, edges;
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

void eliminar_arista (Arista a, deque<Arista> lados){
	
	struct Arista arco = lados.front();
	lados.pop_front();
	deque<Arista> lados2;
	
	while(!lados.empty()){
	
		if ((arco.nodo1 != a.nodo1) and (arco.nodo2 != a.nodo2)) 
		{
			lados2.push_front(arco);
		}
	
		else if ((arco.nodo1 == a.nodo1) and (arco.nodo1 == a.nodo1) and ((a.nodo2 == 1) or (a.nodo1 == 1)))
		{
			lados2.push_front(arco);
		}
	
		arco = lados.front();
	    lados.pop_front();
	}
	
	lados = lados2;
}

priority_queue<struct Arista, vector<Arista>, Mycomparison> obtener_lista_de_sucesores(string nodo){


	struct AdjListNode* v;

	// Encontramos la lista de adyacencia del nodo de entrada.
	// for (int i = 1; i < graph->V; ++i) {

	// 	if (graph->array[i].nodeid->id == (nodo - '0')) {
	// 		v = graph->array[i].nodeid;
	// 		break;
	// 	}
	// }

	int index = stoi(nodo);
	v = graph->array[index].nodeid;

	//cout << v->id << endl;

	//deque<Arista> sucesores;
	

	priority_queue<struct Arista, vector<Arista>, Mycomparison> pq;
	
	for (int i = 0; i < aristas.size(); ++i)
	{
		if ((aristas[i].nodo1 == v->id) or (aristas[i].nodo2 == v->id))
		{
			pq.push(aristas[i]);
			pq.push(crear_arista(aristas[i].nodo1, aristas[i].nodo2, aristas[i].costo, 0));
		}
	}

	return pq;
}

string obtener_primer_nodo(string camino) {
	
	string aux = camino;

	char c = camino.front();
	int i = (int) c;

	int k = 0;
	while ((i > 46) && (i < 58)) {

		aux.erase(0,1);
		i = aux.front();
		++k;
	}

	string out = camino.substr( 0, k );
	return out;	
}

bool hay_ciclo(string nodo, struct Arista lado, struct Solucion solucion) {

	int len;
	string aux, node;

	aux = solucion.camino;

	node = obtener_primer_nodo(aux);
	len = node.length()+3;
	aux.erase( 0, len );

	// nodo2 = obtener_primer_nodo(solucion.camino);
	// len = nodo2.length()+3;
	// soucion.camino.erase( 0, len );
	
	struct AdjListNode* v;
	int index = stoi(nodo);
	
	v = graph->array[index].nodeid;
	
	int salida;
	if (v->id == lado.nodo1) {
		
		salida = lado.nodo2;
	}

	else {
		
		salida = lado.nodo1;
	}

	// Chequea del primer al ultimo nodo en el camino si la arista a introducir forma un ciclo
	while (aux.length() > 0) {

		if (salida == stoi(node)) {
			return true;
		}

		node = obtener_primer_nodo(aux);
		len = node.length()+3;
		aux.erase( 0, len );
	}
	
	return false;
}

bool beneficio_negativo(string nodo, struct Arista lado, struct Solucion solucion) {
	
	struct AdjListNode* v;
	int index = stoi(nodo);
	
	v = graph->array[index].nodeid;
	
	int salida;
	if (v->id == lado.nodo1) {
		
		salida = lado.nodo2;
	}

	else {
		
		salida = lado.nodo1;
	}

	int b = lado.beneficio - lado.costo;
	deque<Arista> aux = edges;

	while (!aux.empty()) {

		b = b + aux.front().costo;  

		if ( (aux.front().nodo1 == salida) || (aux.front().nodo2 == salida) ) {
			return (b <= 0);
		}

		aux.pop_front();
	}

	// No hay ciclo.
	return false;
}

bool ciclo_negativo(string nodo, struct Arista lado, struct Solucion solucion){
	
	if ((hay_ciclo(nodo, lado, solucion)) && (beneficio_negativo(nodo,lado, solucion))) {
		return true;
	}

	return false;
}

bool arista_pertenece(string nodo, struct Arista lado, struct Solucion solucion) {

	struct Arista a = extraer_arista(edges, lado.nodo1, lado.nodo2);

	if (a.nodo1 == -1) {
		return false;
	}

	else {
		return true;
	}

	// int i = 0;
	// int count = 0;
	
	// struct AdjListNode* v;
	
	// int index = nodo - '0';
	// v = graph->array[index].nodeid;
	
	// int salida;
	// if (v->id == lado.nodo1) {
	// 	salida = lado.nodo2;
	// }

	// else {
	// 	salida = lado.nodo1;
	// }

	// while ((i + 4) < solucion.camino.length()) {
		
	// 	if (( v->id  == atoi(solucion.camino.substr(i,1).c_str()) ) 

	// 		&& (( salida == atoi(solucion.camino.substr(i+4,1).c_str()) ))
	// 	{
	// 		count++;
	// 	}

	// 	i = i + 4;
	// }

	// return count;
}

bool esta_lado_en_solparcial(string nodo, struct Arista lado, struct Solucion solucion){

	if (arista_pertenece(nodo, lado, solucion) == false) {
		return false;
	}

	else if (arista_pertenece(nodo, lado, solucion) == true){
		
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

bool repite_ciclo(string nodo, priority_queue<struct Arista, std::vector<Arista>, Mycomparison> adyacentes, struct Arista arista, struct Solucion solucion) {

	return hay_ciclo(nodo, arista, solucion);
}

void agregar_lado(string nodo, struct Arista arista, struct Solucion& solucion) {

	edges.push_front(arista);

	struct AdjListNode* v;
	int index = stoi(nodo);
	v = graph->array[index].nodeid;
	string str = " - ";
	
	if (v->id == arista.nodo1)
	{
		str.append(to_string(arista.nodo2));
	}

	else{
		str.append(to_string(arista.nodo1));
	}
	
	solucion.camino.append(str);
	solucion.beneficio = solucion.beneficio + (arista.beneficio - arista.costo);
	eliminar_arista(arista, aristas);
}

string obtener_ultimo_nodo(string camino) {
	
	string aux = camino;

	char c = camino.back();
	int i = (int) c;

	int k = 0;
	while ((i > 46) && (i < 58)) {

		aux.pop_back();
		i = aux.back();
		++k;
	}

	string out = camino.substr( camino.length()-k, k );
	return out;
}

struct Arista eliminar_ultimo_lado() {

	string nodo1, nodo2;
	struct Arista arista;

	cout << solParcial.camino << endl;

	//c = solParcial.camino.back();

	if (solParcial.camino.length() > 1) {

		int len;

		nodo2 = obtener_ultimo_nodo(solParcial.camino);
		len = nodo2.length()+3;
		cout << len << endl;
		solParcial.camino.erase( solParcial.camino.length()-len, len );

		cout << solParcial.camino << endl;

		nodo1 = obtener_ultimo_nodo(solParcial.camino);
		len = nodo1.length()+3;
		cout << len << endl;

		if (solParcial.camino.length()-len > -1) {
			solParcial.camino.erase( solParcial.camino.length()-len, len );
		}

		else {
			solParcial.camino.erase( 0, len );
		}

		//nodo2 = solParcial.camino.at(solParcial.camino.length()-1);
		//nodo1 = solParcial.camino.at(solParcial.camino.length()-5);
		//solParcial.camino.erase(solParcial.camino.length()-6, 5);

		cout << endl;
		cout << "nodo1: " << nodo1 << "nodo2: " << nodo2 << endl;
		cout << endl;
		
		arista = extraer_arista(aristas, stoi(nodo1), stoi(nodo2));

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