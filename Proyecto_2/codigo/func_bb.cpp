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


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

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

deque<Arista> obtener_lista_de_sucesores (Vertice v, deque<Arista>& aristas){

	deque<Arista> sucesores;
	struct AdjListNode* next = v.next;
	while (next != NULL){
		Arista lado = extraer_arista(aristas, v.id, next.id);
		sucesores.push_front(lado);
		sucesores.push_front(crear_arista(v.id, next.id, lado.costo, 0));
		next = v.next;
	}
	return sucesores
}

int arista_pertenece (struct Arista lado, struct Solucion solucion){

	int count = 0;

	for (int i = 0; i < strlen(solucion); ++i)
	{
		if (((lado.nodo1 == atoi(solucion[i].c_str()))) and ((lado.nodo2 == atoi(solucion[i+1].c_str()))))
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
	elif (arista_pertenece(lado, solucion) == 1){
		if (lado.beneficio == 0)
		{
			return false;
		}else{
			return true;
		}
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