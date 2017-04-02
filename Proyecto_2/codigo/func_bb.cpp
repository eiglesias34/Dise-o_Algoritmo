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
*   Última modificación: 01/04/17
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

void eliminar_arista (Arista a){
	
	for (int i = 0; i < edges.size(); ++i)
	{
		if (((a.nodo1 == edges[i].nodo1) and (a.nodo2 == edges[i].nodo2)) or ((a.nodo1 == edges[i].nodo2) and (a.nodo2 == edges[i].nodo1)))
		{
			edges.erase(edges.begin()+i);
		}
	}
}

priority_queue<struct Arista, vector<Arista>, Mycomparison> obtener_lista_de_sucesores(string nodo){


	struct AdjListNode* v;

	int index = stoi(nodo);
	v = graph->array[index].nodeid;
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
	
	int nodo_dest;

	if (v->id == lado.nodo1) {
		
		nodo_dest = lado.nodo2;
	}

	else {
		
		nodo_dest = lado.nodo1;
	}

	int b = lado.beneficio - lado.costo;
	deque<Arista> aux = edges;

	cout << "beneficio negativo nodo " << nodo << endl;

	while (!aux.empty()) {

		cout << "Aux size: " << aux.size() << endl;

		cout << "b antes " << b << endl;

		b = b + (aux.front().beneficio - aux.front().costo);

		cout << "b despues " << b << endl;  

		if ( (aux.front().nodo1 == nodo_dest) || (aux.front().nodo2 == nodo_dest) ) {
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
	int maxBeneficio = (beneficioDisponible -  max(0, beneficioE)) + beneficioSolParcial;
	
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

	int len;
	string nodo1, nodo2;
	struct Arista arista;

	cout << "Sol. antes de borrar: " <<solParcial.camino << endl;

	nodo2 = obtener_ultimo_nodo(solParcial.camino);
	len = nodo2.length()+3;

	int a = solParcial.camino.length() - len;
	//cout << a << endl;
		
	if (a >= 0) {
		solParcial.camino.erase( solParcial.camino.length()-len, len );
	}

	else {
		solParcial.camino.erase( 0, len-3 );	
	}

	//cout << "length " << solParcial.camino.length() << endl;
	cout << "Sol. despues de borrar: " << solParcial.camino << "\n" << endl;

	if (solParcial.camino.length() > 0) {
		nodo1 = obtener_ultimo_nodo(solParcial.camino);

		//arista = extraer_arista(aristas, stoi(nodo1), stoi(nodo2));
		
		cout << "nodo1: " << nodo1 << "\n" << "nodo2: " << nodo2 << endl;
		cout << endl;
		cout << "solParcial " << solParcial.camino << "\n" << endl;

		arista = edges.front();
		edges.pop_front();
		solParcial.beneficio = solParcial.beneficio - (arista.beneficio - arista.costo);

		//eliminar_arista(arista);
		return arista;
	}

	return crear_arista(-1, -1, -1, -1);
	//len = nodo1.length()+3;

	//cout << "length " << solParcial.camino.length() << endl;
	//cout << "length " << solParcial.camino.length() - len << endl;

	// if ( (solParcial.camino.length() - len) >= 0 ) {

	// 	cout << "\nif" << endl;
	// 	solParcial.camino.erase( solParcial.camino.length()-len, len );
	// }

	// else {

	// 	cout << "\nelse" << endl;
	// 	solParcial.camino.erase( 0, len-3 );
	// }
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