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

struct Solucion
{
	int beneficio;
	string camino;
};

bool hay_ciclo (struct Arista lado, struct Solucion solucion){
	for (int i = 0; i < solucion.camino.length(); ++i)
	{
		if (lado.nodo2 == atoi(solucion.camino.substr(i,1).c_str()))
		{
			return true;
		}
	}
	return false;
}

bool beneficio_negativo (struct Arista lado, struct Solucion solucion, deque<Arista>& aristas){
	int count = lado.costo - lado.beneficio;
	for (int i = solucion.camino.length()-1; 0 < i; --i)
	{
		Arista a = extraer_arista(aristas, atoi(solucion.camino.substr(i-1,1).c_str()), atoi(solucion.camino.substr(i,1).c_str()));
		count = count + (a.costo - a.beneficio);
		if (atoi(solucion.camino.substr(i-1,1).c_str()) == lado.nodo2)
		{
			break;
		}
	}
	return count < 0;
}

bool ciclo_negativo (struct Arista lado, struct Solucion solucion, deque<Arista>& aristas){
	if ((hay_ciclo(lado, solucion)) and beneficio_negativo(lado, solucion, aristas))
	{
		return true;
	}
	return false;
}

deque<Arista> obtener_lista_de_sucesores (AdjListNode v, deque<Arista>& aristas){

	deque<Arista> sucesores;
	struct AdjListNode* next = v.next;
	while (next != NULL){
		Arista lado = extraer_arista(aristas, v.id, next->id);
		sucesores.push_front(lado);
		sucesores.push_front(crear_arista(v.id, next->id, lado.costo, 0));
		next = v.next;
	}
	return sucesores;
}

int arista_pertenece (struct Arista lado, struct Solucion solucion){

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

	if (arista_pertenece(lado, solucion) == 0)
	{
		return false;
	}
	else if (arista_pertenece(lado, solucion) == 1){
		if (lado.beneficio == 0)
		{
			return false;
		}else{
			return true;
		}
	}else{
		return true;
	}
}

bool cumpleAcotamiento(struct Arista lado, struct Solucion solucion) {
	
	int beneficioE = lado.beneficio - lado.costo;
	int beneficioSolParcial = solParcial.beneficio + beneficioE;
	int maxBeneficio = beneficioDisponible -  max(0, beneficioE) + beneficioSolParcial;
	
	if (maxBeneficio <= mejorSol.beneficio)	{
		return false;
	}

	return true;
}